/*    Code by:  Danielle DiScalfani and Steve Everett
 * 
 * 
 * 
 * File:   PGRecFirstMain1719.c
 * Author: castlesr
 *
 * Created on September 13, 2020, 12:56 PM
 */

// PIC16F1719 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection Bits (HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit cannot be cleared once it is set by software)
#pragma config ZCDDIS = ON      // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR and can be enabled with ZCDSEN bit.)
#pragma config PLLEN = OFF      // Phase Lock Loop enable (4x PLL is enabled when software sets the SPLLEN bit)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include "mcc.h"
#include "lcd.h"

#define  _XTAL_FREQ 8000000
char Artist [16];
char Title [16];
char Song [16];
void play(char nibble); //function to play notes
char prev;
void C(void);  //C function prototype
void D(void); //D function prototype
void E(void); //E function prototype
void F(void); //F function prototype
void G(void); //G function prototype
void A(void); //A function prototype
void B(void); //B function prototype
void silence(void); //silence function prototype

void main()
{
    SYSTEM_Initialize();    //Setup ports
    LCD_Initialize();       //Setup LCD  
    TRISCbits.TRISC7 = 1;   //Setup pin 7 as an input
    TRISCbits.TRISC6 = 0;   //Setup pin 6 as output
    TRISCbits.TRISC0 = 0;   //Setup pin 0 as output
    ANSELC=0;               //Digital on all pins in PORTC
    char readIn;            //byte of data read in
    GIE=0;                  //no interrupts
    BRG16=0;                //Set BAUD RATE
    BRGH=0;
    SP1BRGL= 12;
    SP1BRGH=0;
    SYNC=0;                 //asynchronous mode
    SPEN=1;                 //enable serial transmission
    TX9=0;                  //8-bit mode
    RX9=0;

    __delay_ms(12000);
    
      
         TXEN=0;         //disable transmission

    while(1)                //infinite loop
    {
        CREN=1;               //enable continuous receive
        LCD_Clear();        //clear contents on LCD and return cursor to top left
        __delay_ms(100);    //delay to allow command time to take place before writing to LCD
        
        do   
        {
        prev=readIn;         //store the readIn value as character prev
        while(!RCIF);        //While flag is not raised
        readIn=RC1REG;       //Set readIn to value from RC1REG
        }
        while((readIn !='A')||(prev !=0x3C));     //waiting for '<A'
      
            int i=0;                              //set i at 0
        do
        {
            while(!RCIF);                      //While flag is not raised
            readIn=RC1REG;                     //Set readIn to value from RC1REG
            if ((readIn!='>')&&(readIn!='<'))  //If it is not < and >
 
            Artist[i]=readIn;                 //Store readIn values in Artist Array
            i++;
            }
        
        while(readIn !=0x3C);             //While the readIn is not a <
        Artist[i]=0;                     //Truncate
        LCD_GoTo(0,0);                   //Go to top left of LCD 
        LCD_WriteString(Artist);        //Display the Artist on the top line of LCD 
        
        do   
        {
        prev=readIn;                  //store the readIn value as character prev  
        while(!RCIF);                 //While flag is not raised 
        readIn=RC1REG;                //Set readIn to value from RC1REG
        }
        while((readIn !='T')||(prev !=0x3C));     //waiting for '<T'
      
            int t=0;                               //set t at 0
        do
        {
            while(!RCIF);                        //While flag is not raised
            readIn=RC1REG;                       //Set readIn to value from RC1REG
            if ((readIn!='>')&&(readIn!='<'))    //If it is not < and >
            {    
            Title[t]=readIn;                    //Store readIn values in Artist Array
            t++;
            }
        }
        while(readIn !=0x3C);                  //While the readIn is not a '<'
        Title[t]=0;                           //Truncate
        LCD_GoTo(1,0);                       //Go To bottom left of LCD 
        LCD_WriteString(Title);             //Display the Title on bottom line of LCD
        __delay_ms(500);                    //Delay for half a second
        
       
        do   
        {
        prev=readIn;                     //store the readIn value as character prev
        while(!RCIF);                    //While flag is not raised
        readIn=RC1REG;                   //Set readIn to value from RC1REG
        }
        while((readIn !='S')||(prev !=0x3C));     //waiting for '<S'
        int s=0;                                  //set s at 0
        
        do
        {
            while(!RCIF);                          //While flag is not raised
            readIn=RC1REG;                         //Set readIn to value from RC1REG
            if ((readIn!='>')&&(readIn!='<'))
            {    
            Song[s]=readIn;                       //Store the readIn values into the Song array
            s++;
            }
        }
            while(readIn !=0x3C);
            CREN=0;                           //Do not take in any more information
            for (i=0;i<s;i++)                // for loop in which the song will be played while i<s
            {
                play(Song[i]);
            }
        while(readIn !=0x3C);               //complete the above loop while readIn is not a '<'
    }
}

void C()// frequency 1046.52 Hz
{
    for(int i=0; i<523; i++)
    {
        RC0=1;                   //RC0 High
            __delay_us(477);    //delay for half the period
        RC0=0;                 //RC0 Low
            __delay_us(468);  //slightly less to account for overhead in for loop
    }
}

