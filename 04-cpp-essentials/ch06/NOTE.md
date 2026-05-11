# Chapitre 6 — Opérateurs (learncpp)

Notes personnelles d'étude du Chapter 6 de learncpp.com.
Fichier d'exercice : `06_operators.cpp`.

---

## 6.1 — Précédence et associativité

**Concept** : chaque opérateur a une **priorité** qui détermine l'ordre d'évaluation.
`*` et `/` ont priorité plus élevée que `+` et `-`.

```cpp
int a = 2 + 3 * 4;     // 14 (multiplication d'abord)
int b = (2 + 3) * 4;   // 20 (parenthèses forcent l'ordre)
```

**Règle pro** : en cas de doute, **mets des parenthèses**. C'est gratuit en performance, et ça aide la lecture.

| Niveau | Opérateurs |
|---|---|
| 1 (le plus prioritaire) | `()`, `[]`, `.`, `->` |
| 2 | `++`, `--`, `!`, unary `-` |
| 3 | `*`, `/`, `%` |
| 4 | `+`, `-` |
| 5 | `<`, `<=`, `>`, `>=` |
| 6 | `==`, `!=` |
| 7 | `&&` |
| 8 | `||` |
| 9 | `=`, `+=`, `-=`, etc. |

---

## 6.4 — Pré-increment vs post-increment

**Concept** : `++x` (préfixe) et `x++` (suffixe) ont le **même effet** sur `x`, mais leur **valeur retournée** diffère.

```cpp
int x = 5;
int y = x++;   // POST : y reçoit 5, puis x devient 6
int u = 5;
int v = ++u;   // PRE  : u devient 6, puis v reçoit 6
```

**Règle pro** : préférer `++x` (pré) — c'est plus performant car pas de copie temporaire.
- Pour les types simples (`int`), le compilo optimise les deux à l'identique.
- Pour les types complexes (itérateurs, objets), la version postfixe **alloue une copie**.

**Convention en boucles** : `for (auto it = begin(); it != end(); ++it)` (jamais `it++`).

---

## 6.6 — ⚠️ Comparaison de flottants

**Problème** : à cause de la représentation IEEE 754, l'arithmétique flottante est **imprécise**.

```cpp
double d1 = 0.1 + 0.2;
double d2 = 0.3;
if (d1 == d2) { ... }  // FAUX ! d1 ≈ 0.30000000000000004
```

**Solution** : comparer avec une **tolérance (epsilon)** :

```cpp
#include <cmath>
constexpr double epsilon = 1e-9;
if (std::abs(d1 - d2) < epsilon) {
    // d1 et d2 sont "essentiellement égaux"
}
```

Cette technique est universelle en calcul numérique (simulation optique, physique, finance, etc.).

---

## 6.7 — Short-circuit evaluation (`&&`, `||`)

**Concept** : `&&` et `||` évaluent **de gauche à droite** et s'arrêtent dès que le résultat est connu.

- `a && b` : si `a` est `false`, `b` n'est **pas évalué**.
- `a || b` : si `a` est `true`, `b` n'est **pas évalué**.

**Application — protection contre les null pointers** :

```cpp
int* ptr = nullptr;
if (ptr != nullptr && *ptr > 0) {
    // safe : *ptr n'est lu que si ptr non-null
}
```

⚠️ **L'ordre compte !** Le mauvais ordre cause un segfault :

```cpp
if (*ptr > 0 && ptr != nullptr) {  // 💥 segfault — déréférence AVANT le check
```

**Règle pro** : toujours mettre la **garde** (`ptr != nullptr`) en **premier**.

---

## Bonnes pratiques transversales (Chapter 6)

1. **Parenthèses en cas de doute** sur la précédence.
2. **`++x` plutôt que `x++`** par défaut (perfs).
3. **Jamais `==` sur des flottants** — toujours `std::abs(a-b) < epsilon`.
4. **Short-circuit** = protection gratuite contre les segfaults, à utiliser systématiquement.

---

## Glossaire

- **Précédence** : ordre dans lequel les opérateurs sont évalués.
- **Associativité** : sens d'évaluation pour des opérateurs de même précédence (souvent gauche-à-droite).
- **Pré-increment** : `++x` retourne la valeur **après** incrément.
- **Post-increment** : `x++` retourne la valeur **avant** incrément.
- **Epsilon** : petite tolérance pour les comparaisons flottantes (typiquement `1e-9`).
- **Short-circuit evaluation** : `&&` et `||` arrêtent l'évaluation dès que le résultat est déterminé.