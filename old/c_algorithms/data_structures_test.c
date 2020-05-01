#include <stdio.h>
#include <stdlib.h>
#include "linked_list.c"


void test_remove_duplicates()
{
      list *l = malloc(sizeof(list));
      l->next = NULL;

      insert_list(&l, 1);
      insert_list(&l, 1);
      insert_list(&l, 1);
      insert_list(&l, 1);
      insert_list(&l, 1);
      insert_list(&l, 1);
      insert_list(&l, 1);
      insert_list(&l, 1);
      insert_list(&l, 2);
      insert_list(&l, 2);
      insert_list(&l, 3);
      insert_list(&l, 3);
      insert_list(&l, 3);
      insert_list(&l, 3);
      insert_list(&l, 4);


      remove_duplicates(&l);
      print_list(l);
}

void test_reverse()
{
      list *l = NULL;

      insert_list(&l, 1); insert_list(&l, 2); insert_list(&l, 3);
      insert_list(&l, 4); insert_list(&l, 5); insert_list(&l, 6);
      insert_list(&l, 7); insert_list(&l, 8); insert_list(&l, 9);
      insert_list(&l, 10); insert_list(&l, 11);

      print_list(l);
      reverse_list(&l);
      print_list(l);
}

void test_k_last()
{
      list *l = NULL;

      insert_list(&l, 11); insert_list(&l, 22); insert_list(&l, 33);
      insert_list(&l, 44); insert_list(&l, 55); insert_list(&l, 66);
      insert_list(&l, 77); insert_list(&l, 88); insert_list(&l, 99);

      print_list(l);
      k_last_elements(l, 3);
}

void test_remove_middle()
{
      list *l = NULL;

      insert_list(&l, 11); insert_list(&l, 22); insert_list(&l, 33);
      insert_list(&l, 44); insert_list(&l, 55); insert_list(&l, 66);
      insert_list(&l, 77);

      remove_middle(&l);
      print_list(l);
}

void test_partition()
{
      list *l = NULL;

      insert_list(&l, 11); insert_list(&l, 50); insert_list(&l, 70);
      insert_list(&l, 21); insert_list(&l, 100); insert_list(&l, 20);
      insert_list(&l, 22);

      partition_list(&l, 50);
      print_list(l);
}


int main(int argc, char const *argv[])
{

      //test_remove_duplicates();
      //test_reverse();
      //test_k_last();
      //test_remove_middle();
      test_partition();

      return 0;
}
