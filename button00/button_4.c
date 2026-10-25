#include <16F877A.h>
#fuses XT, NOWDT, NOLVP, BROWNOUT, NOPUT, NOPROTECT, NODEBUG
#use delay(clock=4M)
#use fast_io(B)
#use standard_io(D)

//IS USING OR and  LEFT DISPLACEMENT

short current_d2_state = 0;
short last_d2_state = 0;

short current_d3_state = 0;
short last_d3_state = 0;

char ports_b = 0x00;

void clear_d2_context(void) {
    current_d2_state = 0;
    last_d2_state = 0;
    ports_b = 0x00;
}

void clear_d3_context(void) {
    current_d3_state = 0;
    last_d3_state = 0;
    ports_b = 0x00;
}

int main(void) {
    set_tris_b(0x00);

    output_b(0x00);
    output_d(0x00);

    while (true) {
        current_d2_state = input(PIN_D2);
        current_d3_state = input(PIN_D3);

        if (current_d2_state == 1 && last_d2_state == 0) {            
            delay_ms(10);

            if (ports_b == 0x00) {
                ports_b |= 0x01;
            } 
            else if (ports_b <= 0x80) {
                ports_b <<= 0x01;
            } 
            else {
                clear_d2_context();
                continue;
            }
            
            output_b(ports_b);
        }

        if (current_d3_state == 1 && last_d3_state == 0) {
            delay_ms(10);

            if (ports_b == 0x00) {
                ports_b |= 0x80;
            }
            else if (ports_b <= 0x80) {
                ports_b >>= 0x01;
            }
            else {
                clear_d3_context();
                continue;
            }

            output_b(ports_b);
        }
        
        last_d2_state = current_d2_state;
        last_d3_state = current_d3_state;
    }

    return 0;
}
