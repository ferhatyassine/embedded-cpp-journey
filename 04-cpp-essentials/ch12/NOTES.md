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


Les références sont **immutables dans leur binding**. C'est leur force et leur limitation.

### 3. Dangling reference
```cpp
int& dangling_ref() {
    int local{42};
    return local;       // ❌ local meurt à la sortie, ref pointe sur du garbage
}


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
```
---
 ## Partie- pointers

### Concept de base

un **pointer** est une variable qui **contient une adresse memoire** d'un autre objet

```cpp
int x{42};
int* ptr{&x}; // ptr contient l'adresse de x

std::cout << x;   // 42 (valeur)
std::cout << &X;  // 0x7ff... (adresse de x)
std::cout << ptr; // 0x7ff..  (idem,ptr contient cette adresse)
std::cout <<*ptr; // 42 (valeur A l'adresse contenue dans ptr)
```

**Operateurs cles**:
- `&x` -> adresse de x (operateur "adresse-of")
- `*ptr` -> valeur a l'adresse contenue dans ptr (operateur "dereference")

remarque : **`*` et `&` sont contextuels** :
- Dans un **type** : `int* p` = pointer vers int, `int& r`= reference vers int
-  Dans une **expression** : `*ptr` = dereferencement, `&x` = adresse de 

**Taille** : sur Linux 46-bit, ** tout pointer fait 8 octets**(peu importe le type pointé)
**Fichier** : `03_pointers_basics.cpp`
---
### reassignation et `nullptr`
**Difference cle avec les references** : un pointer peut etre **reassigne** :

```cpp
int* p{nullptr}; // pointer vide
if (p != nullptr) { /*safe to dereference*/}
if (p) {/* forme courte idiomatique*/}
```
**Dereferencer `nullptr` = SEGFAULT** (crash immediat).
**Bonne pratique : toujours **verifier avant de dereferencer**
**Dangling pointer** : pointer vers une memoire liberee ou hors scope = undefined behavior

**Fichier** :`04_pointers_reassign.cpp`

---
### `const` avec pointer
3 variantes a distinguer (lecture **droite - a - gauche**):
|Forme                  | Modifier `*ptr` ? | Reassigner `ptr` ? |
|---|---|---|
|`int* ptr`             |        YES        |         YES        |
|`const int* ptr`       |        NO         |         YES        |
|`int* const ptr`       |        YES        |         NO         |
|`const int* const ptr` |        NO         |         NO         |

**Astuce mnemo** : le `const s'appelique a ce qui est **juste a gauche**
- `const int *`  -> "const int" est a gauche du `*` -> la valeur pointee est const
- `int * const` -> "const" est a gauche de "ptr" -> le pointer lui-meme est const

**Usage embedded typique**
```cpp
unit32_t* const STATUS_REG{(unit32_t*)0x40021000};
*STATUS_REG = 1;    // ✅ ecriture dans le registre
// STATUS_REG = &x; // ❌ adresse fixe
```
**fichier** : `05_pointers_const.cpp`
---
### Pass by address

passer un **pointer** a une fonction = lui donner l'adresse de l'objet pour qu'elle puisse le modifier.

```cpp
void increment(int* n) {
    if(n == nullptr) return; // toujours check null
    (*n)++ // parentheses obligatoires : *n++ != (*n)++, priorite aux parenthese 
}

int x{5};
increment(&x); // x devient 6
increment (nullptr); //safe, ne plante pa , pas de crash
```
**piege classique** : `*n++` increment le **pointer**, pas la valeur. toujours `(*n)++`.
**operateur fleche `->`** : raccourci pour `(*ptr).membre` : 
```cpp
Task* t{&some_task};
t->done = true; // equivalent a (*t).done = true
```

**fichier** : `06_pass_by_address.cpp`
---
### pointers vs references - la comparaison final 

|critere            |    reference `T&` | pointer `T*`        |
|---|---|---|
|init obligatoire   |         ✅        |       ❌           |
|peut etre null     |         ❌        | ✅ (`nullptr`)     |
|reassignable       |         ❌        |       ✅           |
|syntaxe d'acces    | direct (`ref`)    |dereference(`*ptr`)  |
|arithmetique       |         ❌        |   ✅  (arrays)     |
---
**regle pro de choix de parametre de fonction** :
|CAS                                 |   Forme a utiliser   |
|---|---|
|Type primitif, lecture              |  `T` (par valeur)    |
|Gros objet , lecture, jamais null   | `const T&`           |
|Gros objet , lecture,peut etre null | `const T*`           |
|Modification , jamais null          | `T&`                 |
|Modification , peut etre null       | `T*`                 |
---
**En general** : preferer les **references**; n'utiliser les pointers que si on a besoin de `nullptr`, de la reassignation,
ou de l'arithmetique d'adresse.
---
## pieges a connaitre (part 2 )
1. **dereferencement d'un `nulptr`** = segfault.
2. **`(*ptr)++` vs `*ptr++`**: toujours mettre les parentheses.
3. **Dangling pointer** apres un free / fin de scope.
4. **comparer un pointer avec `0` ou `NULL`**: utiliser `nullptr` en C++ moderne.
5. **confusion `&` (adresse vs reference)** : c'est contextuel, lis bien la declaration .
---

## Glossaire (complements partie 2)
- **Pointer** : variable qui contient adresse memoire.
- **Address-of operator (`&`)** : retourne l'adresse d'une variable.
- **Dereference operator (`*`)** : acced a la valeur a l'adresse contenue dans un pointer.
- **`nullptr`** : pointer "vide" (introduit en C++11, a preferer a `NULL` ou `0`).
- **Arrow operator (`->`)**: raccourci pour `(*ptr).membre` .
- **Dangling pointer** : pointer vers une memoire qui n'existe plus.
- **Pass by adress** : passer un pointer en parametre de fonction.