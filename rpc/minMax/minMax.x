/* minmax.x */
struct IntArray {
    int values[100];
};

struct MinMax {
    int min;
    int max;
};

program MINMAX_PROG {
    version MINMAX_VERS {
        MinMax find_min_max(IntArray) = 1;
    } = 1;
} = 55555;
