#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 20

void startup(void)
{
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    tinygl_text("P,S,R. press nav to begin ");

    pacer_init (PACER_RATE);

    while (1) {

        pacer_wait();

        tinygl_update();
    }
}

int main (void)
{
    system_init();
    startup();

    return 0;
}
