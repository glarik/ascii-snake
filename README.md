# Intro

This is a fairly rough implementation of the famouse snake game. The snake is made of `o` characters and eats "fruits" that are really just `a` characters :). Here is a "screenshot":

----------------------------------------------------------------------------------
|                                                                                |
|                                                                                |
|                                                                                |
|              a                                         a                       |
|                          a                                                     |
|                                                                                |
|                                                                                |
|a                                                                               |
|                                                                                |
|                                                                                |
|                                                                                |
|     oooooooooo                                                                 |
|                                                                                |
|                                                                                |
|                                                                                |
|                                                                                |
|                                                                                |
|                                                                                |
|                                                                                |
|                                                                                |
|                                                                                |
|                                                                                |
|                                                                                |
|                                                                                |
|                                                                                |
----------------------------------------------------------------------------------

# Building and running

Simply navigate to the repo directory in your terminal and execute the creatively named `buildrun.sh` script.

```bash
./buildrun.sh
```

This will create the bin directory if it doesn't already exist, then build snake.o inside that directory, and finally run it.

Note: You may need to first make `build.sh` executable like so:

```bash
chmod +x buildrun.sh
```
