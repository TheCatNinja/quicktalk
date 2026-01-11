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