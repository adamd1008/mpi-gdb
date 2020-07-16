#include <stdio.h>
#include <stdlib.h>

#include "mpi_gdb.h"

int main(int argc, char** argv)
{
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
    {
        fprintf(stderr, "Couldn't init MPI\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_GDB_INIT();

    MPI_Finalize();

    return EXIT_SUCCESS;
}
