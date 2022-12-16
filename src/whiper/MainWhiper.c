#include <stdio.h>
//#include "wwcommon.h"
#include "whiper.h"
//#include "table.h"

int main ()
{
    GET_DISHES_TYPES(DISHES_TYPES_FILE);
    //TIME_EXE(101);
    StartTableWork(WHIPER_P);

    type_t cur_dish_t = 0;
    while(1)
    {
        WaitingWhileTableEmpty();
        
        cur_dish_t = TakeDish();
        //printf("i whipping dish %u\n", cur_dish_t);
        Whip(TIME_EXE(cur_dish_t));

        printf("i whiped dish %u\n", cur_dish_t);
    }
    
    return 0;
}