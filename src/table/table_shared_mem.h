#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

#include "table.h"

//#define FILE_NAME "tmp/file"
/*
typedef struct
{
    int     flag;
    size_t  num;    
    type_t* types;
} types_array;
*/
#define ARRAY_SZ sizeof(int) + sizeof(size_t) + TABLE_LIMIT*sizeof(type_t)
#define PROC_FLAG   *(int*)shm_ptr
#define DISHES_NUM  *(size_t*)(shm_ptr+sizeof(int))
#define DISHES(i)   *((type_t*)(shm_ptr+sizeof(int)+sizeof(size_t))+i)
#define DISHES_STR   (type_t*)(shm_ptr+sizeof(int)+sizeof(size_t))
//static types_array  GetTypesArray   ();
//static int          PushDish        (types_array* dishes_ptr, type_t new_dish);
//static type_t       PopDish         (types_array* dishes_ptr);
static int          PushDish        (type_t new_dish);
static type_t       PopDish         ();
//static size_t       GetDishesNum    ();
//static int          GetProcFlag     ();
//static type_t*      GetDishes       ();

//static int      shmid = 0;
static void*    shm_ptr = NULL; 

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

    int shmid = shmget (key, ARRAY_SZ, proc_flag);
    if (shmid < 0)
    {
        printf ("errno = %d\n",  errno);
        assert ("wrong shmget" && NULL);
    }

    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr < 0)
    {
        assert("wrong shmat" && NULL);
    }

    if (process == WASHER_P)
    {
        for(int i = 0; i < ARRAY_SZ; i++)
        {
            ((char*)shm_ptr)[i] = 0;
        }
    }

    return 0;
}

int WaitingWhileTableFull ()
{
    //types_array dishes;
    /*do
    {
        dishes = GetTypesArray();
    } */
    while (PROC_FLAG == WHIPER_P || DISHES_NUM >= TABLE_LIMIT);
    
    return 0;
}

int WaitingWhileTableEmpty ()
{
    //types_array dishes;
    /*do
    {
        dishes = GetTypesArray();
    }*/ 
    while (PROC_FLAG == WASHER_P || DISHES_NUM <= 0);
    
    return 0;
}

int PutDish (const type_t type)
{
    //types_array dishes = GetTypesArray();
    PROC_FLAG = WASHER_P;
    //printf("before pushing, on the table %d dishes:\n %s\n", DISHES_NUM, (char*)DISHES_STR);
    PushDish(type);
    printf("after pushing, on the table %d dishes:\n %s\n", DISHES_NUM, (char*)DISHES_STR);
    PROC_FLAG = NOT_A_P;
    
    return 0;
}

type_t TakeDish ()
{
    //types_array dishes = GetTypesArray();
    PROC_FLAG = WHIPER_P;
    printf("before poping, on the table %d dishes:\n %s\n", DISHES_NUM, (char*)DISHES_STR);
    type_t res = PopDish();
    //printf("before poping, on the table %d dishes:\n %s\n", DISHES_NUM, (char*)DISHES_STR);
    printf("dish %u was poped\n", res);
    PROC_FLAG = NOT_A_P;
    
    return res;
}
/*
types_array GetTypesArray()
{
    types_array result = {};

    void* shmaddr = shmat (shmid, NULL, 0);
    if (shmaddr == -1)
    {
        assert ("wrong shmat" && NULL);
    }

    result.flag = *(int*)shmaddr;
    result.num = *(size_t*)(shmaddr + sizeof(result.flag));
    result.types = (type_t*)(shmaddr + sizeof(result.flag) + sizeof(result.num));

    if (result.num < 0 || result.num > TABLE_LIMIT)
    {
        assert("wrong size" && NULL);
    }

    return result;
}
*/
int PushDish (type_t new_dish)
{
    DISHES(DISHES_NUM) = new_dish;
    DISHES_NUM+=1;

    return 0;
}

type_t PopDish ()
{
    type_t res = DISHES(DISHES_NUM - 1);

    DISHES_NUM-=1;

    return res; 
}