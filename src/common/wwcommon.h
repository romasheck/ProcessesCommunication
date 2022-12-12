#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "file_work.h"
#include "hash.h"

#define DISHES_TYPES dishes_types
#define GET_DISHES_TYPES(file_name) \
        dish_t* dishes_types = ReadTypesOfDishes(file_name)
#define TIME_EXE(type) \
        GetTimeExe (type, dishes_types)

#define MAX_NUM_OF_DISHES_TYPES 100
#define MAX_LEN_OF_TYPES_NAME   20

typedef uint32_t type_t;
typedef uint32_t time_exe_t;

typedef struct
{
    type_t type;
    time_exe_t time_exe;
} dish_t;

typedef struct
{
    size_t dishes_num;
    dish_t* dishes; 
} dishes_array;

dish_t*     ReadTypesOfDishes       (const char* file_name);

uint32_t    GetTimeExe              (type_t found_type, dish_t* dishes_types);

#define HASH_DISHE_TYPE(str, len) \
        Jenkins_one_at_a_time_hash(str, len)

#endif
