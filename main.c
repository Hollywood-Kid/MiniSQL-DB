#include "json_reader.h"
#include "hashtab.h"

int main() {
  char *data = load_JSON_file("shema.json");
  
  HashTab *hashtab = new_hashtab(10000, STRING_ELEM, DECIMAL_ELEM);

  set_hashtab(hashtab, string("A"), decimal(555));
  set_hashtab(hashtab, string("B"), decimal(333));
  set_hashtab(hashtab, string("C"), decimal(111));
  set_hashtab(hashtab, string("D"), decimal(777));

  print_hashtab(hashtab);
  free_hashtab(hashtab);
  return 0;
}