#include <stdio.h>
#include "moderation.h"

int main() {
    printf("Inicjowanie listy...\n");
    initList();

    printf("Dodawanie postow...\n");
    addPost("Ala", "Post Ala", REPORT_SPAM, 1);          // ID = 1
    addPost("Alicja", "Post Alicji", REPORT_HATE, 4);    // ID = 2
    addPost("Bob", "Post Boba", REPORT_FAKE, 7);         // ID = 3
    addPost("Cecylia", "Post Cecylii", REPORT_SPAM, 10); // ID = 4

    printf("Lista po dodaniu postow:\n");
    printAllPosts();

    printf("Sortowanie po autorze:\n");
    sortAndPrintByAuthor();

    printf("Sortowanie po liczbie zgloszen:\n");
    sortAndPrintByReports();

    printf("Wyszukiwanie autorow zaczynajacych sie na 'Al':\n");
    searchByAuthorPrefix("Al");

    printf("Wyszukiwanie postow z liczba zgloszen >= 5:\n");
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