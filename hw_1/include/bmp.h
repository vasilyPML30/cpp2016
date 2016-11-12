#ifndef _BMP_H_
#define _BMP_H_

typedef struct
{
    short bf_type;
    int bf_size, bf_reserved, bf_off_bits;
} bitmap_file_header;

typedef struct
{
    int bi_size, bi_width, bi_height;
    short bi_planes, bi_bit_count;
    int bi_compression, bi_size_image;
    int bi_x_pels_per_meter, bi_y_pels_per_meter;
    int bi_crl_used, bi_crl_important;
} bitmap_core_header;

typedef struct
{
    char b, g, r;
} pixel;

typedef struct
{
    bitmap_file_header file_header;
    bitmap_core_header core_header;
    int padding;
    pixel **data;
} bmp;

int load_bmp(const char *file_name, bmp *pic);
int save_bmp(const char *file_name, const bmp *pic);
int free_bmp(bmp *pic);
int crop(bmp *pic, int x, int y, int w, int h);
int rotate(bmp *pic);

#endif