void D()// frequency 1174.66 Hz
{
    for(int i=0; i<587; i++)
    {
        RC0=1;                   //RC0 High
            __delay_us(425);    //delay for half the period
        RC0=0;                 //RC0 Low
            __delay_us(416);  //slightly less to account for overhead in for loop
    }   
}

void E()// frequency 1318.51 Hz
{
    for(int i=0; i<659; i++)
    {
        RC0=1;                   //RCO High
            __delay_us(379);    //delay for half the period
        RC0=0;                 //RC0 Low
            __delay_us(370);  //slightly less to account for overhead in for loop
    }
}

void F()// frequency 1396.91 Hz
{
    for(int i=0; i<698; i++)
    {
        RC0=1;                  //RC0 High
            __delay_us(357);    //delay for half the period
        RC0=0;                //RC0 Low
            __delay_us(348);  //slightly less to account for overhead in for loop
    }
}

void G()// frequency 1567.98 Hz
{
    for(int i=0; i<783; i++)
    {
        RC0=1;                  //RC0 High
            __delay_us(318);    //delay for half the period
        RC0=0;                //RC0 Low
            __delay_us(309);  //slightly less to account for overhead in for loop
    }
}


void A()// frequency 1760.00 Hz
{
    for(int i=0; i<880; i++)
    {
        RC0=1;                  //RC0 High
            __delay_us(284);    //delay for half the period
        RC0=0;                //RC0 Low
            __delay_us(275); //slightly less to account for overhead in for loop
    }
}

void B()// frequency 1975.53 Hz
{
    for(int i=0; i<987; i++)
    {
        RC0=1;                  //RC0 High
            __delay_us(278);    //delay for half the period
        RC0=0;                //RC0 Low
            __delay_us(269); //slightly less to account for overhead in for loop
    }
}

void silence()
{
    RC0=0;
    __delay_ms(100);                    //pause for .1 of a second
}

void play(char nibble)
{
    char UN = nibble/16;            //Upper nibble of data received
    char LN= nibble % 16;          //Lower nibble of data received
    if (UN==0)                    //if UN=0 play A quarter note
        {
            A();
            silence();
        }
        else if (UN==1)         //if UN=1 play A half note
        { 
            A();
            A();
            silence();
        }
        else if (UN==2)        //if UN=2 play B quarter note
        {
            B();
            silence();
        }
        else if (UN==3)        //if UN=3 play B half note
        { 
            B();
            B();
            silence();
        }
        else if (UN==4)        //if UN=4 play C quarter note
        { 
            C();
            silence();
        }
        
        else if (UN==5)        //if UN=5 play C half note
        {
            C();
            C();
            silence();
        }
        
        else if (UN==6)        //if UN=6 play D quarter note
        {
            D();
            silence();
        }
        else if (UN==7)         //if UN=7 play D half note
        {
            D();
            D();
            silence();
        }
        else if (UN==8)         //if UN=8 play E quarter note
        { 
            E();
            silence();
        }
        else if (UN==9)         //if UN=9 play E half note
        {
            E();
            E();
            silence();
        }
        else if (UN==10)        //if UN=10 play F quarter note
        {
            F();
            silence();
        }
        else if (UN==11)        //if UN=11 play F half note
        {
            F();
            F();
            silence();
        }
        else if (UN==12)        //if UN=12 play G quarter note
        {
            G();
            silence();
        }
        else if (UN==13)        //if UN=13 play G half note
        {
            G();
            G();
            silence();
        }
        else 
            silence();          //otherwise delay
            
        
        if (LN==0)              //if LN=0 play A quarter note
        {
            A();
            silence();
        }
        else if (LN==1)         //if LN=1 play A half note
        { 
            A();
            A();
            silence();
        }
        else if (LN==2)         //if LN=2 play B quarter note
        {
            B();
            silence();
        }
        else if (LN==3)         //if LN=3 play B half note
        { 
            B();
            B();
            silence();
        }
        else if (LN==4)         //if LN=4 play C quarter note
        { 
            C();
            silence();
        }
        
        else if (LN==5)         //if LN=5 play C half note
        {
            C();
            C();
            silence();
        }
        
        else if (LN==6)         //if LN=6 play D quarter note
        {
            D();
            silence();
        }
        else if (LN==7)         //if LN=7 play D half note
        {
            D();
            D();
            silence();
        }
        else if (LN==8)        //if LN=8 play E quarter note
        { 
            E();
            silence();
        }
        else if (LN==9)        //if LN=9 play E half note
        {
            E();
            E();
            silence();
        }
        else if (LN==10)       //if LN=10 play F quarter note
        {
            F();
            silence();
        }
        else if (LN==11)       //if LN=0 play F half note
        {
            F();
            F();
            silence();
        }
        else if (LN==12)       //if LN=12 play G quarter note
        {
            G();
            silence();
        }
        else if (LN==13)        //if LN=13 play G half note
        {
            G();
            G();
            silence();
        }
        else                   // otherwise delay
            silence();
            }
      
    
    


