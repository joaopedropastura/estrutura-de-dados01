#include "lib.h"

Cost insertion_sort(UserData **list)
{
    int i = 2, j = 1, lenght = (*list)[0].rg;
    Cost cost = {0, 0};

    while(i <= lenght)
    {
        UserData aux = (*list)[i];
        j = i - 1;
        while(j >= 1 && (*list)[j].rg > aux.rg)
        {
            (*list)[j + 1] = (*list)[j];
            j--;
            cost.comp++;
            cost.mov++;
        }
        (*list)[j + 1] = aux;
        i++;
        cost.mov++;
    }
    return cost;
}