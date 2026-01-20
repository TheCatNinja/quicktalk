#include "menu.h"
#include "moderation.h"

int main(int argc, char *argv[]) {
    const char *defaultLoad = NULL;
    const char *defaultSave = NULL;

    if (argc >= 2) defaultLoad = argv[1];
    if (argc >= 3) defaultSave = argv[2];

    initList();
    runMenu(defaultLoad, defaultSave);
    return 0;
}