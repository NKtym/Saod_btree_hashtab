#include <stdio.h>
#include "btree.h"
#include "hashtab.h"
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>


double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getRand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main(){
    printf("\nTEST\n");
    struct bstree *tree,*node;
    tree=bstree_create("A",54);
    bstree_add(tree,"C",46);
    bstree_add(tree,"B",62);
    node=bstree_lookup(tree,"B");
    printf("Found value for key %s: %d\n",node->key,node->value);
    node=bstree_min(tree);
    printf("Min key: %s, value: %d\n",node->key,node->value);
    node=bstree_max(tree);
    printf("Max key: %s, value: %d\n",node->key,node->value);
    node=bstree_delete(tree,"C");
    struct listnode *node2;
    struct listnode *hashtab3[200000];
    struct listnode *hashtab2[200000];
    hashtab_init(hashtab2);
    hashtab_add(hashtab2,"A", 17,"hash");
    hashtab_add(hashtab2,"B", 4,"hash");
    hashtab_add(hashtab2,"C", 14,"hash");
    node2 = hashtab_lookup(hashtab2,"C","hash");
    if (node2 != NULL)
	printf("Node: %s, %d\n", node2->key, node2->value);
    hashtab_delete(hashtab2,"B");
    node2 = hashtab_lookup(hashtab2, "B","hash");
    if (node2 != NULL)
	printf("Node: %s, %d\n", node2->key, node2->value);
    else
	printf("Node not found\n");
    unsigned int h = KRHash("A");
    printf("Hash sum: %d\n", h);
    h = JenkinsHash("A");
    printf("%d\n",h);
    return 0;
}
