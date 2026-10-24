#include <16F877A.h>
#fuses XT, NOWDT, NOPUT, BROWNOUT, NOLVP, NOPROTECT, NODEBUG
#use delay(clock = 4M)
#use standard_io(D)
#use fast_io(B)


typedef struct {
    int8 data[4];
    int8 size;
} PORTS;

void set_state(PORTS ports, int8 level) {
    for (int8 p = 0; p < ports.size; p++)
    {
        if (level >= 1) {
            output_high(ports.data[p]);
        } 
        else if (level <= 0) {
            output_low(ports.data[p]);
        }
    }
}

int main(void)
{
    PORTS portsd = {{PIN_D7, PIN_D6, PIN_D5, PIN_D4}, 4};
    int8 index = 0;
    short current_btn_state = 0;
    short last_btn_state = 0;

    set_tris_b(0xFF);

    while (true)
    {
        current_btn_state = input(PIN_B0);

        if (current_btn_state == 1 && last_btn_state == 0) {
            delay_ms(10);

            if (index < portsd.size) {
                output_high(portsd.data[index]);
                index++;

            } else {
                index = 0;
                set_state(portsd, 0);
            }
        }

        last_btn_state = current_btn_state;
    }

    return 0;
}
