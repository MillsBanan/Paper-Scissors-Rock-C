/** @file round.c
    @authors Evan Oijordsbakken, Ryan Miller
    @date   10 October 2019
    @brief Handles the playing of each round

*/

#include "round.h"
#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "messages.h"

/** Valid signs: P = paper, R = rock, and S = Scissors. */
const char signs[3] = {'P', 'S', 'R'};

/** Plays a round of paper scissors rock
    @param &stage the current stage of the game.  */
void round_task(char* stage)
{
    static char p1_sign = 0;
    static char p2_sign = 0;
    static uint8_t index = 0;

    if (p1_sign == 0) {
        sign_select(&p1_sign, &index);
    }
    if (p2_sign == 0) {
        sign_recieve(&p2_sign);
    }
    if (p1_sign != 0 && p2_sign != 0) {
        char result = round_result(p1_sign, p2_sign);
        p1_sign = 0;
        p2_sign = 0;
        index = 0;
        *stage = result;
    } else {
        display_character(signs[index]);
    }
}

/** Allows the player to select a sign using the navswitch
    @param p1_sign variable to hold the sign selected by the player.  */
void sign_select(char* p1_sign, uint8_t &index)
{

    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        if (*index == 2) {
            *index = 0;
        } else {
            *index++;
        }
    } else if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        if (*index == 0) {
            *index = 2;
        } else {
            *index--;
        }
    }
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        ir_uart_putc(signs[*index]);
        *p1_sign = signs[*index];
    }
}


/** Polls the IR reciever, assigns the recieved sign to p2_sign if valid
    @param p2_sign variable to hold the recieved sign from the other player.  */
void sign_recieve(char* p2_sign)
{
    if (ir_uart_read_ready_p()) {
        *p2_sign = ir_uart_getc();
        /*
        char temp = ir_uart_getc();
        if (temp == 'R' || temp == 'S' || temp == 'P') {
            *p2_sign = temp;
        } */
    }
}


/** Determines the outcome of the round
    @param p1_sign sign selected by player one
    @param p2_sign sign selected by player two
    @return outcome of the round relative to player one.  */
char round_result(char p1_sign, char p2_sign)
{
    char result;

    if (p1_sign == p2_sign) {
        result = 'D'; // Draw
    } else if (p1_sign == 'P' && p2_sign == 'R') {
        result = 'W'; // Win
    } else if (p1_sign == 'R' && p2_sign == 'S') {
        result = 'W';
    } else if (p1_sign == 'S' && p2_sign == 'P') {
        result = 'W';
    } else {
        result = 'L'; // Loss
    }
    return result;
}
