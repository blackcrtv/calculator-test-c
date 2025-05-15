#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <windows.h>
#include <GL/glut.h>

#define MAX_LUNGIME_LINIE 100
#define MAX_LUNGIME_NUME 50
#define MAX_ALIMENTE 100
#define MAX_MESE 50
#define MAX_ALIMENTE_PER_MASA 30
#define MAX_CUVINTE_IGNORATE 20

struct InformatiiNutritive {
    float calorii;
    float carbohidrati;
    float proteine;
    float fibre;
};

struct Aliment {
    char nume[MAX_LUNGIME_NUME];
    struct InformatiiNutritive info;
};

// Lista de cuvinte care trebuie ignorate
const char* cuvinteIgnorate[] = {
    "cu", "si", "de", "la", "pe", "in", "din", "fara" 
};
#define NUMAR_CUVINTE_IGNORATE (sizeof(cuvinteIgnorate)/sizeof(cuvinteIgnorate[0]))

// Verifica daca un cuvant trebuie ignorat
int esteCuvantDeIgnorat(const char* cuvant) {
    for (int i = 0; i < NUMAR_CUVINTE_IGNORATE; i++) {
        if (strcmp(cuvinteIgnorate[i], cuvant) == 0) {
            return 1;
        }
    }
    return 0;
}

// Sanitizeaza un nume de aliment (elimina spatii, face lowercase)
void sanitizeazaNume(char* nume) {
    // Elimina spatiile de la inceput si sfarsit
    char* start = nume;
    while (*start == ' ') start++;
    
    char* end = nume + strlen(nume) - 1;
    while (end > start && *end == ' ') {
        *end = '\0';
        end--;
    }
    
    // Muta stringul la inceput daca au fost spatii eliminate
    if (start != nume) {
        memmove(nume, start, strlen(start) + 1);
    }
    
    // Converteste la lowercase
    for (char* p = nume; *p; p++) {
        *p = tolower(*p);
    }
}

// Citeste alimentele din fisier
int citesteAlimente(const char* numeFisier, struct Aliment* aliments, int* numarAliments) {
    FILE *fisier = fopen(numeFisier, "r");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului %s\n", numeFisier);
        return 0;
    }

    char linie[MAX_LUNGIME_LINIE];
    *numarAliments = 0;
    int lineCount = 0;

    while (fgets(linie, sizeof(linie), fisier) && *numarAliments < MAX_ALIMENTE) {
        lineCount++;
        // Remove newline and trailing spaces
        char* end = linie + strlen(linie) - 1;
        while (end >= linie && (*end == '\n' || *end == ' ' || *end == '\r')) {
            *end = '\0';
            end--;
        }
        if (strlen(linie) == 0) {
            continue;  // Skip empty lines
        }
        
        // Initialize all values to 0
        aliments[*numarAliments].info.calorii = 0;
        aliments[*numarAliments].info.carbohidrati = 0;
        aliments[*numarAliments].info.proteine = 0;
        aliments[*numarAliments].info.fibre = 0;
        
        // Read the name first
        char* nume = strtok(linie, ",");
        if (nume == NULL) continue;
        
        strncpy(aliments[*numarAliments].nume, nume, MAX_LUNGIME_NUME - 1);
        aliments[*numarAliments].nume[MAX_LUNGIME_NUME - 1] = '\0';
        sanitizeazaNume(aliments[*numarAliments].nume);
        
        // Read the values
        char* val = strtok(NULL, ",");
        if (val != NULL) aliments[*numarAliments].info.calorii = atof(val);
        
        val = strtok(NULL, ",");
        if (val != NULL) aliments[*numarAliments].info.carbohidrati = atof(val);
        
        val = strtok(NULL, ",");
        if (val != NULL) aliments[*numarAliments].info.proteine = atof(val);
        
        val = strtok(NULL, ",");
        if (val != NULL) aliments[*numarAliments].info.fibre = atof(val);

        (*numarAliments)++;
    }

    fclose(fisier);
    return 1;
}

// Citeste numele meselor din fisier
int citesteMese(const char* numeFisier, char mese[][MAX_LUNGIME_NUME], int* numarMese) {
    FILE *fisier = fopen(numeFisier, "r");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului %s\n", numeFisier);
        return 0;
    }

    char linie[MAX_LUNGIME_LINIE];
    *numarMese = 0;

    while (fgets(linie, sizeof(linie), fisier) && *numarMese < MAX_MESE) {
        linie[strcspn(linie, "\n")] = 0;
        
        // Citeste primul nume de masa din linie
        char* masa = strtok(linie, ",");
        while (masa != NULL && *numarMese < MAX_MESE) {
            // Elimina spatiile de la inceput si sfarsit
            while (*masa == ' ') masa++;
            char* sfarsit = masa + strlen(masa) - 1;
            while (sfarsit > masa && *sfarsit == ' ') {
                *sfarsit = '\0';
                sfarsit--;
            }
            
            strncpy(mese[*numarMese], masa, MAX_LUNGIME_NUME - 1);
            mese[*numarMese][MAX_LUNGIME_NUME - 1] = '\0';
            
            (*numarMese)++;
            
            masa = strtok(NULL, ",");
        }
    }

    fclose(fisier);
    return 1;
}

