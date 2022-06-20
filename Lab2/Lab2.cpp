#include <iostream>
#include <omp.h>
//Variant-9
using namespace std;
int main()
{
	double start_time, end_time;
    start_time = omp_get_wtime();
    long  const n = 100;
    long double a[n][n];
    int Nmax{}, Nind{}, i, j = 0;
    int d = 0;
    int k;
    #pragma omp parallel private(n)
    {
        k = omp_get_thread_num();
        for (int i = 0; i < n; i++) {
            #pragma omp parallel for shared(a, Nind) private(i, j, Nmax) shedule(dynamic)
            {
                for (int j = 0; j < n; j++) {
                    a[i][j] = rand() % 100;
                    //cout << "|   " << a[i][j] << "  ";
                }
            }
            if (Nmax < a[i][j]) {
                #pragma omp critical
                Nmax = a[i][j];
                Nind = i;
            };
            printf("|  %d: calc of the iteration numb - %d", k, i);
            cout << " " << endl;
        }
    }
    cout << "\nMax matrix value = " << Nmax << endl;
    end_time = omp_get_wtime();
    cout << "Time: " << end_time - start_time << endl;
}