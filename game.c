#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "score.h"

#define PACER_RATE 500
#define MESSAGE_RATE 20

/* Commonly used helper functions */
void ir_comms (char input)
{
    if (input == 'Y' || input == 'N') {
        ready_check()
    }
}

void display_character(char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/** Helper functions for startup_task() */

/** Displays game title and awaits player interaction */
void startup_screen(void)
{
    int cont = 0;

    tinygl_text("Paper Scissors Rock, best of 3. Push navswitch to continue.");


    while (!cont) {

        pacer_wait();
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            cont = 1;
        }
    }
}

/** Displays the player ready check screen.
  Transmits a Y or N over IR to the other player if ready or not, respectively.
  Returns 1 if both players are ready. */
int ready_screen(void)
{
    uint8_t cont = 0;
    char character = 'Y';
    char player2_char = 'N';
    int rdy1 = 0;
    int rdy2 = 0;

    display_character(character);

    while (!cont) {

        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_EAST) || navswitch_push_event_p (NAVSWITCH_WEST)) {
            if (character == 'Y') {
                character = 'N';
            } else {
                character = 'Y';
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            ir_uart_putc(character);
            if (character == 'Y') {
                rdy1 = 1;
            } else {
                rdy1 = 0;
            }
        }

        if (ir_uart_read_ready_p ()) {
            player2_char = ir_uart_getc ();
            if (player2_char == 'Y') {
                rdy2 = 1;
            } else {
                rdy2 = 0;
            }
        }

        if (rdy1 && rdy2) {
            return 1;
        }

        display_character(character);
    }
    return 0;
}

void round_task (void)
{
    /* TODO - select P, S or R */

    /*TODO - Communicate choice to other device and await response */

}

/** Displays the welcome message for the game, including instructions
    Then waits for a connection to a second player. */
void startup_task(void)
{
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    pacer_init(PACER_RATE);
    ir_uart_init ();
    startup_screen();
}

int main (void)
{
    system_init();
    startup_task();

    while (1) {
        /* Paced loop here for game operation? */
    }

    tinygl_clear();
    tinygl_update ();

    return 0;
}
