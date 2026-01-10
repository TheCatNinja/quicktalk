#include <stdio.h>
#include "structs.h"

Post* addPost(const char *author, const char *content, ReportType report, int reportsCount);

void printPost(const Post *p);

int main() {
    Post *p = addPost("TestUser", "To jest testowy post", REPORT_SPAM, 5);

    if (p == NULL) {
        printf("Nie udało się dodać posta.\n");
        return 1;
    }

    printf("Dodano post! Oto jego dane:\n\n");
    printPost(p);

    return 0;
}