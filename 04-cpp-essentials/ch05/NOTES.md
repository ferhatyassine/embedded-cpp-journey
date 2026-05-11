# Chapitre 5 — Constantes et chaînes (learncpp)

Notes personnelles d'étude du Chapter 5 de learncpp.com.
Chaque section correspond à un exercice `0X_*.cpp` dans ce dossier.

---

## 5.1 — Variables constantes (`const`)

**Concept** : `const` = variable en lecture seule, initialisation obligatoire à la déclaration.

| Règle | Pourquoi |
|---|---|
| Utiliser `const` dès que possible | Empêche les modifications accidentelles |
| Doit être initialisé à la déclaration | Erreur de compilation sinon |
| Auto-documentation | Le lecteur sait que la valeur est fixe |

**Fichier** : `01_const.cpp`

```cpp
--- EN ---
# Chapter 5 — Constants and Strings (learncpp)

Personal study notes from learncpp.com Chapter 5.
Each section has a corresponding `0X_*.cpp` exercise in this folder.

---

## 5.1 — Constant variables (`const`)

**Concept** : `const` = read-only variable, must be initialized at declaration.

| Rule | Why |
|---|---|
| Use `const` whenever possible | Prevents accidental modification |
| Must initialize at declaration | Compiler error otherwise |
| Self-documents intent | Reader knows the value is fixed |

**File** : `01_const.cpp`

```cpp
const int max_attempts{3};
// max_attempts = 5;  // ❌ compile error
```

---

## 5.2 — Literals

**Concept** : values written directly in code, with optional suffixes to specify type.

| Suffix | Type | Example |
|---|---|---|
| (none) | `int` / `double` | `42`, `3.14` |
| `L` | `long` | `42L` |
| `LL` | `long long` | `42LL` |
| `u` / `U` | `unsigned` | `42u` |
| `f` | `float` | `3.14f` |

**Bonus C++14** : digit separator `'` for readability — `1'000'000` = `1000000`.

**Pitfall — narrowing conversion** :
```cpp
float f{3.14};   // ⚠️ double → float (warning with -Wnarrowing or -Wpedantic)
float f{3.14f};  // ✅ correct
```

> Note : `-Wnarrowing` is NOT in `-Wall -Wextra` by default. Add it explicitly.

**File** : `02_literals.cpp`

---

## 5.3 — Numeral systems

| Base | Prefix | Example | Value |
|---|---|---|---|
| Decimal | (none) | `42` | 42 |
| Octal | `0` | `052` | 42 |
| Hexadecimal | `0x` | `0x2A` | 42 |
| Binary (C++14) | `0b` | `0b101010` | 42 |

**Use in embedded** :
- `0x` for memory addresses, register values (1 hex digit = 4 bits = 1 nibble)
- `0b` for bit masks

**Stream manipulators** for display :
```cpp
std::cout << std::hex << 255;  // "ff"
std::cout << std::oct << 255;  // "377"
std::cout << std::dec << 255;  // back to "255" — always reset!
```

**Bit testing** (essential for embedded) :
```cpp
constexpr int FLAG_LASER_ON{0b0001};
int status{0b0111};
bool laser = (status & FLAG_LASER_ON);  // bitwise AND
```

**File** : `03_numeral.cpp`

---

## 5.5 & 5.6 — `constexpr`

**Concept** : `constexpr` = constant evaluated **at compile-time**, not runtime.

| Keyword | Modifiable? | Computed when? |
|---|---|---|
| `const` | ❌ | Init time (can be runtime) |
| `constexpr` | ❌ | **Compile time mandatory** |

**`constexpr` functions** can be evaluated at compile-time if all arguments are known then:

```cpp
constexpr int square(int x) { return x * x; }
constexpr int y = square(7);   // computed at compile time → 49
int z = square(some_runtime_input);  // computed at runtime — also fine
```

**Pro hierarchy** :
1. `constexpr` if value known at compile time
2. `const` otherwise (read-only)
3. Normal variable only if mutation is required

**File** : `04_constexpr.cpp`

---

## 5.7 — `std::string`

**Concept** : modern, memory-managed string. Header `<string>`.

**Useful methods** :

| Method | Purpose |
|---|---|
| `.length()` / `.size()` | character count |
| `.empty()` | bool true if empty |
| `.find("X")` | position or `std::string::npos` |
| `.substr(start, len)` | sub-string |
| `+=` | append in place |
| `==`, `!=` | compare |
| `.at(i)` | bounds-checked indexing |
| `[i]` | unchecked indexing (faster, risky) |

**Pattern** :
```cpp
std::string s{"hello"};
s += ", world";              // "hello, world"
if (s.find("world") != std::string::npos) { ... }
std::string first = s.substr(0, 5);  // "hello"
```

---

## 5.8 — `std::string_view`

**Concept** : lightweight non-owning view = pointer + size. No allocation. Header `<string_view>`.

| Type | Owns memory? | Param cost |
|---|---|---|
| `std::string` (by value) | yes | full copy ❌ |
| `const std::string&` | no (just reference) | reference ✅ |
| `std::string_view` | no (just a view) | ~16 bytes ⚡ |

**Idiomatic modern usage** : prefer `std::string_view` for read-only function parameters.

```cpp
void print_length(std::string_view s) {
    std::cout << s.length();
}
print_length("literal");    // works
print_length(std::string{"hi"});  // works
```

**⚠️ Pitfall** : `string_view` does NOT own its data. Never let a `string_view` outlive the source string.

```cpp
std::string_view make_view() {
    std::string local{"hello"};
    return local;  // 💥 dangling view — local dies, view points to garbage
}
```

**File** : `05_strings.cpp`

============================================================









## Cross-cutting best practices (Chapter 5)

1. **`const` everywhere by default**, even local variables.
2. **`constexpr`** for compile-time constants (zero runtime cost).
3. **Uniform initialization** `{}` over `=` — catches narrowing conversions.
4. **`std::string_view`** for read-only string parameters.
5. **`const std::string&`** when modification is forbidden but full string features needed.
6. Compile with strict flags : `-Wall -Wextra -Wpedantic -std=c++17`.
7. In embedded code, hex `0x...` and binary `0b...` literals improve clarity.

---

## Glossary

- **Literal** : value written directly in code (e.g., `42`, `3.14f`, `"hello"`).
- **Narrowing conversion** : implicit conversion to a type with less precision (e.g., `double` → `float`).
- **Compile-time** : during the build (g++ runs).
- **Runtime** : during program execution (`./binary` runs).
- **Dangling reference/pointer/view** : pointer/reference to memory that has been freed or gone out of scope.