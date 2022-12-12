#ifndef FILE_WORK_H_INCLUDED
#define FILE_WORK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <string.h>

char*   my_fread    (const char * file_name);

int     my_fprintf  (const char * file_name, const char * str);   

#endif 