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
#include <stdlib.h>
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



int mergesort(int* tabla, int ip, int iu) {
    int medio;

    if (ip > iu)
        return ERR;

    if (ip == iu)
        return OK;

    medio = (ip + iu) / 2;

    if (mergesort(tabla, ip, medio) == ERR)
        return ERR;

    if (mergesort(tabla, medio + 1, iu) == ERR)
        return ERR;

    if (merge(tabla, ip, iu, medio) == ERR)
        return ERR;

    return OK;
}

int merge(int* tabla, int ip, int iu, int imedio) {
    int *Taux;
    int i = ip;
    int j = imedio + 1;
    int k = 0;
    int n = iu - ip + 1;

    Taux = (int*)malloc(n * sizeof(int));
    if (Taux == NULL)
        return ERR;

    while (i <= imedio && j <= iu) {
        if (tabla[i] <= tabla[j])
            Taux[k++] = tabla[i++];
        else
            Taux[k++] = tabla[j++];
    }

    while (i <= imedio)
        Taux[k++] = tabla[i++];

    while (j <= iu)
        Taux[k++] = tabla[j++];

    for (k = 0; k < n; k++)
        tabla[ip + k] = Taux[k];

    free(Taux);
    return OK;
}


int quicksort(int* tabla, int ip, int iu) {
    int M;

    if (ip > iu)
        return ERR;

    if (ip == iu)
        return OK;

    if (partition(tabla, ip, iu, &M) == ERR)
        return ERR;

    if (ip < M - 1)
        quicksort(tabla, ip, M - 1);

    if (M + 1 < iu)
        quicksort(tabla, M + 1, iu);

    return OK;
}

int partition(int* tabla, int ip, int iu, int *pos) {
    int pivote, i, j, tmp;
    int medio;

    /* Elegir pivote usando la mediana de tres */
    if (median(tabla, ip, iu, &medio) == ERR)
        return ERR;

    pivote = tabla[medio];

    /* Mover pivote al final */
    tmp = tabla[medio];
    tabla[medio] = tabla[iu];
    tabla[iu] = tmp;

    i = ip;
    for (j = ip; j < iu; j++) {
        if (tabla[j] < pivote) {
            tmp = tabla[i];
            tabla[i] = tabla[j];
            tabla[j] = tmp;
            i++;
        }
    }

    /* Colocar el pivote en su posición final */
    tmp = tabla[i];
    tabla[i] = tabla[iu];
    tabla[iu] = tmp;

    *pos = i;
    return OK;
}

int median(int *tabla, int ip, int iu, int *pos) {
    int medio = (ip + iu) / 2;
    int a = tabla[ip];
    int b = tabla[medio];
    int c = tabla[iu];

    /* Comparar para obtener la mediana de tres */
    if ((a <= b && b <= c) || (c <= b && b <= a))
        *pos = medio;
    else if ((b <= a && a <= c) || (c <= a && a <= b))
        *pos = ip;
    else
        *pos = iu;

    return OK;
}

/* median_stat: devuelve en *pos el índice (ip..iu) que contiene
   la mediana entre tabla[ip], tabla[(ip+iu)/2] y tabla[iu].
   Devuelve OK (0) o ERR (-1) en caso de error (por ejemplo ip>iu).
*/


int median_stat(int *tabla, int ip, int iu, int *pos) {
    int imedio;
    int a, b, c;

    if (tabla == NULL || pos == NULL || ip > iu)
        return ERR;

    imedio = (ip + iu) / 2;
    a = tabla[ip];
    b = tabla[imedio];
    c = tabla[iu];

    /* Comparar para hallar la mediana de tres valores */
    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        *pos = imedio;
    } else if ((b <= a && a <= c) || (c <= a && a <= b)) {
        *pos = ip;
    } else {
        *pos = iu;
    }

    return OK;
}

/* Variante de partition que usa median_stat como pivote.
   Además permite acumular operaciones básicas (ops): si ops != NULL,
   se incrementa *ops por cada comparación entre elementos del array
   (esto es una definición de ejemplo de "operación básica").
   Firma: int partition_count(int *tabla, int ip, int iu, int *pos, long *ops)
   Devuelve OK/ERR y coloca la posición final del pivote en *pos.
*/
int partition_count(int *tabla, int ip, int iu, int *pos, long *ops) {
    int piv_idx;
    int piv_val;
    int i, j, tmp;
    int cmp_result;

    if (tabla == NULL || pos == NULL || ip > iu)
        return ERR;

    /* obtener índice del pivote usando median_stat */
    if (median_stat(tabla, ip, iu, &piv_idx) == ERR)
        return ERR;

    /* opcional: contar la comparación que hace median_stat (si quieres) */
    /* aquí no incrementamos ops por median_stat internamente,
       pero podrías sumar 2 ó 3 si quieres reflejar esas comparaciones. */

    /* llevar pivote al final (iu) */
    tmp = tabla[piv_idx];
    tabla[piv_idx] = tabla[iu];
    tabla[iu] = tmp;

    piv_val = tabla[iu];
    i = ip;

    for (j = ip; j < iu; j++) {
        /* contar comparación tabla[j] < piv_val */
        if (ops) (*ops)++;

        if (tabla[j] < piv_val) {
            /* swap tabla[i] <-> tabla[j] */
            tmp = tabla[i];
            tabla[i] = tabla[j];
            tabla[j] = tmp;
            i++;
            /* contar también el swap como operaciones si lo deseas:
               if (ops) (*ops) += SWAP_COST; */
        }
    }

    /* colocar pivote en su posición final i */
    tmp = tabla[i];
    tabla[i] = tabla[iu];
    tabla[iu] = tmp;

    *pos = i;
    return OK;
}









