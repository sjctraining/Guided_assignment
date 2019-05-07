#include <reg51.h>

sbit sw1 = P2^0;                         // Connect switch 1 to pin 2.0 of port 2
sbit sw2 = P2^7;                         // Connect switch 2 to pin 2.7 of port 2
sbit tr  = P1^0;                         // Signal fed to the base of the transistor from pin 1.0 of port 1

void main()
{
    int x;
    while(1)
    {
         if(sw1 == 0 && sw2 == 0)        // Both the switches are closed, 0% Duty Cycle
         {
              tr = 0;                    // Motor does not run
         }

         if(sw1 == 0 && sw2 == 1)        // Switch 1 is closed and switch 2 is open, 50% Duty Cycle
         { 
              tr = 1;                 
              for(x = 0; x < 600; x++);  // 600 machine cycles for ON state
              tr = 0;
              for(x = 0; x < 600; x++);  // 600 machine cycles for OFF state
         }

         if(sw1 == 1 && sw2 == 0)        // Switch 1 is open and switch 2 is closed, 75% Duty Cycle
         {
              tr = 1;
              for(x = 0; x < 900; x++);  // 900 machine cycles for ON state
              tr = 0;
              for(x = 0; x < 300; x++);  // 300 machine cycles for OFF state
         }

         if(sw1 == 1 && sw2 == 1)        // Both the switches are open, 100% Duty Cycle
         {
              tr = 1;                    // Motor runs at full speed
         }
    }
}