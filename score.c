/* @file score.c
    @authors R. Miller, E. Oijordsbakken
    @date 9 October 2019
    @brief Score Keeping
*/
#include "button.h"
#include "tinygl.h"
#include "pacer.h"
#include "uint8toa.h"
#include "score.h"


/** Initialise player scores for both players */
void score_init(void)
{
    p1_score = 0;
    p2_score = 0;
}

/**  Increments the score of player */
void increment_score (uint8_t player)
{
    player++;
}

/** Displays the score of both the players */
void display_score (void)
{
    //Couldn't get any of this to work gg
    int cont = 0;
    char* buffer[4];
    uint8toa (p1_score, buffer, 0);
    tinygl_text (buffer);

    while (!cont) {
        pacer_wait();
        tinygl_update();
    }
}
