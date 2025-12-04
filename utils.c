#include <stdio.h>
#include <windows.h>

int loadHighScore() {
    FILE *file = fopen("highscore.txt", "r");
    int highScore = 0;
    if(file) {
        fscanf(file, "%d", &highScore);
        fclose(file);
    }
    return highScore;
}

void saveHighScore(int score) {
    FILE *file = fopen("highscore.txt", "w");
    if(file) {
        fprintf(file, "%d", score);
        fclose(file);
    }
}

void beep() {
    // Simple sound effect (would be High-Level Modification #4)
    Beep(440, 100);
}