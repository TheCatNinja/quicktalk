#include <stdio.h>
#include "structs.h"

const char* reportTypeToStr(ReportType r) {
    switch (r) {
        case REPORT_SPAM:           return "spam";
        case REPORT_HATE:           return "nienawisc";
        case REPORT_VULGAR:         return "wulgarne";
        case REPORT_FAKE:           return "fake news";
        case REPORT_INAPPRIOPRIATE: return "nieodpowiednie";
        default:                    return "nieznane";
    }
}

const char* statusToStr(ModerationStatus s) {
    switch (s) {
        case MODSTAT_TO_VERIFY:      return "do weryfikacji";
        case MODSTAT_UNDER_ANALYSIS: return "w analizie";
        case MODSTAT_APPROVED:       return "zatwierdzony";
        case MODSTAT_DELETED:        return "usuniety";
        default:                     return "nieznany";
    }
}

void printPost(const Post *p){
    if (!p) return;
    printf("ID: %d\n", p->id);
    printf("Autor: %s\n", p->author);
    printf("Tresc: %s\n", p->content);
    printf("Kategoria zgloszenia: %s\n", reportTypeToStr(p->report));
    printf("Liczba zgloszen: %d\n", p->reportsCount);
    printf("Status moderacji: %s\n", statusToStr(p->status));
}