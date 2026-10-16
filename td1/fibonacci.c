/*
 * TD1 - Exercice 1 : Fibonacci
 *
 * 1. Algorithme naif (recursif)        -> temps O(2^n), memoire O(n)
 * 2. Programmation dynamique (memo)    -> temps O(n),   memoire O(n)
 * 3. Comparaison des temps avec clock()
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 1. Version naive : on applique directement la definition
 *    F(n) = F(n-1) + F(n-2)
 *    Probleme : on recalcule plein de fois les memes valeurs. */
long long fib_naive(int n)
{
    if (n <= 1)
        return n;
    return fib_naive(n - 1) + fib_naive(n - 2);
}

/* 2. Version programmation dynamique (comme dans le cours)
 *    dp[i] = -1 veut dire "pas encore calcule".
 *    Chaque F(i) est calcule une seule fois puis garde dans dp. */
long long fib_dp_rec(int n, long long dp[])
{
    if (n <= 1)
        return n;
    if (dp[n] != -1)          /* deja calcule -> on le renvoie direct */
        return dp[n];
    dp[n] = fib_dp_rec(n - 1, dp) + fib_dp_rec(n - 2, dp);
    return dp[n];
}

long long fib_dp(int n)
{
    long long *dp = malloc((n + 1) * sizeof(long long));
    if (dp == NULL) {
        printf("Erreur malloc\n");
        exit(1);
    }
    for (int i = 0; i <= n; i++)
        dp[i] = -1;

    long long res = fib_dp_rec(n, dp);
    free(dp);
    return res;
}

int main(void)
{
    clock_t debut, fin;
    double t_naive, t_dp;

    printf("  n | F(n)              | naive (s)  | dp (s)\n");
    printf("----+-------------------+------------+-----------\n");

    /* on s'arrete a 45 sinon la version naive prend trop de temps */
    for (int n = 5; n <= 45; n += 5) {
        debut = clock();
        long long a = fib_naive(n);
        fin = clock();
        t_naive = (double)(fin - debut) / CLOCKS_PER_SEC;

        debut = clock();
        long long b = fib_dp(n);
        fin = clock();
        t_dp = (double)(fin - debut) / CLOCKS_PER_SEC;

        if (a != b)
            printf("Attention : les deux versions ne donnent pas le meme resultat !\n");

        printf(" %2d | %-17lld | %10.6f | %10.6f\n", n, a, t_naive, t_dp);
    }

    /* la version dp marche aussi pour des n beaucoup plus grands */
    debut = clock();
    long long big = fib_dp(90);
    fin = clock();
    printf("\nAvec la dp : F(90) = %lld en %f s\n",
           big, (double)(fin - debut) / CLOCKS_PER_SEC);
    printf("(F(93) depasse deja la limite d'un long long)\n");

    return 0;
}
