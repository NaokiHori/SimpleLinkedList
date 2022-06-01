#include <CUnit/CUnitCI.h>
#include "linked_list.c"


void my_setUp(llist_t ***nodes, const char str[]){
  // create linked list artificially
  const size_t nitems = strlen(str);
  (*nodes) = my_calloc(nitems, sizeof(llist_t*));
  for(size_t i = 0; i < nitems; i++){
    (*nodes)[i] = my_calloc(1, sizeof(llist_t));
    char c = str[i];
    (*nodes)[i]->data = my_calloc(1, sizeof(char));
    memcpy((*nodes)[i]->data, &c, sizeof(char));
    (*nodes)[i]->data_size = sizeof(char);
  }
  for(size_t i = 0; i < nitems-1; i++){
    (*nodes)[i]->node_next = (*nodes)[i+1];
  }
}

void my_tearDown(llist_t **nodes){
  // clean-up linked list,
  //   mainly created by setUp
  //   but partially added by tests
  llist_t *node_curr = nodes[0];
  llist_t *node_next = NULL;
  while(node_curr != NULL){
    node_next = node_curr->node_next;
    my_free(node_curr->data);
    my_free(node_curr);
    node_curr = node_next;
  }
  my_free(nodes);
}

static char *from_llist_to_str(llist_t *node_root){
  size_t nitems;
  llist_get_nitems(&nitems, node_root);
  char *str = my_calloc(nitems+1, sizeof(char));
  llist_t *node_curr = node_root;
  for(size_t i = 0; i < nitems; i++){
    str[i] = *(char *)(node_curr->data);
    node_curr = node_curr->node_next;
  }
  str[nitems] = '\0';
  return str;
}

// normal use, add a few integer numbers to NULL link list, copy
static void test_llist_insert_case0(void){
  // answers
  const size_t nitems_data_answer = 4;
  const int retval_ans = 0;
  int *data_answer = NULL;
  // create answer
  data_answer = my_calloc(nitems_data_answer, sizeof(int));
  for(size_t i = 0; i < nitems_data_answer; i++){
    data_answer[i] = i;
  }
  // args
  llist_t *node_root = NULL;
  size_t loc = 0;
  const size_t data_size = sizeof(int)*nitems_data_answer;
  const bool do_copy = true;
  int retval = llist_insert(&node_root, loc, data_answer, data_size, do_copy);
  CU_ASSERT(retval_ans == retval);
  for(size_t i = 0; i < nitems_data_answer; i++){
    int d0 = data_answer[i];
    int d1 = ((int *)(node_root->data))[i];
    CU_ASSERT(d0 == d1);
  }
  // clean-up
  my_free(node_root->data);
  my_free(node_root);
  my_free(data_answer);
}

// normal use, add a few integer numbers to NULL link list, no copy
static void test_llist_insert_case1(void){
  // answers
  const size_t nitems_data_answer = 4;
  const int retval_ans = 0;
  int *data_answer = NULL;
  // create answer
  data_answer = my_calloc(nitems_data_answer, sizeof(int));
  for(size_t i = 0; i < nitems_data_answer; i++){
    data_answer[i] = i;
  }
  // args
  llist_t *node_root = NULL;
  size_t loc = 0;
  const size_t data_size = sizeof(data_answer);
  const bool do_copy = false;
  int retval = llist_insert(&node_root, loc, data_answer, data_size, do_copy);
  CU_ASSERT(retval_ans == retval);
  for(size_t i = 0; i < nitems_data_answer; i++){
    // not only value but address should also be the same
    int d0 = data_answer[i];
    int d1 = ((int *)(node_root->data))[i];
    CU_ASSERT(d0 == d1);
    int *ptr0 = &(data_answer[i]);
    int *ptr1 = &(((int *)(node_root->data))[i]);
    CU_ASSERT_PTR_EQUAL(ptr0, ptr1);
  }
  // clean-up
  // my_free(node_root->data); should not be called, since it's reference to data_answer freed later
  my_free(node_root);
  my_free(data_answer);
}

