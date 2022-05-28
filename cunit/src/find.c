#include <CUnit/CUnitCI.h>
#include "linked_list.c"


void my_setUp(llist_t ***nodes, const size_t nitems, const bool is_null_data){
  (*nodes) = my_calloc(nitems, sizeof(llist_t *));
  for(size_t i = 0; i < nitems; i++){
    (*nodes)[i] = my_calloc(1, sizeof(llist_t));
    if(is_null_data){
      (*nodes)[i]->data = NULL;
      (*nodes)[i]->data_size = sizeof(int);
    }else{
      (*nodes)[i]->data = my_calloc(1, sizeof(int));
      int i_int = (int)i;
      memcpy((*nodes)[i]->data, &i_int, sizeof(int));
      (*nodes)[i]->data_size = sizeof(int);
    }
  }
  for(size_t i = 0; i < nitems-1; i++){
    (*nodes)[i]->next = (*nodes)[i+1];
  }
}

void my_tearDown(llist_t **nodes, const size_t nitems){
  for(size_t i = 0; i < nitems; i++){
    my_free(nodes[i]->data);
    my_free(nodes[i]);
  }
  my_free(nodes);
}

// normal use, NULL link list
static void test_llist_find_case0(void){
  // answers
  const int loc_ans = -1;
  const int retval_ans = 0;
  // args
  int loc;
  const int pattern = 3;
  const size_t pattern_size = sizeof(int);
  // exec
  int retval = llist_find(&loc, NULL, &pattern, pattern_size);
  CU_ASSERT(retval_ans == retval);
  CU_ASSERT(loc_ans == loc);
}

// normal use, find integer pattern, found
static void test_llist_find_case1(void){
  // answers
  const int loc_ans = 3;
  const int retval_ans = 0;
  // args
  const size_t nitems = 10;
  int loc;
  llist_t **nodes = NULL;
  const int pattern = 3;
  const size_t pattern_size = sizeof(int);
  // prepare
  my_setUp(&nodes, nitems, false);
  // exec
  int retval = llist_find(&loc, nodes[0], &pattern, pattern_size);
  CU_ASSERT(retval_ans == retval);
  CU_ASSERT(loc_ans == loc);
  // clean-up
  my_tearDown(nodes, nitems);
}

// normal use, find integer pattern, not found
static void test_llist_find_case2(void){
  // answers
  const int loc_ans = -1;
  const int retval_ans = 0;
  // args
  const size_t nitems = 10;
  int loc;
  llist_t **nodes = NULL;
  const int pattern = 101;
  const size_t pattern_size = sizeof(int);
  // prepare
  my_setUp(&nodes, nitems, false);
  // exec
  int retval = llist_find(&loc, nodes[0], &pattern, pattern_size);
  CU_ASSERT(retval_ans == retval);
  CU_ASSERT(loc_ans == loc);
  // clean-up
  my_tearDown(nodes, nitems);
}

// abnormal use, NULL node->data
static void test_llist_find_case3(void){
  // answers
  const int retval_ans = -1;
  // args
  const size_t nitems = 10;
  int loc;
  llist_t **nodes = NULL;
  const int pattern = 3;
  const size_t pattern_size = sizeof(int);
  // prepare
  my_setUp(&nodes, nitems, true);
  // exec
  int retval = llist_find(&loc, nodes[0], &pattern, pattern_size);
  CU_ASSERT(retval_ans == retval);
  // clean-up
  my_tearDown(nodes, nitems);
}

// abnormal use, NULL pattern
static void test_llist_find_case4(void){
  // answers
  const int retval_ans = -1;
  // args
  const size_t nitems = 10;
  int loc;
  llist_t **nodes = NULL;
  const size_t pattern_size = sizeof(int);
  // prepare
  my_setUp(&nodes, nitems, false);
  // exec
  int retval = llist_find(&loc, nodes[0], NULL, pattern_size);
  CU_ASSERT(retval_ans == retval);
  // clean-up
  my_tearDown(nodes, nitems);
}

// abnormal use, zero pattern size
static void test_llist_find_case5(void){
  // answers
  const int retval_ans = -1;
  // args
  const size_t nitems = 10;
  int loc;
  llist_t **nodes = NULL;
  const int pattern = 3;
  const size_t pattern_size = 0;
  // prepare
  my_setUp(&nodes, nitems, false);
  // exec
  int retval = llist_find(&loc, nodes[0], &pattern, pattern_size);
  CU_ASSERT(retval_ans == retval);
  // clean-up
  my_tearDown(nodes, nitems);
}

// abnormal use, too many nodes
static void test_llist_find_case6(void){
  // answers
  const int retval_ans = -1;
  // args
  const size_t nitems = 2*USHRT_MAX;
  int loc;
  llist_t **nodes = NULL;
  const int pattern = 2*USHRT_MAX;
  const size_t pattern_size = sizeof(int);
  // prepare
  my_setUp(&nodes, nitems, false);
  // exec
  int retval = llist_find(&loc, nodes[0], &pattern, pattern_size);
  CU_ASSERT(retval_ans == retval);
  // clean-up
  my_tearDown(nodes, nitems);
}

CUNIT_CI_RUN(
    "find",
    CUNIT_CI_TEST(test_llist_find_case0),
    CUNIT_CI_TEST(test_llist_find_case1),
    CUNIT_CI_TEST(test_llist_find_case2),
    CUNIT_CI_TEST(test_llist_find_case3),
    CUNIT_CI_TEST(test_llist_find_case4),
    CUNIT_CI_TEST(test_llist_find_case5),
    CUNIT_CI_TEST(test_llist_find_case6)
);
