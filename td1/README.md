# TD1 - Introduction to Algorithms

| Exercice | Fichier | Contenu |
|---|---|---|
| 1. Fibonacci | `fibonacci.c` | version naive (récursive) + programmation dynamique + temps avec `clock()` |
| 2. Nombres premiers | `primes.c` | version naïve en O(n√n) + crible d'Ératosthène + temps avec `clock()` |

## Compiler et lancer

```
make run
```

ou sans `make` :

```
gcc -Wall -Wextra -std=c99 fibonacci.c -o fibonacci
gcc -Wall -Wextra -std=c99 primes.c -o primes
./fibonacci
./primes
```

## Exercice 1 - Fibonacci

| Version | Temps | Mémoire |
|---|---|---|
| Naïve (récursive) | O(2^n) | O(n) (profondeur de la récursion) |
| Programmation dynamique | O(n) | O(n) (tableau `dp` + récursion) |

La version naïve recalcule plusieurs fois les mêmes valeurs : `F(n-1)` recalcule `F(n-2)`,
qui est déjà calculé par l'autre appel. Avec la dp, chaque `F(i)` est calculé une seule fois.

Résultats obtenus sur ma machine :

| n | naïve (s) | dp (s) |
|---|---|---|
| 30 | 0.007 | 0.000002 |
| 35 | 0.078 | 0.000005 |
| 40 | 0.866 | 0.000006 |
| 45 | 9.648 | 0.000006 |

Quand n augmente de 5, le temps de la version naïve est multiplié par environ 11
(≈ φ⁵ avec φ ≈ 1.618), ce qui confirme la croissance exponentielle.
La version dp reste quasiment instantanée.

## Exercice 2 - Nombres premiers

### 1. Version naïve - O(n√n)

Pour chaque `i < n`, on teste les diviseurs `d` tant que `d * d <= i`.
On fait n tests et chacun coûte au plus √n, donc O(n√n).

### 2. Crible d'Ératosthène

Indice du TD : les multiples d'un nombre premier ne sont pas premiers.
On garde un tableau `compose[]`. Quand on trouve un nombre `p` pas encore rayé,
il est premier, et on raye tous ses multiples `p², p² + p, p² + 2p, ...`.
(On peut commencer à `p²` car les multiples plus petits ont déjà été rayés.)

### 3. Preuve de la complexité O(n log(log n))

Pour chaque premier `p ≤ n`, la boucle intérieure raye au plus `n / p` cases.
Le nombre total d'opérations est donc :

```
n/2 + n/3 + n/5 + n/7 + ...  =  n × (somme des 1/p pour p premier ≤ n)
```

D'après l'indice du TD :

```
somme des 1/p (p premier ≤ n)  ≤  log(log(n + 1)) + M
```

où M est la constante de Meissel-Mertens (≈ 0.26).
Donc le nombre d'opérations est au plus :

```
n × (log(log(n + 1)) + M)
```

La boucle extérieure ajoute O(n) (on passe une fois sur chaque case).
Au total : O(n) + O(n log(log n)) = **O(n log(log n))**.

Mémoire : le tableau `compose` de taille n, donc **O(n)**.

### 4. Comparaison des temps

| n | nb de premiers | naïf (s) | crible (s) |
|---|---|---|---|
| 10 000 | 1 229 | 0.0003 | 0.00007 |
| 100 000 | 9 592 | 0.006 | 0.0008 |
| 1 000 000 | 78 498 | 0.135 | 0.007 |
| 10 000 000 | 664 579 | 3.319 | 0.115 |

Pour n = 10⁷, le crible est environ 30 fois plus rapide.
Les temps changent selon la machine, mais l'écart grandit toujours avec n.
