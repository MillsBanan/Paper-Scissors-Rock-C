#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 20

/* Commonly used helper functions */

void display_character(char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text(buffer);
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

        pacer_wait();
        tinygl_update();
        navswitch_update();

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

        if (ir_uart_read_ready_p()) {
            player2_char = ir_uart_getc();
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

char sign_select(void)
{
    uint8_t signs_index = 0;
    uint8_t cont = 0;
    char signs[3] = {'P', 'S', 'R'};

    display_character(signs[signs_index]);

    while (!cont) {

        pacer_wait();
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p(NAVSWITCH_EAST)) {
            if (signs_index == 2) {
                signs_index = 0;
            } else {
                signs_index++;
            }
        } else if (navswitch_push_event_p(NAVSWITCH_WEST)) {
            if (signs_index == 0) {
                signs_index = 2;
            } else {
                signs_index--;
            }
        }

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            cont = 1;
        }

        display_character(signs[signs_index]);
    }
    return signs[signs_index];
}
char round_result (char p1_sign, char p2_sign)
{
    if (p1_sign == p2_sign) {
        return 'D';
    } else if (p1_sign == 'P' && p2_sign == 'R') {
        return 'W';
    } else if (p1_sign == 'R' && p2_sign == 'S') {
        return 'W';
    } else if (p1_sign == 'S' && p2_sign == 'P') {
        return 'W';
    } else {
        return 'L';
    }
}
void round_task(void)
{
    char p1_sign = sign_select();
    char p2_sign = 'P';

    uint8_t cont = 0;
    uint8_t sent = 0;
    uint8_t recvd = 0;

    while (!cont) {
        pacer_wait();
        if (!sent) {
            ir_uart_putc(p1_sign);
            sent = 1;
        }
        if (ir_uart_read_ready_p()) {
            p2_sign = ir_uart_getc();
            recvd = 1;
        }
        if (sent && recvd) {
            cont = 1;
        }
    }
    char result = round_result(p1_sign, p2_sign);
    display_character(result);

    while(1) {
        pacer_wait();
        tinygl_update();
    }
}

/** Displays the welcome message for the game, including instructions
    Then waits for a connection to a second player. */
void startup_task(void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    pacer_init(PACER_RATE);
    ir_uart_init();
    startup_screen();
}

int main (void)
{
    system_init();
    startup_task();
    ready_screen();
    round_task();
    while (1) {
        pacer_wait();
        tinygl_clear();

    }

    return 0;
}
