#include "image_filter.h"

void print_filter(double *filter, int size){
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			printf("%f ", filter[i * size + j]);
		}
		puts("");
	}
}

BITMAPDATA_t filtering(BITMAPDATA_t input, double filter[], int size){
	BITMAPDATA_t output;

	output.data = malloc(sizeof(unsigned char) * input.height * input.width * input.ch);
	if (output.data == NULL){
		printf("malloc error\n");
		exit(1);
	}
	output.ch = input.ch;
	output.height = input.height;
	output.width = input.width;

	for (int c = 0; c < input.ch; c++){
		for (int i = size/2; i < input.height - size/2; i++){
			for (int j = size/2; j < input.width - size/2; j++){
				// フィルタリング
				int sum = 0;
				for (int k = -size/2; k <= size/2; k++){
					for (int l = -size/2; l <= size/2; l++){
						sum += filter[(k+size/2)*size + (l+size/2)] * input.data[input.ch * ((i + k) * input.width + (j + l)) + c];
					}
				}
				output.data[input.ch * (i * input.width + j) + c] = sum;
			}
		}
	}
	return output;
}


BITMAPDATA_t average_filter(BITMAPDATA_t input, int size){
	BITMAPDATA_t output;
	double filter[size * size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			filter[i*size + j] = 1.0 / (size * size);

	output = filtering(input, filter, size);

	return output;
}

BITMAPDATA_t gaussian_filter(BITMAPDATA_t input, int size, double sigma){
	BITMAPDATA_t output;
	double filter[size * size];
	double sum = 0;

	for (int x = -size/2; x <= size/2; x++){
		for (int y = -size/2; y <= size/2; y++){
			filter[(x + size/2)*size + (y+size/2)] = (1.0/2*M_PI*sigma*sigma) * exp(-(x*x+y*y)/(2.0*sigma*sigma));
			sum += (1.0/2*M_PI*sigma*sigma) * exp(-(x*x+y*y)/(2.0*sigma*sigma));
		}
	}

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			filter[i * size + j] /= sum;

	output = filtering(input, filter, size);

	return output;
}

BITMAPDATA_t bilateral_filter(BITMAPDATA_t input, int size, double sigma_d, double sigma_r){
	BITMAPDATA_t output;

	output.data = malloc(sizeof(unsigned char) * input.height * input.width * input.ch);
	if (output.data == NULL){
		printf("malloc error\n");
		exit(1);
	}
	output.ch = input.ch;
	output.height = input.height;
	output.width = input.width;

	for (int c = 0; c < input.ch; c++){
		for (int i = size/2; i < input.height - size/2; i++){
			for (int j = size/2; j < input.width - size/2; j++){
				// フィルタリング
				// 分母(denominator)の合計
				double d_sum = 0;
				// 分子(numerator)の合計
				double n_sum = 0;
				for (int k = -size/2; k <= size/2; k++){
					for (int l = -size/2; l <= size/2; l++){
						double w = exp(-(k*k+l*l)/(2*pow(sigma_d, 2)) - pow(input.data[input.ch*(i*input.width+j)+c] - input.data[input.ch*((i+k)*input.width+(j+l))+c], 2)/(2*pow(sigma_r, 2)));

						d_sum += w;
						n_sum += w * input.data[input.ch*((i+k)*input.width+(j+l))+c];
					}
				}
				output.data[input.ch * (i * input.width + j) + c] = (int)(n_sum/d_sum);
			}
		}
	}

	return output;
}