// normal use, add a character in the middle of pre-defined linked list
static void test_llist_insert_case2(void){
  const char str_test[] = {"abcefg"};
  // answers
  const int retval_ans = 0;
  const char str_answer[] = {"abcdefg"};
  // args
  llist_t **nodes = NULL;
  size_t loc = 3;
  char c = 'd';
  const size_t data_size = sizeof(char);
  const bool do_copy = true;
  // prepare
  my_setUp(&nodes, str_test);
  int retval = llist_insert(&(nodes[0]), loc, &c, data_size, do_copy);
  CU_ASSERT(retval_ans == retval);
  // extract data from linked list, compare as two strings
  char *str = from_llist_to_str(nodes[0]);
  for(size_t i = 0; i < strlen(str); i++){
    CU_ASSERT(str_answer[i] == str[i]);
  }
  my_free(str);
  // clean-up
  my_tearDown(nodes);
}

// normal use, add a character to the root of pre-defined linked list
static void test_llist_insert_case3(void){
  const char str_test[] = {"bcdefg"};
  // answers
  const int retval_ans = 0;
  const char str_answer[] = {"abcdefg"};
  // args
  llist_t **nodes = NULL;
  size_t loc = 0;
  char c = 'a';
  const size_t data_size = sizeof(char);
  const bool do_copy = true;
  // prepare
  my_setUp(&nodes, str_test);
  int retval = llist_insert(&(nodes[0]), loc, &c, data_size, do_copy);
  CU_ASSERT(retval_ans == retval);
  // extract data from linked list, compare as two strings
  char *str = from_llist_to_str(nodes[0]);
  for(size_t i = 0; i < strlen(str); i++){
    CU_ASSERT(str_answer[i] == str[i]);
  }
  my_free(str);
  // clean-up
  my_tearDown(nodes);
}

// normal use, add a character to the end of pre-defined linked list
static void test_llist_insert_case4(void){
  const char str_test[] = {"abcdef"};
  // answers
  const int retval_ans = 0;
  const char str_answer[] = {"abcdefg"};
  // args
  llist_t **nodes = NULL;
  size_t loc = 6;
  char c = 'g';
  const size_t data_size = sizeof(char);
  const bool do_copy = true;
  // prepare
  my_setUp(&nodes, str_test);
  int retval = llist_insert(&(nodes[0]), loc, &c, data_size, do_copy);
  CU_ASSERT(retval_ans == retval);
  // extract data from linked list, compare as two strings
  char *str = from_llist_to_str(nodes[0]);
  for(size_t i = 0; i < strlen(str); i++){
    CU_ASSERT(str_answer[i] == str[i]);
  }
  my_free(str);
  // clean-up
  my_tearDown(nodes);
}

// abnormal use, try to add a character out-of-range
static void test_llist_insert_case5(void){
  const char str_test[] = {"abcdef"};
  // answers
  const int retval_ans = -1;
  // args
  llist_t **nodes = NULL;
  size_t loc = 100;
  char c = 'x';
  const size_t data_size = sizeof(char);
  const bool do_copy = true;
  // prepare
  my_setUp(&nodes, str_test);
  int retval = llist_insert(&(nodes[0]), loc, &c, data_size, do_copy);
  CU_ASSERT(retval_ans == retval);
  // clean-up
  my_tearDown(nodes);
}

CUNIT_CI_RUN(
    "insert",
    CUNIT_CI_TEST(test_llist_insert_case0),
    CUNIT_CI_TEST(test_llist_insert_case1),
    CUNIT_CI_TEST(test_llist_insert_case2),
    CUNIT_CI_TEST(test_llist_insert_case3),
    CUNIT_CI_TEST(test_llist_insert_case4),
    CUNIT_CI_TEST(test_llist_insert_case5)
);

