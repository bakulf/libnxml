#include "nxml.h"
#include <stdarg.h>

void
print_data (nxml_data_t * root, int id)
{
  int i;
  nxml_attr_t *attr;

  for (i = 0; i < id; i++)
    printf ("  ");
  printf ("%s ", root->value);

  if (root->ns)
    {
      if (root->ns->prefix)
	printf ("Prefix: -%s- NS: -%s-", root->ns->prefix, root->ns->ns);
      else
	printf ("No Prefix NS: -%s-", root->ns->ns);
    }

  printf ("\n");

  attr = root->attributes;
  while (attr)
    {

      for (i = 0; i < id; i++)
	printf ("  ");

      printf (" - Attr: -%s- -%s-\n", attr->name, attr->value);

      for (i = 0; i < id; i++)
	printf ("  ");

      if (attr->ns)
	{
	  if (attr->ns->prefix)
	    printf (" - Prefix -%s- NS: -%s-", attr->ns->prefix,
		    attr->ns->ns);
	  else
	    printf (" - No Prefix NS: -%s-", attr->ns->ns);

	  printf ("\n");
	}

      attr = attr->next;
    }

  root = root->children;
  id++;

  while (root)
    {
      if (root->type == NXML_TYPE_ELEMENT)
	print_data (root, id);
      root = root->next;
    }
}

int
main (int argc, char **argv)
{
  nxml_t *data;
  nxml_data_t *root;
  nxml_error_t ret;

  if (argc != 2)
    {
      fprintf (stderr,
	       "Usage:\n\t%s url_xml\n\nExample:\n\t%s [file.xml|http://server/file.xml]\n\n",
	       argv[0], argv[0]);
      return 1;
    }

  printf ("Creating a new data struct...\n");
  if ((ret = nxml_new (&data)) != NXML_OK)
    {
      puts (nxml_strerror (NULL, ret));
      return 1;
    }

  printf ("Setting error function...\n");
  if ((ret = nxml_set_func (data, nxml_print_generic)) != NXML_OK)
    {
      puts (nxml_strerror (data, ret));
      return 1;
    }

  printf ("Parsing the document...\n");
  if (!strncmp (argv[1], "http://", 7))
    ret = nxml_parse_url (data, argv[1]);
  else
    ret = nxml_parse_file (data, argv[1]);

  if (ret != NXML_OK)
    {
      puts (nxml_strerror (data, ret));
      return 1;
    }

  printf ("Namespaces...\n");
  root = data->data;
  while (root)
    {
      if (root->type == NXML_TYPE_ELEMENT)
	print_data (root, 1);
      root = root->next;
    }

  printf ("Freeing memory...\n");
  nxml_free (data);

  puts ("Bye!");
  return 0;
}
