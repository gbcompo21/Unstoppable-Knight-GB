#include <gb/gb.h>
#include <gb/font.h>
#include "inc/functions.h"
#include "src/titlescreen_data.c"
#include "src/titlescreen_map.c"

void main(){

    //Choose font
    font_t min_font;

    
    //Set up the titlescreen
    set_bkg_data(0, 149, titlescreen_data);
    set_bkg_tiles(0, 0, 20, 18, titlescreen_map);

    SHOW_BKG;
    DISPLAY_ON;

    //The game won't begin until the start button is pressed
    waitpad(J_START | J_A);

    fadeOut();

    //fadeIn();

    HIDE_BKG;
    DISPLAY_OFF;

    disable_interrupts();

    //Set font
    font_init();
    min_font = font_load(font_min); // 36 tiles
    font_set(min_font);

    setupBackground();
    set_win_tiles(0, 0, 20, 1, windowmap);
    move_win(7, 128);
    set_sprite_data(0, 32, knight_sprites);
    setupPlayer();
    setupCoins();
    setupArrow();
    setupObstacles();
    init();

    while(1){
        SHOW_WIN;
        if(game_on == TRUE){
            scroll_bkg(0, 4);
            joyHandler();
            if(player.x < 40){
                player.x = 40;
            } else if(player.x > 120){
                player.x = 120;
            }
            positionCoins();
            playerAnimation();
            moveCharacter(&player, player.x, player.y);
            positionArrow();
            positionObstacles();
            updateHealth();
            //Updates the whole window layer
            set_win_tiles(0, 0, 20, 1, windowmap);
            if (frame > 2){
                frame = 0;
                hit = FALSE;
            }
        } else {
            if(joypad() & J_START){
                //Restart game
                game_on = TRUE;
                setupBackground();
                SHOW_SPRITES;
                performDelay(10);
            }
        }
        wait_vbl_done();
    }
}