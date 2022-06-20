#include <iostream>
#include <omp.h>

using namespace std;
int main()
{
    const int AllThreads = omp_get_max_threads();
    int currentThread;

    omp_set_num_threads(AllThreads);

    #pragma omp parallel private(currentThread) 
    {
        currentThread = omp_get_thread_num();

        printf("I am %d thread from %d threads!!!", currentThread, AllThreads);

        #pragma omp sections
        {
            #pragma omp section
            {
                printf("\nI'm first section");
            }
            #pragma omp section
            {
                printf("\nI'm second section");
            }
            #pragma omp section
            {
                printf("\nI'm third section");
            }
        }
    }

}