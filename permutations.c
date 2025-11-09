/**
 *
 * Descripcion: Implementacion de funciones que generan permutaciones
 *
 * Fichero: permutations.c
 * Autor: Ruben García, Marco Manceñido
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */

#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "permutations.h"

/***************************************************/
/* Funcion: random_num                              */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que genera un numero aleatorio          */
/* entre dos valores dados                          */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                         */
/* int sup: limite superior                          */
/* Salida: int: numero aleatorio                   */
/***************************************************/
int random_num(int inf, int sup)
{
    assert(sup >= inf); 

    return rand() / (RAND_MAX + 1.) * (sup - inf + 1) + inf;
}

/***************************************************/
/* Funcion: generate_perm                           */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que genera una permutacion aleatoria    */
/*                                                 */
/* Entrada:                                        */
/* int N: numero de elementos en la permutacion    */
/* Salida: int*: puntero a array de enteros con    */
/* la permutacion o NULL en caso de error          */
/***************************************************/
int* generate_perm(int N)
{
    int *perm;
    int j, num;

    perm = malloc(N * sizeof(int));
    if(perm == NULL){
        return NULL;
    }

    for(j = 0; j < N; j++){
        perm[j] = j + 1;
    }

    for(j = 0; j < N; j++){
        num = random_num(j, N - 1);
        swap(&perm[j], &perm[num]);
    }

    return perm;
}

/***************************************************/
/* Funcion: generate_permutations                   */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias con N elementos                       */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: numero de permutaciones           */
/* int N: numero de elementos en cada permutacion  */
/* Salida: int**: array de punteros a enteros que */
/* apuntan a cada permutacion o NULL en caso error */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
    int **perm;
    int i;

    assert(n_perms >= 1 && N >= 1); 

    perm = malloc(n_perms * sizeof(int*));
    if(perm == NULL){
        return NULL;
    }

    for(i = 0; i < n_perms; i++){
        perm[i] = generate_perm(N);
        if(perm[i] == NULL){
            for(i = i - 1; i >= 0; i--){
                free(perm[i]);
            }
            free(perm);
            return NULL;
        }
    }

    return perm;
}

/***************************************************/
/* Funcion: free_permutations                       */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que libera la memoria de las            */
/* permutaciones generadas                          */
/*                                                 */
/* Entrada:                                        */
/* int **perm: puntero a array de permutaciones   */
/* int n_perms: numero de permutaciones           */
/* Salida: void                                   */
/***************************************************/
void free_permutations(int **perm, int n_perms)
{
    int i;

    if(perm == NULL){
        return;
    }

    for(i = 0; i < n_perms; i++){
        free(perm[i]);
    }

    free(perm);
}