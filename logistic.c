/*
 @file:         logistic.c
 @author:       Silversmithe
 @description:  Given a set of presentation groups, determine an order
                for the groups to present using a chaotic function
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000
#define GROUP_SIZE 7

// 3.5 < P < 4 == Chaotic Behavior
const double p = 3.7; 
const double x0 = 0.5;

/*
 @function:     logistic
 @param:        (int) k : the number of iterations for the logistic map
 @param:        (double*) memo : memoized results
 @return:       (double) : value of the logistic function
 */
double logistic(int k, double* memo){
    if(k == 0)
    {
        return memo[0];
    }
    return p * memo[k-1] * ( 1.0 - memo[k-1]);
}

int main(int argc, char* argv[])
{
    int i=1;
    int j=0;
    double result;
    double* memo = malloc(sizeof(double)*SIZE);
    double* order = malloc(sizeof(double)*GROUP_SIZE);
    int* count = malloc(sizeof(int)*GROUP_SIZE);
    int input;

    // init group
    for(i=0;i<GROUP_SIZE; i++) { order[i] = 0; }

    memo[0]=0.5;

    for(i=1; i<SIZE; i++)
    {
        result = logistic(i, memo);
        memo[i]=result;
    }

    printf("values generated, please have groups choose...\n");

    for(i=0; i<GROUP_SIZE; i++)
    {
        printf("Group %d, pick a random number between 1 and %d\n", i+1, SIZE);
        scanf("%d", &input);
        result = memo[input];
        order[i] = result;
    }
    
    /**************
     * PICK ORDER *
     **************/
    int a, b;
    for(a=0; a<GROUP_SIZE; a++){ count[a]=GROUP_SIZE; }
    for(a=0; a<GROUP_SIZE; a++)
    {
        for(b=a+1; b<GROUP_SIZE; b++)
        {
            if(order[a] > order[b])
            { 
                count[b]--; 
            }
            else if(order[a] < order[b])
            {
                count[a]--;
            }
        }
    }

    /***************
     * PRINT TEAMS *
     ***************/
    printf("\nTeam\t|\tValue\t|\tOrder\n");
    printf("_________________________________________\n");
    for(i=0; i<GROUP_SIZE; i++)
    {
        printf("%d\t|\t%f|\t%d\n",i+1, order[i], count[i]);
    }

    printf("Thank you!\n");
    free(memo);
    free(order);
    free(count);

    return EXIT_SUCCESS;
}
