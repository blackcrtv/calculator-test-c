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

### `calculeazaTotalNutritii(char mese[][MAX_LUNGIME_NUME], int numarMese, struct Aliment* aliments, int numarAliments)`
**Scop**: Calculează totalul nutrienților (proteine, carbohidrați, fibre) pentru toate mesele.
**Parametri**:
- `mese`: char[][] - lista de mese
- `numarMese`: int - numărul de mese
- `aliments`: struct Aliment* - lista de alimente disponibile
- `numarAliments`: int - numărul de alimente disponibile
**Logică**: 
- Calculează suma totală pentru fiecare tip de nutrient
- Stochează rezultatele în variabilele globale pentru pie chart
**Linie cheie**: `totalProteine += info.proteine;`

### `deseneazaPieChart()`
**Scop**: Funcție OpenGL pentru desenarea graficului circular cu distribuția nutrienților.
**Logică**: 
- Desenează un grafic circular (pie chart) cu trei secțiuni
- Fiecare secțiune reprezintă proporția unui nutrient (proteine, carbohidrați, fibre)
- Afișează un legend cu procentele exacte
**Culori**:
- Roșu pentru proteine
- Verde pentru carbohidrați
- Albastru pentru fibre
**Linie cheie**: `endAngle = startAngle + (totalProteine / total) * 360.0f;`

### `creeazaFereastraPieChart()`
**Scop**: Creează o fereastră separată pentru afișarea graficului circular.
**Logică**: 
- Inițializează o nouă fereastră GLUT
- Poziționează fereastra la dreapta ferestrei principale
- Setează funcția de desenare pentru pie chart
**Linie cheie**: `glutCreateWindow("Distributia Nutritiilor");`

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

### `struct EvaluareSanatate`
```c
struct EvaluareSanatate {
    int esteSanatoasa;
    float scorSanatate;  // 0-100, unde 100 este cel mai sănătos
};
```
Structură pentru stocarea evaluării sănătății unei mese.

### `evalueazaSanatateMasa(struct InformatiiNutritive info)`
**Scop**: Evaluează sănătatea unei mese bazată pe conținutul său nutrițional.
**Parametri**:
- `info`: struct InformatiiNutritive - informațiile nutritive ale mesei
**Return**: struct EvaluareSanatate cu rezultatul evaluării
**Logică de evaluare**:
1. **Verificare Calorii** (40% din scor):
   - Mese peste 1000 kcal sunt considerate nesănătoase
   - Scorul scade proporțional cu numărul de calorii

2. **Prezența Nutrienților** (30% din scor):
   - Verifică prezența proteinelor (+25%)
   - Verifică prezența carbohidraților (+25%)
   - Verifică prezența fibrelor (+25%)

3. **Balanța Nutrienților** (30% din scor):
   - Penalizează mesele cu un nutrient dominant (>70%)
   - Promovează mesele cu distribuție echilibrată

**Linie cheie**: `evaluare.scorSanatate = (scorCalorii * 0.4f) + (scorNutrienti * 0.3f) + (balantaNutrienti * 0.3f);`

### `obtineCuloareMasa(struct EvaluareSanatate evaluare, float* r, float* g, float* b)`
**Scop**: Generează culoarea corespunzătoare pentru afișarea mesei în grafic.
**Parametri**:
- `evaluare`: struct EvaluareSanatate - rezultatul evaluării
- `r, g, b`: float* - pointeri către componentele de culoare
**Logică**:
- Verde pentru mese sănătoase (scor >= 60)
- Roșu pentru mese nesănătoase (scor < 60)
- Intensitatea culorii variază cu scorul
**Linie cheie**: `*g = 0.5f + (evaluare.scorSanatate / 200.0f);`

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

## Diferențe între Grafice

