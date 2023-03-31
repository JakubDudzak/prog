#include <stdlib.h>
#include "bmp.h"

int main(){
    FILE* fp = fopen("../file.bmp", "r");
    FILE* fw = fopen("../file2.bmp", "wb");
    bmp_image* image = read_bmp(fp);

    write_bmp(fw,image);
    free_bmp_image(image);
    fclose(fp);
    fclose(fw);
    return 0;
}