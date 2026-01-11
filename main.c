#include <stdio.h>
#include "moderation.h"

int main() {
    printf("Inicjowanie listy...");
    initList();

    printf("Test: dodawanie posta\n");
    addPost("TestUser", "Testowy post", REPORT_SPAM, 3);

    printf("Test: wyswietlenie listy\n");
    printAllPosts();

    printf("Test: zwalnianie listy\n");
    freeList();

    printf("Test: wyswietlenie listy po freeList()\n");
    printAllPosts();

    return 0;
}