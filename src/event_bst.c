#include "event_bst.h"
#include "logging.h"
#include "mevent.h"
#include "utils.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEPARATOR "\n\n"

// Define the structure of a node in the event binary search tree
typedef struct EventBstNodeStruct *EventBstNode;

struct EventBstNodeStruct {
  Event value;
  EventBstNode parent;
  EventBstNode left;
  EventBstNode right;
};

// Define the structure of the event binary search tree
struct EventBstStruct {
  EventBstNode root;
  size_t size;
};

// Function to create a new empty event binary search tree
EventBst new_event_bst(void) {
  EventBst bst = my_alloc(1, sizeof(*bst));
  bst->root = NULL;
  bst->size = 0;
  return bst;
}

// Function to insert an event into the event binary search tree
int bst_insert_event(EventBst bst, Event event) {
  // Error handling for NULL BST pointer
  if (bst == NULL_EVENT_BST) {
    log_error("Bst is NULL in 'bst_insert_event'");
    return -1;
  }

  // Create a new node for the event to insert
  EventBstNode to_insert = my_alloc(1, sizeof(*to_insert));
  to_insert->value = event;
  to_insert->parent = NULL;
  to_insert->left = NULL;
  to_insert->right = NULL;

  // Traverse the tree to find the correct position to insert the new event
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

  // Insert the new node into the tree
  to_insert->parent = parent;
  if (parent == NULL) {
    bst->root = to_insert;
  } else if (cmp_event(to_insert->value, parent->value) < 0) {
    parent->left = to_insert;
  } else {
    parent->right = to_insert;
  }

  // Update the size of the BST
  bst->size += 1;
  return 0;
}

// Helper function to search for an event in the event binary search tree
static EventBstNode bst_search_event(EventBst bst, ConstEvent event) {
  EventBstNode res = bst->root;
  while (res != NULL && !are_events_equal(event, res->value)) {
    if (cmp_event(event, res->value) < 0) {
      res = res->left;
    } else {
      res = res->right;
    }
  }
  return res;
}

// Helper function to recursively search for an event by ID in the event binary
// search tree
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

// Helper function to search for an event by ID in the event binary search tree
static EventBstNode bst_search_event_by_id(EventBst bst, unsigned int id) {
  return bst_nodes_search_event_by_id(bst->root, id);
}

// Helper function to shift nodes during node removal in the event binary search
// tree
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

// Helper function to find the maximum node in the event binary search tree
static EventBstNode bst_maximum(EventBstNode node) {
  if (node == NULL) {
    return NULL;
  }
  while (node->right != NULL) {
    node = node->right;
  }
  return node;
}

// Helper function to find the minimum node in the event binary search tree
static EventBstNode bst_minimum(EventBstNode node) {
  if (node == NULL) {
    return NULL;
  }
  while (node->left != NULL) {
    node = node->left;
  }
  return node;
}

// Helper function to find the predecessor node of a given node in the event
// binary search tree
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

// Helper function to find the successor node of a given node in the event
// binary search tree
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

// Helper function to remove a node from the event binary search tree
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

// Function to remove an event from the event binary search tree
Event bst_remove_event(EventBst bst, ConstEvent event) {

  EventBstNode to_delete = bst_search_event(bst, event);
  return bst_remove_node(bst, to_delete);
}

// Function to get an event by ID from the event binary search tree
Event bst_get_event_by_id(EventBst bst, unsigned int id) {
  EventBstNode to_delete = bst_search_event_by_id(bst, id);
  if (to_delete == NULL) {
    return NULL_EVENT;
  }
  return to_delete->value;
}

// Function to remove an event by ID from the event binary search tree
Event bst_remove_event_by_id(EventBst bst, unsigned int id) {
  EventBstNode to_delete = bst_search_event_by_id(bst, id);
  return bst_remove_node(bst, to_delete);
}

// Function to print all events in the event binary search tree
static void print_event_bst_nodes(EventBstNode node, ConstRoomList room_list) {
  if (node == NULL) {
    return;
  }
  print_event_bst_nodes(node->left, room_list);
  print_event(node->value,
              get_room_by_id(room_list, get_event_room_id(node->value)));
  printf(SEPARATOR);
  print_event_bst_nodes(node->right, room_list);
}

