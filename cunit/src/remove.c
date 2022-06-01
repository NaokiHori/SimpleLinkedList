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
    (*nodes)[i]->data_is_copied = true;
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

// normal use, remove a character from the middle of pre-defined linked list
static void test_llist_remove_case0(void){
  const char str_test[] = {"abcdefg"};
  // answers
  const int retval_ans = 0;
  const char str_answer[] = {"abcefg"};
  // args
  llist_t **nodes = NULL;
  size_t loc = 3;
  // prepare
  my_setUp(&nodes, str_test);
  int retval = llist_remove(&(nodes[0]), loc);
  CU_ASSERT(retval_ans == retval);
  // extract data from linked list and compare
  char *str = from_llist_to_str(nodes[0]);
  CU_ASSERT(strlen(str_answer) == strlen(str));
  for(size_t i = 0; i < strlen(str); i++){
    CU_ASSERT(str_answer[i] == str[i]);
  }
  my_free(str);
  // clean-up
  my_tearDown(nodes);
}

// normal use, remove the root node of pre-defined linked list
static void test_llist_remove_case1(void){
  const char str_test[] = {"abcdefg"};
  // answers
  const int retval_ans = 0;
  const char str_answer[] = {"bcdefg"};
  // args
  llist_t **nodes = NULL;
  size_t loc = 0;
  // prepare
  my_setUp(&nodes, str_test);
  int retval = llist_remove(&(nodes[0]), loc);
  CU_ASSERT(retval_ans == retval);
  // extract data from linked list and compare
  char *str = from_llist_to_str(nodes[0]);
  CU_ASSERT(strlen(str_answer) == strlen(str));
  for(size_t i = 0; i < strlen(str); i++){
    CU_ASSERT(str_answer[i] == str[i]);
  }
  my_free(str);
  // clean-up
  my_tearDown(nodes);
}

// normal use, remove the end node of pre-defined linked list
static void test_llist_remove_case2(void){
  const char str_test[] = {"abcdefg"};
  // answers
  const int retval_ans = 0;
  const char str_answer[] = {"abcdef"};
  // args
  llist_t **nodes = NULL;
  size_t loc = 6;
  // prepare
  my_setUp(&nodes, str_test);
  int retval = llist_remove(&(nodes[0]), loc);
  CU_ASSERT(retval_ans == retval);
  // extract data from linked list and compare
  char *str = from_llist_to_str(nodes[0]);
  CU_ASSERT(strlen(str_answer) == strlen(str));
  for(size_t i = 0; i < strlen(str); i++){
    CU_ASSERT(str_answer[i] == str[i]);
  }
  my_free(str);
  // clean-up
  my_tearDown(nodes);
}

// abnormal use, try to remove a node out-of-range
static void test_llist_remove_case3(void){
  const char str_test[] = {"abcdefg"};
  // answers
  const int retval_ans = -1;
  // args
  llist_t **nodes = NULL;
  size_t loc = 100;
  // prepare
  my_setUp(&nodes, str_test);
  int retval = llist_remove(&(nodes[0]), loc);
  CU_ASSERT(retval_ans == retval);
  // clean-up
  my_tearDown(nodes);
}

// normal use, try to remove all nodes
static void test_llist_remove_case4(void){
  const char str_test[] = {"abcdefg"};
  // answers
  const int retval_ans = 0;
  // args
  llist_t **nodes = NULL;
  size_t loc = 0;
  // prepare
  my_setUp(&nodes, str_test);
  for(size_t i = 0; i < strlen(str_test); i++){
    int retval = llist_remove(&(nodes[0]), loc);
    CU_ASSERT(retval_ans == retval);
  }
  // clean-up
  my_tearDown(nodes);
}

CUNIT_CI_RUN(
    "remove",
    CUNIT_CI_TEST(test_llist_remove_case0),
    CUNIT_CI_TEST(test_llist_remove_case1),
    CUNIT_CI_TEST(test_llist_remove_case2),
    CUNIT_CI_TEST(test_llist_remove_case3),
    CUNIT_CI_TEST(test_llist_remove_case4)
);

