# Calculator de Calorii și Nutriție

## Scopul Programului
Acest program este un calculator de calorii și nutriție care analizează mesele și calculează informațiile nutritive pentru fiecare masă. Programul poate:
- Citi informații despre alimente dintr-un fișier
- Citi lista de mese dintr-un fișier
- Calcula caloriile și nutrienții pentru fiecare masă
- Genera un raport detaliat
- Crea o vizualizare grafică a caloriilor per masă

## Structura Fișierelor
- `date-de-intrare/` - Directorul care trebuie să conțină:
  - `nutrition.txt` - Fișier cu informații despre alimente (format: nume,calorii,carbohidrati,proteine,fibre)
  - `mese.txt` - Fișier cu lista de mese (câte o masă pe linie, cu ingredientele separate prin virgulă)
- `date-de-iesire/` - Directorul unde se vor salva rezultatele:
  - `rezultate_mese.txt` - Raportul cu informațiile nutritive pentru fiecare masă

## Formatul Fișierului nutrition.txt

Fișierul `nutrition.txt` conține informații despre valorile nutritive ale alimentelor. Fiecare linie reprezintă un aliment și are următorul format:
```
nume,calorii,carbohidrati,proteine,fibre
```

### Explicație detaliată a câmpurilor:
1. **nume**: Numele alimentului (un singur cuvânt, fără spații)
   - Exemplu: `pui`
   - Restricții: Doar litere mici, fără spații sau caractere speciale

2. **calorii**: Numărul de calorii per 100g
   - Exemplu: `165`
   - Unitate: kcal
   - Format: Număr întreg sau zecimal

3. **carbohidrati**: Cantitatea de carbohidrați per 100g
   - Exemplu: `0`
   - Unitate: grame
   - Format: Număr întreg sau zecimal

4. **proteine**: Cantitatea de proteine per 100g
   - Exemplu: `31`
   - Unitate: grame
   - Format: Număr întreg sau zecimal

5. **fibre**: Cantitatea de fibre per 100g
   - Exemplu: `0`
   - Unitate: grame
   - Format: Număr întreg sau zecimal

### Exemple de linii:
```
pui,165,0,31,0        # Carne cu proteine, fără carbohidrați
orez,130,28,3,0.4     # Carbohidrați complecși
ou,155,1.1,12.6,0     # Proteine și grăsimi
spanac,23,3.6,2.9,2.2 # Legume cu fibre
```

### Note importante:
- Toate valorile sunt per 100g de aliment
- Numele alimentelor trebuie să fie unice
- Nu se permit spații în numele alimentelor
- Valorile nutritive trebuie să fie numere pozitive
- Separatorul între câmpuri este virgula (,)
- Nu se permit linii goale în fișier

## Formatul Fișierului mese.txt

Fișierul `mese.txt` conține lista de mese și ingredientele lor. Fiecare linie reprezintă o masă și are următorul format:
```
nume_masa,ingredient1,ingredient2,ingredient3,...
```

### Explicație detaliată a câmpurilor:
1. **nume_masa**: Numele mesei
   - Exemplu: `mic_dejun`
   - Poate conține spații
   - Trebuie să fie unic

2. **ingrediente**: Lista de ingrediente separate prin virgulă
   - Exemplu: `ou,paine,lapte`
   - Numele ingredientelor trebuie să corespundă cu cele din nutrition.txt
   - Nu se permit spații în numele ingredientelor

### Exemple de linii:
```
mic_dejun,ou,paine,lapte
pranz,pui,orez,rosii
cina,somon,spanac,usturoi
gustare,banane,iaurt
```

### Note importante:
- Fiecare masă trebuie să aibă cel puțin un ingredient
- Numărul maxim de ingrediente per masă este 30 (MAX_ALIMENTE_PER_MASA)
- Numele ingredientelor trebuie să fie exact ca în nutrition.txt
- Nu se permit linii goale în fișier
- Separatorul între câmpuri este virgula (,)
- Programul va ignora cuvintele: "cu", "si", "de", "la", "pe", "in", "din", "fara"

### Exemplu de procesare:
Pentru o linie ca:
```
mic_dejun,ou cu paine si lapte
```
Programul va procesa doar: `ou`, `paine`, `lapte`

## Funcții Principale

### `sanitizeazaNume(char* nume)`
**Scop**: Curăță și standardizează numele alimentelor.
**Parametri**:
- `nume`: pointer la char - numele de curățat
**Logică**: 
- Elimină spațiile de la început și sfârșit
- Convertește totul la lowercase
**Linie cheie**: `*p = tolower(*p);`

### `citesteAlimente(const char* numeFisier, struct Aliment* aliments, int* numarAliments)`
**Scop**: Citește informațiile despre alimente din fișier.
**Parametri**:
- `numeFisier`: const char* - numele fișierului de citit
- `aliments`: struct Aliment* - array-ul unde se vor stoca alimentele
- `numarAliments`: int* - pointer la numărul de alimente citite
**Return**: 1 pentru succes, 0 pentru eroare
**Linie cheie**: `strncpy(aliments[*numarAliments].nume, nume, MAX_LUNGIME_NUME - 1);`

