#include <stdio.h>
#include "btree.h"
#include "hashtab.h"
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>


#define HASH_SIZE 128

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
    //test
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
    //node=bstree_delete(tree,"C");
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
    //test
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
    //exp1
    printf("\nEXP 1\n");
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
    //exp1
    //exp5
    printf("\nEXP 5\n");
    tree = bstree_create(words[0],0);
    for(int i = 2;i<=n;i++){
	bstree_add(tree,words[i-1],i-1);
	if(i%10000 == 0){
	    double t = 0.0;
	    clock_t begin=clock();
    	    node=bstree_max(tree);
            clock_t end=clock();
	    t+=(double)(end-begin)/ CLOCKS_PER_SEC;
	    printf("n = %d; time = %.10lf \n", i, t);
            printf("Max key: %s, value: %d\n",node->key,node->value);
	}
    }
    //exp5
    //exp6
    printf("\nEXP 6\n");
    int colizeon = 0;
    hashtab_init(hashtab2);
    hashtab_init(hashtab3);
    for(int i = 1;i<=n;i++){
	hashtab_add(hashtab2,words[i],i-1,"KRhash");
	hashtab_add(hashtab3,words[i],i-1,"Jenkinshash");
	if(i%10000 == 0){
	    colizeon=0;
	    char* w = words[getRand(0, i-1)];
	    double t = 0.0;
	    clock_t begin=clock();
	    node2 = hashtab_lookup(hashtab2,w,"KRhash");
	    clock_t end=clock();
	    t+=(double)(end-begin)/ CLOCKS_PER_SEC;
	    printf("KRHASH n = %d; time = %.10lf \n", i, t);
	    for (int j = 0; j < i; j++)
            {
                if (hashtab2[j] != NULL)
                    colizeon++;
            }
	    printf("KRHash colizeon = %d\n", i - colizeon);
	    double c = wtime();
	    node2 = hashtab_lookup(hashtab3,w,"Jenkinshash");
	    t = wtime() - c;
	    printf("JENCKINS n = %d; time = %.10lf \n", i, t);
	    for (int j = 0; j < i; j++)
            {
                if (hashtab3[j] != NULL)
                    colizeon++;
            }
	    printf("Jenckins colizeon = %d\n", i - colizeon);
	}
    }
    //epx6
    return 0;
}
