#include "image_filter.h"

BITMAPDATA_t gray_scale(BITMAPDATA_t bitmap){
	BITMAPDATA_t output;
	int i, j, c;
	int sum, ave;

	output.data = malloc(sizeof(unsigned char) * bitmap.height * bitmap.width * bitmap.ch);
	output.ch = bitmap.ch;
	output.height = bitmap.height;
	output.width = bitmap.width;

	/* グレースケールに変換 */
	for(j = 0; j < bitmap.height; j++){
		for(i = 0; i < bitmap.width; i++){
			sum = 0;
			for(c = 0; c < bitmap.ch; c++){
				sum += bitmap.data[bitmap.ch * (i + j * bitmap.width) + c];
			}
			ave = sum / bitmap.ch;
			for(c = 0; c < bitmap.ch; c++){
				output.data[bitmap.ch * (i + j * bitmap.width) + c] = ave;
			}
		}
	}
	return output;
}
