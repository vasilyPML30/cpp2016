#include "bmp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

pixel **new_array(int w, int h)
{
    int padding = (4 - sizeof(pixel) * w % 4) % 4;
    char *data = (char *)malloc((sizeof(pixel) * w + padding) * h);
    if (data == NULL)
        return NULL;
    memset(data, 0, (sizeof(pixel) * w + padding) * h);
    pixel **array = (pixel **)malloc(sizeof(pixel *) * h);
    if (array == NULL)
        return NULL;
    for (int i = 0; i < h; i++)
        array[i] = (pixel *)(data + i * (w * sizeof(pixel) + padding));
    return array;
}

int load_bmp(const char *file_name, bmp *pic)
{
    FILE *file;
    file = fopen(file_name, "rb");
    if (file == NULL)
        return 1;
    fread(&pic->file_header.bf_type, sizeof(short), 1, file);
    if (ferror(file) != 0)
        return 1;
    fread(&pic->file_header.bf_size, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fread(&pic->file_header.bf_reserved, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fread(&pic->file_header.bf_off_bits, sizeof(int), 1, file);

    fread(&pic->core_header.bi_size, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fread(&pic->core_header.bi_width, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fread(&pic->core_header.bi_height, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fread(&pic->core_header.bi_planes, sizeof(short), 1, file);
    if (ferror(file) != 0)
        return 1;
    fread(&pic->core_header.bi_bit_count, sizeof(short), 1, file);
    if (ferror(file) != 0)
        return 1;
    fread(&pic->core_header.bi_compression, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fread(&pic->core_header.bi_size_image, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fread(&pic->core_header.bi_x_pels_per_meter, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fread(&pic->core_header.bi_y_pels_per_meter, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fread(&pic->core_header.bi_crl_used, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fread(&pic->core_header.bi_crl_important, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    pic->padding = (4 - sizeof(pixel) * pic->core_header.bi_width % 4) % 4;
    pic->data = new_array(pic->core_header.bi_width, pic->core_header.bi_height);
    if (pic->data == NULL)
        return 1;
    fread(pic->data[0], sizeof(char), (pic->core_header.bi_width * sizeof(pixel) + pic->padding) * pic->core_header.bi_height, file);
    if (ferror(file) != 0)
        return 1;
    fclose(file);
    return 0;
}

int save_bmp(const char *file_name, const bmp *pic)
{
    FILE *file;
    file = fopen(file_name, "wb");
    if (file == NULL)
        return 1;

    fwrite(&pic->file_header.bf_type, sizeof(short), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->file_header.bf_size, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->file_header.bf_reserved, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->file_header.bf_off_bits, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->core_header.bi_size, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->core_header.bi_width, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->core_header.bi_height, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->core_header.bi_planes, sizeof(short), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->core_header.bi_bit_count, sizeof(short), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->core_header.bi_compression, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->core_header.bi_size_image, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->core_header.bi_x_pels_per_meter, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->core_header.bi_y_pels_per_meter, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->core_header.bi_crl_used, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(&pic->core_header.bi_crl_important, sizeof(int), 1, file);
    if (ferror(file) != 0)
        return 1;
    fwrite(pic->data[0], sizeof(char), (sizeof(pixel) * pic->core_header.bi_width + pic->padding) * pic->core_header.bi_height, file);  
    if (ferror(file) != 0)
        return 1;
    fclose(file);
    return 0;
}

int free_bmp(bmp *pic)
{
    free(pic->data[0]);
    free(pic->data);
    return 0;
}

int crop(bmp *pic, int x, int y, int w, int h)
{
    int new_padding = (4 - sizeof(pixel) * w % 4) % 4;
    pixel **new_data = new_array(w, h);
    if (new_data == NULL)
        return 1;
    for (int i = 0; i < h; i++)
        memcpy(new_data[i], pic->data[y + i] + x, w * sizeof(pixel));
    if (free_bmp(pic) != 0)
        return 1;

    pic->data = new_data;
    pic->padding = new_padding;
    pic->file_header.bf_size = pic->file_header.bf_off_bits + h * (w * sizeof(pixel) + pic->padding);
    pic->core_header.bi_size_image = h * (w * sizeof(pixel) + pic->padding);
    pic->core_header.bi_width = w;
    pic->core_header.bi_height = h;
    return 0;
}

int rotate(bmp *pic)
{
    int new_w = pic->core_header.bi_height;
    int new_h = pic->core_header.bi_width;
    int new_padding = (4 - sizeof(pixel) * new_w % 4) % 4;

    pixel **new_data = new_array(new_w, new_h);
    if (new_data == NULL)
        return 1;
    for (int i = 0; i < new_h; i++)
        for (int j = 0; j < new_w; j++)
            new_data[new_h - i - 1][j] = pic->data[j][i];
    if (free_bmp(pic) != 0)
        return 1;
    pic->data = new_data;
    pic->padding = new_padding;
    pic->file_header.bf_size = pic->file_header.bf_off_bits + new_h * (new_w * sizeof(pixel) + pic->padding);
    pic->core_header.bi_size_image = new_h * (new_w * sizeof(pixel) + pic->padding);
    pic->core_header.bi_width = new_w;
    pic->core_header.bi_height = new_h;
    return 0;
}
