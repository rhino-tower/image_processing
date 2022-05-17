#ifndef IMAGE_FILTER_H
#define IMAGE_FILTER_H

#include <math.h>

#include "my_jpeg.h"

BITMAPDATA_t gray_scale(BITMAPDATA_t);

// smoothing
void print_filter(double *, int);
BITMAPDATA_t average_filter(BITMAPDATA_t, int);
BITMAPDATA_t gaussian_filter(BITMAPDATA_t, int, double);
BITMAPDATA_t bilateral_filter(BITMAPDATA_t, int, double, double);

#endif
