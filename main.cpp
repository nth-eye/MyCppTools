#include "tools.h"

int fact_count(int a)
{
    int res = 1;
    for (int i = 1; i < a; ++i)
        res *= i;
    for (int i = 0; i < res; ++i)
        --a;
    return a;
};

int main()
{
    printf("fact_count: %lu clock_t \n", measure_time<10>(fact_count, 11));
    // std::cout << measure_time<100>(fact_count, 11) << " ns" <<std::endl;
    // std::cout << measure_time<100, std::chrono::microseconds>(fact_count, 11) << " us" <<std::endl;
    // std::cout << measure_time<100, std::chrono::milliseconds>(fact_count, 11) << " ms" <<std::endl;
}