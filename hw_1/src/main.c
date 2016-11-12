#include "message.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    bmp pic;
    int x, y, w, h;
    if (argc < 2)
        return 1;
    if (strcmp(argv[1], "crop-rotate") == 0)
    {
        if (argc != 8)
            return 1;
        if (load_bmp(argv[2], &pic) != 0)
            return 1;
        x = strtol(argv[4], NULL, 10);
        y = strtol(argv[5], NULL, 10);
        w = strtol(argv[6], NULL, 10);
        h = strtol(argv[7], NULL, 10);
        if (x < 0 || pic.core_header.bi_width < x + w || y < 0 || pic.core_header.bi_height < y + h)
            return 1;
        y = pic.core_header.bi_height - y - h;
        if (crop(&pic, x, y, w, h) != 0)
            return 1;
        if (rotate(&pic) != 0)
            return 1;
        if (save_bmp(argv[3], &pic) != 0)
            return 1;
        if (free_bmp(&pic) != 0)
            return 1;
    }
    else if (strcmp(argv[1], "insert") == 0)
    {
        if (argc != 6)
            return 1;
        if (load_bmp(argv[2], &pic) != 0)
            return 1;
        char *msg;
        int max_len = pic.core_header.bi_width * pic.core_header.bi_height;
        if ((msg = (char *)malloc(max_len)) == NULL)
            return 1;
        memset(msg, 0, max_len);
        if (load_msg(argv[5], msg, max_len) != 0)
            return 1;
        if (insert_msg(argv[4], msg, &pic))
            return 1;
        if (save_bmp(argv[3], &pic))
            return 1;
        if (free_bmp(&pic) != 0)
            return 1;
        free(msg);
    }
    else if (strcmp(argv[1], "extract") == 0)
    {
        if (argc != 5)
            return 1;
        if (load_bmp(argv[2], &pic) != 0)
            return 1;
        char *msg;
        int max_len = pic.core_header.bi_width * pic.core_header.bi_height;
        if ((msg = (char *)malloc(max_len)) == NULL)
            return 1;
        memset(msg, 0, max_len);
        if (extract_msg(argv[3], msg, &pic) != 0)
            return 1;
        if (save_msg(argv[4], msg))
            return 1;
        if (free_bmp(&pic) != 0)
            return 1;
        free(msg);
    }
    else
        return 1;
    return 0;
}
