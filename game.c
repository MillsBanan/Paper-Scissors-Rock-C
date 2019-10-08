#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 20

void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/* Displays the welcome message for the game, including instructions
 * Then waits for a connection to a second player.
*/
void startup_task(void)
{
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    pacer_init(PACER_RATE);
    

    tinygl_text("Paper Scissors Rock, best of 3. Push navswitch to continue.");
    

    while (1) {
        pacer_wait();
        tinygl_update();
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            break;
        }
    }
    
    char character = 'Y';
    display_character(character);
    pacer_init (PACER_RATE);
    
    while (1) {
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
        display_character(character);
    }
}

int main (void)
{
    system_init();
    startup_task();

    return 0;
}
