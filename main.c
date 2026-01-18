#include <stdio.h>
#include "moderation.h"

int main() {
    printf("Inicjowanie listy...\n");
    initList();

    printf("Dodawanie postow...\n");
    addPost("Ala", "Post Ala", REPORT_SPAM, 1);
    addPost("Bob", "Post Boba", REPORT_HATE, 5);
    addPost("Cecylia", "Post Cecylii", REPORT_FAKE, 10);

    printf("Lista po dodaniu postow:\n");
    printAllPosts();

    printf("Zapisywanie listy do pliku test.txt...\n");
    saveToText("test.txt");

    printf("Czyszczenie listy...\n");
    freeList();

    printf("Lista po freeList (powinna byc pusta):\n");
    printAllPosts();

    printf("Wczytywanie listy z test.txt...\n");
    loadFromText("test.txt");

    printf("Lista po loadFromText:\n");
    printAllPosts();

    printf("Zwalnianie listy na koniec...\n");
    freeList();

    return 0;
}