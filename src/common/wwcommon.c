#include "wwcommon.h"

static uint32_t         GetDishType         (const char* buf, dish_t* dishe);

static dish_t           FindType            (const type_t found_type, dish_t* dishes_types);

#define TYPE(i) dishes_types[i].type

dish_t* ReadTypesOfDishes (const char* file_name)
{
    dish_t* dishes_types = calloc(MAX_NUM_OF_DISHES_TYPES, sizeof(dish_t));

    const char* buffer = strcat(my_fread (file_name), "\0");

    uint32_t cur_dish_num = 0;
    uint32_t i = 0;
    while (buffer [i] != '\0')
    {
        i += GetDishType(buffer + i, dishes_types + cur_dish_num);
        i++;//skip \n
        cur_dish_num++;
    }

    return dishes_types;
}

static uint32_t GetDishType (const char* buf, dish_t* dish)//<,> - fake
{
    uint32_t cunt = 0, i = 0;
    char dish_name[MAX_LEN_OF_TYPES_NAME] = {};

    if (buf[cunt] == '<') cunt++;//reading <type>
    else assert("wrong reading" && NULL);
    while (buf[cunt] != '>')
    {
        dish_name[i] = buf[cunt];
        i++;
        cunt++;
        if (i > MAX_LEN_OF_TYPES_NAME - 2)
        {
            assert ("so fucking big name of dish" && NULL);
        }
    }
    strcat (dish_name, "\0");
    dish->type = HASH_DISHE_TYPE (dish_name, strlen(dish_name));
    cunt++; //skip '>'

    if (buf[cunt] == ':') cunt++;//skip ':'
    else assert("wrong reading" && NULL);

    if (buf[cunt] == '<') cunt++;//reading "<time>"
    else assert("wrong reading" && NULL);
    dish->time_exe = atoi(buf + cunt);
    while (buf[cunt] != '>') cunt++;
    cunt++; //skip '>'

    return cunt;
}

uint32_t GetTimeExe (type_t found_type, dish_t* dishes_types)
{
    dish_t tmp = FindType (found_type, dishes_types);

    return tmp.time_exe;
}

static dish_t FindType (const type_t found_type, dish_t* dishes_types)
{
    if (found_type == 0) assert ("wrong type 0" && NULL);
    for (size_t i = 0; i < MAX_NUM_OF_DISHES_TYPES; i++)
    {
        if (TYPE(i) != found_type) continue;
        else return dishes_types[i];
    }
    
    assert ("wrong finding dish" && NULL);
}

int PrintDishesTypes (const dish_t* dishes_types)
{
    printf ("dishes types ->\n");
    int i = 0;
    while (*(char*)(dishes_types + i) != '\0')
    {
        printf("<%u>:<%u>\n", dishes_types[i].type, dishes_types[i].time_exe);
        i++;
    }
}
