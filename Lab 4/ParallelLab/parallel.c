//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Nathan Tjoar
 * UCLA ID : 005081232
 * Email : ntjoar@g.ucla.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

void work_it_par(long *old, long *new) {
  int i,j,k;
  int u;
  long compute_it;
  long aggregate=1.0;

 #pragma omp parallel
  {
#pragma omp for private (i,j,k,compute_it) reduction(+:aggregate) 
  for (i=1; i<DIM-1; i++) {
    int idimsqr = i*DIM*DIM;
    for (j=1; j<DIM-1; j++) {
      int jdim = j*DIM;
      for  (k=1; k<DIM-1; k++) {
        compute_it = old[idimsqr+jdim+k] * we_need_the_func();
        aggregate += compute_it / gimmie_the_func();
      }
    }
  }

#pragma omp single nowait
  printf("AGGR:%ld\n",aggregate);

#pragma omp for private(i,j,k) 
  for (i=1; i<DIM-1; i++) {
	int dimsqr = DIM*DIM;
    int idimsqr = i*dimsqr;
	int dimsqrmin = idimsqr - dimsqr;
	int dimsqrplus = idimsqr + dimsqr;
    for (j=1; j<DIM-1; j++) {
      int jdim = j*DIM;
      for (k=1; k<DIM-1; k++) {
        new[idimsqr+jdim+k]=0;
		int acc1=0;
		int acc2=0;
		int acc3=0;
		//u = -1
		//v == -1
		//w = -1, w = 0, w = 1
		acc1 = acc1 + (old[dimsqrmin+jdim-DIM+(k-1)] + old[dimsqrmin+jdim-DIM+k] + old[dimsqrmin+jdim-DIM+(k+1)]);

		//v == 0
		//w = -1, w = 0, w = 1
		acc2 = acc2 + (old[dimsqrmin+jdim+(k-1)] + old[dimsqrmin+jdim+k] + old[dimsqrmin+jdim+(k+1)]);

		//v == -1
		//w = -1, w = 0, w = 1
		acc3 = acc3 + (old[dimsqrmin+jdim+DIM+(k-1)] + old[dimsqrmin+jdim+DIM+k] + old[dimsqrmin+jdim+DIM+(k+1)]);

		//u = 0
		//v == -1
		//w = -1, w = 0, w = 1
		acc1 = acc1 + (old[idimsqr+jdim-DIM+(k-1)] + old[idimsqr+jdim-DIM+k] + old[idimsqr+jdim-DIM+(k+1)]);

		//v == 0
		//w = -1, w = 0, w = 1
		acc2 = acc2 + (old[idimsqr+jdim+(k-1)] + old[idimsqr+jdim+k] + old[idimsqr+jdim+(k+1)]);

		//v == -1
		//w = -1, w = 0, w = 1
		acc3 = acc3 + (old[idimsqr+jdim+DIM+(k-1)] + old[idimsqr+jdim+DIM+k] + old[idimsqr+jdim+DIM+(k+1)]);

		//u = 1
		//v == -1
		//w = -1, w = 0, w = 1
		acc1 = acc1 + (old[dimsqrplus+jdim-DIM+(k-1)] + old[dimsqrplus+jdim-DIM+k] + old[dimsqrplus+jdim-DIM+(k+1)]);

		//v == 0
		//w = -1, w = 0, w = 1
		acc2 = acc2 + (old[dimsqrplus+jdim+(k-1)] + old[dimsqrplus+jdim+k] + old[dimsqrplus+jdim+(k+1)]);

		//v == -1
		//w = -1, w = 0, w = 1
		acc3 = acc3 + (old[dimsqrplus+jdim+DIM+(k-1)] + old[dimsqrplus+jdim+DIM+k] + old[dimsqrplus+jdim+DIM+(k+1)]);
		
		acc3 = acc3 + (acc1 + acc2);
        acc3 = acc3 / 27;
		new[idimsqr+jdim+k] = acc3;
      }
    }
  }
    
  #pragma omp single nowait
  for (i=1; i<DIM-1; i++) {
    for ( j=1; j<DIM-1; j++) {
      for ( k=1; k<DIM-1; k++) {
        u=(new[i*DIM*DIM+j*DIM+k]/100);
        if (u<=0) u=0;
        if (u>=9) u=9;
        histogrammy[u]++;
      }
    }
  }
  }
}
