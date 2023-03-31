#include <stdlib.h>
#include "bmp.h"



bmp_header* read_bmp_header(FILE* stream){
    bmp_header* info = calloc(1,sizeof (bmp_header));
    fread(&info->type, sizeof (info->type), 1, stream);
    if(info->type != 0x4D42)
        return NULL;
    fread(&info->size, sizeof (info->size), 1, stream);
    fread(&info->reserved1, sizeof (info->reserved1), 1, stream);
    fread(&info->reserved2, sizeof (info->reserved2), 1, stream);
    fread(&info->offset, sizeof (info->offset), 1, stream);
    fread(&info->dib_size, sizeof (info->dib_size), 1, stream);
    fread(&info->width, sizeof (info->width), 1, stream);
    fread(&info->height, sizeof (info->height), 1, stream);
    fread(&info->planes, sizeof (info->planes), 1, stream);
    fread(&info->bpp, sizeof (info->bpp), 1, stream);
    fread(&info->compression, sizeof (info->compression), 1, stream);
    fread(&info->image_size, sizeof (info->image_size), 1, stream);
    fread(&info->x_ppm, sizeof (info->x_ppm), 1, stream);
    fread(&info->y_ppm, sizeof (info->y_ppm), 1, stream);
    fread(&info->num_colors, sizeof (info->num_colors), 1, stream);
    fread(&info->important_colors, sizeof (info->important_colors), 1, stream);
    return(info);
}
pixel* read_data(FILE* stream, const bmp_header* header){
    if(header==NULL) {
        fprintf(stderr, "Error: This is not a BMP file.\n");
        return NULL;
    }
    pixel* data = calloc(sizeof (pixel),header->width*header->height);
    //fseek(stream,8*14,SEEK_SET);
    int j = 0;
    int i = 0;
    int width = header->width;
    int height = header->height;
    for ( i = 0; i <height; ++i) {
        //fseek(stream,header->width,SEEK_CUR);
        fseek(stream,header->width,SEEK_END-(header->width*i));
        for (; j < width; ++j) {
            fread(&data->red   , sizeof (data->blue), 1, stream);
            fread(&data->green, sizeof (data->green), 1, stream);
            fread(&data->blue, sizeof (data->red), 1, stream);
            fseek(stream,sizeof (data->blue),SEEK_CUR);
        }
    }
    return data;
}
bmp_image* read_bmp(FILE* stream){
    if(stream == NULL){
        fprintf(stderr, "readbmpstreamsnullError: This is not a BMP file.\n");
        exit(EXIT_FAILURE);
    }
    bmp_image* image = calloc(1, sizeof(bmp_image));
    image->header = read_bmp_header(stream);
    if (image->header==NULL)
        fprintf(stderr, "readbmpheadersnullError: This is not a BMP file.\n");
    image->data = read_data(stream,image->header);
    if (image->data==NULL)
        fprintf(stderr, "Error: Corrupted BMP file.\n");
    return image;

}
bool write_bmp(FILE* stream, const bmp_image* image){
    if((stream == NULL)||(image == NULL))
        return false;
    fwrite(&image->header->type, sizeof (image->header->type), 1, stream);
    //printf("%x",image->header->type);
    fwrite(&image->header->size, sizeof (image->header->size), 1, stream);
    fwrite(&image->header->reserved1, sizeof (image->header->reserved1), 1, stream);
    fwrite(&image->header->reserved2, sizeof (image->header->reserved2), 1, stream);
    fwrite(&image->header->offset, sizeof (image->header->offset), 1, stream);
    fwrite(&image->header->dib_size, sizeof (image->header->dib_size), 1, stream);
    fwrite(&image->header->width, sizeof (image->header->width), 1, stream);
    fwrite(&image->header->height, sizeof (image->header->height), 1, stream);
    fwrite(&image->header->planes, sizeof (image->header->planes), 1, stream);
    fwrite(&image->header->bpp, sizeof (image->header->bpp), 1, stream);
    fwrite(&image->header->compression, sizeof (image->header->compression), 1, stream);
    fwrite(&image->header->image_size, sizeof (image->header->image_size), 1, stream);
    fwrite(&image->header->x_ppm, sizeof (image->header->x_ppm), 1, stream);
    fwrite(&image->header->y_ppm, sizeof (image->header->y_ppm), 1, stream);
    fwrite(&image->header->num_colors, sizeof (image->header->num_colors), 1, stream);
    fwrite(&image->header->important_colors, sizeof (image->header->important_colors), 1, stream);
    pixel * data = image->data;
    for (int i = 0; i < image->header->height; i++) {
        for (int j = 0; j < image->header->width; j++,data += sizeof (image->data->blue)*3) {
            fwrite(&data->blue, sizeof (image->data->blue), 1, stream);
            fwrite(&data->green, sizeof (image->data->blue), 1, stream);
            fwrite(&data->red, sizeof (image->data->blue), 1, stream);
        }
    }
    //fwrite(&image->header, sizeof(image->header),1,stream);
    //fwrite(&image->data, sizeof(image->data),1,stream);
    return true;
}
/*
int main(){
    FILE* fp = fopen("../file.bmp", "r");
    FILE* fw = fopen("../file2.bmp", "wb");
    bmp_image* image = read_bmp(fp);
    bmp_image* image2 = malloc(sizeof image);
    free(image);
    fclose(fp);
    fclose(fw);
    //unsigned char x = fgetc(stream);
    //putchar(x);
    //fseek(stream,0,SEEK_SET);
    */
/*
    fseek(stream, -5,0);
    read_bmp_header(stream);*//*

    return 0;
}*/
void free_bmp_image(bmp_image* image){
    free(image);
}