/** @file   game.c
    @authors Evan Oijordsbakken, Ryan Miller
    @date   09 October 2019

    This file runs the main program of the PSR game
    for the UCFK for Assignment
*/

 #include "system.h"
 #include "pacer.h"
 #include "ir_uart.h"
 #include "tinygl.h"
 #include "navswitch.h"
 #include "../fonts/font5x7_1.h"

#define PACER_RATE 800
#define MESSAGE_RATE 25

void start_screen(void)
{
    tinygl_text("Paper Scissors Rock: First to 2");

    while (1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            break;
        }
    }
}


void startup_init(void)
{
    system_init();
    ir_uart_init ();
    pacer_init(PACER_RATE);
    screen_init(PACER_RATE, MESSAGE_RATE);
    tinygl_init (pacer_rate);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (msg_rate);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

void ready_task(char* stage)
{

}

int main(void)
{
    startup_init();
    start_screen();

    char stage = 'R';

    while (1) {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        switch (stage) {
            case 'R' : // Ready check
                ready_task(&stage);
                break;
        }
    }
}
