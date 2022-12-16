#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

#include "table.h"

//#define FILE_NAME
static size_t* shm_ptr;
#define TABLE_FULL  *shm_ptr==TABLE_LIMIT
#define TABLE_EMPTY *shm_ptr==0
#define TABLE_ADD   *shm_ptr+=1
#define TABLE_SUB   *shm_ptr-=1

#define TABLE_Q 1

static int msqid = 0;

int StartTableWork(const int process)
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

    msqid = msgget(key, proc_flag);
    if (msqid < 0)
    {
        printf("errno = %d\n", errno);
        assert("wrong  msgget" && NULL);
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
    struct mymsgbuf {
        long mtype;
        type_t type;
    } mybuf;
    mybuf.type = type;
    mybuf.mtype = TABLE_Q;

    int tmp = msgsnd(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf.type), 0);
    if(tmp < 0)
    {
        printf ("errno = %d, dish is %u\n", errno, type);
        assert("wrong msgsnd" && NULL);
    }

    TABLE_ADD;

    printf ("on the table %d dishes\n", *shm_ptr);

    return 0;
}

type_t TakeDish ()
{
    struct mymsgbuf {
        long mtype;
        type_t type;
    } mybuf;
    mybuf.mtype = TABLE_Q;
    mybuf.type = 0;

    int tmp = msgrcv (msqid, (struct msgbuf *) &mybuf, sizeof(mybuf.type), 0, 0);
    if (tmp < 0)
    {
        assert ("wrong msgrcv" && NULL);
    }

    TABLE_SUB;

    return mybuf.type;
}