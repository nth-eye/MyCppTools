// #include <chrono>
#include <cstddef>
#include <cstdbool>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <cstdlib>

// // \brief Measure execution time of a function.
// // \tparam N Number of function calls over which result will be averaged.
// // \tparam D Duration type in which measure time.
// // \tparam Fn Function to measure.
// // \tparam Args Function arguments for perfect forwarding.
// // \return Average execution time.
// template<size_t N = 1, class D = std::chrono::nanoseconds, class Fn, class ...Args>
// auto measure_time(Fn &&fn, Args &&...args)
// {
//     const auto start = std::chrono::high_resolution_clock::now();
//     for (auto i = 0; i < N; ++i) (fn)(std::forward<Args>(args)...);
//     const auto stop = std::chrono::high_resolution_clock::now();
//     return std::chrono::duration_cast<D>(stop - start).count() / static_cast<double>(N);
// }

// // \brief Specialization to measure execution time of a member function.
// // \tparam N Number of function calls over which result will be averaged.
// // \tparam D Duration type in which measure time. 
// // \tparam Fn Function to measure.
// // \tparam Ptr Pointer to object instance on which member function will be called.
// // \tparam Args Function arguments for perfect forwarding.
// // \return Average execution time.
// template<size_t N = 1, class D = std::chrono::nanoseconds, class Fn, class Ptr, class ...Args>
// auto measure_time(Fn &&fn, Ptr *ptr, Args &&...args)
// {
//     const auto start = std::chrono::high_resolution_clock::now();
//     for (auto i = 0; i < N; ++i) (ptr->*fn)(std::forward<Args>(args)...);
//     const auto stop = std::chrono::high_resolution_clock::now();
//     return std::chrono::duration_cast<D>(stop - start).count() / static_cast<double>(N);
// }

// Measure execution time of a function.
template<size_t N = 1, class Fn, class ...Args>
clock_t measure_time(Fn &&fn, Args &&...args)
{
    clock_t begin = clock();
    for (size_t i = 0; i < N; ++i) 
        fn(args...);
    clock_t end = clock();

    return (end - begin) / N;
}

// Measure execution time of a member function.
template<size_t N = 1, class Fn, class Ptr, class ...Args>
clock_t measure_time(Fn &&fn, Ptr *ptr, Args &&...args)
{
    clock_t begin = clock();
    for (size_t i = 0; i < N; ++i) 
        (ptr->*fn)(args...);
    clock_t end = clock();

    return (end - begin) / N;
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
float str_to_float(char *str)
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

// Convert string to integer. Return true if conversion was successful.
bool str_to_int(const char *str, long *val, int base)
{
    char *endptr;
    unsigned long res = strtoul(str, &endptr, base);

    if (endptr > str) {
        *val = res;
        return true;
    }
    return false;
}

// Convert string to integer. Return true if conversion was successful and int is in given range.
bool str_to_int_range(const char *str, long *val, int base, long min, long max)
{
    if (str_to_int(str, val, base) && *val >= min && *val <= max)
        return true;
    return false; 
}

// Convert string to hex array using map table.
int str_to_hex(const char *hex_str, uint8_t *byte_array, size_t byte_array_len)
{
    // Mapping of ASCII characters to hex values
    static const uint8_t hashmap[256] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //  !"#$%&'()*+,-./
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0123456789:;<=>?
        0x00, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // @ABCDEFGHIJKLMNO
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // PQRSTUVWXYZ[\]^_
        0x00, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // `abcdefghijklmno
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // pqrstuvwxyz{|}~.
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
    };
    size_t hex_str_len = strlen(hex_str);
    size_t i = 0, j = 0;
    // The output array size is half the hex_str length (rounded up)
    size_t byte_array_size = (hex_str_len + 1) / 2;

    if (byte_array_size > byte_array_len)
        return -1;

    if (hex_str_len & 1) {
        uint8_t idx = hex_str[0];
        byte_array[j] = hashmap[idx];
        i = j = 1;
    }
    for (; i < hex_str_len; i += 2, j++) {
        uint8_t idx0 = hex_str[i];
        uint8_t idx1 = hex_str[i + 1];
        byte_array[j] = (hashmap[idx0] << 4) | hashmap[idx1];
    }
    return byte_array_size;
}

// Splits string by given delimiter and saves pointers to "ptr_arr". Modifies string.
size_t split(char *str, char *ptr_arr[], const char *delim, size_t max_n_lines)
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

// Integer power function.
constexpr int ipow(int base, int exp)
{
    int result = 1;
    while (1) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }
    return result;
}

// Maps integer from one range to another.
int map(int val, int in_min, int in_max, int out_min, int out_max)
{
    double slope = 1.0 * (out_max - out_min) / (in_max - in_min);
    return out_min + slope * (val - in_min);
}
