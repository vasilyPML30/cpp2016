#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "bmp.h"

int load_msg(const char *file_name, char *msg, int max_len);
int save_msg(const char *file_name, const char *msg);
int insert_msg(const char *key_file_name, const char *msg, bmp *pic);
int extract_msg(const char *key_file_name, char *msg, const bmp *pic);

#endif