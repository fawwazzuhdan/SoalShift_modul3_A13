#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pthread_t tid[1000];
int array[1000];
int status = 0;

void sort(int n)
{
	int c = 1, d, t;
	for (c; c < n - 1; c++)
	{
		d = c;

		while (d > 0 && array[d - 1] > array[d])
		{
			t = array[d];
			array[d] = array[d - 1];
			array[d - 1] = t;

			d--;
		}
	}
}

void *factorial(void *arg)
{

	int b = *(int *)arg;

	int a = 1;
	int c = array[b];

	while (c > 0)
	{
		a *= c;
		c--;
	}
	printf("%d! = %d\n", array[b], a);
	status = 1;
}

int main(int argc, char const *argv[])
{
	int i = 1;
	int err;
	int a = 0, b = 0;
	for (i; i < argc; i++)
	{
		array[i - 1] = atoi(argv[i]);
	}
	sort(argc);

	for (a; a < argc - 1; a++)
	{
		int x = a;
		int *y = &x;

		status = 0;
		err = pthread_create(&(tid[a]), NULL, factorial, (void *)y);
		while (status == 0)
			;
	}
	while (b < argc - 1)
	{
		pthread_join(tid[b], NULL);
		b++;
	}

	exit(0);
	return 0;
}