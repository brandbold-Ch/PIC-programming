#include <16f877a.h>
#fuses XT, NOWDT, NOPUT, NOLVP, NOPROTECT, BROWNOUT
#use delay(clock=4M)
//#use standard_io(B)
#use fast_io(B)
//#use fixed_io(b_outputs=PIN_B0)


void main() {

   int8 counter = 0;
   int16 delay = 100;

   set_tris_b(0);
   output_b(0);

   while(true) {

      if (counter == 10) {
         counter = 0;
         delay += 100;

         if (delay == 1100) {
            delay = 100;
         }
         
      }

      output_high(PIN_B0);
      delay_ms(delay);
      output_low(PIN_B0);
      delay_ms(delay);

      counter++;
   }
}
