/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso (adaptado con implementación)
 * Version: 1.1
 * Fecha: 02-10-2025
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "times.h"
#include "sorting.h"
#include "permutations.h"   /* Necesaria para generate_permutations() */

/***************************************************/
/* Function: average_sorting_time                  */
/*                                                 */
/* Calcula el tiempo medio y estadísticas de OB    */
/* sobre n_perms permutaciones de tamaño N         */
/***************************************************/
short average_sorting_time(pfunc_sort method, 
                           int n_perms,
                           int N, 
                           PTIME_AA ptime)
{
    int i, j;
    int **perms = NULL;      /* matriz de permutaciones */
    int ob;                  /* nº de veces que se ejecuta la OB */
    double total_time = 0;   /* suma acumulada de tiempos */
    double total_ob = 0;     /* suma acumulada de OB */
    int min_ob = -1, max_ob = -1;
    clock_t start, end;

    assert(method == NULL);
    assert(ptime == NULL);
    assert(n_perms <= 0);
    assert(N <= 0);

    perms = generate_permutations(n_perms, N);
    if (!perms)
        return ERR;

    for (i = 0; i < n_perms; i++) {
        int *perm_copy = (int*) malloc(N * sizeof(int));
        if (!perm_copy) {
            free_permutations(perms, n_perms);
            return ERR;
        }

        /* Copiar la permutación porque el algoritmo modifica el array */
        for (j = 0; j < N; j++) perm_copy[j] = perms[i][j];

        start = clock();
        ob = method(perm_copy, 0, N-1);
        end = clock();

        total_time += (double)(end - start) / CLOCKS_PER_SEC;
        total_ob += ob;

        if (min_ob == -1 || ob < min_ob) min_ob = ob;
        if (max_ob == -1 || ob > max_ob) max_ob = ob;

        free(perm_copy);
    }

    /* Guardar resultados en la estructura */
    ptime->N = N;
    ptime->n_elems = n_perms;
    ptime->time = total_time / n_perms;
    ptime->average_ob = total_ob / n_perms;
    ptime->min_ob = min_ob;
    ptime->max_ob = max_ob;

    free_permutations(perms, n_perms);
    return OK;
}

/***************************************************/
/* Function: generate_sorting_times                */
/*                                                 */
/* Ejecuta average_sorting_time para varios N      */
/* y guarda los resultados en un fichero           */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                             int num_min, int num_max, 
                             int incr, int n_perms)
{
    int i, n_times;
    PTIME_AA times = NULL;

    if (!method || !file || num_min <= 0 || num_max < num_min || incr <= 0 || n_perms <= 0)
        return ERR;

    n_times = ((num_max - num_min) / incr) + 1;
    times = (PTIME_AA) malloc(n_times * sizeof(TIME_AA));
    if (!times)
        return ERR;

    for (i = 0; i < n_times; i++) {
        int N = num_min + i*incr;
        if (average_sorting_time(method, n_perms, N, &times[i]) == ERR) {
            free(times);
            return ERR;
        }
    }

    if (save_time_table(file, times, n_times) == ERR) {
        free(times);
        return ERR;
    }

    free(times);
    return OK;
}

/***************************************************/
/* Function: save_time_table                       */
/*                                                 */
/* Guarda los resultados en un fichero de texto    */
/* con el formato:                                 */
/* N   time   avg_OB   min_OB   max_OB             */
/***************************************************/
short save_time_table(char* file, PTIME_AA times, int n_times)
{
    int i;
    FILE *fout;

    if (!file || !times || n_times <= 0)
        return ERR;

    fout = fopen(file, "w");
    if (!fout) return ERR;

    for (i = 0; i < n_times; i++) {
        fprintf(fout, "%d\t%.6f\t%.2f\t%d\t%d\n",
                times[i].N,
                times[i].time,
                times[i].average_ob,
                times[i].min_ob,
                times[i].max_ob);
    }

    fclose(fout);
    return OK;
}

