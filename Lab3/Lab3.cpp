#include <iostream>
#include <math.h>
#include <omp.h>
using namespace std;

//Variant - 3

double f(double x)
{
	return sin(x);
}

int main(int t)
{
	cout << " Write 1 for choose cale - Synchronization with directives\n Write 2 for choose case - Synchronyzation with locks\n Your choose: ";
	cin >> t;
	switch (t)
	{
	case 1:
    #pragma omp parallel private (Integral, n) shared(a,b,h)
	{
		double start_time, end_time;
		double Integral;
		double a, b; // Задаю відрізок інтегрування a=0.0 b=1.0
		double h; // Задаю крок інтегрування 0.1
		double n; // Число розбивань

		cout << "Enter the beginning of the integration segment: "; // Початок відрізку
		cin >> a;
		cout << "Enter the end of the integration segment: "; // Кінець відрізку
		cin >> b;
		cout << "Enter the integration step: "; // Крок інтегрування
		cin >> h;

		start_time = omp_get_wtime();
        #pragma omp atomic
		n = (b - a) / h; //Формула обчислення числа розбивань

        #pragma omp barier
		Integral = h * (f(a) + f(b)) / 2.0;

        #pragma omp for shedule(static, 4)
		for (int i = 1; i <= n - 1; i++)
        #pragma omp flush
			Integral = Integral + h * f(a + h * i);
		cout << "The integral is approximately equal to " << Integral << "\n";
		end_time = omp_get_wtime();
		cout << "Code execution time = " << end_time - start_time;
		return 0;
	}
	case 2:
    #pragma omp parallel private (Integral, n) shared(a,b,h)
	{
		omp_lock_t lock;
		double start_time, end_time;
		double Integral;
		double a, b; // Задаю відрізок інтегрування a=0.0 b=1.0
		double h; // Задаю крок інтегрування 0.1
		double n; // Число розбивань

		cout << "Enter the beginning of the integration segment: "; // Початок відрізку
		cin >> a;
		cout << "Enter the end of the integration segment: "; // Кінець відрізку
		cin >> b;
		cout << "Enter the integration step: "; // Крок інтегрування
		cin >> h;
		start_time = omp_get_wtime();
		omp_init_lock(&lock);
        #pragma omp parallel
		{
		n = (b - a) / h; //Формула обчислення числа розбивань
		omp_set_lock(&lock);
		Integral = h * (f(a) + f(b)) / 2.0;
		for (int i = 1; i <= n - 1; i++) {
			Integral = Integral + h * f(a + h * i);
		}
		cout << "The integral is approximately equal to " << Integral << "\n";
		omp_unset_lock(&lock); 
		}
		omp_destroy_lock(&lock);
		end_time = omp_get_wtime();
		cout << "Code execution time = " << end_time - start_time;
		return 0;
	}
	}
   
}