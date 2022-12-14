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
#include <unistd.h>

//#include "file_work.h"

#include "table.h"

#define FILE_NAME "/home/princep/PROGS/Computers_teq/TaskTwoZadavalnik/TheOne/file" 

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

static int semid = 0;

static int sem_op(int i, int op)               
{
    struct sembuf mybuf = {};

    printf ("semid = %d, sem_num = %d, sem_op = %d \n", semid, i, op);
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

int StartTableWork (const int process)
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

    switch (process)
    {
    case WASHER_P:
        A(FREE, TABLE_LIMIT);
        break;

    case WHIPER_P:
        break;

    default:
        assert ("undefined process!" && NULL);
        break;
    }

    return 0;
}

int WaitingWhileTableFull ()
{
    P(FREE);

    return 0;
}

int WaitingWhileTableEmpty  ()
{
    P(FILLED);

    return 0;
}

int PutDish (const type_t type)
{
    PushDish(type);

    V(FILLED);

    return 0;
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
    //printf("i am push dish %u\n", type);

    SentTypesArray(table);

    return 0;
}

static type_t PopDish ()
{
    types_array table = GetTypesArray();
    
    printf ("i recieved table with %d dishes:\n", table.num);
    printf ("%s\n", (char*)table.types);
    table.num--;
    //*((char*)(table.types + table.num + 1)) = '=';
    //printf ("table.num = %d\n", table.num);
    //printf ("%d symbols-->%s\n", table.num*sizeof(type_t), table.types);
    type_t result = table.types[table.num];
    //table.num--;
    SentTypesArray(table);
    printf("i poped dish %u\n", result);
    
    return result;
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
    if (file_sz < 0)
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

    //printf("%d\n", buffer_sz/sizeof(type_t));
    
    types_array result = {buf, buffer_sz/sizeof(type_t)};
    return result;
}

static int SentTypesArray (const types_array table)
{
    FILE *file = fopen("file", "w");
    fclose(file);
    
    int file_id = open (FILE_NAME, O_WRONLY);
    if (file_id == -1)
    {
        assert ("File not opened!" && NULL);
    }
    printf ("on the table %d dishes before writing", table.num);
    int writen_sz = write(file_id, (char*)table.types, table.num*sizeof(type_t));
    if (writen_sz != table.num*sizeof(table.types[0]))
    {
        assert ("Sizes are diiferentf" && NULL);
    }

    printf ("i wrote %d bytes\n", writen_sz);
    //printf("%s\n", (char*)table.types);

    if (close (file_id) == -1)
    {
        printf("Bad closing\n");
    }
    
    return writen_sz;
} 
