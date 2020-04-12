#include "image.hpp"

int main(int argc, char** argv)
{
    int rank, size, tag, rc, i;
    MPI_Status status;
    rc = MPI_Init(&argc, &argv);
    rc = MPI_Comm_size(MPI_COMM_WORLD, &size);
    rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    tag = 100;
    int height, width, heightInc, widthInc;
    Image image;
    image = loadImage("image.png");
    Matrix filter = createKernel(5, 5);

    if(rank == 0)
    {
        height = image[0].size();
        width = image[0][0].size();

        heightInc = height / size;
        widthInc = width / size;

        
        for (int i = 1; i < size; i++)
        {
            //std::cout << k << std::endl;
            MPI_Send(&heightInc, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
            MPI_Send(&widthInc, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
        }
    }
    else
    {

        MPI_Recv(&heightInc, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(&widthInc, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

        int infLimitH = rank * heightInc;
        int supLimitH = infLimitH + heightInc;
        
        int infLimitW = rank * widthInc;
        int supLimitW = infLimitW + widthInc;

        Image newImage = applyFilter(image, filter, infLimitH, supLimitH, infLimitW, supLimitW);

       // std::cout << infLimit << ", " << supLimit << std::endl;
    }


    MPI_Finalize();

    // Image newImage = applyFilter(image, filter);

    // std::cout << "Execution time: " << time << std::endl;
    // saveImage(newImage, "newImage.png");
}
o
