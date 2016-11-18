/******************************************************************************
* FILE: mpi_hello.c
* DESCRIPTION:
*   MPI tutorial example code: Simple hello world program
* AUTHOR: Blaise Barney
* LAST REVISED: 03/05/10
******************************************************************************/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define MASTER 0

int main(int argc, char *argv[])
{
    int numtasks, taskid, len, claimed;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Get_processor_name(hostname, &len);
    MPI_Query_thread(&claimed);
    printf("nivel de hilos: %d\n", claimed);
    printf("rango:%d\n", taskid);
    if (!(taskid % 2))
        printf("processor name: %s\n", hostname);

    if (taskid == MASTER)
        printf("yo soy el maestro total tareas:%d\n", numtasks);
    MPI_Finalize();
}
