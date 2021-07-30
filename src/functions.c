#include "../inc/functions.h"

BOOLEAN game_on = TRUE;

uint16_t seed;

void interruptLCD(){
    HIDE_WIN;
}

void turnOnSound(){
    NR52_REG = 0x8F; //Turn on the sound
    NR51_REG = 0x11; //Enable the sound channels
    NR50_REG = 0x77; //Increase the volume to its max()
}

void turnOffSound(){
    NR52_REG = 0x00;
}

void init(){
    SHOW_WIN;
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
    turnOnSound();

    add_LCD(interruptLCD);
    enable_interrupts();
    set_interrupts(VBL_IFLAG | LCD_IFLAG);
}

void performDelay(UINT8 numloops){
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }
}

<<<<<<< HEAD
=======
UBYTE checkCollision(GameCharacter* one, GameCharacter* two){
    return(one->x >= two->x && one->x <= two->x + two->w) && (one->y >= two->y && one->y <= two->y + two->h) || (two->x >= one->x && two->x <= one->x + one->w) && (two->y >= one->y && two->y <= one->y + one->h);
}

// Give the player a smaller hitbox
UBYTE checkPlayerCollision(GameCharacter* character){
    return(player.x  + 2 >= character->x && player.x + 2 <= character->x + character->w) && (player.y + 2 >= character->y && player.y + 2 <= character->y + character->h) || (character->x >= player.x + 2 && character->x <= player.x + player.w - 2) && (character->y >= player.y + 2 && character->y <= player.y + player.h - 2);
}

void moveCharacter(GameCharacter* character, UINT8 x, UINT8 y){
    move_sprite(character->spriteID[0], x, y);
    move_sprite(character->spriteID[1], x + spritesize, y);
    move_sprite(character->spriteID[2], x, y + spritesize);
    move_sprite(character->spriteID[3], x + spritesize, y + spritesize);
}

void setupPlayer(){
    player.x = 80;
    player.y = 20;
    player.h = 16;
    player.w = 16;
    player.health = 3;

    //load player's sprites
    set_sprite_tile(0, 0);
    player.spriteID[0] = 0;
    set_sprite_tile(2, 0);
    player.spriteID[1] = 2;
    set_sprite_tile(1, 1);
    player.spriteID[2] = 1;
    set_sprite_tile(3, 3);
    player.spriteID[3] = 3;

    moveCharacter(&player, player.x, player.y);
}

void Animations(){
    UINT8 n = 3*frame + frame;

    //Orc Animation
    set_sprite_tile(obstacles[1].spriteID[0], 19 + n);
    set_sprite_prop(obstacles[1].spriteID[0], S_PRIORITY | 4);
    set_sprite_tile(obstacles[1].spriteID[2], 20 + n);
    set_sprite_prop(obstacles[1].spriteID[2], S_PRIORITY | 4);    
    set_sprite_tile(obstacles[1].spriteID[1], 21 + n);
    set_sprite_prop(obstacles[1].spriteID[1], S_PRIORITY | 4);    
    set_sprite_tile(obstacles[1].spriteID[3], 22 + n); 
    set_sprite_prop(obstacles[1].spriteID[3], S_PRIORITY | 4);

    if(obstacles[0].y < 8){
        hit = FALSE; // Makes the player hitable again
    }


    if(hit == TRUE){
        //Hit effect
        set_sprite_tile(0, 32);
        set_sprite_tile(2, 32);
        set_sprite_tile(1, 32);
        set_sprite_tile(3, 32);
        performDelay(2);
        set_sprite_tile(0, 0 + n);
        set_sprite_tile(2, 2 + n);
        set_sprite_tile(1, 1 + n);
        set_sprite_tile(3, 3 + n);
        performDelay(2);
    } else {
        //Default Animation
        set_sprite_tile(0, 0 + n);
        set_sprite_tile(2, 2 + n);
        set_sprite_tile(1, 1 + n);
        set_sprite_tile(3, 3 + n);
        performDelay(4);
    }
    frame++;
}

void setupCoins(){
    for(i = 0; i < 3; i++){
        coins[i].x = 16*randomize(5) + 48;
        coins[i].y = player.y + 120 + randomize(80);
        coins[i].h = 8;
        coins[i].w = 8;
        coins[i].health = 1;

        spriteID = 4 + i;
        //load coin's sprite
        set_sprite_tile(spriteID, 12);
        set_sprite_prop(spriteID, 1);
        coins[i].spriteID[0] = spriteID;

        move_sprite(coins[i].spriteID[0], coins[i].x, coins[i].y);
    }
}

void positionCoins(){
    for(i = 0; i < 3; i++){
        if(coins[i].health > 0){
            coins[i].y -= 4;
            if(checkCollision(&player, &coins[i]) == TRUE ){
                coins[i].health = 0;
                coinSound();
                updateCoinsCounter();
                updateScore();
            } else if(coins[i].y < 8){
                coins[i].health = 0;
            }
        } else {
            coins[i].x = 16*randomize(5) + 48;
            coins[i].y = player.y + 120;  
            coins[i].health = 1;

            //Not exactly sure if this part of the code do something or not. Sometimes it looks like it does, sometimes don't
            if(checkCollision(&coins[i], &coins[i+1]) == TRUE){
                coins[i].x = 16*randomize(5) + 48;
                coins[i].y = player.y + 120 + 16; 
            }
            for(UINT8 j = 0; j < 2; j++){
                if(checkCollision(&coins[i], &obstacles[j]) == TRUE){
                    coins[i].x = 16*randomize(5) + 48;
                    coins[i].y = player.y + 120 + 24;  
                }
            }
            //
        }
        move_sprite(coins[i].spriteID[0], coins[i].x, coins[i].y);
    }
}

