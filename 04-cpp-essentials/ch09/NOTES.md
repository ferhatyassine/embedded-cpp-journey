# Chapter 9 - Error Handling (gestion des erreurs)
> notes de synthese en francais. Reference personnelle.
>chapitre learncpp.com couvrant les strategies de gestion d'erreur en c++17:
>exceptions, `std::optional<T>`, et leur combinaison.

---
## 1. concepts couverts
- Les 3 strategies historiques de gestion d'erreur en c++: valeur sentinelle,exception, `std::optional<T>`.
- Mecanique des exceptions : `try`,`throw`,`catch`, et hirarchie de `std::exception`.
- `std::optional<T>` (C++17) : un type qui exprime "valeur ou absence" sans surcoût d'exception.
- pattern de conversion : transformer une exception (imposee par la stdlib) en `std::optional` (plus simple cote appelant ).

---

## 2. Strategies de gestion d'erreur - quand utiliser quoi
| Strategie | Cas d'usage | Cout | Force le check ? |
|---|---|---|---|
| Valeur sentielle (`-1`,`nullptr`) | Code legacy C, perf critique | Leger | ❌ |
| Exception (`throw`) | Erreur **exceptionnelle** | Élevé (unwinding) | ✅ |
| `std::optional<T>` | Absence **attendue** | Quasi nul | ⚠️ (compilo aide) |

**Regle pratique** :
- Erreur **inattendue** (fichier corrompu, OOM,invariant cassé) -> `throw`.
- Absence **normale** (recherche,parse user input, lookup) -> `std::optional`.
- Sentinelle uniquement en code legacy ou perf critique extreme.
---

## 3. Exceptions : try / throw / catch
### Syntaxe de base

```cpp
#include
int safe_divide(int a, int b){
    if(b == 0)
    throw std::runtime_error("division par 0");
return a / b ;
}

try{
    int r = safe_divide(10,0);
}
catch (cons std::exception& e){
    std::cerr<<"Erreur: " <<e.what()<< '\n';
}
```
### Flux d'execution

1. `throw` interrompt immediatement la fonction.
2. La pile se deroule (stack unwinding) : les destructeurs des variables locales sont appeles (RAII).
3. L'execution saute au premier `catch` compatible.

### Hierarchie standard utile
| Classe | Quand|
|---|---|
|`std::runtime_error`| Erreur runtime generique |
|`std::logic_error`| Bug logique (precotions violees) |
|`std::invalid_argument`| Argument invalide passe a la stdlib (ex : `std::stoi("abc")`) |
|`std::out_of_range`| Index hors linites (ex : `vec.at(99)`) |
|`std::bad_alloc`| `new` qui n'a plus de memoire |`std::bad_optional_access`| `.value()` sur un optional vide |

Toutes heritent de `std::exception` et exposant `.what()`.

### Bonnes pratiques

- **Attraper par reference const** :`catch (const::exception& e)`.
- `catch (std::exception& e)` -> slicing, perte du type derive. A eviter.
- `catch (...)` -> attrape tout, mais perd toute info, A reserver au `main()` en dernier recours.
- **ordre des catch**: du plus specifique au plus general.
- **Ne pas throw pour le controle de flux** : c'est cher et ce n'est pas l'intention.
---

## 4. std::optional<T>
### Syntaxe de base 
```cpp
#include

std::optional parse_int(const std::string& s){
    try{
        return std::stoi(s)  // optional contient la valeur 
    }
    catch (const std::exception&){
        return std::nullopt;   // optional vide
    }
}
```
### 3 facons de lire un optional

```cpp
auto opt = parse_int("42");
// 1) Explicite : has_value() + value()
if(opt.has_value())
std::cout <<opt.value();

//2) Court : if(opt) + *opt
if(opt)
std::cout <<*opt;

//3) Safe : value_or(fallback)
int n = opt.value_or(-1);
```

### Regle d'or
- `.value()` sur optional vide -> **exception** `std::bad_optional_access`.
- `*opt` sur optional vide -> **UB** (undefined behavior)
- **Toujours tester avant** OU utiliser `value_or(...)`.
- `std::nullopt` est la constante "absent". Pas de `NULL` en C++.

## 5. Pattern de conversion exception -> optional

Quand la stdlib **impose** des exceptions (ex: `srd::stoi`), mais que tu veux exposer une API plus simple a ton appelant, tu **traduis**:
```cpp
std::optional parse_int(const std::string& s){
    try{
        return std::stoi(s);
    }
    catch (const std::exception&){
        return std::nullopt;
    }
}
```

c'est exactement le cas pour proteger les inputs CLI (ex : `todo done abc` dans le TODO CLI).

---

## 6. Bonnes pratiques générales

- **Zéro warning à la compilation**. Un warning = un bug potentiel. Discipline non négociable.
- `catch` par référence const, jamais par valeur.
- Pas de `throw` pour absence "normale" → préférer `optional`.
- Pas d'`optional` pour erreur "exceptionnelle" → préférer exception.
- Toujours **tester `.value_or(...)`** ou **`if (opt)`** avant `*opt`.

---

## 7. Pièges rencontrés

| Piège | Symptôme | Solution |
|---|---|---|
| Fonction `int` sans `return` final | `warning: control reaches end of non-void function` + valeur aberrante au runtime (UB) | Toujours un `return` couvrant les cas hors `throw` |
| Oubli de `#include <optional>` | `'optional' is not a member of 'std'` | Ajouter l'include |
| Oubli de `-std=c++17` | `'optional' is not a member of 'std'` | Ajouter le flag |
| `.value()` sur optional vide | Exception `std::bad_optional_access` | Tester avec `has_value()` ou utiliser `value_or` |
| Catch par valeur | Slicing du type dérivé | Toujours `catch (const T& e)` |
| Catch trop général en premier | Warning + le catch spécifique n'est jamais atteint | Du plus spécifique au plus général |

---

## 8. Glossaire

- **Exception** : objet lancé via `throw` qui interrompt l'exécution et remonte la pile jusqu'à un `catch` compatible.
- **Stack unwinding** : déroulement de la pile pendant le throw, avec appel des destructeurs locaux (essentiel pour RAII).
- **`std::exception`** : classe mère de toutes les exceptions standard, avec méthode `.what()`.
- **`std::optional<T>`** : type wrapper "valeur ou rien" introduit en C++17.
- **`std::nullopt`** : constante représentant l'absence de valeur dans un optional.
- **`.value()`** : extrait la valeur d'un optional, throw si vide.
- **`value_or(x)`** : extrait la valeur, ou `x` si vide. Safe.
- **RAII** (Resource Acquisition Is Initialization) : pattern C++ qui garantit la libération des ressources via les destructeurs, même en cas d'exception.
- **Sentinelle** : valeur "spéciale" utilisée pour signaler une erreur ou une absence (ex : `-1`, `nullptr`). Pratique C dépréciée en C++ moderne.

---

## 9. Exercices réalisés

- `01_exceptions.cpp` — try/throw/catch sur `safe_divide` + `std::stoi`.
- `02_optional.cpp` — `parse_int` retournant `std::optional<int>`, démonstration des 3 façons de lire.

---

**Fin du chapitre 9.**

