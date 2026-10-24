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

char left_operand = 0x00;
char right_operand = 0x01;

void clear_operands(void) {
    left_operand = 0x00;
    right_operand = 0x01;
}

void clear_d2_context(void) {
    current_d2_state = 0;
    last_d2_state = 0;

    clear_operands();
}

void clear_d3_context(void) {
    current_d3_state = 0;
    last_d3_state = 0;

    clear_operands();
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

            if (left_operand == 0x00) {
                left_operand |= right_operand;
                output_b(left_operand);
            } 
            else if (right_operand == 0x09) {
                clear_d2_context();
                continue;
            } 
            else {
                output_b(left_operand << right_operand);
                right_operand++;
            }
        }

        if (current_d3_state == 1 && last_d3_state == 0) {
            delay_ms(10);

            if (left_operand == 0x00) {
                left_operand |= 0x80;
                output_b(left_operand);
            }
            else if (right_operand == 0x09) {
                clear_d3_context();
                continue;
            }
            else {
                output_b(left_operand >> right_operand);
                right_operand++;
                /*
                if (0x01 <= right_operand && right_operand <= 0x08) {
                    right_operand--;
                    output_b(left_operand >> 1);
                }
                else {
                    output_b(left_operand >> right_operand);
                    right_operand++;
                }*/
            }
        }

        last_d2_state = current_d2_state;
        last_d3_state = current_d3_state;
    }

    return 0;
}