### Graficul cu Bare (Original)
- **Scop**: Afișează caloriile pentru fiecare masă individuală
- **Date necesare**: Calorii per masă
- **Utilizare**: Pentru a compara conținutul caloric între mese diferite
- **Vizualizare**: Bare verticale, fiecare reprezentând o masă
- **Perspectivă**: Oferă o vedere detaliată a fiecărei mese
- **Implementare tehnică**:
  - Folosește primitive simple OpenGL (GL_QUADS)
  - Desenează manual fiecare bară ca un dreptunghi
  - Calculează manual pozițiile și dimensiunile barelor
  - Implementare directă a scalării și poziționării
  - Nu necesită calcule trigonometrice
  - Folosește un singur tip de primitivă grafică

### Graficul Circular (Nou)
- **Scop**: Afișează distribuția procentuală a nutrienților în toate mesele
- **Date necesare**: Total proteine, carbohidrați și fibre
- **Utilizare**: Pentru a înțelege balanța generală a nutrienților în dieta completă
- **Vizualizare**: Cercul împărțit în trei secțiuni proporționale
- **Perspectivă**: Oferă o vedere de ansamblu a compoziției nutriționale
- **Implementare tehnică**:
  - Folosește primitive complexe OpenGL (GL_TRIANGLE_FAN)
  - Aproximare a cercului prin triunghiuri
  - Calcule trigonometrice pentru generarea punctelor
  - Implementare matematică a secțiunilor circulare
  - Folosește funcții trigonometrice (sin, cos) pentru calculul coordonatelor
  - Necesită gestionarea unghiurilor și a radianilor
  - Implementare mai sofisticată a culorilor și transparenței
  - Folosește mai multe tipuri de primitive grafice pentru legendă și text

### Diferențe în Implementare
1. **Complexitate a Codului**:
   - Bar Chart: 
     - Implementare manuală a fiecărei bare
     - Calcule directe pentru poziționare și scalare
     - Cod repetitiv pentru fiecare bară
     - Necesită gestionare manuală a spațiului
   - Pie Chart:
     - Implementare modulară cu funcții separate
     - Reutilizare a codului pentru fiecare secțiune
     - Calcule automate pentru proporții
     - Gestionare centralizată a desenării

2. **Structura Implementării**:
   - Bar Chart:
     - Toată logica într-o singură funcție (display)
     - Gestionare manuală a datelor
     - Scalare manuală pentru fiecare bară
     - Poziționare explicită a textului
   - Pie Chart:
     - Funcții separate pentru calcul și desenare
     - Variabile globale pentru stocarea datelor
     - Scalare automată bazată pe procente
     - Sistem de legendă integrat

3. **Gestionarea Datelor**:
   - Bar Chart:
     - Date stocate în array-uri separate
     - Necesită alocare dinamică de memorie
     - Gestionare manuală a eliberării memoriei
     - Recalculare la fiecare desenare
   - Pie Chart:
     - Date calculate o singură dată la inițializare
     - Stocare simplă în variabile globale
     - Nu necesită alocare dinamică
     - Reutilizare a calculelor

4. **Extensibilitate**:
   - Bar Chart:
     - Modificări necesare pentru fiecare element nou
     - Limitări în adăugarea de funcționalități
     - Cod mai greu de întreținut
     - Schimbări necesare pentru fiecare ajustare
   - Pie Chart:
     - Ușor de extins cu noi tipuri de nutrienți
     - Adăugare simplă de noi funcționalități
     - Cod mai ușor de întreținut
     - Ajustări automate la modificări

5. **Performanță**:
   - Bar Chart:
     - Calcule repetate la fiecare frame
     - Mai multe operații de desenare
     - Gestionare manuală a resurselor
     - Overhead pentru fiecare element
   - Pie Chart:
     - Calcule o singură dată la inițializare
     - Operații de desenare optimizate
     - Gestionare simplificată a resurselor
     - Performanță constantă indiferent de date

