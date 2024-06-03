#include <curses.h>
//#include <stdio.h>
//#include <sys/select.h>
//#include <termios.h>
//#include <unistd.h>
#include <list>
#include <random>
#include <vector>

namespace Snake {

int rndInt(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
}

char getDirInput() {
    int ch = getch();

    if ((char)ch == 'q') {
        return 'q';
    }

    // down is 258
    // up is 259
    // left is 260
    // right is 261
    if (ch == 258) {
        return 'D';
    } else if (ch == 259) {
        return 'U';
    } else if (ch == 260) {
        return 'L';
    } else if (ch == 261) {
        return 'R';
    } else {
        return 'N';
    }
}

void getNewDir(std::vector<std::pair<int, int>>& snekDirs, char& curDir, bool& quitFlag) {
    char newDir = getDirInput();

    if (newDir == 'q') {
        quitFlag = true;
        return;
    }

    // new direction has been pressed
    if (curDir != newDir) {
        // only allow 90 degree turns
        if (newDir == 'U' && curDir != 'D') {
            snekDirs[0] = std::make_pair(0, -1);
        } else if (newDir == 'D' && curDir != 'U') {
            snekDirs[0] = std::make_pair(0, 1);
        } else if (newDir == 'R' && curDir != 'L') {
            snekDirs[0] = std::make_pair(1, 0);
        } else if (newDir == 'L' && curDir != 'R') {
            snekDirs[0] = std::make_pair(-1, 0);
        } else {
            // invalid key
            return;
        }

        curDir = newDir;
    }
}

void makeFruits(std::vector<std::pair<int, int>>& snekVec,
                std::list<std::pair<int, int>>& fruits,
                int nFruits,
                int xMax,
                int yMax) {
    for (size_t i = 0; i < nFruits; ++i) {
        int x;
        int y;
        bool collision;

        do {
            collision = false;

            // Note: it's possible that multiple fruits will have the same
            // coordinates, for now we don't care.
            x = rndInt(0, xMax);
            y = rndInt(0, yMax);

            // make sure fruits aren't where snake is
            for (auto p : snekVec) {
                if (p.first == x && p.second == y) {
                    collision = true;
                }
            }
        } while (collision);

        fruits.push_back(std::make_pair(x, y));
    }
}

} // namespace Snake
