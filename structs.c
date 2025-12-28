#include <stdio.h>
#include "structs.h"

void printPost(const Post *p){
    const char *reportStr[] = {
        "spam",
        "hejt",
        "wulgaryzmy",
        "fejk-news",
        "nieodpowiednie tresci"
    };

    const char *statusStr[] = {
        "do weryfikacji",
        "w trakcie analizy",
        "zatwierdzone",
        "usuniete"
    };

    printf("ID: %d\n", p->id);
    printf("Autor: %s\n", p->author);
    printf("Tresc: %s\n", p->content);
    printf("Kategoria zgloszenia: %s\n", reportStr[p->report]);
    printf("Liczba zgloszen: %d\n", p->reportsCount);
    printf("Status moderacji: %s\n", statusStr[p->status]);
}