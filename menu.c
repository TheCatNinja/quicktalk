#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "moderation.h"
#include "structs.h"

static void readLine(char *buf, size_t size) {
    if (!fgets(buf, size, stdin)) {
        buf[0] = '\0';
        return;
    }
    buf[strcspn(buf, "\n")] = '\0';
}

static int readInt(const char *prompt) {
    char buf[128];
    int value;
    while (1) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) {
            printf("Blad wejscia.\n");
            continue;
        }
        if (sscanf(buf, "%d", &value) == 1) return value;
        printf("Niepoprawna liczba, sproboj ponownie.\n");
    }
}

static void menuAddPost(void) {
    char author[MAX_AUTHOR];
    char content[MAX_CONTENT];
    int r, rc;

    printf("Autor: ");
    readLine(author, sizeof(author));

    printf("Tresc: ");
    readLine(content, sizeof(content));

    while (1) {
        r = readInt("Kategoria (0=spam,1=naduzycie,2=inne): ");
        if (r >= 0 && r <= 2) break;
        printf("Niepoprawna kategoria.\n");
    }

    rc = readInt("Liczba zgloszen (>=0): ");
    if (rc < 0) rc = 0;

    PostNode *node = addPost(author, content, (ReportType)r, rc);
    if (node) {
        printf("Dodano post:\n");
        printPost(&node->data);
    }
}

static void menuEditPost(void) {
    int id = readInt("Podaj ID posta do edycji: ");
    editPost(id);
}

static void menuDeletePost(void) {
    int id = readInt("Podaj ID posta do usuniecia: ");
    deletePostById(id);
}

static void menuDeleteByReports(void) {
    int min = readInt("Usun posty z liczba zgloszen >= : ");
    deletePostsByMinReports(min);
}

static void menuSearchAuthor(void) {
    char prefix[MAX_AUTHOR];
    printf("Podaj prefiks autora: ");
    readLine(prefix, sizeof(prefix));
    searchByAuthorPrefix(prefix);
}

static void menuSearchReports(void) {
    int min = readInt("Szukaj postow z liczba zgloszen >= : ");
    searchByMinReports(min);
}

static void menuSortAuthor(void) {
    sortAndPrintByAuthor();
}

static void menuSortReports(void) {
    sortAndPrintByReports();
}

static void printMenu(void) {
    printf("\nMENU\n");
    printf("1. Dodaj post\n");
    printf("2. Edytuj post\n");
    printf("3. Usun post po ID\n");
    printf("4. Usun posty o liczbie zgloszen >= X\n");
    printf("5. Wyswietl wszystkie posty\n");
    printf("6. Szukaj po prefiksie autora\n");
    printf("7. Szukaj po liczbie zgloszen\n");
    printf("8. Sortuj i wyswietl po autorze\n");
    printf("9. Sortuj i wyswietl po liczbie zgloszen\n");
    printf("10. Zapisz do pliku\n");
    printf("11. Wczytaj z pliku\n");
    printf("0. Wyjscie\n");
}

void runMenu(const char *defaultLoad, const char *defaultSave) {
    if (defaultLoad) {
        printf("Proba wczytania danych z pliku: %s\n", defaultLoad);
        loadFromText(defaultLoad);
    }

    char buf[64];
    int choice;

    while (1) {
        printMenu();
        printf("Wybor: ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        if (sscanf(buf, "%d", &choice) != 1) {
            printf("Niepoprawny wybor.\n");
            continue;
        }

        switch (choice) {
            case 1: menuAddPost(); break;
            case 2: menuEditPost(); break;
            case 3: menuDeletePost(); break;
            case 4: menuDeleteByReports(); break;
            case 5: printAllPosts(); break;
            case 6: menuSearchAuthor(); break;
            case 7: menuSearchReports(); break;
            case 8: menuSortAuthor(); break;
            case 9: menuSortReports(); break;
            case 10: {
                char filename[256];
                if (defaultSave) {
                    printf("Uzycie domyslnej sciezki: %s\n", defaultSave);
                    saveToText(defaultSave);
                } else {
                    printf("Podaj nazwe pliku do zapisu: ");
                    readLine(filename, sizeof(filename));
                    saveToText(filename);
                }
                break;
            }
            case 11: {
                char filename[256];
                printf("Podaj nazwe pliku do odczytu: ");
                readLine(filename, sizeof(filename));
                loadFromText(filename);
                break;
            }
            case 0:
                if (defaultSave) {
                    printf("Zapis do pliku koncowego: %s\n", defaultSave);
                    saveToText(defaultSave);
                }
                freeList();
                printf("Koniec programu.\n");
                return;
            default:
                printf("Nieznana opcja.\n");
        }
    }

    freeList();
}