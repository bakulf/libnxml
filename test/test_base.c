/* nXml - Copyright (C) 2005-2007 baku - Andrea Marchesini
 *                                     <baku@ippolita.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <err.h>
#include <unistd.h>

#include "nxml.h"

typedef struct test_case_t {
  const char *label;
  nxml_t *nxml;
  const char *content;
  size_t content_len;
  enum {
    as_buffer,
    as_file,
  } parse_as;
  nxml_error_t expected_result;
} test_case_t;

static void buffer_to_file(char *path_template, const test_case_t *tc) {
  int fd;
  const char *bytes;
  size_t len;

  fd = mkstemp(path_template);
  if (fd == -1)
    err(1, "mkstemp failed");

  bytes = tc->content;
  len = tc->content_len;

  while (len > 0) {
    ssize_t n;

    n = write(fd, bytes, len);
    switch (n) {
    case 0:
      close(fd);
      errx(1, "write on %d returned zero?", fd);

    case -1:
      close(fd);
      errx(1, "write on %d failed", fd);

    default:
      bytes += n;
      len -= n;
    }
  }

  close(fd);
}

static void run_test(const test_case_t *tc) {
  nxml_error_t e = NXML_OK;
  char temp_path[] = "libnxml_test_XXXXXX";

  switch (tc->parse_as) {
  case as_buffer:
    e = nxml_parse_buffer(tc->nxml, (char *)tc->content, tc->content_len);
    break;
  case as_file:
    buffer_to_file(temp_path, tc);
    e = nxml_parse_file(tc->nxml, temp_path);
    unlink(temp_path);
    break;
  }

  if (e != tc->expected_result)
    errx(1, "not ok - %s, expected %s, got %s", tc->label,
         nxml_strerror(tc->nxml, tc->expected_result),
         nxml_strerror(tc->nxml, e));
}

#define test(_nxml, _test_case, _expected_result)                              \
  do {                                                                         \
    test_case_t tc = {.label = #_test_case,                                    \
                      .nxml = _nxml,                                           \
                      .content = _test_case,                                   \
                      .content_len = sizeof(_test_case) - 1,                   \
                      .expected_result = _expected_result};                    \
    tc.parse_as = as_buffer;                                                   \
    run_test(&tc);                                                             \
                                                                               \
    tc.parse_as = as_file;                                                     \
    run_test(&tc);                                                             \
  } while (0)

#define good_xml                                                               \
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"                                 \
  "<rss version=\"2.0\">"                                                      \
  "<channel>"                                                                  \
  "  <title>feed title</title>"                                                \
  "  <description>channel description</description>"                           \
  "  <item>"                                                                   \
  "    <title>title 0</title>"                                                 \
  "    <link>http://example.com</link>"                                        \
  "    <description>hello</description>"                                       \
  "  </item>"                                                                  \
  "  <item>"                                                                   \
  "    <title>title 1</title>"                                                 \
  "    <link>http://example.com</link>"                                        \
  "    <description>world</description>"                                       \
  "  </item>"                                                                  \
  "</channel>"                                                                 \
  "</rss>"

#define weird_version "<?xml version=\"999.0\" encoding=\"UTF-8\"?>"

#define xml_broken_afl_0                                                       \
  "<?xml version='1.0\" encoding=\"UTF-8\" ?>"                                 \
  "<rss version=\"2.0\">"                                                      \
  "<channel>"                                                                  \
  "  <title>feed e</title>"                                                    \
  "  <description>cha des</description>"                                       \
  "  <item>"                                                                   \
  "<title>t 0</title>"                                                         \
  "    <link>httcom</link>"                                                    \
  "    <description>hello</description>"                                       \
  "  </item>"                                                                  \
  "  <item>"                                                                   \
  "    <title>title 1</title>"                                                 \
  "    <link>om</link>"                                                        \
  "    <description>world</description>"                                       \
  "  </item>"                                                                  \
  "</channel>"                                                                 \
  "</rss>"

#define xml_broken_afl_1 "<?xml ven=\"1.0\""

int main(int argc, char **argv) {
  nxml_t *nxml;

  if (nxml_new(&nxml) != NXML_OK)
    err(1, "nxml_new failed");

  nxml_set_func(nxml, nxml_print_generic);

  test(nxml, good_xml, NXML_OK);
  test(nxml, weird_version, NXML_ERR_PARSER);

  /* Test cases reported by running the American Fuzzy Lop */
  test(nxml, xml_broken_afl_0, NXML_ERR_PARSER);
  test(nxml, xml_broken_afl_1, NXML_ERR_PARSER);

  nxml_free(nxml);
  return 0;
}
