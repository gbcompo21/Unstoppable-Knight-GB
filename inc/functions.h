#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <gb/gb.h>
#include <rand.h>
#include "../audio/gbt_player.h"
#include "gameCharacter.h"
#include "characters.h"
#include "windowLayer.h"
#include "GameOverBackground.h"


extern const unsigned char * song_Data[];

extern BOOLEAN game_on;

extern uint16_t seed;

extern void interruptLCD();
extern void turnOnSound();
extern void turnOffSound();
extern void init();
extern void performDelay(UINT8 numloops);

extern void joyHandler();

extern void updateLives();
extern void fadeOut();
extern void fadeIn();
extern void resetBackground();

extern void hitSound();
extern void coinSound();
extern UINT8 randomize(UINT8 n);
extern void gameOverScreen();

#endif