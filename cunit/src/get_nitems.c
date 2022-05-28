#include <CUnit/CUnitCI.h>
#include "linked_list.c"


// normal use, empty link list
static void test_llist_get_nitems_case0(void){
  // answers
  const size_t nitems_ans = 0;
  const int retval_ans = 0;
  // args
  size_t nitems;
  llist_t *node_root = NULL;
  // exec
  int retval = llist_get_nitems(&nitems, node_root);
  CU_ASSERT(retval_ans == retval);
  CU_ASSERT(nitems_ans == nitems);
}

// normal use, single node
static void test_llist_get_nitems_case1(void){
  // answers
  const size_t nitems_ans = 1;
  const int retval_ans = 0;
  // args
  size_t nitems;
  llist_t *node_root = my_calloc(1, sizeof(llist_t));
  // exec
  int retval = llist_get_nitems(&nitems, node_root);
  CU_ASSERT(retval_ans == retval);
  CU_ASSERT(nitems_ans == nitems);
  // clean-up
  my_free(node_root);
}

// normal use, many nodes
static void test_llist_get_nitems_case2(void){
  // answers
  const size_t nitems_ans = 100;
  const int retval_ans = 0;
  // args
  size_t nitems;
  llist_t **nodes = NULL;
  // prepare
  {
    nodes = my_calloc(nitems_ans, sizeof(llist_t *));
    for(size_t i = 0; i < nitems_ans; i++){
      nodes[i] = my_calloc(1, sizeof(llist_t));
    }
    for(size_t i = 0; i < nitems_ans-1; i++){
      nodes[i]->next = nodes[i+1];
    }
  }
  int retval = llist_get_nitems(&nitems, nodes[0]);
  CU_ASSERT(retval_ans == retval);
  CU_ASSERT(nitems_ans == nitems);
  // clean-up
  for(size_t i = 0; i < nitems_ans; i++){
    my_free(nodes[i]);
  }
  my_free(nodes);
}

// abnormal use, too many nodes
static void test_llist_get_nitems_case3(void){
  // answers
  const size_t nitems_ans = 2*USHRT_MAX;
  const int retval_ans = -1;
  // args
  size_t nitems;
  llist_t **nodes = NULL;
  // prepare
  {
    nodes = my_calloc(nitems_ans, sizeof(llist_t *));
    for(size_t i = 0; i < nitems_ans; i++){
      nodes[i] = my_calloc(1, sizeof(llist_t));
    }
    for(size_t i = 0; i < nitems_ans-1; i++){
      nodes[i]->next = nodes[i+1];
    }
  }
  int retval = llist_get_nitems(&nitems, nodes[0]);
  CU_ASSERT(retval_ans == retval);
  // clean-up
  for(size_t i = 0; i < nitems_ans; i++){
    my_free(nodes[i]);
  }
  my_free(nodes);
}

// abnormal use, recursive
static void test_llist_get_nitems_case4(void){
  // answers
  const size_t nitems_ans = 2;
  const int retval_ans = -1;
  // args
  size_t nitems;
  llist_t **nodes = NULL;
  // prepare
  {
    nodes = my_calloc(nitems_ans, sizeof(llist_t *));
    for(size_t i = 0; i < nitems_ans; i++){
      nodes[i] = my_calloc(1, sizeof(llist_t));
    }
    // node 0 points to 1, and vice versa
    nodes[0]->next = nodes[1];
    nodes[1]->next = nodes[0];
  }
  int retval = llist_get_nitems(&nitems, nodes[0]);
  CU_ASSERT(retval_ans == retval);
  // clean-up
  for(size_t i = 0; i < nitems_ans; i++){
    my_free(nodes[i]);
  }
  my_free(nodes);
}

CUNIT_CI_RUN(
    "get_nitems",
    CUNIT_CI_TEST(test_llist_get_nitems_case0),
    CUNIT_CI_TEST(test_llist_get_nitems_case1),
    CUNIT_CI_TEST(test_llist_get_nitems_case2),
    CUNIT_CI_TEST(test_llist_get_nitems_case3),
    CUNIT_CI_TEST(test_llist_get_nitems_case4)
);

