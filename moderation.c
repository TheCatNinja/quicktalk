#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

/*PRZEROBIĆ TO NA MALLOC*/

#define MAX_POSTS 1000

static int nextID = 1;
static Post posts[MAX_POSTS];
static int postsCount = 0;

Post* addPost(const char *author, const char *content, ReportType report, int reportsCount){
    if (postsCount >= MAX_POSTS){
        printf("UWAGA: Przekroczono maksymalna liczbe postow!\n");
        return NULL;
    }

    Post *p = &posts[postsCount++];
    p->id = nextID++;
    strncpy(p->author, author, sizeof(p->author) - 1);
    p->author[sizeof(p->author) - 1] = '\0';

    strncpy(p->content, content, sizeof(p->content) - 1);
    p->content[sizeof(p->content) - 1] = '\0';

    p->report = report;
    p->reportsCount = reportsCount;
    p->status = MODSTAT_TO_VERIFY;

    return p;
}