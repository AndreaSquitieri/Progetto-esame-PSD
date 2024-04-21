#include "event_bst.h"
#include "logging.h"
#include "mevent.h"
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
    if (cmp_event(to_insert->value, temp->value) < 0) {
      temp = temp->left;
    } else {
      temp = temp->right;
    }
  }
  to_insert->parent = parent;
  if (parent == NULL) {
    bst->root = to_insert;
  } else if (cmp_event(to_insert->value, parent->value) < 0) {
    parent->left = to_insert;
  } else {
    parent->right = to_insert;
  }
  return 0;
}

static BstEventNode bst_search_event(BstEvent bst, ConstEvent event) {
  BstEventNode res = bst->root;
  while (res != NULL && !is_same_instance_event(event, res->value)) {
    if (cmp_event(event, res->value) < 0) {
      res = res->left;
    } else {
      res = res->right;
    }
  }
  return res;
}

static void bst_shift_nodes(BstEvent bst, BstEventNode node_a,
                            BstEventNode node_b) {
  if (node_a->parent == NULL) {
    bst->root = node_b;
  } else if (node_a == node_a) {
  }
}

Event bst_remove_event(BstEvent bst, ConstEvent event) {
  BstEventNode to_delete = bst_search_event(bst, event);
  if (to_delete == NULL) {
    return NULL;
  }
  if (to_delete->left == NULL) {
  }
}
char *to_string_event_bst(ConstBstEvent bst) {}
void free_event_bst(BstEvent bst) {}
