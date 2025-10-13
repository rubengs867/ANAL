/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Marco Manceñido, Rubén García
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"

/***************************************************/
/* Function: swap                                   */
/* Date:                                           */
/* Authors: Marco Manceñido, Rubén García          */
/*                                                 */
/* Intercambia los valores de dos enteros          */
/*                                                 */
/* Input:                                          */
/* int *a: puntero al primer entero                */
/* int *b: puntero al segundo entero               */
/* Output:                                         */
/* void                                            */
/***************************************************/
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
/* Function: InsertSort                            */
/* Date:                                           */
/* Authors: Marco Manceñido, Rubén García          */
/*                                                 */
/* Implementa el algoritmo de ordenación por       */
/* inserción (Insertion Sort). Devuelve el número  */
/* de veces que se ejecuta la Operación Básica (OB)*/
/* o ERR en caso de error.                         */
/*                                                 */
/* Input:                                          */
/* int *array: puntero al array a ordenar          */
/* int ip: índice inicial del array                */
/* int iu: índice final del array                  */
/* Output:                                         */
/* int: número de veces que se ejecuta la OB       */
/*       o ERR si hay error                        */
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
/* Function: BubbleSort                            */
/* Date:                                           */
/* Authors: Marco Manceñido, Rubén García          */
/*                                                 */
/* Implementa el algoritmo de ordenación por       */
/* burbuja (Bubble Sort). Devuelve el número de    */
/* veces que se ejecuta la Operación Básica (OB)   */
/* o ERR en caso de error.                         */
/*                                                 */
/* Input:                                          */
/* int *array: puntero al array a ordenar          */
/* int ip: índice inicial del array                */
/* int iu: índice final del array                  */
/* Output:                                         */
/* int: número de veces que se ejecuta la OB       */
/*       o ERR si hay error                        */
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








