#include <stdlib.h>
#include <stdlib.h>
#include "btree.h"

#define HASH_SIZE 128

unsigned int hash(char *key)
{
    unsigned int h = 0;
    while (*key)
        h += (unsigned int)*key++;
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
    if(tree==NULL)
	return NULL;
    while(tree->left!=NULL)
	tree=tree->left;
    return tree;
}

struct bstree *bstree_max(struct bstree *tree)
{
    if(tree==NULL)
	return NULL;
    while(tree->right!=NULL)
	tree=tree->right;
    return tree;
}

//struct bstree *bstree_delete(struct bstree *tree,char* key)
//{
 //   if(tree==NULL)
//	return NULL;
  //  struct bstree *temp;
    //if(key<tree->key)
	//tree->left=bstree_delete(tree->left,key);
    //else if(key>tree->key)
//	tree->right=bstree_delete(tree->right,key);
  //  else{
	//if(tree->left==NULL && tree->right==NULL){
	  //  free(tree);
	    //return NULL;
//	}
//	else if(tree->left==NULL && tree->right!=NULL){
//	    tree=tree->right;
//	}
//	else if(tree->right==NULL && tree->left!=NULL){
//	    tree=tree->left;
//	}
//	else if(tree->right!=NULL && tree->left!=NULL){
//	    temp=tree->right;
//	    while(temp->left!=NULL)
//		temp=temp->left;
//	    tree=temp;
//	    free(temp);
//	}
//    }
//    return tree;
//}
