#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int my_rank, p, tag = 0;
    char msg[20];
    char resp[20];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    if (my_rank == 0)
    {
        strcpy(msg, "Hello ");
        MPI_Sendrecv(msg, strlen(msg) + 1, MPI_CHAR, 1, tag, resp, 20, MPI_CHAR, 1, tag, MPI_COMM_WORLD, &status);
        printf("%d: I have sent '%s' to 1\n", my_rank, msg);
        printf("%d: I have received '%s' from 1\n", my_rank, resp);
    }
    else if (my_rank == 1)
    {
        /*
        Un abrazo mortal puede suceder cuando usamos el comando de abajo
        MPI_Recv(msg, 20, MPI_CHAR, 1, tag, MPI_COMM_WORLD, &status);
        En este comando estamos enviando el mensaje al rango 1, que es el mismo que lo envía, por la cual el otro
        hilo se queda esperando por un mensaje que nunca va a llegar, quedando en un estado de deadlock
        */
        MPI_Recv(msg, 20, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
        printf("I have received '%s' from 0\n", msg);
        strcpy(resp, "HELLO ");
        MPI_Send(resp, strlen(resp) + 1, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
        printf("I have sent '%s' to 0\n", resp);
    }
    MPI_Finalize();
}
