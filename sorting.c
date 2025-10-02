/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"
void swap(int *a, int *b)
{
    int temp;

    if (!a || !b) {
        return; 
    }

    temp = *a;
    *a = *b;
    *b = temp;
}

/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int InsertSort(int *array, int ip, int iu)
{
    int size, i, j, key;
    int counter = 0; 

    if (!array || ip < 0 || iu < ip) {
        return ERR;
    }

    size = iu - ip + 1;

    for (i = 1; i < size; ++i) {
        key = array[ip + i];
        j = ip + i - 1;

        while (j >= ip) {
            counter++;  
            if (array[j] > key) {
                array[j + 1] = array[j];
                j--;
            } else {
                break;
            }
        }

        array[j + 1] = key;
    }

    return counter;
}




/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int *array, int ip, int iu)
{
    int i, j;
    int size, counter = 0;

    if (!array || ip < 0 || iu < ip) {
        return ERR;
    }

    size = iu - ip + 1;

    for (i = 0; i < size - 1; i++) {
        for (j = ip; j < iu - i; j++) {
            counter++; 
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }

    return counter;
}







