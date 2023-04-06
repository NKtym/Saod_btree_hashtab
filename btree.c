#include <stdlib.h>
#include <string.h>
#include "btree.h"

unsigned int hash(char *key)
{
    unsigned int h = 0, hash_mul = 31;
    while (*key)
        h = h * hash_mul + (unsigned int)*key++;
    return h % 200000;
}

struct bstree *bstree_create(char* key,int value)
{
    struct bstree *node;
    node=malloc(sizeof(*node));
    if(node!=NULL){
	node->key=key;
	node->value=value;
	node->left=NULL;
	node->right=NULL;
    }
    return node;
}

void bstree_add(struct bstree *tree,char* key, int value)
{
    if(tree==NULL)
	return;
    struct bstree *parent, *node;
    int index = hash(key);
    while(tree!=NULL){
	parent=tree;
	if(index<hash(tree->key))
	    tree=tree->left;
	else if(index>hash(tree->key))
	    tree=tree->right;
	else
	    return;
    }
    node=bstree_create(key,value);
    if(index<hash(parent->key))
	parent->left=node;
    else
	parent->right=node;

}

struct bstree *bstree_lookup(struct bstree *tree, char* key)
{
    int index = hash(key);
    while(tree!=NULL){
	if(index==hash(tree->key))
	    return tree;
	else if(index<hash(tree->key))
	    tree=tree->left;
	else
	    tree=tree->right;
    }
    return tree;
}

struct bstree *bstree_min(struct bstree *tree)
{
    if(!tree)
	return NULL;
    while(tree->left)
	tree=tree->left;
    return tree;
}

struct bstree *bstree_max(struct bstree *tree)
{
    if(!tree)
	return NULL;
    while(tree->right)
	tree=tree->right;
    return tree;
}

struct bstree *bstree_delete(struct bstree *tree,char* key){
  struct bstree *parent = NULL;
  struct bstree *node = tree;

  // Find the node to be deleted and its parent
  while (node) {
    if (strcmp(key, node->key) == 0) {
      break;
    } else if (strcmp(key, node->key) < 0) {
      parent = node;
      node = node->left;
    } else {
      parent = node;
      node = node->right;
    }
  }

  // If the node was not found, return the original tree
  if (!node) {
    return tree;
  }

  // If the node has no children, just remove it
  if (!node->left && !node->right) {
    if (!parent) {
      // The node is the root of the tree
      free(node);
      return NULL;
    } else if (parent->left == node) {
      parent->left = NULL;
    } else {
      parent->right = NULL;
    }
    free(node);
  }
  // If the node has one child, replace it with its child
  else if (!node->left || !node->right) {
    struct bstree *child = node->left ? node->left : node->right;
    if (!parent) {
      // The node is the root of the tree
      free(node);
      return child;
    } else if (parent->left == node) {
      parent->left = child;
    } else {
      parent->right = child;
    }
    free(node);
  }
  // If the node has two children, replace it with the minimum node in its
  // right subtree
  else {
    struct bstree *successor = bstree_min(node->right);
    node->key = successor->key;
    node->value = successor->value;
    tree->right = bstree_delete(tree->right, successor->key);
  }

  return tree;
}


