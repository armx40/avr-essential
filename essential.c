#define MCU 328 // 328 for ATmega320 or 8 for ATmega8`
#include <avr/io.h>

// USART START //
void USARTinit(uint16_t ubrr_value){
  #if MCU == 8
    //8 for 115200 baud rate at 16MHz
    UBRRL = ubrr_value;
    UBRRH = (ubrr_value>>8);
    UCSRC=(1<<URSEL)|(3<<UCSZ0);
    UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
  #endif
  #if MCU == 328
    UBRR0L = ubrr_value;
    UBRR0H = (ubrr_value>>8);
    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
    UCSR0C = (3<<UCSZ00);
  #endif
}
char USARTReadChar(){
  #if MCU == 8
   while(!(UCSRA & (1<<RXC))){}
   return UDR;
  #endif
  #if MCU == 328
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0;
  #endif
}
void USARTWriteChar(char data){
  #if MCU == 8
   while(!(UCSRA & (1<<UDR0)));
   UDR=data;
  #endif
  #if MCU == 328
   while(!(UCSR0A & (1<<UDRE0)));
   UDR0=data;
  #endif
}
unsigned char *USARTReadString(int si){
 unsigned char s[si+1], x, i = 0;
 while(i<=(si-1)){
    unsigned char x = USARTReadChar();
    if (isalnum(x)) {
    s[i] = x;
    i++;
  }
 }
    return(s);
}
void USARTSendString(char s[]){
  int i = 0;
  while((s[i] != '\0')) {
    USARTWriteChar(s[i]);
    i++;
  }
}
// USART END //

// SPI START //
void initMasterSPI() {
  DDRB |= (1<<PB5)|(1<<PB3)|(1<<PB2);
  SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}
char transmitMaster(unsigned char data) {
  SPDR = data;
  while(!(SPSR & (1<<SPIF)));
  return SPDR;
}
void initSlaveSPI() {
  DDRB |= (1<<PB4);
  SPCR = (1<<SPE);
}
char receiveSlave() {
  while(!(SPSR & (1<<SPIF)));
  return SPDR;
}
// SPI END //

// ADC START //
void initADC() {
  ADMUX = (1<<REFS0); //AVcc
  ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}
int readADC(uint8_t ch) {
  ch &= 0b00000111;
  ADMUX = (ADMUX & 0xF8)|ch;
  ADCSRA |= (1<<ADSC);
  while(ADCSRA & (1<<ADSC));
  return (ADC);
}
// ADC END //
