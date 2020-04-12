#pragma once

#include <iostream>
#include <vector>
#include <assert.h>
#include <cmath>
#include <png++/png.hpp>
#include "mpi.h"


typedef std::vector<double> Array;
typedef std::vector<Array> Image;

Matrix createKernel(int, int);

Image loadImage(const char*);

void saveImage(Image&, const char*);

Image applyFilter(Image&, Image &filter, int, int, int, int);

