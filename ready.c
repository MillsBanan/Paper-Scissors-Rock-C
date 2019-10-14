/** @file round.c
    @authors Evan Oijordsbakken, Ryan Miller
    @date   11 October 2019
    @brief Ready check

*/

#include "ready.h"
#include "system.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "navswitch.h"
#include "messages.h"



/** Changes the current selection of the player
    @param char* p1_ready variable to hold the choice of the player. */
static void change_selection(char* p1_ready)
{
    if (navswitch_push_event_p(NAVSWITCH_EAST) || navswitch_push_event_p(NAVSWITCH_WEST)) {
        if (*p1_ready == 'Y') {
            *p1_ready = 'N';
        } else {
            *p1_ready = 'Y';
        }
    }
}

/** Allows each player to select whether or not they are ready,
    */
void ready_task(char* stage)
{
    static char p1_ready = 'Y';
    static char p2_ready = 'N';
    static uint8_t sent_Y = 0;

    display_character(p1_ready);
    change_selection(&p1_ready);

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        ir_uart_putc(p1_ready);
        if (p1_ready == 'Y') {
            sent_Y = 1;
        } else {
            sent_Y = 0;
        }
    }
    if (ir_uart_read_ready_p()) {
        p2_ready = ir_uart_getc();
    }
    if (sent_Y && p2_ready == 'Y') {
        p2_ready = 'N';
        sent_Y = 0;
        *stage = 'P';
    }
}
