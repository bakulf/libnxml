#include "nxml.h"
#include <stdarg.h>

void
my_printf (char *str, ...)
{
  va_list va;

  va_start (va, str);
  vfprintf (stderr, str, va);
  va_end (va);
}

int
main (int argc, char **argv)
{
  nxml_t *data;
  nxml_error_t ret;
  nxml_data_t *element, *tmp;
  nxml_doctype_t *doctype;

  if (argc != 2)
    {
      fprintf (stderr,
	       "Usage:\n\t%s url_xml\n\nExample:\n\t%s [file.xml|http://server/file.xml]\n\n",
	       argv[0], argv[0]);
      return 1;
    }

  ret = nxml_new (&data);

  if (ret != NXML_OK)
    {
      puts (nxml_strerror (data, ret));
      return 1;
    }

  ret = nxml_set_func (data, my_printf);

  if (ret != NXML_OK)
    {
      puts (nxml_strerror (data, ret));
      return 1;
    }

  if (!strncmp (argv[1], "http://", 7) || !strncmp (argv[1], "https://", 8))
    ret = nxml_parse_url (data, argv[1]);
  else
    ret = nxml_parse_file (data, argv[1]);

  if (ret != NXML_OK)
    {
      puts (nxml_strerror (data, ret));
      return 1;
    }

  nxml_root_element (data, &element);
  printf ("Root element: %p: -%s-\n", (void *) element,
	  element ? element->value : "");

  if (element)
    {
      tmp = element->children;
      while (tmp)
	{
	  printf ("  subelement: %p: -%s-\n", (void *) tmp,
		  tmp ? tmp->value : "");
	  tmp = tmp->next;
	}
    }

  nxml_find_element (data, element, "body", &element);
  if (element && nxml_find_element (data, element, "div", &element) == NXML_OK
      && element)
    {
      printf ("\ndiv element: -%p-\n", (void *) element);
    }

  nxml_doctype_element (data, &doctype);

  if (doctype)
    printf ("\nDoctype: -%s-%s-\n", doctype->name, doctype->value);

  nxml_free (data);

  return 0;
}
