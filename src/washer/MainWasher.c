#include "washer.h"
//#include "/home/princep/PROGS/Computers_teq/TaskTwoZadavalnik/TheOne/src/common/file_work.h"

int main ()
{
    //printf("I am at the line %d\n", __LINE__);
    //my_fread("/home/princep/PROGS/Computers_teq/TaskTwoZadavalnik/TheOne/dirty_dishes.txt");
    //printf("I am at the line %d\n", __LINE__);
    GET_DISHES_TYPES(DISHES_TYPES_FILE);
    //printf("%d %d\n", *((int*)dishes_types), *((int*)dishes_types + 1));
    dishes_array dirty_dishes = GetDirtyDishes(DIRTY_DISHES_FILE);

    //PRINT_DISHES_TYPES;
    PrintDirtyDishes(dirty_dishes);
    //printf ("num of dirty dishes eq %d\n", dirty_dishes.dishes_num);

    StartTableWork(WASHER_P);
    for (int i = 0; i < dirty_dishes.dishes_num; i++)
    {
        //printf("iteration number %d\n", i);
        WaitingWhileTableFull();
        
        Wash(TIME_EXE(TYPE(i)));
        //printf ("I washed dish %u\n", TYPE(i));
        PutDish(TYPE(i));
    }
    //free (dishes_types); //no, 'cause dishes_types is static memory
    return 0;
}