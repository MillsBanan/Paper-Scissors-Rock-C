/* @file score.c
    @authors R. Miller, E. Oijordsbakken
    @date 9 October 2019
    @brief Score Keeping
*/

#ifndef SCORE_H
#define SCORE_H

uint8_t p1_score;
uint8_t p2_score;

/** Initialise player scores for both players */
void score_init(void);

/**  Increments the score of player */
void increment_score (uint8_t player);

/** Displays the score of both the players while the button is pressed */
void display_score (void);

#endif /* SCORE_H */
