#include "../game.h"

void updateGameLogic() {
    // Update posisi pemain
    gameData.player.update();
    
    // Update ghost AI dengan BFS
    gameData.ghost.setDifficulty(2);
    gameData.ghost.update(gameData.maze, 
                          gameData.player.getX(), 
                          gameData.player.getY());
    
    // Cek collision
    checkCollisions();
    
    // Cek kondisi win/lose
    checkGameState();
}

void checkCollisions() {
    int pX = gameData.player.getX();
    int pY = gameData.player.getY();
    int gX = gameData.ghost.getX();
    int gY = gameData.ghost.getY();
    
    if (pX == gX && pY == gY) {
        gameData.isRunning = false; // Game Over
    }
}