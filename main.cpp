#include "image.hpp"

int main(int argc, char* argv[])
{

    int rank, size;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

	
    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Get_processor_name(processor_name, &namelen);


    if (rank == 0)
    {
        Image filter = createKernel(5, 5);
        Image image = loadImage("image.png");
        Image newImage = applyFilter(image, filter);
        saveImage(newImage, "newImage.png");
    }
/*
    double start_time = omp_get_wtime();
    Image newImage = applyFilter(image, filter);
    double time = omp_get_wtime() - start_time;

    std::cout << "Execution time: " << time << std::endl;
    saveImage(newImage, "newImage.png");*/

    MPI_Finalize();
}