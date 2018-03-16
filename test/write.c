#include "nxml.h"

int
main (int argc, char **argv)
{
  nxml_t *data;
  nxml_error_t ret;

  if (argc != 3)
    {
      fprintf (stderr,
	       "Usage:\n\t%s url_xml|file output\n\nExample:\n\t%s http://ngvision.org/xml file.xml\n\n",
	       argv[0], argv[0]);
      return 1;
    }

  nxml_new (&data);
  nxml_set_func (data, nxml_print_generic);

  if (!strncmp (argv[1], "http://", 7) || !strncmp (argv[1], "ftp://", 6))
    ret = nxml_parse_url (data, argv[1]);
  else
    ret = nxml_parse_file (data, argv[1]);

  if (ret)
    {
      fprintf (stderr, "NXML return error (parsing): %s\n",
	       nxml_strerror (data, ret));
      nxml_free (data);
      return 1;
    }

  ret = nxml_write_file (data, argv[2]);

  if (ret)
    {
      fprintf (stderr, "NXML return error (writing): %s\n",
	       nxml_strerror (data, ret));
      nxml_free (data);
      return 1;
    }

  nxml_free (data);

  return 0;
}
