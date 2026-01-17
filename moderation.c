#include <stdlib.h>
#include <string.h>
#include "moderation.h"

static PostNode *head = NULL;
static int nextID = 1;

void initList(void) {
    head = NULL;
    nextID = 1;
}

void freeList(void) {
    PostNode *cur = head;
    while (cur) {
        PostNode *next = cur->next;
        free(cur);
        cur = next;
    }
    head = NULL;
}

PostNode* addPost(const char *author, const char *content, ReportType report, int reportsCount){
    PostNode *node = malloc(sizeof(PostNode));
    if (!node) {
        printf("=!= Blad alokacji pamieci =!=\n");
        return NULL;
    }

    node->data.id = nextID++;

    strncpy(node->data.author, author, MAX_AUTHOR -1);
    node->data.author[MAX_AUTHOR - 1] = '\0';

    strncpy(node->data.content, content, MAX_CONTENT -1);
    node->data.content[MAX_CONTENT - 1] = '\0';

    node->data.report = report;
    node->data.reportsCount = (reportsCount < 0) ? 0 : reportsCount;
    node->data.status = MODSTAT_TO_VERIFY;

    node->next = head;
    head = node;

    return node;
}

PostNode* findPostById(int id){
    PostNode *cur = head;
    while (cur) {
        if (cur->data.id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}

int editPost(int id){
    PostNode *node = findPostById(id);
    if (!node) {
        printf("Nie znaleziono posta o ID %d.\n", id);
        return 0;
    }

    char buf[512];
    int choice;

    printf("Edycja posta:\n");
    printPost(&node->data);
    printf("\n1. Zmien autora\n2. Zmien tresc\n3. Zmien kategorie\n4. Zmien liczbe zgloszen\n5. Zmien status\n0. Koniec edycji\n");

    while (1) {
        printf("Wybierz pole do edycji: ");
        if (!fgets(buf, sizeof(buf), stdin)) return 0;
        if (sscanf(buf, "%d", &choice) != 1){
            printf("Niepoprawny wybor.\n");
            continue;
        }
        if (choice == 0) break;

        switch (choice) {
            case 1:
                printf("Nowy autor: ");
                if (!fgets(buf, sizeof(buf), stdin)) return 0;
                buf[strcspn(buf, "\n")] = '\0';
                strncpy(node->data.author, buf, MAX_AUTHOR - 1);
                node->data.author[MAX_AUTHOR - 1] = '\0';
                break;
            case 2:
                printf("Nowa tresc: ");
                if (!fgets(buf, sizeof(buf), stdin)) return 0;
                buf[strcspn(buf, "\n")] = '\0';
                strncpy(node->data.content, buf, MAX_CONTENT - 1);
                node->data.content[MAX_CONTENT - 1] = '\0';
                break;
            case 3: {
                int r;
                printf("Nowa kategoria (0=spam, 1=nienawisc, 2=wulgaryzmy, 3=fake news, 4=nieodpowiednie): ");
                if (!fgets(buf, sizeof(buf), stdin)) return 0;
                if (sscanf(buf, "%d", &r) == 1 && r >= 0 && r <= 4) {
                    node->data.report = (ReportType)r;
                } else {
                    printf("Niepoprawna liczba.\n");
                }
                break;
            }
            case 4: {
                int rc;
                printf("Nowa liczba zgloszen: ");
                if (!fgets(buf, sizeof(buf), stdin)) return 0;
                if (sscanf(buf, "%d", &rc) == 1 && rc >= 0) {
                    node->data.reportsCount = rc;
                } else {
                    printf("Niepoprawna liczba.\n");
                }
                break;
            }
            case 5: {
                int s;
                printf("Nowy status (0=do weryfikacji, 1=w analizie, 2=zatwierdzony, 3=usuniety): ");
                if (!fgets(buf, sizeof(buf), stdin)) return 0;
                if (sscanf(buf, "%d", &s) == 1 && s >= 0 && s <= 3) {
                    node->data.status = (ModerationStatus)s;
                } else {
                    printf("Niepoprawny status.\n");
                }
                break;
            }
            default:
                printf("Nieznana opcja.\n");
        }
    }
    return 1;
}

int canDelete(const Post *p){
    if (p->status == MODSTAT_TO_VERIFY || p->status == MODSTAT_UNDER_ANALYSIS){
        return 0;
    }
    return 1;
}

int deletePostById(int id){
    PostNode *cur = head;
    PostNode *prev = NULL;

    while (cur) {
        if (cur->data.id == id){
            if (!canDelete(&cur->data)){
                printf("Nie mozna usunac posta ID %d -> status: %s.\n",
                        id, statusToStr(cur->data.status));
                return 0;
            }
            if (prev) prev->next = cur->next;
            else head = cur->next;
            free(cur);
            printf("Usunieto post ID %d.\n", id);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("Nie znaleziono posta o ID %d.\n", id);
    return 0;
}

int deletePostsByMinReports(int minReports){
    PostNode *cur = head;
    PostNode *prev = NULL;
    int removed = 0;

    while (cur) {
        if (cur->data.reportsCount >= minReports && canDelete(&cur->data)){
            PostNode *toDel = cur;
            if (prev) prev->next = cur->next;
            else head = cur->next;
            cur = cur->next;
            free(toDel);
            removed++;
            continue;
        }
        prev = cur;
        cur = cur->next;
    }

    printf("Usunieto %d postow spelniajacych kryterium.\n", removed);
    return removed;
}

void printAllPosts(void) {
    PostNode *cur = head;
    int idx = 0;

    if (!cur) {
        printf("=!= Brak postow =!=\n");
        return;
    }

    while (cur) {
        printf("=== Post %d ===\n", ++idx);
        printPost(&cur->data);
        printf("\n");
        cur = cur->next;
    }
}