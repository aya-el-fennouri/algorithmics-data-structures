/* TD2 - Exercice 2 : The Tournament Rankings
   Tri par selection, insertion, bulles, fusion et rapide */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---------- Question 1 : fonctions utiles ---------- */

/* echange deux entiers (on passe leurs adresses) */
void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* verifie que le tableau est trie dans l'ordre croissant (les egalites sont autorisees) */
int is_sorted_ascending(int A[], int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            return 0;
        }
    }
    return 1;
}

/* copie le tableau source dans le tableau destination */
void copy_array(int source[], int destination[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        destination[i] = source[i];
    }
}

void afficher_tableau(int A[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

/* ---------- Question 2 : tri par selection ---------- */
/* on cherche le plus petit et on le met au debut */
/* pire cas : O(n^2) */
void selection_sort(int A[], int n) {
    int i, j, min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }
        swap_int(&A[i], &A[min]);
    }
}

/* ---------- Question 3 : tri par insertion ---------- */
/* on insere chaque element a sa place dans la partie deja triee */
/* meilleur cas : O(n) (deja trie), pire cas : O(n^2) (trie a l'envers) */
void insertion_sort(int A[], int n) {
    int i, j, cle;
    for (i = 1; i < n; i++) {
        cle = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > cle) {
            A[j + 1] = A[j];   /* on decale vers la droite */
            j--;
        }
        A[j + 1] = cle;
    }
}

/* ---------- Question 4 : tri a bulles ---------- */
/* on compare les voisins et on les echange s'ils sont dans le mauvais ordre */
/* pire cas : O(n^2) */
void bubble_sort(int A[], int n) {
    int i, j;
    int echange;
    for (i = 0; i < n - 1; i++) {
        echange = 0;
        for (j = 0; j < n - 1 - i; j++) {
            if (A[j] > A[j + 1]) {
                swap_int(&A[j], &A[j + 1]);
                echange = 1;
            }
        }
        if (echange == 0) {
            break;   /* aucun echange : le tableau est deja trie */
        }
    }
}

/* ---------- Question 5 : tri fusion ---------- */
/* fusionne les deux parties triees A[debut..milieu] et A[milieu+1..fin] */
void fusion(int A[], int debut, int milieu, int fin) {
    int taille = fin - debut + 1;
    int *temp = malloc(taille * sizeof(int));
    int i = debut;
    int j = milieu + 1;
    int k = 0;

    /* on prend a chaque fois le plus petit des deux */
    while (i <= milieu && j <= fin) {
        if (A[i] <= A[j]) {
            temp[k] = A[i];
            i++;
        } else {
            temp[k] = A[j];
            j++;
        }
        k++;
    }
    /* on recopie ce qui reste */
    while (i <= milieu) {
        temp[k] = A[i];
        i++;
        k++;
    }
    while (j <= fin) {
        temp[k] = A[j];
        j++;
        k++;
    }
    /* on remet le resultat dans A */
    for (k = 0; k < taille; k++) {
        A[debut + k] = temp[k];
    }
    free(temp);
}

void merge_sort_rec(int A[], int debut, int fin) {
    int milieu;
    if (debut < fin) {
        milieu = (debut + fin) / 2;
        merge_sort_rec(A, debut, milieu);      /* trie la moitie gauche */
        merge_sort_rec(A, milieu + 1, fin);    /* trie la moitie droite */
        fusion(A, debut, milieu, fin);         /* fusionne les deux */
    }
}

/* pire cas : O(n log n) */
void merge_sort(int A[], int n) {
    merge_sort_rec(A, 0, n - 1);
}

/* ---------- Question 6 : tri rapide ---------- */
/* le pivot est le dernier element (comme dans le cours) */
/* on met les plus petits a gauche, les plus grands a droite */
int partition(int A[], int low, int high) {
    int pivot = A[high];
    int i = low - 1;
    int j;
    for (j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            swap_int(&A[i], &A[j]);
        }
    }
    swap_int(&A[i + 1], &A[high]);   /* on met le pivot a sa place */
    return i + 1;
}

void quick_sort_rec(int A[], int low, int high) {
    int p;
    if (low < high) {
        p = partition(A, low, high);
        quick_sort_rec(A, low, p - 1);
        quick_sort_rec(A, p + 1, high);
    }
}

/* meilleur cas : O(n log n), pire cas : O(n^2) */
void quick_sort(int A[], int n) {
    quick_sort_rec(A, 0, n - 1);
}

/* ---------- Tests avec l'exemple du cours ---------- */
void tests(void) {
    int original[8] = {8, 3, 1, 7, 0, 10, 2, 5};
    int A[8];
    int a = 4, b = 9;

    printf("===== Tests =====\n");
    swap_int(&a, &b);
    printf("swap_int(4, 9) -> a = %d, b = %d\n", a, b);
    printf("tableau de depart : ");
    afficher_tableau(original, 8);

    copy_array(original, A, 8);
    selection_sort(A, 8);
    printf("selection : ");
    afficher_tableau(A, 8);

    copy_array(original, A, 8);
    insertion_sort(A, 8);
    printf("insertion : ");
    afficher_tableau(A, 8);

    copy_array(original, A, 8);
    bubble_sort(A, 8);
    printf("bulles    : ");
    afficher_tableau(A, 8);

    copy_array(original, A, 8);
    merge_sort(A, 8);
    printf("fusion    : ");
    afficher_tableau(A, 8);

    copy_array(original, A, 8);
    quick_sort(A, 8);
    printf("rapide    : ");
    afficher_tableau(A, 8);

    printf("is_sorted_ascending(depart) = %d (attendu 0)\n", is_sorted_ascending(original, 8));
    printf("is_sorted_ascending(trie)   = %d (attendu 1)\n", is_sorted_ascending(A, 8));
}

/* ---------- Question 7 : comparaison des temps ---------- */
/* mesure le temps d'un tri sur une copie du tableau original */
double mesurer(void (*tri)(int[], int), int original[], int copie[], int n) {
    clock_t debut;
    double temps;

    copy_array(original, copie, n);   /* chaque tri recoit la meme copie */
    debut = clock();
    tri(copie, n);
    temps = (double)(clock() - debut) / CLOCKS_PER_SEC;

    if (is_sorted_ascending(copie, n) == 0) {
        printf("ERREUR : le tableau n'est pas trie !\n");
    }
    return temps;
}

void comparaison(void) {
    int tailles[4] = {1000, 5000, 10000, 50000};
    int t, i, n;
    int *original;
    int *copie;

    printf("\n===== Comparaison des temps (en secondes) =====\n");
    printf("%8s %10s %10s %10s %10s %10s\n",
           "n", "selection", "insertion", "bulles", "fusion", "rapide");

    for (t = 0; t < 4; t++) {
        n = tailles[t];
        original = malloc(n * sizeof(int));
        copie = malloc(n * sizeof(int));

        /* scores aleatoires entre 0 et 1000000 */
        for (i = 0; i < n; i++) {
            original[i] = rand() % 1000001;
        }

        printf("%8d", n);
        printf(" %10.4f", mesurer(selection_sort, original, copie, n));
        printf(" %10.4f", mesurer(insertion_sort, original, copie, n));
        printf(" %10.4f", mesurer(bubble_sort, original, copie, n));
        printf(" %10.4f", mesurer(merge_sort, original, copie, n));
        printf(" %10.4f", mesurer(quick_sort, original, copie, n));
        printf("\n");

        free(original);
        free(copie);
    }
}

int main(void) {
    srand(time(NULL));
    tests();
    comparaison();
    return 0;
}