### `citesteMese(const char* numeFisier, char mese[][MAX_LUNGIME_NUME], int* numarMese)`
**Scop**: Citește lista de mese din fișier.
**Parametri**:
- `numeFisier`: const char* - numele fișierului de citit
- `mese`: char[][] - array-ul unde se vor stoca mesele
- `numarMese`: int* - pointer la numărul de mese citite
**Return**: 1 pentru succes, 0 pentru eroare
**Linie cheie**: `strncpy(mese[*numarMese], masa, MAX_LUNGIME_NUME - 1);`

### `calculeazaInformatiiNutritive(const char* masa, struct Aliment* aliments, int numarAliments)`
**Scop**: Calculează informațiile nutritive pentru o masă.
**Parametri**:
- `masa`: const char* - descrierea mesei
- `aliments`: struct Aliment* - lista de alimente disponibile
- `numarAliments`: int - numărul de alimente disponibile
**Return**: struct InformatiiNutritive cu valorile calculate
**Linie cheie**: `info.calorii += aliment->info.calorii;`

### `scrieInformatiiMeseInFisier(const char* numeFisier, char mese[][MAX_LUNGIME_NUME], int numarMese, struct Aliment* aliments, int numarAliments)`
**Scop**: Scrie informațiile nutritive pentru toate mesele într-un fișier.
**Parametri**:
- `numeFisier`: const char* - numele fișierului de ieșire
- `mese`: char[][] - lista de mese
- `numarMese`: int - numărul de mese
- `aliments`: struct Aliment* - lista de alimente
- `numarAliments`: int - numărul de alimente
**Linie cheie**: `fprintf(fout, "Calorii: %.1f kcal\n", info.calorii);`

### `display()`
**Scop**: Funcție OpenGL pentru desenarea graficului cu caloriile per masă.
**Logică**: 
- Desenează bare pentru fiecare masă
- Scala înălțimea barelor în funcție de caloriile maxime
- Afișează valorile caloriilor deasupra barelor
**Linie cheie**: `glVertex2f(-0.9f + i * barWidth, -0.9f + caloriiMese[i] * scale);`

## Structuri de Date

### `struct InformatiiNutritive`
```c
struct InformatiiNutritive {
    float calorii;
    float carbohidrati;
    float proteine;
    float fibre;
};
```
Stochează informațiile nutritive pentru un aliment sau o masă.

### `struct Aliment`
```c
struct Aliment {
    char nume[MAX_LUNGIME_NUME];
    struct InformatiiNutritive info;
};
```
Reprezintă un aliment cu numele și informațiile sale nutritive.

## Constante Importante
- `MAX_LUNGIME_LINIE`: 100 - Lungimea maximă a unei linii din fișier
- `MAX_LUNGIME_NUME`: 50 - Lungimea maximă a unui nume de aliment
- `MAX_ALIMENTE`: 100 - Numărul maxim de alimente
- `MAX_MESE`: 50 - Numărul maxim de mese
- `MAX_ALIMENTE_PER_MASA`: 30 - Numărul maxim de alimente per masă 

## Pointeri și Gestionarea Memoriei

### Pointeri Dublu (**)
În program, pointerii dublu sunt folosiți în două locuri principale:
1. `char** numeMese` - Pentru stocarea numelor meselor în mod dinamic
   - Este folosit pentru a aloca memorie pentru un array de string-uri
   - Permite modificarea pointerilor individuali către fiecare nume de masă
   - Este necesar pentru că numele meselor au lungimi variabile

### Funcții de Gestionare a Memoriei

#### `malloc()`
- Alocă memorie dinamică în heap
- În program este folosit pentru:
  - `caloriiMese = (float*)malloc(numarMese * sizeof(float))` - Pentru stocarea caloriilor
  - `numeMese = (char**)malloc(numarMese * sizeof(char*))` - Pentru array-ul de nume
  - `numeMese[i] = strdup(mese[i])` - Pentru fiecare nume individual
- Avantaje:
  - Permite alocarea memoriei doar când este necesar
  - Permite redimensionarea la runtime
  - Evită limitările array-urilor statice

#### `free()`
- Eliberează memoria alocată cu malloc
- În program este folosit în funcția `cleanup()`:
  - `free(caloriiMese)` - Eliberează memoria pentru caloriile meselor
  - `free(numeMese[i])` - Eliberează memoria pentru fiecare nume
  - `free(numeMese)` - Eliberează memoria pentru array-ul de pointeri
- Important pentru:
  - Prevenirea memory leaks
  - Returnarea memoriei sistemului
  - Curățarea resurselor la încheierea programului 