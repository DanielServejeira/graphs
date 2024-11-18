#include<stdio.h>

#include "english_interface.h"
#include "portuguese_interface.h"

typedef enum {
    ENGLISH = 1,
    PORTUGUESE
} Language;

int main() {
    Language language;

    printf("By Daniel Servejeira & Raphael Leiva\n"
           "\nSelect your language: "
           "\n[1] English"
           "\n[2] Portuguese (Coming soon...)\n\n");

    while (scanf("%d", (int*)&language) != 1 || language < ENGLISH || language > PORTUGUESE) {
        printf("Invalid option. Please select a valid language: "
               "\n[1] English"
               "\n[2] Portuguese (Coming soon...)\n\n");
        while (getchar() != '\n');
    }

    system("cls");

    switch(language) {
        case ENGLISH:
            run_english_interface();
            break;

        case PORTUGUESE:
            run_portuguese_interface();
            break;
    }

    return 0;
}