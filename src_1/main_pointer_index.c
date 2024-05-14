#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include <sys/time.h>
#include <time.h>

#ifndef NMAX
#error NMAX is not defined
#endif

#define N_REPS 1000000

typedef int array_t[NMAX];

unsigned long long get_time_now(void)
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC_RAW, &time);
    return time.tv_sec * 1000000000ULL + time.tv_nsec;
    // struct timeval val;

    // if (gettimeofday(&val, NULL))
    // {
    //     return (unsigned long long)-1;
    // }
    // return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}


void init_random_arr(array_t arr, size_t len)
{
    srand (time(NULL));
    for (size_t i = 0; i < len; i++)
        arr[i] = rand();
}

void bubble_sort(array_t arr, size_t len)
{
    for (size_t i = 0; i < len - 1; i++)
        for (size_t j = 0; j < len - i - 1; j++)
            if (*(arr + j) > *(arr + (j + 1)))
            {
                int temp = *(arr + j);
                *(arr + j) = *(arr + (j + 1));
                *(arr + (j + 1)) = temp;
            }
}


int main(void)
{
    array_t arr;
    size_t len = NMAX;
    unsigned long long begin, end;
    
    // init_random_arr(src, len);
    unsigned long long data[N_REPS];
    // memcpy(arr, src, sizeof(src));
    double sum = 0.0;
    int c = 7;
    for (int i = 0; i < c; i++)
    {
        // memcpy(arr, src, sizeof(src));
        init_random_arr(arr, len);
        begin = get_time_now();
        bubble_sort(arr, len);
        end = get_time_now();
        data[i] = end - begin;
        printf("%llu\n", end - begin);
        sum += end - begin;
    }
    double avg = sum / c;
    double s_sq = 0.0;
    for (int i = 0; i < c; i++)
        s_sq += (data[i] - avg) * (data[i] - avg);
    s_sq /= c - 1;

    double s = sqrt(s_sq);
    double std_err = s / sqrt(c);
    double rse = (std_err / avg) * 100;
    // init_random_arr(src, len);

    while (rse > 1.0)
    {
        // memcpy(arr, src, sizeof(src));
        init_random_arr(arr, len);
        begin = get_time_now();
        bubble_sort(arr, len);
        end = get_time_now();

        data[c] = end - begin;
        printf("%llu\n", end - begin);
        
        sum += end - begin;

        c++;
        avg = sum / c;

        s_sq = 0.0;
        for (int i = 0; i < c; i++)
            s_sq += (data[i] - avg) * (data[i] - avg);
        s_sq /= c - 1;
        s = sqrt(s_sq);
        std_err = s / sqrt(c);
        rse = (std_err / avg) * 100;
    }
    return 0;
}
