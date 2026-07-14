#include <omp.h>
#include<stdio.h>
static long num_steps = 100000000;
double step;
int main ()
{
    double x, pi, sum = 0.0;
    step = 1.0/(double) num_steps;
    double tdata = omp_get_wtime();
    int perThreadSum[omp_get_max_threads()];

    #pragma omp parallel
    {
        int numthreads = omp_get_num_threads();
        int numThreadSteps = num_steps / numthreads;
        int thisThreadIs = omp_get_thread_num();
        int start = thisThreadIs * numThreadSteps;
        int finish = (thisThreadIs + 1) * numThreadSteps;
        float thisThreadSum = 0;

        for (int i=start; i< finish; i++){
            x = (i+0.5)*step;
            thisThreadSum = thisThreadSum + 4.0/(1.0+x*x);
        }
        perThreadSum[thisThreadIs] = thisThreadSum;
    }
    for (int i = 0; i < omp_get_max_threads(); i++){
        sum = sum + perThreadSum[i];
    }
    
    pi = step * sum;
    tdata = omp_get_wtime() - tdata;
    printf(" pi = %f in %f secs\n",pi, tdata);
}