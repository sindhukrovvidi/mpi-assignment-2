#include <stdio.h>
#include <stdlib.h>
#include<mpi.h>
struct bucket
{
    int count;
    int* value;
};
int compareIntegers(const void* first, const void* second)
{
    int x = *((int*)first), y =  *((int*)second);
    if (x == y)
    {
        return 0;
    }
    else if (x < y)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
void bucketSort(int a[],int n)
{
    struct bucket arrays[3];
    int i, j, k;
    for (i = 0; i < 3; i++)
    {
        arrays[i].count = 0;
        arrays[i].value = (int*)malloc(sizeof(int) * n);
    }

    for (i = 0; i < n; i++)
    {
        if (a[i] < 0)
        {
            arrays[0].value[arrays[0].count++] = a[i];
        }
        else if (a[i] > 10)
        {
            arrays[2].value[arrays[2].count++] = a[i];
        }
        else
        {
            arrays[1].value[arrays[1].count++] = a[i];
        }
    }
    for (k = 0, i = 0; i < 3; i++)
    {
        qsort(arrays[i].value, arrays[i].count, sizeof(int), &compareIntegers);
        for (j = 0; j <arrays[i].count; j++)
        {
            a[k + j] = arrays[i].value[j];
        }
        k += arrays[i].count;
        free(arrays[i].value);
    }
}
int main(int argc,char *arg[]) {
    int size,rank,no,i=12,j,k,n;
    n=i;
    int a[20] = {5,34,56,32,-1,-99,89,45,67,13,-13,43,60,12,4,30,-7,9,1,20 };
    MPI_Init(NULL,NULL);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank==0){
	    printf("Numbers before sorting: ");
	    for (j = 0; j<i; j++)
	    {
		printf("%d ", a[j]);
	    }
	    MPI_Send(&a,1,MPI_INT,1,1,MPI_COMM_WORLD);
    }
    else{
	MPI_Recv(&a,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
    	bucketSort(a, n);
    	printf("\nNumbers after sorting: ");
    	for (k = 0; k<i; k++)
        	printf("%d ", a[k]);
    }
    printf("\n");
    MPI_Finalize();
return 0;
}
