#ifndef WASHER_H_INCLUDED
#define WASHER_H_INCLUDED

#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

#include "../common/wwcommon.h"
#include "../table/table.h"

#define PRINT_LINE printf("I am at the line %d\n", __LINE__);

#define DISHES_TYPES_FILE "/home/princep/PROGS/Computers_teq/TaskTwoZadavalnik/TheOne/dishes_types.txt"
#define DIRTY_DISHES_FILE "/home/princep/PROGS/Computers_teq/TaskTwoZadavalnik/TheOne/dirty_dishes.txt"

#define MAX_NUM_OF_DIRTY_DISH 100

#define DISHES(i) dirty_dishes.dishes[i]
#define TYPE(i)   DISHES(i)

typedef struct
{
    size_t dishes_num;
    type_t* dishes; 
} dishes_array;

dishes_array    GetDirtyDishes      (const char* dirty_dishes_file);

int             Wash                (const time_exe_t time);

int             PrintDirtyDishes    (dishes_array dirty_dishes);

#endif