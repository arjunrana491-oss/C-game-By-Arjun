#ifndef GAME_H
#define GAME_H

#define WIDTH 60
#define HEIGHT 20
#define MAX_OBSTACLES 10

typedef struct {
    int x, y;
    int alive;
} Obstacle;

typedef struct {
    int x, y;
    int lives;
    int score;
} Player;

void startGame(int highScore);
void drawGame(Player player, Obstacle obstacles[], int obstacleCount, int difficulty);
void updateGame(Player *player, Obstacle obstacles[], int *obstacleCount, int *difficulty);
void spawnObstacle(Obstacle obstacles[], int *obstacleCount);
int checkCollision(Player player, Obstacle obstacles[], int obstacleCount);

#endif