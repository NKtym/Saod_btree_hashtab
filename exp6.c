#include <stdio.h>
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
    struct listnode *hashtab3[200000];
    struct listnode *hashtab2[200000];
    struct listnode *node2;
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
	    printf("KRHASH n = %d; time = %.6lf \n", i, t);
	    for (int j = 0; j < i; j++)
            {
                if (hashtab2[j] == NULL)
                    colizeon++;
            }
	    printf("KRHash colizeon = %d\n", colizeon);
	    t = 0.0;
	    begin=clock();
	    node2 = hashtab_lookup(hashtab3,w,"Jenkinshash");
	    end=clock();
	    t+=(double)(end-begin)/ CLOCKS_PER_SEC;
	    printf("JENCKINS n = %d; time = %.6lf \n", i, t);
	    for (int j = 0; j < i; j++)
            {
                if (hashtab3[j] == NULL)
                    colizeon++;
            }
	    printf("Jenckins colizeon = %d\n", colizeon);
	}
    }
    return 0;
}
