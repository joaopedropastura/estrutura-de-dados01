#include "lib.h"


Cost bubble_sort(UserData **list)
{
    int i = 1, j = 1, lenght = (*list)[0].rg;
    Cost cost = {0, 0};

    while(i <= lenght)
    {
        j = 1;
        while(j <= lenght - i)
        {
            if((*list)[j].rg > (*list)[j + 1].rg)
            {
                UserData aux = (*list)[j];
                (*list)[j] = (*list)[j + 1];
                (*list)[j + 1] = aux;
                cost.mov++;
            }
            j++;
            cost.comp++;
        }
        i++;
    }
    return cost;
}