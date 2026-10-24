#include <16F877A.h>
#fuses NOWDT, XT, NOPUT, BROWNOUT, NOLVP, NOPROTECT, NODEBUG
#use delay(clock=4M)
#use standard_io(D)
#use fast_io(B)

int main(void) {
    unsigned char ports_b = 0;

    set_tris_b(0x00);
    output_b(0x00);

    output_low(PIN_D0);

    short current_btn_state = 0;
    short last_btn_state = 0;

    while (true) {
        current_btn_state = input(PIN_D0);

        if (current_btn_state == 1 && last_btn_state == 0) {
            delay_ms(10);

            ports_b++;
            output_b(ports_b);
        }

        last_btn_state = current_btn_state;
    }
}