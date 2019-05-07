#include <reg51.h>

sbit led = P1^0;                 // LED  is connected to pin 1.0 of Port 1

void uart_msg(unsigned char*c);  // Function to Transmit String from 8051 thru serial port
void uart_tx(unsigned char);     // Function to Transmit character from 8051 thru serial port
char uart_rx();                  // Function to receive character from 8051 thru serial port

void main()
{
    char inData;
    TMOD = 0x20;                 // Timer 1 in Mode 2 Auto Reload
    TH1  = 0xFD;                 // Load Baud Rate 9600 to Timer Register
    SCON = 0x50;                 // Serial Mode 1 REN enabled 
    TR1  = 1;                    // Start Timer 1
    
    P1  = 0;                     // Clear port initially 
    led = 0;                     // Initially LED turn OFF 
    
    while(1)
    {
        inData = uart_rx();      // Receive Character Serially 
        if(inData == '1')
        {
            led = 1;             // Turn ON LED 
            uart_msg("LED_ON");  // Send status of LED
        }
        else if(inData == '2')
        {
            led = 0;             // Turn OFF LED 
            uart_msg("LED_OFF"); // Send status of LED
        }
        else
        {
            uart_msg("Enter valid Input");
        }
    
    }
}

char uart_rx()
{
    while (RI==0);              // Wait until Reception to complete
    RI = 0;                     // Clear Receiver Interrupt Flag
    return(SBUF);
}

void uart_msg(unsigned char *c)
{
    while(*c)                   // Iterate through the String until it Reaches End of String ('\0')
    {
        uart_tx(*c++);
    }
}

void uart_tx(unsigned char serialdata)
{
    SBUF = serialdata;          // Load Data to Serial Buffer Register
    while(!TI);                 // Wait Until Transmission To Complete
    TI   = 0;                   // Clear Transmission Interrupt Flag
}
