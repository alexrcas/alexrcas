#include "image.hpp"


Matrix createKernel(int height, int width)
{
    Matrix kernel(height, Array(width));
    double sum=0.0;

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            kernel[i][j] = 1; 
            sum += kernel[i][j];
        }

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            kernel[i][j] /= sum;

    return kernel;
}


Image loadImage(const char *filename)
{
    png::image<png::gray_pixel> image(filename);
    Image imageMatrix(1, Matrix(image.get_height(), Array(image.get_width())));

    for (int height = 0; height < image.get_height(); height++)
        for (int width = 0; width < image.get_width() ; width++)
            imageMatrix[0][height][width] = image[height][width];

    return imageMatrix;
}

void saveImage(Image &image, const char *filename)
{
    int height = image[0].size();
    int width = image[0][0].size();

    png::image<png::gray_pixel> imageFile(width, height);

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            imageFile[y][x] = image[0][y][x];

    imageFile.write(filename);
}

Image applyFilter(Image &image, Matrix &filter)
{
    int height = image[0].size();
    int width = image[0][0].size();
    int filterHeight = filter.size();
    int filterWidth = filter[0].size();
    int newImageHeight = height - filterHeight+1;
    int newImageWidth = width - filterWidth+1;

    Image newImage(3, Matrix(newImageHeight, Array(newImageWidth)));

        #pragma omp parallel for
        for (int i = 0; i < newImageHeight; i++)
            for (int j = 0; j < newImageWidth; j++)
                for (int h = i; h < i + filterHeight; h++)
                    for (int w = j; w < j+filterWidth; w++)
                        newImage[0][i][j] += filter[h-i][w-j]*image[0][h][w];

    return newImage;
}

