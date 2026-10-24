#include <16F877A.h>
#fuses XT, NOWDT, NOPUT, BROWNOUT, NOLVP, NOPROTECT, NODEBUG
#use delay(clock=4M)
#use standard_io(D)
#use fast_io(B)


int main(void) {

    set_tris_b(0xFF);
    output_low(PIN_D6);

    while (true) {
        if (input(PIN_B0)) {

            output_high(PIN_D6);
            delay_ms(1500);

        } else {
            output_low(PIN_D6);
        }
    }
    
    return 0;
}
