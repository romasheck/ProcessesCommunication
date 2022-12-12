#include "washer.h"

int main ()
{
    GET_DISHES_TYPES(DISHES_TYPES_FILE);

    dishes_array dirty_dishes = GetDirtyDishes(DIRTY_DISHES_FILE);

    for (int i = 0; i < dirty_dishes.dishes_num; i++)
    {
        WaitingWhileTableFull();
        
        Wash(TIME_EXE(TYPE(i)));
        
        PutDish(TYPE(i));
    }
    //free (dishes_types); //no, 'cause dishes_types is static memory
    return 0;
}