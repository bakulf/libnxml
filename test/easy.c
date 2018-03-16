#include "nxml.h"

void
check (nxml_t * data, nxml_error_t err)
{
  puts (nxmle_strerror (data, err));

  if (err != NXML_OK)
    exit (1);
}

int
main (int argc, char **argv)
{
  nxml_t *data;
  nxml_data_t *element, *text;
  nxml_attr_t *attribute;
  nxml_error_t err;
  char *buffer;

  fprintf (stdout, "New data... ");
  data = nxmle_new_data (&err);
  check (data, err);

  fprintf (stdout, "Freeing memory... ");
  err = nxmle_free (data);
  check (data, err);

  fprintf (stdout, "New data from url... ");
  data =
    nxmle_new_data_from_url ("http://www.autistici.org/bakunin/index.php",
			     &err);
  check (data, err);

  buffer = NULL;
  fprintf (stdout, "Writing in a buffer... ");

  buffer = nxmle_write_buffer (data, &err);
  check (data, err);

  fprintf (stdout, "Freeing memory... ");
  err = nxmle_free (data);
  check (data, err);

  fprintf (stdout, "New data from buffer... ");
  data = nxmle_new_data_from_buffer (buffer, 0, &err);
  check (data, err);

  free (buffer);

  fprintf (stdout, "Writing to file... ");
  err = nxmle_write_file (data, "TEST");
  check (data, err);

  fprintf (stdout, "Freeing memory... ");
  err = nxmle_free (data);
  check (data, err);

  fprintf (stdout, "New data from file... ");
  data = nxmle_new_data_from_file ("TEST", &err);
  check (data, err);

  unlink ("TEST");

  fprintf (stdout, "New nxml_data_t element... ");
  element = nxmle_add_new (data, NULL, &err);
  check (data, err);

  fprintf (stdout, "Removing nxml_data_t element... ");
  err = nxmle_remove (data, NULL, element);
  check (data, err);

  fprintf (stdout, "Re-insert nxml_data_t element... ");
  element = nxmle_add_data (data, NULL, element, &err);
  check (data, err);

  element->value = strdup ("hello_world");
  element->type = NXML_TYPE_ELEMENT;

  fprintf (stdout, "Adding attribute to element... ");
  attribute = nxmle_add_attribute_new (data, element, &err);
  check (data, err);

  attribute->name = strdup ("hello");
  attribute->value = strdup ("world");

  fprintf (stdout, "Removing attribute to element... ");
  err = nxmle_remove_attribute (data, element, attribute);
  check (data, err);

  fprintf (stdout, "Re-insert a attribute to element... ");
  attribute = nxmle_add_attribute_data (data, element, attribute, &err);
  check (data, err);

  fprintf (stdout, "Searching the root element... ");
  element = nxmle_root_element (data, &err);
  check (data, err);

  printf ("ROOT element: %s\n", element->value);

  fprintf (stdout, "Removing the root element element... ");
  err = nxmle_remove (data, NULL, element);
  nxml_free_data (element);
  check (data, err);

  fprintf (stdout, "Searching the 'hello_world' element... ");
  element = nxmle_find_element (data, NULL, "hello_world", &err);
  check (data, err);

  printf ("Founded element: %s\n", element->value);

  fprintf (stdout, "Searching attribute 'hello' in the root element... ");
  buffer = nxmle_find_attribute (element, "hello", &err);
  check (data, err);

  printf ("Value: %s\n", buffer);
  free (buffer);

  fprintf (stdout, "New nxml_data_t element... ");
  text = nxmle_add_new (data, element, &err);
  check (data, err);

  text->value = strdup ("bla bla bla...");
  text->type = NXML_TYPE_TEXT;

  fprintf (stdout, "Getting string in the root element... ");
  buffer = nxmle_get_string (element, &err);
  check (data, err);

  printf ("Value: %s\n", buffer);
  free (buffer);

  nxml_free (data);
  return 0;
}
