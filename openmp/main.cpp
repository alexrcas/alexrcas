#include "image.hpp"

int main()
{
    Matrix filter = createKernel(5, 5);

    Image image = loadImage("image.png");

    double start_time = omp_get_wtime();
    Image newImage = applyFilter(image, filter);
    double time = omp_get_wtime() - start_time;

    std::cout << "Execution time: " << time << std::endl;
    saveImage(newImage, "newImage.png");
}