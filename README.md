# avr-essential
Essential functions to get started with programming an AVR ATmega MCU

## How to use?
- Create a new file like main.c
- Include essential.c
- In the main.c create the main function and start programming

## What is included in essential.c?
- USART
- SPI
- ADC
* more functionalities will be added regularly.

## Usage
### USART
- To initialize USART use `USARTinit(uint16_t ubrr_value)`. For various `ubrr_value` visit this site or check the datasheet.
- Read a character using `USARTReadChar()`.
- Write a character using `USARTWriteChar(char data)`.
- Read a string using `USARTReadString(int si)`. Where `int si` is the size of the string to read.
- Send a string using `USARTSendString(char s[])`. Where `char s[]` is the string to be sent. 
### SPI
- To initilize Master use `initMasterSPI()`.
- To initilize Slave use `initSlaveSPI()`.
- To transmit data in Master mode use `transmitMaster(unsigned char data)`.
### ADC
- To initilize ADC use `initADC()`.
- To read the input voltage use `readADC(uint8_t ch)`. Where `uint8_t ch` is the channel.
