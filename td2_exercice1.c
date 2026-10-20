/* TD2 - Exercice 1 : The Lost Artifact
   Recherche lineaire, recherche par sauts (jump search) et recherche dichotomique (binary search) */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---------- Question 1 : verifier que le tableau est strictement croissant ---------- */
int is_sorted_increasing(int A[], int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (A[i] >= A[i + 1]) {
            return 0;   /* pas strictement croissant */
        }
    }
    return 1;
}

/* petite fonction pour avoir le minimum de deux entiers */
int minimum(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

/* ---------- Question 2 : recherche lineaire ---------- */
/* on regarde les cases une par une */
/* pire cas : O(n) (x est a la fin ou absent) */
int linear_search(int A[], int n, int x) {
    int i;
    for (i = 0; i < n; i++) {
        if (A[i] == x) {
            return i;
        }
    }
    return -1;
}

/* ---------- Question 3 : recherche par sauts ---------- */
/* version sans la verification du tri */
int jump_search_sans_verif(int A[], int n, int x) {
    int saut = 1;
    int prev = 0;
    int fin;
    int i;

    /* saut = partie entiere de racine de n */
    while ((saut + 1) * (saut + 1) <= n) {
        saut++;
    }

    fin = saut;
    /* on avance par blocs tant que la fin du bloc est plus petite que x */
    while (A[minimum(fin, n) - 1] < x) {
        prev = fin;
        fin = fin + saut;
        if (prev >= n) {
            return -1;   /* on a depasse la fin du tableau */
        }
    }

    /* on cherche x case par case dans le bon bloc */
    for (i = prev; i < minimum(fin, n); i++) {
        if (A[i] == x) {
            return i;
        }
    }
    return -1;
}

/* pire cas : O(racine(n)) pour la recherche, mais O(n) avec la verification */
int jump_search(int A[], int n, int x) {
    if (is_sorted_increasing(A, n) == 0) {
        return -1;
    }
    return jump_search_sans_verif(A, n, x);
}

/* ---------- Question 4 : recherche dichotomique ---------- */
/* version sans la verification du tri */
int binary_search_sans_verif(int A[], int n, int x) {
    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if (A[mid] == x) {
            return mid;
        } else if (A[mid] < x) {
            low = mid + 1;    /* x est dans la moitie droite */
        } else {
            high = mid - 1;   /* x est dans la moitie gauche */
        }
    }
    return -1;
}

/* pire cas : O(log n) pour la recherche, mais O(n) avec la verification */
int binary_search(int A[], int n, int x) {
    if (is_sorted_increasing(A, n) == 0) {
        return -1;
    }
    return binary_search_sans_verif(A, n, x);
}

/* ---------- Tests avec l'exemple du cours ---------- */
void tests(void) {
    int A[9] = {-21, -9, -2, 1, 3, 11, 12, 21, 22};
    int B[5] = {1, -2, 3, 11, 2};    /* tableau pas trie */

    printf("===== Tests =====\n");
    printf("is_sorted_increasing(A) = %d (attendu 1)\n", is_sorted_increasing(A, 9));
    printf("is_sorted_increasing(B) = %d (attendu 0)\n", is_sorted_increasing(B, 5));

    printf("linear_search(B, 11) = %d (attendu 3)\n", linear_search(B, 5, 11));
    printf("linear_search(A, 21) = %d (attendu 7)\n", linear_search(A, 9, 21));
    printf("jump_search(A, 21)   = %d (attendu 7)\n", jump_search(A, 9, 21));
    printf("binary_search(A, 21) = %d (attendu 7)\n", binary_search(A, 9, 21));

    printf("linear_search(A, 5)  = %d (attendu -1)\n", linear_search(A, 9, 5));
    printf("jump_search(A, 5)    = %d (attendu -1)\n", jump_search(A, 9, 5));
    printf("binary_search(A, 5)  = %d (attendu -1)\n", binary_search(A, 9, 5));

    printf("jump_search(A, -21)  = %d (attendu 0)\n", jump_search(A, 9, -21));
    printf("binary_search(A, 22) = %d (attendu 8)\n", binary_search(A, 9, 22));
    printf("jump_search(A, 100)  = %d (attendu -1)\n", jump_search(A, 9, 100));

    printf("jump_search(B, 11)   = %d (attendu -1 car B n'est pas trie)\n", jump_search(B, 5, 11));
    printf("binary_search(B, 11) = %d (attendu -1 car B n'est pas trie)\n", binary_search(B, 5, 11));
}

/* ---------- Question 5 : comparaison des temps ---------- */
void comparaison(void) {
    int tailles[4] = {1000, 10000, 100000, 1000000};
    int repetitions = 100;   /* une seule recherche est trop rapide pour clock() */
    int t, r, i, n, x;
    int *A;
    clock_t debut;
    double t_lin, t_jump, t_bin, t_jump_sv, t_bin_sv;

    printf("\n===== Comparaison des temps (%d recherches, en secondes) =====\n", repetitions);
    printf("%10s %10s %10s %10s %14s %14s\n",
           "n", "lineaire", "jump", "binaire", "jump sans ver", "bin sans ver");

    for (t = 0; t < 4; t++) {
        n = tailles[t];
        A = malloc(n * sizeof(int));

        /* tableau trie : 0, 2, 4, 6, ... */
        for (i = 0; i < n; i++) {
            A[i] = 2 * i;
        }
        x = A[n - 1];   /* on cherche le dernier element = pire cas pour la recherche lineaire */

        debut = clock();
        for (r = 0; r < repetitions; r++) linear_search(A, n, x);
        t_lin = (double)(clock() - debut) / CLOCKS_PER_SEC;

        debut = clock();
        for (r = 0; r < repetitions; r++) jump_search(A, n, x);
        t_jump = (double)(clock() - debut) / CLOCKS_PER_SEC;

        debut = clock();
        for (r = 0; r < repetitions; r++) binary_search(A, n, x);
        t_bin = (double)(clock() - debut) / CLOCKS_PER_SEC;

        debut = clock();
        for (r = 0; r < repetitions; r++) jump_search_sans_verif(A, n, x);
        t_jump_sv = (double)(clock() - debut) / CLOCKS_PER_SEC;

        debut = clock();
        for (r = 0; r < repetitions; r++) binary_search_sans_verif(A, n, x);
        t_bin_sv = (double)(clock() - debut) / CLOCKS_PER_SEC;

        printf("%10d %10.4f %10.4f %10.4f %14.6f %14.6f\n",
               n, t_lin, t_jump, t_bin, t_jump_sv, t_bin_sv);

        free(A);
    }
}

int main(void) {
    tests();
    comparaison();
    return 0;
}
