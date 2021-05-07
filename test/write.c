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

#include "nxml.h"

int main(int argc, char **argv) {
  nxml_t *data;
  nxml_error_t ret;

  if (argc != 3) {
    fprintf(stderr,
            "Usage:\n\t%s url_xml|file output\n\nExample:\n\t%s "
            "http://ngvision.org/xml file.xml\n\n",
            argv[0], argv[0]);
    return 1;
  }

  nxml_new(&data);
  nxml_set_func(data, nxml_print_generic);

  if (!strncmp(argv[1], "http://", 7) || !strncmp(argv[1], "ftp://", 6))
    ret = nxml_parse_url(data, argv[1]);
  else
    ret = nxml_parse_file(data, argv[1]);

  if (ret) {
    fprintf(stderr, "NXML return error (parsing): %s\n",
            nxml_strerror(data, ret));
    nxml_free(data);
    return 1;
  }

  ret = nxml_write_file(data, argv[2]);

  if (ret) {
    fprintf(stderr, "NXML return error (writing): %s\n",
            nxml_strerror(data, ret));
    nxml_free(data);
    return 1;
  }

  nxml_free(data);

  return 0;
}
