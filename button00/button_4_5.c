#include <16F877A.h>
#fuses XT, NOWDT, NOLVP, BROWNOUT, NOPUT, NOPROTECT, NODEBUG
#use delay(clock = 4M)
#use fast_io(B)
#use standard_io(D)
#define BIT_1 0x01
#define BIT_0 0x00
#define BIT_7 0x80


// IS USING OR and  LEFT DISPLACEMENT and RIGHT DISPLACEMENT

short current_d2_state = 0;
short last_d2_state = 0;

short current_d3_state = 0;
short last_d3_state = 0;

char ports_b = BIT_0;

int main(void) {
    set_tris_b(BIT_0);

    output_b(BIT_0);
    output_d(BIT_0);

    while (true)
    {
        current_d2_state = input(PIN_D2);
        current_d3_state = input(PIN_D3);

        if (current_d2_state == 1 && last_d2_state == 0)
        {
            delay_ms(10);

            if (input(PIN_D2) != 1)
            {
                continue;
            }

            if (ports_b == BIT_0)
            {
                ports_b = BIT_1;
            }
            else if (ports_b < BIT_7)
            {
                ports_b <<= BIT_1;
            }
            else
            {
                current_d2_state = 0;
                last_d2_state = 0;
                ports_b = BIT_0;
            }

            output_b(ports_b);
        }

        if (current_d3_state == 1 && last_d3_state == 0)
        {
            delay_ms(10);

            if (input(PIN_D3) != 1)
            {
                continue;
            }

            if (ports_b == BIT_0)
            {
                ports_b = BIT_7;
            }
            else if (ports_b <= BIT_7)
            {
                ports_b >>= BIT_1;
            }
            else
            {
                current_d3_state = 0;
                last_d3_state = 0;
                ports_b = BIT_0;
            }

            output_b(ports_b);
        }

        last_d2_state = current_d2_state;
        last_d3_state = current_d3_state;
    }

    return 0;
}
