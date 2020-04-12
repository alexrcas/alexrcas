#pragma once

#include <iostream>
#include <vector>
#include <assert.h>
#include <cmath>
#include <png++/png.hpp>
#include "omp.h"


typedef std::vector<double> Array;
typedef std::vector<Array> Matrix;
typedef std::vector<Matrix> Image;

Matrix createKernel(int, int);

Image loadImage(const char*);

void saveImage(Image&, const char*);

Image applyFilter(Image&, Matrix &filter);

