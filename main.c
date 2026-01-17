#include <stdio.h>
#include "moderation.h"

int main() {
    printf("Inicjowanie listy...\n");
    initList();

    printf("Dodawanie postow...\n");
    addPost("Ala", "Post Ala", REPORT_SPAM, 1);
    addPost("Bob", "Post Bob", REPORT_HATE, 5);
    addPost("Cecylia", "Post Cecylia", REPORT_FAKE, 10);

    printf("Lista po dodaniu postow:\n");
    printAllPosts();

    printf("Usuwanie posta o ID 2...\n");
    deletePostById(2);

    printf("Lista po usunieciu posta o ID 2:\n");
    printAllPosts();

    printf("Usuwanie postow z liczba zgloszen >= 5...\n");
    deletePostsByMinReports(5);

    printf("Lista po usunieciu postow z >= 5 zgloszen:\n");
    printAllPosts();

    printf("Zwalnianie listy...\n");
    freeList();

    printf("Lista po freeList:\n");
    printAllPosts();

    return 0;
}