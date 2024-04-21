#include "event_bst.h"
#include "logging.h"
#include "mevent.h"
#include <stdlib.h>
#include <string.h>

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
  bst->size += 1;
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
  } else if (node_a == node_a->parent->left) {
    node_a->parent->left = node_b;
  } else {
    node_a->parent->right = node_b;
  }
  if (node_b != NULL) {
    node_b->parent = node_a->parent;
  }
}
static BstEventNode bst_maximum(BstEventNode node) {
  if (node == NULL) {
    return NULL;
  }
  while (node->right != NULL) {
    node = node->right;
  }
  return node;
}
static BstEventNode bst_minimum(BstEventNode node) {
  if (node == NULL) {
    return NULL;
  }
  while (node->left != NULL) {
    node = node->left;
  }
  return node;
}
static BstEventNode bst_predeccessor(BstEventNode node) {
  if (node == NULL) {
    return NULL;
  }
  if (node->left != NULL) {
    return bst_maximum(node->left);
  }
  BstEventNode res = node->parent;
  while (res != NULL && node == res->left) {
    node = res;
    res = res->parent;
  }
  return res;
}

static BstEventNode bst_successor(BstEventNode node) {
  if (node == NULL) {
    return NULL;
  }
  if (node->right != NULL) {
    return bst_minimum(node->right);
  }
  BstEventNode res = node->parent;
  while (res != NULL && node == res->right) {
    node = res;
    res = res->parent;
  }
  return res;
}

Event bst_remove_event(BstEvent bst, ConstEvent event) {
  BstEventNode to_delete = bst_search_event(bst, event);
  if (to_delete == NULL) {
    return NULL;
  }
  if (to_delete->left == NULL) {
    bst_shift_nodes(bst, to_delete, to_delete->right);
  } else if (to_delete->right == NULL) {
    bst_shift_nodes(bst, to_delete, to_delete->left);
  } else {
    BstEventNode temp = bst_successor(to_delete);
    if (temp->parent != to_delete) {
      bst_shift_nodes(bst, temp, temp->right);
      temp->right = to_delete->right;
      temp->right->parent = temp;
    }
    bst_shift_nodes(bst, to_delete, temp);
    temp->left = to_delete->left;
    temp->left->parent = temp;
  }
  Event value = to_delete->value;
  free(to_delete);
  bst->size -= 1;
  return value;
}

#define SEPARATOR "\n\n"
static void print_event_bst_nodes(BstEventNode node) {
  if (node == NULL) {
    return;
  }
  print_event_bst_nodes(node->left);
  char *to_print = to_string_event(node->value);
  if (to_print == NULL) {
    return;
  }
  printf("%s%s", to_print, SEPARATOR);
  free(to_print);
  print_event_bst_nodes(node->right);
}

void print_event_bst(ConstBstEvent bst) { print_event_bst_nodes(bst->root); }

static char *to_string_event_bst_nodes(BstEventNode node) {
  // TODO
  // Again, very expensive realloc, should find a way to do something better
  if (node == NULL) {
    return NULL;
  }
  char *res = to_string_event_bst_nodes(node->left);
  size_t size = strlen(res);
  char *to_cat = to_string_event(node->value);
  if (to_cat == NULL) {
    free(res);
    return NULL;
  }
  size += strlen(to_cat) + strlen(SEPARATOR);
  char *temp = realloc(res, (size + 1) * sizeof(char));
  if (temp == NULL) {
    free(res);
    free(to_cat);
    return NULL;
  }
  res = temp;
  strncat(res, SEPARATOR, size - strlen(res));
  strncat(res, to_cat, size - strlen(res));
  free(to_cat);

  to_cat = to_string_event_bst_nodes(node->right);
  if (to_cat == NULL) {
    free(res);
    return NULL;
  }
  size += strlen(to_cat) + strlen(SEPARATOR);
  temp = realloc(res, (size + 1) * sizeof(char));
  if (temp == NULL) {
    free(res);
    free(to_cat);
    return NULL;
  }
  res = temp;
  strncat(res, SEPARATOR, size - strlen(res));
  strncat(res, to_cat, size - strlen(res));
  free(to_cat);
  return res;
}

char *to_string_event_bst(ConstBstEvent bst) {
  return to_string_event_bst_nodes(bst->root);
}

static void free_event_bst_nodes(BstEventNode node) {
  if (node == NULL) {
    return;
  }

  free_event_bst_nodes(node->left);
  free_event_bst_nodes(node->right);

  free_event(node->value);
  free(node);
}

void free_event_bst(BstEvent bst) {
  free_event_bst_nodes(bst->root);
  free(bst);
}
