/*
 * TD1 - Exercice 2 : Nombres premiers
 *
 * On compte les nombres premiers strictement inferieurs a n.
 *
 * 1. Naif : pour chaque i, on teste les diviseurs jusqu'a sqrt(i)
 *           -> temps O(n * sqrt(n)), memoire O(1)
 * 2. Crible d'Eratosthene : on raye les multiples de chaque premier
 *           -> temps O(n log(log n)), memoire O(n)
 * 4. Comparaison des temps avec clock()
 *
 * (la question 3, la preuve de la complexite, est dans le README)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* renvoie 1 si x est premier, 0 sinon */
int est_premier(int x)
{
    if (x < 2)
        return 0;
    /* d * d <= x  revient a  d <= sqrt(x), sans utiliser de float */
    for (int d = 2; d * d <= x; d++) {
        if (x % d == 0)
            return 0;
    }
    return 1;
}

/* 1. Version naive */
int compter_naif(int n)
{
    int compteur = 0;
    for (int i = 2; i < n; i++) {
        if (est_premier(i))
            compteur++;
    }
    return compteur;
}

/* 2. Crible d'Eratosthene
 *    Idee : les multiples d'un nombre premier ne sont pas premiers.
 *    On part d'un tableau ou tout le monde est "peut-etre premier",
 *    et pour chaque premier p on raye 2p, 3p, 4p, ... */
int compter_crible(int n)
{
    if (n < 3)
        return 0;

    /* compose[i] = 1 si i est raye (pas premier), 0 sinon */
    char *compose = calloc(n, sizeof(char));   /* calloc met tout a 0 */
    if (compose == NULL) {
        printf("Erreur calloc\n");
        exit(1);
    }

    int compteur = 0;
    for (int p = 2; p < n; p++) {
        if (compose[p] == 0) {      /* p n'a jamais ete raye -> premier */
            compteur++;
            /* on commence a p*p : les multiples plus petits (2p, 3p...)
             * ont deja ete rayes par des premiers plus petits.
             * long long pour eviter le depassement de p*p */
            for (long long m = (long long)p * p; m < n; m += p)
                compose[m] = 1;
        }
    }

    free(compose);
    return compteur;
}

int main(void)
{
    clock_t debut, fin;
    int valeurs[] = {1000, 10000, 100000, 1000000, 10000000};
    int nb = 5;

    printf("        n | nb premiers | naif (s)   | crible (s)\n");
    printf("----------+-------------+------------+-----------\n");

    for (int k = 0; k < nb; k++) {
        int n = valeurs[k];

        debut = clock();
        int a = compter_naif(n);
        fin = clock();
        double t_naif = (double)(fin - debut) / CLOCKS_PER_SEC;

        debut = clock();
        int b = compter_crible(n);
        fin = clock();
        double t_crible = (double)(fin - debut) / CLOCKS_PER_SEC;

        if (a != b)
            printf("Attention : resultats differents pour n = %d !\n", n);

        printf(" %8d | %11d | %10.6f | %10.6f\n", n, a, t_naif, t_crible);
    }

    return 0;
}