// Function to print all events in the event binary search tree
void print_event_bst(ConstEventBst bst, ConstRoomList room_list) {
  print_event_bst_nodes(bst->root, room_list);
}

// Function to get the size of the event binary search tree
size_t get_bst_size(ConstEventBst bst) { return bst->size; }

// Helper function to recursively free memory allocated for nodes in the event
// binary search tree
static void free_event_bst_nodes(EventBstNode node) {
  if (node == NULL) {
    return;
  }

  free_event_bst_nodes(node->left);
  free_event_bst_nodes(node->right);

  free_event(node->value);
  free(node);
}

// Helper function to recursively apply a predicate function to each node in the
// event binary search tree
static bool every_node(EventBstNode node, EventPredicate predicate,
                       va_list args) {
  if (node == NULL) {
    return true; // Base case: an empty subtree satisfies the condition
  }

  // Check the current node's value
  va_list args_copy;
  va_copy(args_copy, args);
  bool result = predicate(node->value, args_copy);
  va_end(args_copy);

  if (!result) {
    return false; // If the predicate fails for this node's value, return false
  }

  // Recursively check left and right subtrees
  return every_node(node->left, predicate, args) &&
         every_node(node->right, predicate, args);
}

// Function to apply a predicate function to every node in the event binary
// search tree
bool event_bst_every(EventBst bst, EventPredicate predicate, ...) {
  if (bst == NULL_EVENT_BST || bst->root == NULL || bst->size == 0) {
    return true; // Handle edge cases where the tree is empty
  }

  // Initialize variable arguments
  va_list args;
  va_start(args, predicate);

  // Call the recursive function starting from the root node
  bool result = every_node(bst->root, predicate, args);

  // Clean up variable arguments
  va_end(args);

  return result;
}

// Function to free memory allocated for the event binary search tree
void free_event_bst(EventBst bst) {
  if (bst == NULL_EVENT_BST) {
    return;
  }
  free_event_bst_nodes(bst->root);
  free(bst);
}

// Helper function to recursively save event BST nodes to a file
static void save_event_bst_nodes(EventBstNode node, FILE *file) {
  if (node == NULL) {
    return;
  }

  // Save current node's event to the file
  save_event_to_file(node->value, file);

  // Recursively save left and right subtrees
  save_event_bst_nodes(node->left, file);
  save_event_bst_nodes(node->right, file);
}

// Function to save an event BST to a file
void save_event_bst_to_file(ConstEventBst bst, FILE *file) {
  if (file == NULL) {
    log_error("File pointer is NULL");
    return;
  }

  fprintf(file, "%zu\n", bst->size);
  // Traverse the BST and save each event to the file
  save_event_bst_nodes(bst->root, file);
}

// Helper function to recursively save event BST nodes to a file in a sorted
// manner
static void save_event_bst_nodes_sorted(EventBstNode node, FILE *file) {
  if (node == NULL) {
    return;
  }

  // Recursively save left subtree
  save_event_bst_nodes_sorted(node->left, file);

  // Save current node's event to the file
  save_event_to_file(node->value, file);

  // Recursively save right subtree
  save_event_bst_nodes_sorted(node->right, file);
}

// Function to save an event BST to a file, saving them in a sorted way
void save_event_bst_to_file_sorted(ConstEventBst bst, FILE *file) {
  if (file == NULL) {
    log_error("File pointer is NULL");
    return;
  }

  fprintf(file, "%zu\n", bst->size);
  // Traverse the BST and save each event to the file
  save_event_bst_nodes_sorted(bst->root, file);
}

// Function to read an event BST from a file
EventBst read_event_bst_from_file(FILE *file) {
  if (file == NULL) {
    log_error("File pointer is NULL");
    return NULL_EVENT_BST;
  }

  size_t size = 0;
  if (fscanf(file, "%zu\n", &size) != 1) {
    log_error("Error reading BST size");
    return NULL_EVENT_BST;
  }

  EventBst bst = new_event_bst(); // Create a new empty BST

  // Read event data from the file and insert into the BST
  for (size_t i = 0; i < size; i++) {
    Event event = read_event_from_file(file);
    if (event == NULL_EVENT) {
      log_error("Error reading event data");
      free_event_bst(bst);
      return NULL_EVENT_BST;
    }
    bst_insert_event(bst, event);
  }

  return bst;
}
