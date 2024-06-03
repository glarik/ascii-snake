#include <list>
#include <vector>

namespace Snake {

int rndInt(int min, int max);

char getDirInput();

void getNewDir(std::vector<std::pair<int, int>>& snekDirs, char& curDir, bool& quitFlag);

void makeFruits(std::vector<std::pair<int, int>>& snekVec,
                std::list<std::pair<int, int>>& fruits,
                int nFruits,
                int xMax,
                int yMax);

} // namespace Snake
