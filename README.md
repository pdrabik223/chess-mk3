# chess-mk3
The third attempt at chess engine


## Motivation

So... it's supposed to be difficult. 
For as long as I can remember, I always wanted to write my own chess engine from scrap. 
I had 3 attempts already, all pushed me closer to the goal but not one was close enough. 
The project was never about the chess engine itself, it was always more about learning how to make a project like chess engine. 
That's why second attempt spiraled into Learning SDL. 
With this project I would like to do something different: restrain myself as much as possible. 

## The goals for the project:

- Create physical chess board, with piece movement detection and flashing lights based on Arduino Uno board
- Write chess engine for the same Arduino board
- The chess board should be compact, simple, clean and easy to show off

## Rules to the game:
- No external libraries can be used to create chess engine
- Only Arduino can be used to process data
- No online guides, to the reasonable degree obviously
  

## Configure for x64
```s
cd chess_board 
cmake -B buildx64
```
## build for x64

```s

cmake --build buildx64 
```

## Parts
[Hall sensors](https://allegro.pl/oferta/czujnik-halla-a3144-wykrywacz-metali-prad-13664145165)
[Hall sensors, local vendor](https://allegro.pl/moje-allegro/zakupy/kupione/977733b3-8f03-3715-b591-6c909b9daa5f)
[Led strip](https://allegro.pl/oferta/adresowalna-tasma-led-ws2812b-30d-m-ip20-cyfrowa-10583524893)