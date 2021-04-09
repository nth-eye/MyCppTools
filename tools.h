#include <chrono>
#include <cstring>

namespace tool {

// \brief Measure execution time of a function.
// \tparam N Number of function calls over which result will be averaged.
// \tparam D Duration type in which measure time.
// \tparam Fn Function to measure.
// \tparam Args Function arguments for perfect forwarding.
// \return Average execution time.
template<size_t N = 1, class D = std::chrono::nanoseconds, class Fn, class ...Args>
auto measure_time(Fn &&fn, Args &&...args)
{
    const auto start = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < N; ++i) (fn)(std::forward<Args>(args)...);
    const auto stop = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<D>(stop - start).count() / static_cast<double>(N);
}

// \brief Specialization to measure execution time of a member function.
// \tparam N Number of function calls over which result will be averaged.
// \tparam D Duration type in which measure time. 
// \tparam Fn Function to measure.
// \tparam Ptr Pointer to object instance on which member function will be called.
// \tparam Args Function arguments for perfect forwarding.
// \return Average execution time.
template<size_t N = 1, class D = std::chrono::nanoseconds, class Fn, class Ptr, class ...Args>
auto measure_time(Fn &&fn, Ptr *ptr, Args &&...args)
{
    const auto start = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < N; ++i) (ptr->*fn)(std::forward<Args>(args)...);
    const auto stop = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<D>(stop - start).count() / static_cast<double>(N);
}

// Return n-th bit of arr starting from LSB.
constexpr uint8_t get_bit(const uint8_t *arr, int n)
{
    return (arr[n >> 3] >> (n & 7)) & 1;
}

// Return n-th bit of arr starting from MSB.
constexpr uint8_t get_bit_r(const uint8_t *arr, int n)
{
    return (arr[n >> 3] >> (7 - (n & 7))) & 1;
}

// Set n-th bit in array of bytes starting from LSB.
constexpr void set_bit(uint8_t *arr, int n)
{
    arr[n >> 3] |= 1 << (n & 7);
}

// Clear n-th bit in array of bytes starting from LSB.
constexpr void clr_bit(uint8_t *arr, int n)
{
    arr[n >> 3] &= ~(1 << (n & 7));
}

// Print bits nicely with MSB at left.
void print_bits(uint8_t *arr, int n, int pos)
{
    for (int i = 0; i < n; ++i) {
        if (!(i & 7))
            printf(" ");
        if (!(i & 63))
            printf("\n");
        printf("%d", get_bit_r(arr, pos++));
    }
    printf("\n");
}

// Print bits nicely from left to right.
void print_bytes(uint8_t *arr, int n, int pos)
{
    for (int i = 0; i < n; ++i) {
        if (!(i & 3))
            printf(" ");
        if (!(i & 31))
            printf("\n");
        printf("%02x", arr[pos++]);
    }
    printf("\n");
}

// Convert string to float.
constexpr float str_to_float(char *str)
{
    float result = 0.0;
    int len = strlen(str);
    int dot_pos = 0;

    for (int i = 0; i < len; ++i) {
        if (str[i] == '.')
            dot_pos = len - i  - 1;
        else
            result = result * 10.0 + (str[i] - '0');
    }

    while (dot_pos--)
        result /= 10.0;

    return result;
}

// Splits string by given delimiter and saves pointers to "ptr_arr". Modifies string.
constexpr size_t split(char *str, char *ptr_arr[], const char *delim, size_t max_n_lines)
{  
    char *split = strtok(str, delim);
    size_t i = 0;

    while (split && i < max_n_lines) {
        ptr_arr[i++] = split;
        split = strtok(NULL, delim);
    }
    ptr_arr[i] = 0;

    return i;
}

}