// Afiseaza toate alimentele
void afiseazaAlimente(struct Aliment* aliments, int numarAliments) {
    printf("Informatii nutritive:\n");
    printf("------------------------------\n");

    for (int i = 0; i < numarAliments; i++) {
        printf("Aliment: %s\n", aliments[i].nume);
        printf("Calorii: %.1f kcal\n", aliments[i].info.calorii);
        printf("Carbohidrati: %.1f g\n", aliments[i].info.carbohidrati);
        printf("Proteine: %.1f g\n", aliments[i].info.proteine);
        printf("Fibre: %.1f g\n", aliments[i].info.fibre);
        printf("------------------------------\n");
    }
}

// Afiseaza toate mesele
void afiseazaMese(char mese[][MAX_LUNGIME_NUME], int numarMese) {
    printf("Mese disponibile:\n");
    printf("------------------------------\n");
    
    for (int i = 0; i < numarMese; i++) {
        printf("%d. %s\n", i + 1, mese[i]);
    }
    printf("------------------------------\n");
}

// Gaseste un aliment dupa nume (exact match, sanitized)
struct Aliment* gasesteAliment(const char* nume, struct Aliment* aliments, int numarAliments) {
    char numeSanitizat[MAX_LUNGIME_NUME];
    strncpy(numeSanitizat, nume, MAX_LUNGIME_NUME - 1);
    numeSanitizat[MAX_LUNGIME_NUME - 1] = '\0';
    sanitizeazaNume(numeSanitizat);
    
    for (int i = 0; i < numarAliments; i++) {
        char numeAlimentSanitizat[MAX_LUNGIME_NUME];
        strncpy(numeAlimentSanitizat, aliments[i].nume, MAX_LUNGIME_NUME - 1);
        numeAlimentSanitizat[MAX_LUNGIME_NUME - 1] = '\0';
        sanitizeazaNume(numeAlimentSanitizat);
        
        if (strcmp(numeAlimentSanitizat, numeSanitizat) == 0) {
            return &aliments[i];
        }
    }
    return NULL;
}

// Calculeaza informatii nutritive pentru o masa (doar cuvinte simple)
struct InformatiiNutritive calculeazaInformatiiNutritive(const char* masa, struct Aliment* aliments, int numarAliments) {
    struct InformatiiNutritive info = {0, 0, 0, 0};
    char copie[MAX_LUNGIME_LINIE];
    strcpy(copie, masa);
    
    // Imparte masa in cuvinte
    char* cuvinte[MAX_ALIMENTE_PER_MASA];
    int nrCuvinte = 0;
    char* token = strtok(copie, " ");
    while (token != NULL && nrCuvinte < MAX_ALIMENTE_PER_MASA) {
        cuvinte[nrCuvinte++] = token;
        token = strtok(NULL, " ");
    }

    int ingredientGasit = 0;
    for (int i = 0; i < nrCuvinte; i++) {
        if (esteCuvantDeIgnorat(cuvinte[i])) {
            continue;
        }
        char posibilAliment[MAX_LUNGIME_NUME];
        strncpy(posibilAliment, cuvinte[i], MAX_LUNGIME_NUME - 1);
        posibilAliment[MAX_LUNGIME_NUME - 1] = '\0';
        sanitizeazaNume(posibilAliment);
        
        struct Aliment* aliment = gasesteAliment(posibilAliment, aliments, numarAliments);
        if (aliment != NULL) {
            info.calorii += aliment->info.calorii;
            info.carbohidrati += aliment->info.carbohidrati;
            info.proteine += aliment->info.proteine;
            info.fibre += aliment->info.fibre;
            ingredientGasit = 1;
        }
    }
    if (!ingredientGasit) {
        printf("ATENTIE: Nu s-au gasit informatii nutritive pentru niciun ingredient din masa '%s'\n", masa);
    }
    return info;
}