6. **Mentenabilitate**:
   - Bar Chart:
     - Cod mai lung și mai complex
     - Modificări necesare în mai multe locuri
     - Testare mai dificilă
     - Debugging mai complicat
   - Pie Chart:
     - Cod mai scurt și mai organizat
     - Modificări localizate
     - Testare mai ușoară
     - Debugging simplificat

## Funcționalități Principale ale Pie Chart-ului

1. **Calculul Totalurilor**
   - Insumarea tuturor nutrienților din toate mesele
   - Calculul procentajelor pentru fiecare tip de nutrient

2. **Vizualizare Interactivă**
   - Legendă cu procentaje exacte
   - Culori distincte pentru fiecare tip de nutrient

3. **Integrare cu Sistemul Existent**
   - Funcționează în paralel cu graficul de bare
   - Folosește aceleași date de intrare
   - Oferă o perspectivă complementară asupra datelor

4. **Personalizare Vizuală**
   - Culori intuitive pentru fiecare nutrient
   - Titlu descriptiv
   - Legendă clară și ușor de citit

## Note de Utilizare

1. **Date Necesare**
   - Fișierul `nutrition.txt` cu informații despre alimente
   - Fișierul `mese.txt` cu lista de mese
   - Toate alimentele trebuie să aibă valori pentru proteine, carbohidrați și fibre

2. **Interpretarea Rezultatelor**
   - Procentajele arată distribuția relativă a nutrienților
   - Suma tuturor procentajelor este 100%
   - Valorile sunt calculate din totalul absolut al fiecărui nutrient

3. **Limitări**
   - Nu include caloriile în distribuție
   - Presupune că toate mesele au aceeași importanță
   - Nu ia în considerare cantitățile diferite de alimente 

## Sistemul de Evaluare a Sănătății

### Scop
Sistemul de evaluare a sănătății oferă o metodă vizuală și intuitivă pentru a analiza calitatea nutrițională a meselor. Acesta transformă datele nutriționale complexe într-un format ușor de înțeles prin intermediul culorilor.

### Componente Principale

1. **Evaluarea Caloriilor**
   - Limita maximă: 1000 kcal
   - Scor proporțional cu numărul de calorii
   - Impact major asupra evaluării finale (40%)

2. **Diversitatea Nutrienților**
   - Verifică prezența tuturor tipurilor de nutrienți
   - Recompensează mesele complete
   - Contribuție moderată la scor (30%)

3. **Balanța Nutrienților**
   - Analizează distribuția nutrienților
   - Penalizează dominanța unui singur nutrient
   - Contribuție moderată la scor (30%)

### Vizualizare

1. **Sistem de Culori**
   - Verde: Mese sănătoase (scor >= 60)
   - Roșu: Mese nesănătoase (scor < 60)
   - Nuanțe: Intensitatea culorii reflectă scorul

2. **Legendă**
   - Explică semnificația culorilor
   - Ajută la interpretarea graficului
   - Poziționată sub grafic

### Avantaje

1. **Feedback Vizual Imediat**
   - Identificare rapidă a meselor problematice
   - Înțelegere intuitivă a calității nutriționale
   - Ajutor în luarea deciziilor alimentare

2. **Evaluare Complexă**
   - Consideră multiple aspecte nutriționale
   - Balansează diferite factori
   - Oferă o perspectivă de ansamblu

3. **Flexibilitate**
   - Ușor de ajustat parametrii
   - Poate fi extins pentru criterii suplimentare
   - Adaptabil la diferite nevoi nutriționale

### Limitări

1. **Simplificare**
   - Nu ia în considerare toate aspectele nutriționale
   - Generalizează anumite aspecte
   - Poate necesita ajustări pentru cazuri speciale

2. **Subiectivitate**
   - Criteriile sunt definite arbitrar
   - Poate necesita personalizare
   - Nu înlocuiește sfatul nutriționistului

3. **Complexitate Calcul**
   - Necesită procesare suplimentară
   - Poate afecta performanța
   - Requeră memorie suplimentară 