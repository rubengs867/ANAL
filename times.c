/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Marco Manceñido, Rubén García
 * Version: 1.1
 * Fecha: 02-10-2025
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "times.h"

/***************************************************/
/* Function: average_sorting_time                  */
/* Authors: Marco Manceñido, Rubén García         */
/*                                                 */
/* Function that computes the average sorting time*/
/* and basic operations for a sorting method      */
/* applied to multiple permutations                */
/*                                                 */
/* Input:                                          */
/* pfunc_sort method: sorting function pointer    */
/* int n_perms: number of permutations            */
/* int N: size of each permutation                 */
/* PTIME_AA ptime: pointer to store results       */
/* Output: short: OK or ERR                        */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms, int N, PTIME_AA ptime)
{
  clock_t time0, time1;
  int **permutations;
  int i, ob, allob = 0;
  int min_ob;
  int max_ob;

  assert(metodo != NULL);
  assert(ptime != NULL);
  assert(n_perms >= 1);
  assert(N >= 1);

  permutations = generate_permutations(n_perms, N);
  if (permutations == NULL)
      return ERR;

  time0 = clock();

  for (i = 0; i < n_perms; i++)
  {
      ob = metodo(permutations[i], 0, N - 1);
      if (ob == ERR)
      {
          free_permutations(permutations, n_perms);
          return ERR;
      }

      if (i == 0)
      {
          min_ob = max_ob = ob;
          allob += ob;
      }
      else
      {
          allob += ob;
          if (ob < min_ob)
              min_ob = ob;
          else if (ob > max_ob)
              max_ob = ob;
      }
  }

  time1 = clock();

  ptime->time = (double)(time1 - time0) / (double)CLOCKS_PER_SEC / (double)n_perms;
  ptime->average_ob = (double)allob / (double)n_perms;
  ptime->min_ob = min_ob;
  ptime->max_ob = max_ob;
  ptime->N = N;
  ptime->n_elems = n_perms;

  free_permutations(permutations, n_perms);

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times                */
/* Authors: Marco Manceñido, Rubén García         */
/*                                                 */
/* Function that executes average_sorting_time    */
/* for several N values and saves the results     */
/* into a text file                               */
/*                                                 */
/* Input:                                          */
/* pfunc_sort method: sorting function pointer    */
/* char* file: name of the output file            */
/* int num_min: minimum N value                    */
/* int num_max: maximum N value                    */
/* int incr: increment of N                        */
/* int n_perms: number of permutations            */
/* Output: short: OK or ERR                        */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                             int num_min, int num_max, 
                             int incr, int n_perms)
{
  int i, n_times;
  PTIME_AA times = NULL;
  int N;

  assert(method != NULL);
  assert(num_min > 0);
  assert(num_max >= num_min);
  assert(incr > 0);
  assert(n_perms > 0);

  n_times = ((num_max - num_min) / incr) + 1;
  times = (PTIME_AA) malloc(n_times * sizeof(TIME_AA));
  if (!times)
      return ERR;

  for (i = 0; i < n_times; i++)
  {
      N = num_min + i * incr;
      if (average_sorting_time(method, n_perms, N, &times[i]) == ERR)
      {
          free(times);
          return ERR;
      }
  }

  if (save_time_table(file, times, n_times) == ERR)
  {
      free(times);
      return ERR;
  }

  free(times);
  return OK;
}

/***************************************************/
/* Function: save_time_table                       */
/* Authors: Marco Manceñido, Rubén García         */
/*                                                 */
/* Function that saves the timing results in a    */
/* text file with the following format:           */
/* N   time   avg_OB   min_OB   max_OB            */
/*                                                 */
/* Input:                                          */
/* char* file: name of the output file            */
/* PTIME_AA times: array of TIME_AA structures    */
/* int n_times: number of entries                  */
/* Output: short: OK or ERR                        */
/***************************************************/
short save_time_table(char* file, PTIME_AA times, int n_times)
{
  int i;
  FILE *fout;

  assert(file != NULL);
  assert(times != NULL);
  assert(n_times > 0);

  fout = fopen(file, "w");
  if (fout == NULL)
      return ERR;

  for (i = 0; i < n_times; i++)
  {
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