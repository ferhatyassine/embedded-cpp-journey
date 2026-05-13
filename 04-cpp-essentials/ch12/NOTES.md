# Chapitre 12 — References & Pointers (learncpp)

> Notes du chapitre le plus important du cours C++.
> Diviser en 3 parties :
> - **Partie 1** : Lvalue references (ce fichier)
> - **Partie 2** : Pointers (à venir)
> - **Partie 3** : const-pointers, return by ref, std::optional (à venir)

---

## 12.3 — Lvalue references (`T&`)

**Concept** : une **référence** est un **alias** pour une variable existante.
Une fois liée, elle ne peut **pas** être réassignée à une autre variable.

```cpp
int x{5};
int& ref{x};   // ref est un alias pour x
ref = 10;      // modifie x aussi (x devient 10)
```

**Caractéristiques importantes** :

| Propriété | Détail |
|---|---|
| **Initialisation obligatoire** | Une référence non initialisée = erreur |
| **Non-réassignable** | `ref = y` modifie l'original, pas le binding |
| **Pas de "null"** | Une référence pointe toujours vers un objet valide |
| **Même adresse** | `&x == &ref` |

**Syntaxe — distinction critique** :
- `int& r` (dans un **type**) → "référence vers int"
- `&x` (dans une **expression**) → "adresse de x" (pointeur — Partie 2)

Le `&` est **contextuel**. C'est une source classique de confusion.

**Fichier** : `01_references.cpp`

---

## 12.4 — `const` references (`const T&`)

**Concept** : référence en **lecture seule**.

```cpp
const int& read_only{x};
// read_only = 99;  // ❌ erreur de compilation
std::cout << read_only;  // ✅ lecture autorisée
```

**Usage principal** : paramètres de fonction pour des gros objets que la fonction ne doit pas modifier.

---

## 12.5 & 12.6 — Pass by reference

**3 façons de passer un paramètre à une fonction** :

| Forme | Sens | Coût | Modifs visibles ? |
|---|---|---|---|
| `void f(T x)` | Pass by **value** | copie complète | ❌ non |
| `void f(T& x)` | Pass by **reference** | alias (gratuit) | ✅ oui |
| `void f(const T& x)` | Pass by **const reference** | alias (gratuit) | ❌ non (lecture seule) |

**Exemples** :

```cpp
void increment_value(int n) { n++; }    // x reste inchangé après l'appel
void increment_ref(int& n) { n++; }     // x est modifié
void print(const std::string& s) {       // lit s sans copier
    std::cout << s;
}
```

**Règles pro** :

1. **Types primitifs** (`int`, `char`, `bool`) : pass by **value** (`int n`).
   La copie est gratuite (8 octets max).

2. **Gros objets** (`std::string`, `std::vector`, structs, classes) :
   - Si lecture seule → **`const T&`**
   - Si modification → **`T&`**
   - Pass by value = **copie inutile** = perf nulle.

**Tu utilisais déjà ce pattern** dans `cmd_add` du TODO CLI :
```cpp
void cmd_add(const std::string& title) { ... }   // ✅ const ref
```

**Fichier** : `02_pass_by_ref.cpp`

---

## ⚠️ Pièges à connaître

### 1. Référence vers une variable temporaire
```cpp
int& bad = 5;          // ❌ erreur : 5 n'est pas une lvalue
const int& ok = 5;     // ✅ une const ref peut binder à une temporaire
```

### 2. Référence "rebindée" — illusion
```cpp
int a{1}, b{2};
int& ref{a};
ref = b;    // ⚠️ Ce N'EST PAS "ref pointe maintenant vers b".
            // C'est "a = b", donc a devient 2. ref reste un alias de a.
```

Les références sont **immutables dans leur binding**. C'est leur force et leur limitation.

### 3. Dangling reference
```cpp
int& dangling_ref() {
    int local{42};
    return local;       // ❌ local meurt à la sortie, ref pointe sur du garbage
}
```

Ne **jamais** retourner une référence vers une variable locale.

---

## Bonnes pratiques transversales (Partie 1)

1. **Pass by `const T&`** pour tout objet non-trivial en lecture seule.
2. **Pass by value** pour les types primitifs (`int`, `bool`, `char`, ...).
3. **Pass by `T&`** uniquement quand on veut modifier l'appelant.
4. **Une référence doit toujours être initialisée** à un objet valide.
5. **Ne jamais retourner une référence locale**.

---

## Glossaire

- **Lvalue** : expression qui a une adresse identifiable (une "case mémoire"), comme une variable. Peut être à gauche d'un `=`.
- **Rvalue** : expression temporaire sans adresse persistante, comme un littéral ou le résultat d'une fonction. Peut être à droite d'un `=`.
- **Référence** : alias non-réassignable vers une lvalue.
- **`const T&`** : référence en lecture seule, principal idiome pour les paramètres en pro.
- **Pass by value** : la fonction reçoit une copie.
- **Pass by reference** : la fonction reçoit un alias sur l'original.
- **Dangling reference** : référence qui pointe vers une mémoire qui n'existe plus.