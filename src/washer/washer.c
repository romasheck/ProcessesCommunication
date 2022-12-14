#include "washer.h"

static uint32_t GetDirtyDish (const char* buf, type_t* dish);

int Wash (const time_exe_t time)
{
    sleep(time);
}

dishes_array GetDirtyDishes (const char* dirty_dishes_file)
{
    type_t* dishes_types = calloc(MAX_NUM_OF_DIRTY_DISH, sizeof(type_t));

    const char* buffer = strcat(my_fread (dirty_dishes_file), "\0");

    uint32_t cur_dish_num = 0;
    uint32_t i = 0;
    while (buffer [i] == '<')
    {
        i += GetDirtyDish(buffer + i, dishes_types + cur_dish_num);
        cur_dish_num++;
        i++;//skip \n
    }
    //printf ("num of dirty dishes = %d\n", cur_dish_num);
    dishes_array result = {cur_dish_num, dishes_types};
    return result;
}

static uint32_t GetDirtyDish (const char* buf, type_t* dish)//<,> - fake
{
    uint32_t cunt = 0, i = 0;
    char dish_name[MAX_LEN_OF_TYPES_NAME] = {};
    
    //printf ("----> %s \n", buf + cunt);
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
    *dish = HASH_DISHE_TYPE (dish_name, strlen(dish_name));
    cunt++; //skip '>'

    if (buf[cunt] == ':') cunt++;//skip ':'
    else assert("wrong reading" && NULL);

    if (buf[cunt] == '<') cunt++;//reading "<time>"
    else assert("wrong reading" && NULL);
    //dish->time_exe = atoi(buf + cunt);
    while (buf[cunt] != '>') cunt++;
    cunt++; //skip '>'

    return cunt;
}

int PrintDirtyDishes (dishes_array dirty_dishes)
{
    for (int i  = 0 ; i < dirty_dishes.dishes_num ; i++ )
    {
        printf("<%u>\n", dirty_dishes.dishes[i]);
    }
}