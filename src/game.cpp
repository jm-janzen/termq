#include <ncurses.h>
#include <time.h>
#include <stdio.h>

#include <string>
#include <algorithm>

#include "Global.h"  // includes difficulties
#include "World.h"
#include "Map.h"

#include "game.h"
#include "menu.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "Window.h"
#include "DiagWindow.h"
#include "StatusBar.h"

using namespace std;


int startGame() {

    // Retrieve global refs
    Global *global = Global::get();
    int numCoins   = global->getNoCoins();
    int numEnemies = global->getNoEnemies();

    // Setup Windows
    DiagWindow diagWin_game = DiagWindow({{45, 1}, {80,10}});
    Window wgame = Window(game_area);
    Map map = Map(&wgame);

    // StatusBar needs an Actor
    Player player = Player();
    StatusBar statusBar = StatusBar({{41, 1}, {80, 4}}, player);

    // Setup non-Player entities
    std::vector<Enemy> enemies;
    for (int i = 0; i < numEnemies; i++)
        enemies.push_back(Enemy());
    std::vector<Coin> coins;
    for (int i = 0; i < numCoins; i++)
        coins.push_back(Coin());


    // Check if Player & Enemy are too near from each other.
    uint_fast8_t quarterArea = (game_area.area() / 4);
    for (Enemy &enemy : enemies) {
        enemy = Enemy(player);
        do {
            enemy.setPosRand();
        } while (player.getDistance(enemy.getPos()) < quarterArea);
    }


    /*
     * Init placement of Player, Enemy, and Coins
     * Map prioritises drawing items in the reverse
     * of the order that they were added
     */
    map.push(player);
    for (Coin  &coin  : coins)   map.push(coin);
    for (Enemy &enemy : enemies) map.push(enemy);


    /*
     * Game loop begin.
     */

    int coinsCollected = 0;
    string infoMsg = "";
    bool isGameover = false;
    while (isGameover == false) {
        // Advance record of world time
        global->tick();

        // Draw all entities
        map.draw();

        statusBar.refresh();
        diagWin_game.refresh();

        infoMsg = "";
        vec2ui prevPos = player.getPos();

        switch (wgame.getChar()) {
            /*
             * Diagonal keys
             */
            case 55:  // Key up-left
                player.moveNorthWest();
                break;
            case 57:  // Key up-right
                player.moveNorthEast();
                break;
            case 51:  // Key down-right
                player.moveSouthEast();
                break;
            case 49:  // Key down-left
                player.moveSouthWest();
                break;

            /*
             * Orthogonal keys
             */
            case KEY_UP:
            case 56:
            case 'k':
                player.moveNorth();
                break;
            case KEY_DOWN:
            case 50:
            case 'j':
                player.moveSouth();
                break;
            case KEY_LEFT:
            case 52:
            case 'h':
                player.moveWest();
                break;
            case KEY_RIGHT:
            case 54:
            case 'l':
                player.moveEast();
                break;
            case KEY_ENTER: /* numpad enter */
            case '\n':      /* keyboard return */
                break;
            case 27:        /* ESC */
                isGameover = true;
                break;
            default:
                player.wait();
                infoMsg = player.getName();

        }

        if (map.checkCell(player.getPos(), "Enemy")) {
            for (Enemy &enemy : enemies) {
                if (enemy.getPos() == player.getPos()) {
                    player.attack(enemy);
                }
            }
            player.setPos(prevPos);
        }

        std::string playerLastMessage = player.getLastMessage();
        if (playerLastMessage != "") {
            diagWin_game.push(playerLastMessage);
        }

        // Draw Coins again, and check if player has landed on
        // TODO replace this for..range with std iter for loop
        for (auto &coin : coins) {
            if (player.atop(coin.getPos())) {
                coin.setOwnership(PLAYER);
                player.addItem(coin);

                // Erase this coin if owned by Player
                coins.erase(
                    std::remove_if(
                        coins.begin(),
                        coins.end(),
                        [](Coin& c) -> bool {
                            return c.getOwnership() == PLAYER;
                        }
                    ),
                    coins.end()
                );

                if ( ++coinsCollected == numCoins) {
                    isGameover = true;
                }
            }
        }

        // Enemy, seek out player
        std::string enemyLastMessage = "";
        string proximityAlert = "";
        for (size_t i = 0; i < enemies.size(); i++) {
            if (enemies[i].getHP() > 0) {

                // Number of moves == enemy's ACT attribute
                for (size_t j = 0; j < enemies[i].getACT(); j++) {
                    enemies[i].move();
                    enemyLastMessage = enemies[i].getLastMessage();
                    if (enemyLastMessage != "") {
                        diagWin_game.push(enemyLastMessage);
                    }
                }

                // One `!' for each enemy in combat range
                if (enemies[i].isAdjacent(player.getPos())) proximityAlert += "!";
            } else { // pop dead enemy
                enemies.erase(enemies.begin() + i);
            }
        }

        // Game Over
        if (player.getHP() <= 0) {
            wgame.coloSplash(COLOR_PAIR(1));  // Red
            diagWin_game.push("GAME OVER!");
            isGameover = true;
            break;
        }

        // Redraw player's statusbar
        statusBar.refresh();


        // Re-init map with refs to updated entities
        map = Map(&wgame);
        map.push(player);
        for (Coin  &coin  : coins)   map.push(coin);
        for (Enemy &enemy : enemies) map.push(enemy);
    }

    /*
     * Post-game loop operations.
     */
    map.draw();  // Draw last frame.

    // TODO eventually return more information
    return player.getScore();
}

