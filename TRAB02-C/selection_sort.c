#include "lib.h"

Cost selection_sort(UserData **list)
{
    int i = 1, j = 1, min = 0, lenght = (*list)[0].rg;
    Cost cost = {0, 0};

    while(i <= lenght)
    {
        j = i + 1;
        min = i;
        while(j <= lenght)
        {
            if((*list)[j].rg < (*list)[min].rg)
                min = j;
            j++;
            cost.comp++;
        }
        UserData aux = (*list)[i];
        (*list)[i] = (*list)[min];
        (*list)[min] = aux;
        i++;
        cost.mov++;
    }
    return cost;
}
