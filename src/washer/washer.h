#ifndef WASHER_H_INCLUDED
#define WASHER_H_INCLUDED

#include <stdlib.h>
#include <inttypes.h>

#include "/home/princep/PROGS/Computers_teq/TaskTwoZadavalnik/TheOne/src_common/wwcommon.h"
//#include "file_work.h"
#include "/home/princep/PROGS/Computers_teq/TaskTwoZadavalnik/TheOne/src_table/table.h"

#define DISHES_TYPES_FILE "dishes_types.txt"
#define DIRTY_DISHES_FILE "dirty_dishes.txt"
#define MAX_NUM_OF_DIRTY_DISH 100

#define DISHES(i) dirty_dishes.dishes[i]
#define TYPE(i)   DISHES(i).type

dishes_array    GetDirtyDishes      (const char* dirty_dishes_file);

int             Wash                (time_exe_t time);

#endif