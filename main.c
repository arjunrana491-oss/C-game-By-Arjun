#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "game.h"
#include "utils.h"

int main() {
    int choice;
    int highScore = loadHighScore();
    
    // Start Menu (Modification #6)
    do {
        system("cls");
        printf("================================\n");
        printf("     SPACE DEFENDER GAME\n");
        printf("================================\n");
        printf("1. Start Game\n");
        printf("2. View High Score\n");
        printf("3. Exit\n");
        printf("================================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                startGame(highScore);
                break;
            case 2:
                system("cls");
                printf("High Score: %d\n", highScore);
                printf("\nPress any key to continue...");
                _getch();
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice!\n");
                Sleep(1000);
        }
    } while(choice != 3);
    
    return 0;
}