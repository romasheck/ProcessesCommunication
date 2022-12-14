#include "file_work.h"

char* my_fread (const char * file_name)
{
    int file_id = open (file_name, O_RDONLY);
    if (file_id == -1)
    {
        assert ("File not opened!" && NULL);
    }

    struct stat FileInfo;
    stat(file_name, &FileInfo);
    int file_sz = FileInfo.st_size;
    if (file_sz < 0)
    {
        assert ("Empty file" && NULL);
    }

    char* buf = (char*) calloc(file_sz + 1, sizeof(char));

    int buffer_sz = read(file_id, buf, file_sz);
    if (buffer_sz != file_sz)
    {
        assert ("Sizes are diiferentf" && NULL);
    }

    if (close (file_id) == -1)
    {
        printf("Bad closing\n");
    }
    //printf("%s", buf);
    return buf;
}

int my_fprintf (const char * file_name, const char * str)
{
    int file_id = open (file_name, O_WRONLY);
    if (file_id == -1)
    {
        assert ("File not opened!" && NULL);
    }

    /*struct stat FileInfo;
    stat(file_name, &FileInfo);
    int file_sz = FileInfo.st_size;
    if (file_sz < 1)
    {
        assert ("Empty file" && NULL);
    }*/
    size_t str_sz = strlen(str);

    int writen_sz = write(file_id, file_name, str_sz);
    if (writen_sz != str_sz)
    {
        assert ("Sizes are diiferentf" && NULL);
    }

    if (close (file_id) == -1)
    {
        printf("Bad closing\n");
    }
    //printf("%s", buf);
    return writen_sz;
}