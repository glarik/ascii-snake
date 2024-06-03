#include <cstdlib> // atexit
#include <curses.h>
#include <list>
#include <sstream>  // std::ostringstream
#include <unistd.h> // sleep
#include <vector>

#include "SnakeUtils.h"

using namespace Snake;

int GAME_WIDTH = 80;
int GAME_HEIGHT = 25;

int START_LEN = 10;

bool GAME_OVER = false;

int main() {
    // make sure we stop curses on exit
    std::atexit([] { endwin(); });

    // curses init commands
    initscr();
    cbreak(); // get each char input without buffering, but escape chars still work
    noecho();
    keypad(stdscr, true);  // special buttons like arrow keys are mapped to single int
    nodelay(stdscr, true); // non-blocking getch, just checks for queued inputs and returns

    char curDir = 'L';

    std::vector<std::pair<int, int>> snekVec(START_LEN);

    // snake should start in the middle
    int firstX = GAME_WIDTH / 2;
    int firstY = GAME_HEIGHT / 2;
    for (int i = 0; i < snekVec.size(); ++i) {
        snekVec[i] = std::make_pair(firstX + i, firstY);
    }

    // to handle turns, each snake coordinate has its own direction
    std::vector<std::pair<int, int>> snekDirs(START_LEN, std::make_pair(-1, 0));

    size_t nFruits = 5;
    std::list<std::pair<int, int>> fruits;
    makeFruits(snekVec, fruits, nFruits, GAME_WIDTH - 1, GAME_HEIGHT - 1);

    while (!GAME_OVER) {
        for (int y = 0; y < GAME_HEIGHT + 2; ++y) {
            for (int x = 0; x < GAME_WIDTH + 2; ++x) {
                if (y == 0 || y == GAME_HEIGHT + 1) {
                    mvprintw(y, x, "-");
                    continue;
                }

                if (x == 0 || x == GAME_WIDTH + 1) {
                    mvprintw(y, x, "|");
                    continue;
                }

                // this char will be drawn at coords (x,y)
                char c = ' ';

                // check if we should draw fruit
                auto curFruit = fruits.begin();
                for (auto it = fruits.begin(); it != fruits.end(); ++it) {
                    if (x == it->first && y == it->second) {
                        curFruit = it;
                        c = 'a';
                        break;
                    }
                }

                // check if snake is "on top of" fruit
                bool eat = false;
                for (auto sCoord : snekVec) {
                    if (x == sCoord.first && y == sCoord.second) {
                        if (c == 'a') {
                            eat = true;
                        }
                        c = 'o';
                        break;
                    }
                }

                // grow snake
                if (eat) {
                    auto lastCoord = snekVec[snekVec.size() - 1];
                    auto lastDir = snekDirs[snekDirs.size() - 1];

                    // subtracting the direction of the last snake coordinate gives us the
                    // coordinate of the new last snake piece
                    int newX = lastCoord.first - lastDir.first;
                    int newY = lastCoord.second - lastDir.second;

                    snekVec.push_back(std::make_pair(newX, newY));
                    snekDirs.push_back(snekDirs[snekDirs.size() - 1]);

                    // delete fruit
                    fruits.erase(curFruit);

                    eat = false;
                }

                mvprintw(y, x, &c);
            } // for X
        }     // for Y

        // check if user has requested direction change
        bool quitFlag = false;
        getNewDir(snekDirs, curDir, quitFlag);

        if (quitFlag) {
            break;
        }

        int lastLine = GAME_HEIGHT + 2; // for logging

        // move snake
        auto newDirs = snekDirs; // grab copy for later
        for (int i = 0; i < snekVec.size(); ++i) {
            std::ostringstream oss;
            oss << "Snek coords: (" << snekVec[i].first << ", " << snekVec[i].second << ")";

            mvprintw(lastLine++, 0, oss.str().c_str());
            snekVec[i].first += snekDirs[i].first;
            snekVec[i].second += snekDirs[i].second;

            // Whenever adjacent directions are different, we copy over the one on the "left"
            // This will eventually percolate each turn down to the end of the snake.
            if (i > 0 && snekDirs[i] != snekDirs[i - 1]) {
                newDirs[i] = snekDirs[i - 1];
            }

            // check collision with self
            if (i > 0) {
                if (snekVec[0].first == snekVec[i].first &&
                    snekVec[0].second == snekVec[i].second) {
                    GAME_OVER = true;
                    break;
                }
            }
        }
        snekDirs = std::move(newDirs);

        // wall collision check
        if (snekVec[0].first <= 0 || snekVec[0].first > GAME_WIDTH) {
            GAME_OVER = true;
            break;
        }

        if (snekVec[0].second <= 0 || snekVec[0].second > GAME_HEIGHT) {
            GAME_OVER = true;
            break;
        }

        refresh();

        usleep(0.1 /*s*/ * 1000000);
    } // while(!GAME_OVER)

    if (GAME_OVER) { // user lost game, as opposed to quitting
        std::string toPrint = "GAME OVER";
        mvprintw(GAME_HEIGHT / 2, GAME_WIDTH / 2 - toPrint.length() / 2, toPrint.c_str());

        toPrint = "Press 'q' to quit.";
        mvprintw(GAME_HEIGHT / 2 + 2, GAME_WIDTH / 2 - toPrint.length() / 2, toPrint.c_str());
        refresh();

        // turn on blocking getch() to listen for quit command
        nodelay(stdscr, false);
        int ch = ' ';

        while ((char)ch != 'q') {
            ch = getch();
        }
    }

    endwin();
    return 0;
}
