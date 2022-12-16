#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/stat.h>

#include "table.h"

#define FIFO_NAME "tmp/table_fifo"

static size_t* shm_ptr;
#define TABLE_FULL  *shm_ptr==TABLE_LIMIT
#define TABLE_EMPTY *shm_ptr==0
#define TABLE_ADD   *shm_ptr+=1
#define TABLE_SUB   *shm_ptr-=1

int fd;

int StartTableWork (const int process)
{

    key_t key = ftok(FILE_NAME, 0);
    if (key< 0)
    {
        assert ("wrong ftolk" && NULL);
    }

    int proc_flag = 0;
    switch (process)
    {
    case WASHER_P:
        proc_flag = 0666 | IPC_CREAT;
        break;

    case WHIPER_P:
        proc_flag = 0;
        break;

    default:
        assert ("undefined process!" && NULL);
        break;
    }

    int shmid = shmget (key, sizeof(size_t), proc_flag);
    if (shmid < 0)
    {
        printf ("errno = %d\n",  errno);
        assert ("wrong shmget" && NULL);
    }

    shm_ptr = (size_t*)shmat(shmid, NULL, 0);
    if (shm_ptr < 0)
    {
        assert("wrong shmat" && NULL);
    }

    fd = open (FIFO_NAME, O_WRONLY);
    if (fd < 0)
    {
        assert("wrong fifo opening");
    }

    return 0;
}

int WaitingWhileTableFull ()
{
    while (TABLE_FULL);

    return 0;
}

int WaitingWhileTableEmpty ()
{
    printf ("on the table %d dishes\n", *shm_ptr);
    while (TABLE_EMPTY);

    return 0;
}

int PutDish (const type_t type)
{
    int written_sz = write (fd, &type, sizeof(type));
    if(written_sz != sizeof(type))
    {
        assert("written sizes different" && NULL);
    }

    TABLE_ADD;

    printf("on the table %d dishes\n", *shm_ptr);

    return 0;
}

type_t TakeDish ()
{
    type_t res = 0;
    
    int red_sz = read (fd, &res, sizeof(res));
    if(red_sz = sizeof(res))
    {
        assert("red sizes different" && NULL);
    }

    TABLE_SUB;

    return res;
}