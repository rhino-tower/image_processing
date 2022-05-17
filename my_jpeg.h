#ifndef MY_JPEG_H
#define MY_JPEG_H

#include <stdio.h>
#include <stdlib.h>

#include "jpeg-9e/jpeglib.h"

typedef struct {
	unsigned char *data;
	unsigned int width;
	unsigned int height;
	unsigned int ch;
} BITMAPDATA_t;

int jpegFileReadDecode(BITMAPDATA_t *, const char*);
int jpegFileEncodeWrite(BITMAPDATA_t *, const char*);
int freeBitmapData(BITMAPDATA_t *);

#endif
