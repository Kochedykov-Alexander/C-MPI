#include "mpi.h"
#include "iostream"


int main(int argc, char** argv)
{
    
    int size, proc;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (proc == 0)
    {
        printf("Process -  %d \n", proc);
        int a[10];
        for (int i = 0; i < 10; i++)
            a[i] = rand() % 100;
        printf("Send array, process %d \n", proc);
        for (int i = 1; i < size; i++)
            MPI_Send(&a, 10, MPI_INT, i, 99, MPI_COMM_WORLD);
    }
    else
    {
        printf("Process -  %d \n", proc);
        int b[10];
        printf("%d process print array \n", proc);
        MPI_Recv(&b, 10, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
        for (int i = 0; i < 10; i++)
            printf("b[%d]=%d ", i, b[i]);
    }
    MPI_Finalize();
}