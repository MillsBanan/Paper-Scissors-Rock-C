/* @file score.c
    @authors R. Miller, E. Oijordsbakken
    @date 9 October 2019
    @brief Score Keeping
*/
#include <string.h>
#include "button.h"
#include "led.h"
#include "tinygl.h"
#include "pacer.h"


/** Initialise player scores for both players */
void score_init(void)
{
    static uint8_t p1_score = 0;
    static uint8_t p2_score = 0;
}

/**  Increments the score of player */
void increment_score (uint8_t player)
{
    player++;
}

/** Displays the score of both the players while the button is pressed */
void display_score (void)
{
    static uint8_t init = 0;

    if (!init) {
        button_init();
        init = 1;
    }
    char buffer[4];
    itoa (p1_score, buffer, 10);
    tinygl_text (buffer);

    while (button_down_p) {
        pacer_wait();
        tinygl_update();
    }
}
