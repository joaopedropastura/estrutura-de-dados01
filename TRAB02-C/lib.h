#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 20
#endif

#define clear() printf("\033[H\033[J")



int	menu();
Cost selection_sort(UserData **list);
Cost insertion_sort(UserData **list);
Cost bubble_sort(UserData **list);


#endif