void setupArrow(){
    arrow.x = 16*randomize(5) + 48;
    arrow.y = player.y + 120;
    arrow.h = 8;
    arrow.w = 6;
    arrow.health = 1;

    spriteID += 1;
    set_sprite_tile(spriteID, 14);
    set_sprite_prop(spriteID, 3);
    arrow.spriteID[0] = spriteID;

    move_sprite(arrow.spriteID[0], arrow.x, arrow.y);
}

void positionArrow(){
    if(arrow.health > 0){
        arrow.y -= 8;
        if(checkPlayerCollision(&arrow) == TRUE && hit == FALSE){
            arrow.health = 0;
            player.health--;
            hit = TRUE;
            hitSound();
        } else if(arrow.y < 8){
            arrow.health = 0;
        }
    } else {
        arrow.x = 16*randomize(5) + 48;
        arrow.y = player.y + 120;
        arrow.health = 1;
    }
    move_sprite(arrow.spriteID[0], arrow.x, arrow.y);
}

void setupObstacles(){
    spriteID += 1;
    for(i = 0; i < 2; i++){
        obstacles[i].x = 16*randomize(4) + 64;
        obstacles[i].y = player.y + 120;
        obstacles[i].w = 16;
        obstacles[i].h = 16;
        obstacles[i].health = 1;

        UINT8 n = (4*i + i);
        //load obstacles's sprites
        set_sprite_tile(spriteID + n, 15 + n);
        set_sprite_prop(spriteID + n, 3 + i);
        obstacles[i].spriteID[0] = spriteID + n;
        set_sprite_tile(spriteID + n + 1 , 16 + n);
        set_sprite_prop(spriteID + n + 1, 3 + i);
        obstacles[i].spriteID[2] = spriteID + n + 1;
        set_sprite_tile(spriteID + n + 2, 17 + n);
        set_sprite_prop(spriteID + n + 2, 3 + i);
        obstacles[i].spriteID[1] = spriteID + n + 2;
        set_sprite_tile(spriteID + n + 3, 18 + n);
        set_sprite_prop(spriteID + n + 3, 3 + i);
        obstacles[i].spriteID[3] = spriteID + n + 3;

        moveCharacter(&obstacles[i], obstacles[i].x, obstacles[i].y); 
    }   
}

void positionObstacles(){
    for(i = 0; i < 2; i++){
        if(obstacles[i].health > 0){
            obstacles[i].y -= 4 + 2*i;
            if(obstacles[i]. y < 8){
                obstacles[i].health = 0;
            }else if(checkPlayerCollision(&obstacles[i]) == TRUE && hit == FALSE){
                player.health--;
                hit = TRUE;
                hitSound();
            }
        } else {
            obstacles[i].x = 16*randomize(4) + 64;
            obstacles[i].y = player.y + 120;
            obstacles[i].health = 1;
            if(checkCollision(&obstacles[0], &obstacles[1]) == TRUE){
                obstacles[1].x = 16*randomize(4) + 64;
            } 
        }
        moveCharacter(&obstacles[i], obstacles[i].x, obstacles[i].y);
    }
}

void setupBackground(){
    set_bkg_data(37, 13, Knight_tiles);

    // switch to 2nd video memory bank
    VBK_REG = 1;

    // Set background color palette map
    set_bkg_tiles(0, 0, ForestBGWidth, ForestBGHeight, ForestBGPLN1);
    
    // switch to 1st video memory bank
    VBK_REG = 0;

    set_bkg_tiles(0, 0, ForestBGWidth, ForestBGHeight, ForestBGPLN0);
}

>>>>>>> master
void joyHandler(){
    switch (joypad())
    {
    case J_LEFT:
        player.x -= 16;
        break;
    case J_RIGHT:
        player.x += 16;
        break;
    case J_START:
    //Pause game
        game_on = FALSE;
        performDelay(10);
        break;
    default:
        player.x += 0;
        break;
    }
}

//Creates a fade out effect
void fadeOut(){
    for(i = 0; i < 4; i++){
        switch (i)
        {
        case 0:
            BGP_REG = 0xE4;
            break;
        case 1:
            BGP_REG = 0xF9;
            break;
        case 2:
            BGP_REG = 0xFE;
            break;
        case 3:
            BGP_REG = 0xFF;
            break;
        }
        performDelay(10);
    }
}

void resetBackground(){
    HIDE_WIN;
    move_bkg(0, 0); //Moves background to its default position
    HIDE_SPRITES;
}

void hitSound(){
    NR10_REG = 0x25;
    NR11_REG = 0x42;
    NR12_REG = 0x74;
    NR13_REG = 0x00;
    NR14_REG = 0xC3;
}

void coinSound(){
    NR10_REG = 0x32;
    NR11_REG = 0x43;
    NR12_REG = 0x73;
    NR13_REG = 0x01;
    NR14_REG = 0xC3;
}

////Creates a random number between 0 - n
UINT8 randomize(UINT8 n){
    seed = DIV_REG;
    initrand(seed);
    return rand() % n;
}

void gameOverScreen(){
    resetBackground();
    HIDE_WIN;
    gbt_stop();
    set_bkg_data(37, 13, Knight_tiles);
    set_bkg_tiles(0, 0, GameOverWidth, GameOverHeight, GameOver);
    game_on = FALSE;
    //Restart everything to its default values
    hit = FALSE;
    explosion= FALSE;
    player.health = 3;
    windowmap[6] = 0x01;
    windowmap[7] = 0x01;
    windowmap[8] = 0x01;
    windowmap[13] = 0x01;
    windowmap[14] = 0x01;
    setupPlayer();
    setupCoins();
    setupArrow();
    setupObstacles();
    setupBombs();
    gbt_play(song_Data, 2, 2);
    gbt_loop(1);
}