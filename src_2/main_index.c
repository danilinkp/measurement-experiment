#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>

#ifndef NMAX
#error NMAX is not defined
#endif


typedef int array_t[NMAX];

unsigned long long get_time_now(void)
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC_RAW, &time);
    return time.tv_sec * 1000000000ULL + time.tv_nsec;
}

void init_sorted_arr(array_t arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
        arr[i] = i + 1;
}

void init_random_arr(array_t arr, size_t len)
{
    srand (time(NULL));
    for (size_t i = 0; i < len; i++)
        arr[i] = rand();
}

void bubble_sort(array_t arr, size_t len)
{
    for (size_t i = 1; i < len; i++)
        for (size_t j = 0; j < len - i; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}



int main(void)
{
    array_t arr;
    size_t len = NMAX;
    unsigned long long begin, end;

    init_random_arr(arr, len);

    begin = get_time_now();
    bubble_sort(arr, len);
    end = get_time_now();

    printf("%llu\n", end - begin);

    return 0;
}
