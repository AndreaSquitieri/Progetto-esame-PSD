#include "event_bst.h"
#include "logging.h"
#include <stdlib.h>

typedef struct BstEventNodeStruct *BstEventNode;

struct BstEventNodeStruct {
  Event value;
  BstEventNode parent;
  BstEventNode left;
  BstEventNode right;
};

struct BstEventStruct {
  BstEventNode root;
  size_t size;
};

BstEvent new_event_bst(void) {
  BstEvent bst = calloc(1, sizeof(*bst));
  if (bst == NULL) {
    return NULL;
  }
  bst->root = NULL;
  bst->size = 0;
  return bst;
}
int bst_insert_event(BstEvent bst, Event event) {
  // TODO
  // The comparison for now is only based on the date
  // I would like to fallback to alphabetidal order whenever two dates coincides
  if (bst == NULL) {
    log_error("Bst is NULL in 'bst_insert_event'");
    return -1;
  }
  BstEventNode to_insert = calloc(1, sizeof(*to_insert));
  if (to_insert == NULL) {
    log_error("Failed to create 'to_insert' in function 'bst_insert_event'");
    return -1;
  }
  to_insert->value = event;
  BstEventNode parent = NULL;
  BstEventNode temp = bst->root;
  while (temp != NULL) {
    parent = temp;
    if (cmp_date(get_event_date(to_insert->value),
                 get_event_date(temp->value)) < 0) {
      temp = temp->left;
    } else {
      temp = temp->right;
    }
  }
  to_insert->parent = parent;
  if (parent == NULL) {
    bst->root = to_insert;
  } else if (cmp_date(get_event_date(to_insert->value),
                      get_event_date(parent->value)) < 0) {
    parent->left = to_insert;
  } else {
    parent->right = to_insert;
  }
  return 0;
}

Event bst_remove_event(BstEvent bst, Event event) {}
char *to_string_event_bst(ConstBstEvent bst) {}
void free_event_bst(BstEvent bst) {}
