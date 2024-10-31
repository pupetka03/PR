#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* tato struktura sa pouziva na ulozenie stavu otvorenia troch suborov */
typedef struct {
    bool subor1_otvoreny;
    bool subor2_otvoreny;
    bool subor3_otvoreny;
} SuboryStatus;

/* Funkcia kontroluje, ci su vsetky subory zatvorene */
bool zatvorene_subory(SuboryStatus *status) {
    return !((*status).subor1_otvoreny || (*status).subor2_otvoreny || (*status).subor3_otvoreny);
}

/* funkcia otvori subor, ak este nie je otvoreny */
void otvorit_subory(char* menosubora, bool* status_subora) {
    if (*status_subora) {
    return;
    } else {
        FILE *file = fopen(menosubora, "r");
        if (file != NULL) {
            *status_subora = true; /* zmeni stav suboru na "otvoreny" */
            fclose(file);
        }
    }
}

/* funkcia odstrani medzeru */
void vymazat_m( char *vstup, char *vystup) {
    int j = 0;
    for (int i = 0; vstup[i] != '\0'; i++) {
        if (vstup[i] != ' ') {
            vystup[j++] = vstup[i];
        }
    }
    vystup[j] = '\0';
}

void vytlacit_subory(char* subor_data, char* subor_parse, char* subor_string, int row_number) {
    /* tlaci subor_data */
    FILE *file1 = fopen(subor_string, "r");
    if (file1 != NULL) {
        char* x = malloc(100 * sizeof(char));
        for (int i = 0; i <= row_number; i++) {
            if (!fgets(x, 100, file1)) {
                break;
            }
        }
        printf("ID. mer. modulu: %s", x);
        free(x);
        fclose(file1);
    }
    /* tlaci subor_parse */
    FILE *file2 = fopen(subor_data, "r");
    if (file2 != NULL) {
        int cislo[3];
        float cislo4;
        for (int i = 0; i <= row_number; i++) {
            if (fscanf(file2, "%d %d %d %f", &cislo[0], &cislo[1], &cislo[2], &cislo4) == 4) {
                if (i == row_number) {
                    printf("Hodnota 1: %d\n", cislo[2]);
                    printf("Hodnota 2: %.3f\n", cislo4);
                }
            }
        }
        fclose(file2);
    }
    /* tlaci subor_parse */
    FILE *file3 = fopen(subor_parse, "r");
    if (file3 != NULL) {
        char* x = malloc(100 * sizeof(char));
        char* poznamka = malloc(100 * sizeof(char));
        for (int i = 0; i <= row_number; i++) {
            if (!fgets(x, 100, file3)) {
                break;
            }
        }
        vymazat_m(x, poznamka);
        printf("Poznamka: %s\n", poznamka);
        free(x);
        free(poznamka);
        fclose(file3);
    }
}

/* robi pocitanie suborov */
void pocet(char *subor_string, SuboryStatus *status) {
    /* zistuje ci bol subor otvoreny */
    if ((*status).subor3_otvoreny) {
        FILE *file = fopen(subor_string, "r");
        if (file != NULL) {
            int counts[256] = {0};
            char c;

            while ((c = fgetc(file)) != EOF) {
                counts[c]++;
            }
            fclose(file);

            /* vypis poctu velkych pismen */
            for (char i = 'A'; i <= 'Z'; i++) {
                if (counts[i] > 0) {
                    printf("%c : %d\n", i, counts[i]);
                }
            }
            /* vypis poctu malych pismen */
            for (char i = 'a'; i <= 'z'; i++) {
                if (counts[i] > 0) {
                    printf("%c : %d\n", i, counts[i]);
                }
            }
            /* vypis poctu cislic */
            for (char i = '0'; i <= '9'; i++) {
                if (counts[i] > 0) {
                    printf("%c : %d\n", i, counts[i]);
                }
            }
    }
    } else {
        printf("H: Neotvoreny subor.\n");
    }
}

/* funkcia vola funciu vytlacit_subory pre prvych 5 riadkov kazdeho subora */
void tlac_s(SuboryStatus *status) {
    for (int i = 0; i < 5; i++) {
        vytlacit_subory("data.txt", "parse.txt", "string.txt", i);
    }
}

/* funcia vola funciu pocet */
void tlac_h (SuboryStatus *status) {
    pocet("string.txt", status);
}

int main(void) {
    char vyber;
    char prikaz;
    SuboryStatus status = {false, false, false};

    while (true) {
        scanf(" %c", &prikaz);
        if (prikaz == 'v') {
            scanf(" %c", &vyber);
            if (vyber == '1') {
                if (zatvorene_subory(&status)) {
                    otvorit_subory("data.txt", &status.subor1_otvoreny);
                    otvorit_subory("parse.txt", &status.subor2_otvoreny);
                    otvorit_subory("string.txt", &status.subor3_otvoreny);
                    tlac_s(&status);
                }
            } else
                printf("V: Nespravne volba vypisu.\n");
        }
        if (prikaz == 'h') {
            tlac_h(&status);
        }
        if (prikaz == 'k') {
            return 0;
        }
    }
}