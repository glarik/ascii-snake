mkdir -p bin

g++ -std=c++20 -lncurses Snake.cpp SnakeUtils.cpp -o bin/snake.o

./bin/snake.o
