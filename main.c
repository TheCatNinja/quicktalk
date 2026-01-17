#include <stdio.h>
#include "moderation.h"

int main() {
    printf("Inicjowanie listy...\n");
    initList();

    printf("Dodawanie postow...\n");
    addPost("Ala", "Post Ala", REPORT_SPAM, 1);
    addPost("Alicja", "Post Alicji", REPORT_HATE, 4);
    addPost("Bob", "Post Boba", REPORT_FAKE, 7);
    addPost("Cecylia", "Post Cecylii", REPORT_SPAM, 10);

    printf("Lista po dodaniu postow:\n");
    printAllPosts();

    printf("Test: searchByAuthorPrefix(\"Al\")\n");
    searchByAuthorPrefix("Al");

    printf("Test: searchByMinReports(5)\n");
    searchByMinReports(5);

    printf("Usuwanie posta o ID 3...\n");
    deletePostById(3);

    printf("Lista po usunieciu posta o ID 3:\n");
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