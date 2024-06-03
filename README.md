# Intro

This is a fairly rough C++ implementation of the famouse snake game. The snake is made of `o` characters and eats "fruits" that are really just `a` characters :). I made this as a personal project to see whether I could make a simple game with just C++. Ultimately I ended up also using the curses library, which includes many QoL functions for 'drawing' characters on the screen.

# Building and running

Mac and Linux users can simply navigate to the repository's parent directory in your terminal and execute the creatively named `buildrun.sh` script. Windows users, sorry, you're currently on your own.

```bash
./buildrun.sh
```

This will create the bin directory if it doesn't already exist, then build snake.o inside that directory, and finally run it.

Note: You may need to first make `build.sh` executable like so:

```bash
chmod +x buildrun.sh
```
