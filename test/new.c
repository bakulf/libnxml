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

void
check (nxml_t * data, nxml_error_t ret)
{
  puts (nxml_strerror (data, ret));
  if (ret != NXML_OK)
    exit (1);
}

int
main (int argc, char **argv)
{
  nxml_t *data;
  nxml_data_t *item, *root;
  nxml_error_t ret;
  char *buffer;
  char s[1024];
  int i;

  data = NULL;
  fprintf (stdout, "New data... ");
  ret = nxml_new (&data);
  check (NULL, ret);

  root = NULL;
  fprintf (stdout, "Creating a new entity... ");
  ret = nxml_add (data, NULL, &root);
  check (data, ret);

  root->value = strdup ("root_element");
  root->type = NXML_TYPE_ELEMENT;

  for (i = 0; i < 10; i++)
    {
      item = NULL;
      fprintf (stdout, "Creating a new entity... ");
      ret = nxml_add (data, root, &item);
      check (data, ret);

      snprintf (s, sizeof (s), "item%d", i);
      item->value = strdup (s);

      switch (i % 5)
	{
	case 0:
	  item->type = NXML_TYPE_TEXT;
	  break;

	case 1:
	  item->type = NXML_TYPE_COMMENT;
	  break;

	case 2:
	  {
	    int j;
	    nxml_attr_t *attr;

	    item->type = NXML_TYPE_ELEMENT;

	    for (j = 0; j < 10; j++)
	      {
		attr = NULL;
		fprintf (stdout, "Creating a attribute... ");
		ret = nxml_add_attribute (data, item, &attr);
		check (data, ret);

		snprintf (s, sizeof (s), "attr%d", j);
		attr->name = strdup (s);
		attr->value = strdup ("Hello World");
	      }
	  }
	  break;

	case 3:
	  item->type = NXML_TYPE_PI;
	  break;
	}
    }

  buffer = NULL;
  ret = nxml_write_buffer (data, &buffer);
  check (data, ret);

  puts (buffer);
  free (buffer);
  nxml_free (data);

  return 0;
}
