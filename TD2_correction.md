# TD2 : Algorithmes de recherche et de tri

Aya El Fennouri

## Fichiers

- `td2_exercice1.c` : recherche linéaire, recherche par sauts, recherche dichotomique
- `td2_exercice2.c` : tri par sélection, insertion, bulles, fusion, rapide

Pour compiler et lancer :

```
gcc td2_exercice1.c -o exercice1
./exercice1

gcc td2_exercice2.c -o exercice2
./exercice2
```

## Exercice 1 : The Lost Artifact

**Q1.** `is_sorted_increasing` parcourt le tableau une fois et vérifie que `A[i] < A[i+1]` pour chaque case. Complexité : O(n).

**Q2. Recherche linéaire.** On regarde les cases une par une jusqu'à trouver x.
Pire cas : **O(n)**, quand x est à la fin du tableau ou absent.

**Q3. Recherche par sauts.** On avance par blocs de taille ⌊√n⌋, puis on cherche case par case dans le bon bloc.
Il y a au plus √n sauts et au plus √n cases à regarder dans le bloc, donc pire cas : **O(√n)**.
(Comme vu en cours : n/m + m est minimal pour m = √n.)

**Q4. Recherche dichotomique.** À chaque étape on compare x avec la case du milieu et on garde une seule moitié.
Le nombre de cases est divisé par 2 à chaque tour, donc pire cas : **O(log n)**.

**Q5. Comparaison.** On cherche le dernier élément (pire cas) dans des tableaux triés de taille 1 000 à 1 000 000.

- Sans la vérification du tri, la recherche dichotomique est la plus rapide, puis la recherche par sauts, puis la recherche linéaire. Cela correspond aux complexités O(log n) < O(√n) < O(n).
- Avec la vérification, `jump_search` et `binary_search` deviennent presque aussi lentes que la recherche linéaire. La vérification `is_sorted_increasing` coûte O(n) et cache complètement le gain de l'algorithme : le temps total devient O(n) pour les trois.
- Conclusion : il vaut mieux vérifier le tri une seule fois (ou savoir que le tableau est trié), puis faire beaucoup de recherches rapides.

## Exercice 2 : The Tournament Rankings

**Q1.** `swap_int` échange deux entiers grâce à leurs adresses, `is_sorted_ascending` vérifie que `A[i] <= A[i+1]` (les scores égaux sont autorisés), `copy_array` recopie un tableau case par case.

| Tri | Meilleur cas | Pire cas | Explication |
|---|---|---|---|
| Sélection (Q2) | O(n²) | **O(n²)** | Pour chaque case, on parcourt tout le reste pour trouver le minimum, même si le tableau est déjà trié. |
| Insertion (Q3) | **O(n)** | **O(n²)** | Meilleur cas : tableau déjà trié, aucun décalage. Pire cas : tableau trié à l'envers, chaque élément remonte jusqu'au début. |
| Bulles (Q4) | O(n) | **O(n²)** | Jusqu'à n-1 passages de n comparaisons. Avec l'arrêt quand il n'y a aucun échange, un tableau déjà trié prend un seul passage. |
| Fusion (Q5) | O(n log n) | **O(n log n)** | On coupe en deux log n fois, et chaque fusion d'un niveau coûte n. |
| Rapide (Q6) | **O(n log n)** | **O(n²)** | Meilleur cas : le pivot coupe le tableau en deux moitiés égales. Pire cas : le pivot est toujours le plus petit ou le plus grand (par exemple un tableau déjà trié avec le dernier élément comme pivot). |

**Q7. Comparaison.** Chaque tri reçoit une copie identique du même tableau aléatoire (avec `copy_array`).

- Les trois tris en O(n²) deviennent très lents quand n grandit : quand n est multiplié par 5 (10 000 → 50 000), le temps est multiplié par environ 25 = 5².
- Le tri à bulles est le plus lent, car il fait beaucoup d'échanges. Le tri par insertion est le plus rapide des trois tris simples.
- Le tri fusion et le tri rapide restent très rapides, ce qui confirme O(n log n).
- Le tri rapide est un peu plus rapide que le tri fusion en pratique, car il trie sur place sans tableau temporaire (comme dit dans le cours : « very fast in practice »).
