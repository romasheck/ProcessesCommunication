//#ifndef TABLE_SEMAFOR_INCLUDED
//#define TABLE_SEMAFOR_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <inttypes.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>

//#include "file_work.h"

#include "table.h"

#define FILE_NAME "file"

//size_t num_dishes_on_table = 0;

//prototypes of static funcs for work with file like stack
typedef struct
{
    type_t* types;
    size_t num;
} types_array;
static int          PushDish        (const type_t type);
static type_t       PopDish         ();
static types_array  GetTypesArray   ();
static int          SentTypesArray  (const types_array table);

/*************************WORK_WITH_SEMAFS*********************************/

struct sembuf mybuf; 

static int semid = 0;

static int sem_op(int i, int op)               
{
    mybuf.sem_flg = 0;                  
    mybuf.sem_num = i;                  
    mybuf.sem_op = op;                  
    if (semop(semid, &mybuf, 1) < 0)    
    {                                   
        assert("wrong semop" && NULL);  
    }
}

#define V(S)    sem_op(S, 1)
#define P(S)    sem_op(S, -1)
#define A(S, n) sem_op(S, n)

enum SEMAFS
{
    FILLED = 0,
    FREE = 1,
};

int StartTableWork ()
{
    key_t key = ftok(FILE_NAME, 0);
    if (key < 0)
    {
        assert("wrong ftok" && NULL);
    }

    semid = semget(key, 2, 0666 | IPC_CREAT);
    if (semid < 0)
    {
        assert("wrong semget" && NULL);
    }

    A(FREE, TABLE_LIMIT);
}

int WaitingWhileTableFull ()
{
    P(FREE);
}

int WaitingWhileTableEmpty  ()
{
    P(FILLED);
}

int PutDish (const type_t type)
{
    PushDish(type);

    V(FILLED);
}

type_t TakeDish ()
{
    V(FREE);

    return PopDish();
}


/*************************WORK_WITH_FILE*********************************/


static int PushDish (const type_t type)
{
    types_array table = GetTypesArray();
    table.types[table.num] = type;
    table.num++;
    SentTypesArray(table);

    return 0;
}

static type_t PopDish ()
{
    types_array table = GetTypesArray();
    table.num--;
    SentTypesArray(table);

    return table.types[table.num + 1];
}

static types_array GetTypesArray ()
{
    int file_id = open (FILE_NAME, O_RDONLY);
    if (file_id == -1)
    {
        assert ("File not opened!" && NULL);
    }

    struct stat FileInfo;
    stat(FILE_NAME, &FileInfo);
    int file_sz = FileInfo.st_size;
    if (file_sz < 1)
    {
        assert ("Empty file" && NULL);
    }

    type_t* buf = (type_t*) calloc(file_sz + 1 + sizeof(type_t), sizeof(char));

    int buffer_sz = read(file_id, (char*)buf, file_sz);
    if (buffer_sz != file_sz)
    {
        assert ("Sizes are diiferentf" && NULL);
    }

    if (close (file_id) == -1)
    {
        printf("Bad closing\n");
    }
    if (buffer_sz % sizeof(type_t) != 0)
    {
        assert("whaaaaaat" && NULL);
    }
    //printf("%s", buf);
    types_array result = {buf, buffer_sz/sizeof(type_t)};
    return result;
}

static int SentTypesArray (const types_array table)
{
    int file_id = open (FILE_NAME, O_WRONLY);
    if (file_id == -1)
    {
        assert ("File not opened!" && NULL);
    }

    /*struct stat FileInfo;
    stat(FILE_NAME, &FileInfo);
    int file_sz = FileInfo.st_size;
    if (file_sz < 1)
    {
        assert ("Empty file" && NULL);
    }*/

    int writen_sz = write(file_id, (char*)table.types, table.num);
    if (writen_sz != table.num)
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
/*
int TableStatus ()
{
    if (num_dishes_on_table < 0)
    {
        assert ("wrong num_dishes_on_yhe_table" && NULL);
    }
    if (num_dishes_on_table == 0)
    {
        return EMPTY;
    }
    else
    {
        if (num_dishes_on_table < TABLE_LIMIT)
        {
            return NOT_ENF;
        }
        else 
        {
            return FULL;
        }
    } 
}
*/
//#endif