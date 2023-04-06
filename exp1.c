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
    FILE* file;
    file=fopen("a.txt","r");
    int n=200000;
    char words[n][20];
    for(int i=0;i<n;i++)
	fgets(words[i],n-1,file);
    for(int i=0;i<=10;i++)
	printf("%s\n",words[i]);
    fclose(file);
    struct bstree *tree,*node,*node2;
    tree = bstree_create(words[0],0);
    for(int i = 2;i<=n;i++){
	bstree_add(tree,words[i-1],i-1);
	if(i%10000 == 0){
	    char *w = words[getRand(0, i-1)];
	    double t = 0.0;
	    clock_t begin=clock();
	    node = bstree_lookup(tree, w);
	    clock_t end=clock();
	    t+=(double)(end-begin)/ CLOCKS_PER_SEC;
	    printf("n = %d; time = %.6lf \n", i, t);
	}
  }
    struct listnode *hashtab3[200000];
    hashtab_init(hashtab3);
    for(int i = 1;i<=n;i++){
	hashtab_add(hashtab3,words[i],i-1,"hash");
	if(i%10000 == 0){
	    char* w = words[getRand(0, i-1)];
	    double t = 0.0;
	    clock_t begin=clock();
	    node2 = hashtab_lookup(hashtab3,w,"hash");
	    clock_t end=clock();
	    t+=(double)(end-begin)/ CLOCKS_PER_SEC;
	    printf("n = %d; time = %.6lf \n", i, t);
	}
    }
    return 0;
}
