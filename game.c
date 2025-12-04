#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "game.h"
#include "utils.h"

void startGame(int highScore) {
    Player player = {WIDTH/2, HEIGHT-2, 3, 0}; // 3 lives (Modification #2)
    Obstacle obstacles[MAX_OBSTACLES];
    int obstacleCount = 0;
    int difficulty = 1;
    int gameOver = 0;
    char input;
    clock_t lastSpawn = clock();
    
    srand(time(NULL));
    
    while(!gameOver) {
        // Input handling
        if(_kbhit()) {
            input = _getch();
            switch(input) {
                case 'a': if(player.x > 1) player.x--; break;
                case 'd': if(player.x < WIDTH-2) player.x++; break;
                case ' ': // Shooting (High-Level Modification #10 - simplified)
                    // Simple shooting by removing obstacles
                    for(int i = 0; i < obstacleCount; i++) {
                        if(obstacles[i].alive && obstacles[i].y == player.y-1) {
                            obstacles[i].alive = 0;
                            player.score += 10; // Score system (Modification #1)
                        }
                    }
                    break;
                case 27: // ESC to exit
                    gameOver = 1;
                    break;
            }
        }
        
        // Game update
        updateGame(&player, obstacles, &obstacleCount, &difficulty);
        
        // Spawn obstacles periodically
        if(clock() - lastSpawn > (2000/difficulty)) { // Difficulty affects spawn rate
            spawnObstacle(obstacles, &obstacleCount);
            lastSpawn = clock();
        }
        
        // Check collisions
        if(checkCollision(player, obstacles, obstacleCount)) {
            player.lives--;
            if(player.lives <= 0) {
                gameOver = 1;
            }
        }
        
        // Draw everything
        drawGame(player, obstacles, obstacleCount, difficulty);
        
        // Simple delay
        Sleep(50);
    }
    
    // Game Over screen
    system("cls");
    printf("================================\n");
    printf("          GAME OVER\n");
    printf("================================\n");
    printf("Final Score: %d\n", player.score);
    printf("Lives Remaining: %d\n", player.lives);
    
    if(player.score > highScore) {
        printf("NEW HIGH SCORE!\n");
        saveHighScore(player.score);
    }
    
    printf("\nPress any key to return to menu...");
    _getch();
}

void drawGame(Player player, Obstacle obstacles[], int obstacleCount, int difficulty) {
    system("cls");
    
    printf("Score: %d | Lives: %d | Difficulty: %d\n", player.score, player.lives, difficulty);
    printf("Controls: A/D=Move, Space=Shoot, ESC=Exit\n");
    printf("=");
    for(int i = 0; i < WIDTH; i++) printf("=");
    printf("=\n");
    
    for(int y = 0; y < HEIGHT; y++) {
        printf("|");
        for(int x = 0; x < WIDTH; x++) {
            // Draw player
            if(x == player.x && y == player.y) {
                printf("^");
            }
            // Draw obstacles
            else {
                int drawn = 0;
                for(int i = 0; i < obstacleCount; i++) {
                    if(obstacles[i].alive && obstacles[i].x == x && obstacles[i].y == y) {
                        printf("*"); // Improved icon (Modification #9)
                        drawn = 1;
                        break;
                    }
                }
                if(!drawn) printf(" ");
            }
        }
        printf("|\n");
    }
    
    printf("=");
    for(int i = 0; i < WIDTH; i++) printf("=");
    printf("=\n");
}

void updateGame(Player *player, Obstacle obstacles[], int *obstacleCount, int *difficulty) {
    // Move obstacles down
    for(int i = 0; i < *obstacleCount; i++) {
        if(obstacles[i].alive) {
            obstacles[i].y++;
            if(obstacles[i].y >= HEIGHT) {
                obstacles[i].alive = 0;
                player->score += 5;
            }
        }
    }
    
    // Clean up dead obstacles
    int newCount = 0;
    for(int i = 0; i < *obstacleCount; i++) {
        if(obstacles[i].alive) {
            obstacles[newCount++] = obstacles[i];
        }
    }
    *obstacleCount = newCount;
    
    // Increase difficulty over time (Modification #3)
    static int difficultyTimer = 0;
    if(++difficultyTimer > 100) {
        if(*difficulty < 5) {
            (*difficulty)++;
        }
        difficultyTimer = 0;
    }
}

void spawnObstacle(Obstacle obstacles[], int *obstacleCount) {
    if(*obstacleCount < MAX_OBSTACLES) {
        obstacles[*obstacleCount].x = rand() % WIDTH;
        obstacles[*obstacleCount].y = 0;
        obstacles[*obstacleCount].alive = 1;
        (*obstacleCount)++;
    }
}

int checkCollision(Player player, Obstacle obstacles[], int obstacleCount) {
    for(int i = 0; i < obstacleCount; i++) {
        if(obstacles[i].alive && 
           obstacles[i].x == player.x && 
           obstacles[i].y == player.y) {
            obstacles[i].alive = 0;
            return 1;
        }
    }
    return 0;
}