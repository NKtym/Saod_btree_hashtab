#include <stdio.h>
#include "btree.h"
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
    FILE* file,*f;
    file=fopen("a.txt","r");
    int n=200000;
    char words[n][20];
    for(int i=0;i<n;i++)
	fgets(words[i],n-1,file);
    for(int i=0;i<=10;i++)
	printf("%s\n",words[i]);
    fclose(file);
    f=fopen("b.txt","r");
    char wordsword[n][20];
    for(int i=0;i<n;i++)
	fgets(wordsword[i],n-1,f);
    for(int i=0;i<=10;i++)
	printf("%s\n",wordsword[i]);
    fclose(f);
    struct bstree *tree,*node;
    tree = bstree_create(words[0],0);
    for(int i = 2;i<=n;i++){
	bstree_add(tree,words[i-1],i-1);
	if(i%10000 == 0){
	    double t = 0.0;
	    clock_t begin=clock();
    	    node=bstree_max(tree);
            clock_t end=clock();
	    t+=(double)(end-begin)/ CLOCKS_PER_SEC;
	    printf("n = %d; time = %.6lf \n", i, t);
            printf("Max key: %s, value: %d\n",node->key,node->value);
	}
    }
    tree = bstree_create(wordsword[0],0);
    for(int i = 2;i<=n;i++){
	bstree_add(tree,wordsword[i-1],i-1);
	if(i%10000 == 0){
	    double t = 0.0;
	    clock_t begin=clock();
    	    node=bstree_max(tree);
            clock_t end=clock();
	    t+=(double)(end-begin)/ CLOCKS_PER_SEC;
	    printf("n = %d; time = %.6lf \n", i, t);
            printf("Max key: %s, value: %d\n",node->key,node->value);
	}
    }
    return 0;
}