// Afiseaza informatii nutritive pentru o masa
void afiseazaInformatiiMasa(const char* masa, struct InformatiiNutritive info) {
    printf("Masa: %s\n", masa);
    printf("Calorii: %.1f kcal\n", info.calorii);
    printf("Carbohidrati: %.1f g\n", info.carbohidrati);
    printf("Proteine: %.1f g\n", info.proteine);
    printf("Fibre: %.1f g\n", info.fibre);
    printf("------------------------------\n");
}

void sorteazaMeseAlfabetic(char mese[][MAX_LUNGIME_NUME], int numarMese) {
    for (int i = 0; i < numarMese - 1; i++) {
        for (int j = i + 1; j < numarMese; j++) {
            if (strcmp(mese[i], mese[j]) > 0) {
                char temp[MAX_LUNGIME_NUME];
                strcpy(temp, mese[i]);
                strcpy(mese[i], mese[j]);
                strcpy(mese[j], temp);
            }
        }
    }
}

// Add function to write nutritional info to a file
void scrieInformatiiMeseInFisier(const char* numeFisier, char mese[][MAX_LUNGIME_NUME], int numarMese, struct Aliment* aliments, int numarAliments) {
    FILE* fout = fopen(numeFisier, "w");
    if (!fout) {
        printf("Eroare la deschiderea fisierului de iesire %s\n", numeFisier);
        return;
    }
    fprintf(fout, "Informatii nutritive pentru fiecare masa:\n");
    fprintf(fout, "------------------------------\n");
    for (int i = 0; i < numarMese; i++) {
        struct InformatiiNutritive info = calculeazaInformatiiNutritive(mese[i], aliments, numarAliments);
        fprintf(fout, "Masa: %s\n", mese[i]);
        fprintf(fout, "Calorii: %.1f kcal\n", info.calorii);
        fprintf(fout, "Carbohidrati: %.1f g\n", info.carbohidrati);
        fprintf(fout, "Proteine: %.1f g\n", info.proteine);
        fprintf(fout, "Fibre: %.1f g\n", info.fibre);
        fprintf(fout, "------------------------------\n");
    }
    fclose(fout);
}

// Global variables for chart data
float* caloriiMese = NULL;
char** numeMese = NULL;
int numarMeseChart = 0;

// Function to prepare chart data
void pregatesteDateChart(char mese[][MAX_LUNGIME_NUME], int numarMese, struct Aliment* aliments, int numarAliments) {
    caloriiMese = (float*)malloc(numarMese * sizeof(float));
    numeMese = (char**)malloc(numarMese * sizeof(char*));
    numarMeseChart = numarMese;

    for (int i = 0; i < numarMese; i++) {
        numeMese[i] = strdup(mese[i]);
        struct InformatiiNutritive info = calculeazaInformatiiNutritive(mese[i], aliments, numarAliments);
        caloriiMese[i] = info.calorii;
    }
}

// Function to find maximum calories for scaling
float gasesteMaxCalorii() {
    float max = 0;
    for (int i = 0; i < numarMeseChart; i++) {
        if (caloriiMese[i] > max) max = caloriiMese[i];
    }
    return max;
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float maxCalorii = gasesteMaxCalorii();
    float scale = 0.8f / maxCalorii;  // Scale to fit in window
    float barWidth = 0.8f / numarMeseChart;

    // Draw bars
    for (int i = 0; i < numarMeseChart; i++) {
        glBegin(GL_QUADS);
        glColor3f(0.0f, i/(float)numarMeseChart, 1.0f);
        glVertex2f(-0.9f + i * barWidth, -0.9f);
        glVertex2f(-0.9f + (i + 1) * barWidth, -0.9f);
        glVertex2f(-0.9f + (i + 1) * barWidth, -0.9f + caloriiMese[i] * scale);
        glVertex2f(-0.9f + i * barWidth, -0.9f + caloriiMese[i] * scale);
        glEnd();

        // Display calories value
        char buffer[20];
        sprintf(buffer, "%.0f", caloriiMese[i]);
        glRasterPos2f(-0.9f + i * barWidth + barWidth/4, -0.9f + caloriiMese[i] * scale + 0.05f);
        for (int j = 0; buffer[j] != '\0'; j++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buffer[j]);
        }
    }

    // Draw title
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(-0.3f, 0.9f);
    char* title = "Calorii per masa";
    for (int i = 0; title[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, title[i]);
    }

    glFlush();
}

void cleanup() {
    if (caloriiMese) free(caloriiMese);
    if (numeMese) {
        for (int i = 0; i < numarMeseChart; i++) {
            free(numeMese[i]);
        }
        free(numeMese);
    }
}

// Global variables for pie chart
float totalProteine = 0;
float totalCarbohidrati = 0;
float totalFibre = 0;

