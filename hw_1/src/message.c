#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int load_msg(const char *file_name, char *msg, int max_len)
{
    FILE *file;
    file = fopen(file_name, "rt");
    if (file == NULL)
        return 1;
    if (fgets(msg, max_len, file) == NULL)
        return 1;
    fclose(file);
    return 0;
}

int save_msg(const char *file_name, const char *msg)
{
    FILE *file;
    file = fopen(file_name, "wt");
    if (file == NULL)
        return 1;
    if (fputs(msg, file) == EOF)
        return 1;
    fclose(file);
    return 0;
}

int get_code(char c)
{
    if (isalpha(c))
        return c - 'A';
    else if (c == ' ')
        return 26;
    else if (c == '.')
        return 27;
    else if (c == ',')
        return 28;
    return -1;
}

char get_symbol(int code)
{
    if (code < 26)
        return (char)('A' + code);
    else if (code == 26)
        return ' ';
    else if (code == 27)
        return '.';
    else if (code == 28)
        return ',';
    return 0;
}

int insert_msg(const char *key_file_name, const char *msg, bmp *pic)
{
    FILE *file;
    file = fopen(key_file_name, "rt");
    if (file == NULL)
        return 1;
    for (int i = 0; msg[i]; i++)
    {
        int code = get_code(msg[i]);
        if (code < 0)
            return 1;
        for (int b = 0; b < 5; b++)
        {
            int x, y;
            char cmp;
            if (fscanf(file, "%i %i %c", &x, &y, &cmp) == EOF)
                return 1;
            y = pic->core_header.bi_height - y - 1;
            if (cmp == 'r')
            {
                pic->data[y][x].r &= ~(char)0 - 1;
                pic->data[y][x].r |= ((code >> b) & 1);
            }
            else if (cmp == 'g')
            {
                pic->data[y][x].g &= ~0 - 1;
                pic->data[y][x].g |= ((code >> b) & 1);
            }
            else if (cmp == 'b')
            {
                pic->data[y][x].b &= ~0 - 1;
                pic->data[y][x].b |= ((code >> b) & 1);
            }
        }
    }
    fclose(file);
    return 0;
}

int extract_msg(const char *key_file_name, char *msg, const bmp *pic)
{
    FILE *file;
    file = fopen(key_file_name, "rt");
    if (file == NULL)
        return 1;
    int pos = 0;
    while (true)
    {
        int code = 0;
        for (int b = 0; b < 5; b++)
        {
            int x, y;
            char cmp;
            if (fscanf(file, "%i %i %c", &x, &y, &cmp) == EOF)
            {
                if (feof(file))
                    break;
                else
                    return 1;
            }
            y = pic->core_header.bi_height - y - 1;
            if (cmp == 'r')
                code |= ((pic->data[y][x].r & 1) << b);
            else if (cmp == 'g')
                code |= ((pic->data[y][x].g & 1) << b);
            else if (cmp == 'b')
                code |= ((pic->data[y][x].b & 1) << b);
        }
        if (feof(file))
            break;
        char symbol = get_symbol(code);
        if (!symbol)
            return 1;
        msg[pos++] = symbol;
    }
    fclose(file);
    return 0;
}
