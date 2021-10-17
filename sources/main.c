/*
** EPITECH PROJECT, 2021
** B-MAT-400-STG-4-1-203hotline-clement.muth [WSL: Ubuntu]
** File description:
** main
*/

#include <ctype.h>
#include <math.h>
#include <time.h>
#include "hotline.h"

calc_t *calc = NULL;

noreturn bool help(char const *restrict _filepath, int const _output)
{
    char *lineptr = NULL;
    size_t i = 500;
    FILE *stream = GET(FILE *, {
        my_assert(_filepath, PROTO_DATA, ASSERT_INFO("Cannot read property '_filepath' of undefined", ERR_TYPE, FAIL_EXEC), NULL);
        return (fopen(_filepath, "r"));
    });

    while (-1 != getline(&lineptr, &i, stream) && (printf("%s", lineptr)));
    free(lineptr);
    fclose(stream);
    exit(_output);
}


long double binomial_coeff(long double n, long double k)
{
    long double res = 1;
    long double lim = MIN(k, (n - k));

    if (k < 0 || k > n) eraise();
    if (n == 0 || k == 0) return (1);
    for (int i = 0; i < lim; i++) res *= (n - i) / (i + 1);
    return (res);
}

long double poisson(long double k, long double m)
{
    long double fact = 1;

    for (int i = 1; i <= k; ++i) fact *= i;
    return ((exp(-m) * pow(m, k)) / fact);
}

void poisson_distribution(int const nbr)
{
    long double var = nbr / 3600.0;
    long double overload = 0.0;
    long double m = (var * 3500) / 8;
    long double res = 0.0;
    clock_t start = clock();

    printf("Poisson distribution:\n");
    for (int k = 0, j = 0; k <= 50; k++, j++) {
        res = poisson(k, m);
        printf("%i -> %.3Lf", k, res);
        if (50 == k) printf("\n");
        else if (4 == j) (void)(printf("\n") && (j = -1));
        else printf("\t");
        if (25 < k) overload += res;
    }
    clock_t end = clock();
    unsigned long secondes = (unsigned long) difftime(end, start);
    printf("Overload: %.1Lf%%\n", overload * 100);
    printf("computation time: %.2f ms\n\n", ((double)(end - start) / CLOCKS_PER_SEC) * 100);
}

void binominal_distribution(int const nbr)
{
    long double var = nbr / 28800.0;
    long double overload = 0.0;
    long double res = 0.0;
    clock_t start = clock();

    printf("Binomial distribution:\n");
    for (int k = 0, j = 0; k <= 50; k++, j++) {
        res = (binomial_coeff(3500, k) * pow(var, k)) * pow((1 - var), (3500 - k));
        printf("%i -> %.3Lf", k, res);
        if (50 == k) printf("\n");
        else if (4 == j) (void)(printf("\n") && (j = -1));
        else printf("\t");
        if (25 < k) overload += res;
    }
    clock_t end = clock();
    printf("Overload: %.1Lf%%\n", overload * 100);
    printf("computation time: %.2f ms\n\n", ((double)(end - start) / CLOCKS_PER_SEC) * 100);
}

void print_combination(int const k, int const n)
{
    printf("%i-combinations of a set of size %d\n%.0f", n, k, binomial_coeff(k, n));
}

void arg_handling(arr_const_restrict _av, int const _ac)
{
    if (2 != _ac && 3 != _ac) eraise();
    if (2 == _ac) {
        if (!issdigit(_av[1])) eraise();
        if (atoi(_av[1]) < 0) eraise();
        binominal_distribution(atoi(_av[1]));
        poisson_distribution(atoi(_av[1]));
        exit(0);
    }
    if (3 == _ac) {
        if (!issdigit(_av[1]) || !issdigit(_av[2])) eraise();
        print_combination(atoi(_av[1]), atoi(_av[2]));
        exit(0);
    }
}

int main(int const ac, arr_const_restrict av)
{
    if (2 == ac && !strcmp(av[1], "-h")) help("./help.txt", 0);
    arg_handling(av, ac);
    return (0);
}