// Function to calculate total nutrients for pie chart
void calculeazaTotalNutritii(char mese[][MAX_LUNGIME_NUME], int numarMese, struct Aliment* aliments, int numarAliments) {
    totalProteine = 0;
    totalCarbohidrati = 0;
    totalFibre = 0;
    
    for (int i = 0; i < numarMese; i++) {
        struct InformatiiNutritive info = calculeazaInformatiiNutritive(mese[i], aliments, numarAliments);
        totalProteine += info.proteine;
        totalCarbohidrati += info.carbohidrati;
        totalFibre += info.fibre;
    }
}

// Function to draw pie chart
void deseneazaPieChart() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float total = totalProteine + totalCarbohidrati + totalFibre;
    if (total == 0) return;

    float startAngle = 0;
    float radius = 0.4f;
    float centerX = 0.0f;
    float centerY = 0.0f;

    // Draw protein slice
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f); // Red for protein
    glVertex2f(centerX, centerY);
    float endAngle = startAngle + (totalProteine / total) * 360.0f;
    for (float angle = startAngle; angle <= endAngle; angle += 1.0f) {
        float radian = angle * 3.14159f / 180.0f;
        glVertex2f(centerX + radius * cos(radian), centerY + radius * sin(radian));
    }
    glEnd();
    startAngle = endAngle;

    // Draw carbs slice
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 1.0f, 0.0f); // Green for carbs
    glVertex2f(centerX, centerY);
    endAngle = startAngle + (totalCarbohidrati / total) * 360.0f;
    for (float angle = startAngle; angle <= endAngle; angle += 1.0f) {
        float radian = angle * 3.14159f / 180.0f;
        glVertex2f(centerX + radius * cos(radian), centerY + radius * sin(radian));
    }
    glEnd();
    startAngle = endAngle;

    // Draw fiber slice
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue for fiber
    glVertex2f(centerX, centerY);
    endAngle = startAngle + (totalFibre / total) * 360.0f;
    for (float angle = startAngle; angle <= endAngle; angle += 1.0f) {
        float radian = angle * 3.14159f / 180.0f;
        glVertex2f(centerX + radius * cos(radian), centerY + radius * sin(radian));
    }
    glEnd();

    // Draw legend
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(-0.8f, 0.8f);
    char* title = "Distributia Nutritiilor";
    for (int i = 0; title[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, title[i]);
    }

    // Draw legend items
    char buffer[100];
    float yPos = 0.6f;
    float yStep = 0.1f;

    // Protein
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(-0.8f, yPos);
    sprintf(buffer, "Proteine: %.1f%%", (totalProteine / total) * 100);
    for (int i = 0; buffer[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buffer[i]);
    }

    // Carbs
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2f(-0.8f, yPos - yStep);
    sprintf(buffer, "Carbohidrati: %.1f%%", (totalCarbohidrati / total) * 100);
    for (int i = 0; buffer[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buffer[i]);
    }

    // Fiber
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(-0.8f, yPos - 2 * yStep);
    sprintf(buffer, "Fibre: %.1f%%", (totalFibre / total) * 100);
    for (int i = 0; buffer[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buffer[i]);
    }

    glFlush();
}

// Function to create a new window for pie chart
void creeazaFereastraPieChart() {
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(900, 50);  // Position it to the right of the main window
    glutCreateWindow("Distributia Nutritiilor");
    glutDisplayFunc(deseneazaPieChart);
}

int main(int argc, char** argv) {
    struct Aliment aliments[MAX_ALIMENTE];
    int numarAliments = 0;
    char mese[MAX_MESE][MAX_LUNGIME_NUME];
    int numarMese = 0;

    // Citeste alimentele
    if (!citesteAlimente("date-de-intrare/nutrition.txt", aliments, &numarAliments)) {
        return 1;
    }

    // Citeste mesele
    if (!citesteMese("date-de-intrare/mese.txt", mese, &numarMese)) {
        return 1;
    }

    // Sorteaza mesele alfabetic
    sorteazaMeseAlfabetic(mese, numarMese);

    // Scrie informatiile in fisier
    scrieInformatiiMeseInFisier("date-de-iesire/rezultate_mese.txt", mese, numarMese, aliments, numarAliments);

    // Prepare chart data
    pregatesteDateChart(mese, numarMese, aliments, numarAliments);

    // Calculate total nutrients for pie chart
    calculeazaTotalNutritii(mese, numarMese, aliments, numarAliments);

    // Initialize GLUT
    glutInit(&argc, argv);
    
    // Create main window for bar chart
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Calorii per masa");
    glutDisplayFunc(display);
    
    // Create second window for pie chart
    creeazaFereastraPieChart();
    
    glutMainLoop();

    // Cleanup
    cleanup();
    return 0;
} 