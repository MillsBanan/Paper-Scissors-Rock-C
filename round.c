/** @file     round.c
    @authors  Evan Oijordsbakken, Ryan Miller
    @date     15 October 2019
    @brief    Handles the playing of each round

*/


#include "round.h"
#include "system.h"
#include "ir_uart.h"
#include "navswitch.h"
#include "messages.h"


static const char g_signs[3] = {'P', 'S', 'R'}; // Valid signs
static uint8_t g_index= 0; // Current position in signs array


/** Allows the player to select a sign using the navswitch
    @param p1_sign pointer to variable that holds the sign selected by the player.  */
static void sign_select(char* p1_sign)
{
    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        if (g_index== 2) {
            g_index= 0;
        } else {
            g_index++;
        }
    } else if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        if (g_index== 0) {
            g_index= 2;
        } else {
            g_index--;
        }
    }
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        ir_uart_putc(g_signs[g_index]);
        *p1_sign = g_signs[g_index];
    }
}


/** Polls the IR reciever, assigns the recieved sign to p2_sign if valid
    @param p2_sign pointer to variable that holds the recieved sign from the other player.  */
static void sign_recieve(char* p2_sign)
{
    if (ir_uart_read_ready_p()) {
        char temp = ir_uart_getc();

        if (temp == 'R' || temp == 'S' || temp == 'P') {
            *p2_sign = temp;
        }
    }
}


/** Determines the outcome of the round
    @param p1_sign sign selected by player one
    @param p2_sign sign selected by player two
    @return outcome of the round relative to player one.  */
static char round_result(char p1_sign, char p2_sign)
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


/** Plays a round of paper scissors rock, changes the state of the game to the
    respective outcome of the round for each player - ('W', 'L', 'D').
    @param char* stage pointer to variable that holds the current stage of the game.  */
void round_task(char* stage)
{
    static char p1_sign = 0;
    static char p2_sign = 0;

    if (p1_sign == 0) {
        sign_select(&p1_sign);
    }
    if (p2_sign == 0) {
        sign_recieve(&p2_sign);
    }
    if (p1_sign != 0 && p2_sign != 0) {
        char result = round_result(p1_sign, p2_sign);
        
        p1_sign = 0;
        p2_sign = 0;
        g_index= 0;
        *stage = result;
    } else {
        display_character(g_signs[g_index]);
    }
}
