#include "event_bst.h"
#include "logging.h"
#include "mevent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct EventBstNodeStruct *EventBstNode;

struct EventBstNodeStruct {
  Event value;
  EventBstNode parent;
  EventBstNode left;
  EventBstNode right;
};

struct EventBstStruct {
  EventBstNode root;
  size_t size;
};

EventBst new_event_bst(void) {
  EventBst bst = calloc(1, sizeof(*bst));
  if (bst == NULL) {
    return NULL_EVENT_BST;
  }
  bst->root = NULL;
  bst->size = 0;
  return bst;
}

int bst_insert_event(EventBst bst, Event event) {
  if (bst == NULL_EVENT_BST) {
    log_error("Bst is NULL in 'bst_insert_event'");
    return -1;
  }
  EventBstNode to_insert = calloc(1, sizeof(*to_insert));
  if (to_insert == NULL) {
    log_error("Failed to create 'to_insert' in function 'bst_insert_event'");
    return -1;
  }
  to_insert->value = event;
  EventBstNode parent = NULL;
  EventBstNode temp = bst->root;
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

static EventBstNode bst_search_event(EventBst bst, ConstEvent event) {
  EventBstNode res = bst->root;
  while (res != NULL && !is_same_instance_event(event, res->value)) {
    if (cmp_event(event, res->value) < 0) {
      res = res->left;
    } else {
      res = res->right;
    }
  }
  return res;
}

static EventBstNode bst_nodes_search_event_by_id(EventBstNode node,
                                                 unsigned int id) {
  if (node == NULL) {
    return NULL;
  }
  if (get_event_id(node->value) == id) {
    return node;
  }
  EventBstNode temp = NULL;
  temp = bst_nodes_search_event_by_id(node->left, id);
  if (temp != NULL) {
    return temp;
  }
  return bst_nodes_search_event_by_id(node->right, id);
}

static EventBstNode bst_search_event_by_id(EventBst bst, unsigned int id) {
  return bst_nodes_search_event_by_id(bst->root, id);
}

static void bst_shift_nodes(EventBst bst, EventBstNode node_a,
                            EventBstNode node_b) {
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
static EventBstNode bst_maximum(EventBstNode node) {
  if (node == NULL) {
    return NULL;
  }
  while (node->right != NULL) {
    node = node->right;
  }
  return node;
}
static EventBstNode bst_minimum(EventBstNode node) {
  if (node == NULL) {
    return NULL;
  }
  while (node->left != NULL) {
    node = node->left;
  }
  return node;
}
static EventBstNode bst_predeccessor(EventBstNode node) {
  if (node == NULL) {
    return NULL;
  }
  if (node->left != NULL) {
    return bst_maximum(node->left);
  }
  EventBstNode res = node->parent;
  while (res != NULL && node == res->left) {
    node = res;
    res = res->parent;
  }
  return res;
}

static EventBstNode bst_successor(EventBstNode node) {
  if (node == NULL) {
    return NULL;
  }
  if (node->right != NULL) {
    return bst_minimum(node->right);
  }
  EventBstNode res = node->parent;
  while (res != NULL && node == res->right) {
    node = res;
    res = res->parent;
  }
  return res;
}

static Event bst_remove_node(EventBst bst, EventBstNode to_delete) {

  if (to_delete == NULL) {
    return NULL_EVENT;
  }
  if (to_delete->left == NULL) {
    bst_shift_nodes(bst, to_delete, to_delete->right);
  } else if (to_delete->right == NULL) {
    bst_shift_nodes(bst, to_delete, to_delete->left);
  } else {
    EventBstNode temp = bst_successor(to_delete);
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

Event bst_remove_event(EventBst bst, ConstEvent event) {
  EventBstNode to_delete = bst_search_event(bst, event);
  return bst_remove_node(bst, to_delete);
}

Event bst_remove_event_by_id(EventBst bst, unsigned int id) {
  EventBstNode to_delete = bst_search_event_by_id(bst, id);
  return bst_remove_node(bst, to_delete);
}

#define SEPARATOR "\n\n"
static void print_event_bst_nodes(EventBstNode node) {
  if (node == NULL) {
    return;
  }
  print_event_bst_nodes(node->left);
  print_event(node->value);
  printf(SEPARATOR);
  print_event_bst_nodes(node->right);
}

void print_event_bst(ConstEventBst bst) { print_event_bst_nodes(bst->root); }

size_t get_bst_size(ConstEventBst bst) { return bst->size; }

static void free_event_bst_nodes(EventBstNode node) {
  if (node == NULL) {
    return;
  }

  free_event_bst_nodes(node->left);
  free_event_bst_nodes(node->right);

  free_event(node->value);
  free(node);
}

void free_event_bst(EventBst bst) {
  if (bst == NULL_EVENT_BST) {
    return;
  }
  free_event_bst_nodes(bst->root);
  free(bst);
}
