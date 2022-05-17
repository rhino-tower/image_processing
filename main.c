#include "my_jpeg.h"
#include "image_filter.h"

int main(int argc, char *argv[]){

  BITMAPDATA_t bitmap;
  int i, j, c;
  int ave, sum;
  char outname[256];

  FILE *fo;

  if(argc != 2){
    printf("ファイル名が指定されていません\n");
    return -1;
  }

  if(jpegFileReadDecode(&bitmap, argv[1]) == -1){
    printf("jpegFileReadDecode error\n");
    return -1;
  }

  printf("bitmap->data = %p\n", bitmap.data);
  printf("bitmap->width = %d\n", bitmap.width);
  printf("bitmap->height = %d\n", bitmap.height);
  printf("bitmap->ch = %d\n", bitmap.ch);

#if 0
  /* ちゃんと読み込めているか確認する場合はここを有効に */
  fo = fopen("testoutput.ppm", "wb");
  fprintf(fo, "P6\n#\n%d %d\n255\n", bitmap.width, bitmap.height);
  fwrite(bitmap.data, bitmap.height * bitmap.width * 3, 1,fo);
  fclose(fo);
#endif

  BITMAPDATA_t output = bilateral_filter(bitmap, 7, 3.0, 1.0);

  sprintf(outname, "%s", "output.jpg");

  if(jpegFileEncodeWrite(&output, outname) == -1){
    printf("jpegFileEncodeWrite error\n");
    freeBitmapData(&output);
    return -1;
  }

  freeBitmapData(&bitmap);
  freeBitmapData(&output);

  return 0;
}
