#include <stdio.h>
#include "wwcommon.h"
#include "whiper.h"
#include "table.h"

int main ()
{
    GET_DISHES_TYPES(DISHES_TYPES_FILE);

    type_t cur_dish_t = 0;
    while(1)
    {
        /*if (TableStatus() != EMPTY)
        {
            cur_dish_t = TakeDish();
            Whip(TIME_EXE(TYPE(cur_dish_t)));
        }
        else break;//Waiting*/
        WaitingWhileTableEmpty();
        
        cur_dish_t = TakeDish();
        Whip(TIME_EXE(cur_dish_t));
    }
    
    return 0;
}