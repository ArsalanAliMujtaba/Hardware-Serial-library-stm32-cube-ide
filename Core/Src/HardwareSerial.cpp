/*
 * HardwareSerial.cpp
 *
 *  Created on: Sep 2, 2023
 *      Author: Arsalan Ali Mujtaba
 */

#include "HardwareSerial.hpp"
#include "main.h"
#include "string.h"

extern UART_HandleTypeDef huart_;

HardwareSerial::HardwareSerial(UART_HandleTypeDef* huart_) : huart_(huart_) {}

int HardwareSerial::begin(unsigned long int __baudrate)
{
//	huart_->Init.Instance = USART1;
	huart_->Init.BaudRate = __baudrate;
	huart_->Init.WordLength = UART_WORDLENGTH_8B;
	huart_->Init.StopBits = UART_STOPBITS_1;
	huart_->Init.Parity = UART_PARITY_NONE;
	huart_->Init.Mode = UART_MODE_TX_RX;
	huart_->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart_->Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(huart_) != HAL_OK)
	  {
		  return 0;
	  }
	return 1;
}


int HardwareSerial::println(const char *holder){
	print(holder);
	print("\r\n");
}
int HardwareSerial::println(int holder){
	print(holder);
	print("\r\n");
}
int HardwareSerial::println(double holder, int __decimal){
	print(holder,__decimal);
	print("\r\n");
}

int HardwareSerial::print(const char *holder){
	int sizeofholder=strlen(holder);
	HAL_UART_Transmit(huart_,(uint8_t*)holder,sizeofholder,2000);
}
int HardwareSerial::print(char holder){
	HAL_UART_Transmit(huart_,(uint8_t*)holder,1,1);
}
int HardwareSerial::println(char holder){
	print("\r\n");
}
int HardwareSerial::write(char* __wdata, uint16_t __length) {
    HAL_UART_Transmit(huart_, (uint8_t*)__wdata, __length, HAL_MAX_DELAY);
}
int HardwareSerial::print(int holder){
     char temp[20] = {0};
    sprintf(temp, "%d", holder);
    print(temp);
}
int HardwareSerial::print(double holder, int __decimal){
     char temp[20] = {0};
     __decimal == 2 ? sprintf(temp, "%.2f", holder) :
     __decimal == 3 ? sprintf(temp, "%.3f", holder) :
     __decimal == 4 ? sprintf(temp, "%.4f", holder) :
     __decimal == 5 ? sprintf(temp, "%.5f", holder) :
	 __decimal == 6 ? sprintf(temp, "%.6f", holder) :
	 __decimal == 7 ? sprintf(temp, "%.7f", holder) :
	 __decimal == 8 ? sprintf(temp, "%.8f", holder) :
	 __decimal == 9 ? sprintf(temp, "%.9f", holder) :
                      sprintf(temp, "%.10f", holder); // Default to 6 decimal places or adjust as needed

     print(temp);
}


int HardwareSerial::print(int __pdata,int format) {

    char temp[20] = {0};
    if(format == HEX){ sprintf(temp, "0x%02X", __pdata);}
	if(format == DEC){ sprintf(temp, "%d", __pdata);}
	if(format == BIN)
	{
		char binBuffer[9]; // Assuming 32-bit data
		binBuffer[8] = '\0'; // Null-terminate the string

		// Convert to binary string
		for (int i = 7; i >= 0; --i) {
			binBuffer[7 - i] = ((__pdata >> i) & 1) ? '1' : '0';
		}
		strcpy(temp, binBuffer);
	}
//	else sprintf(temp, "%d", __pdata);
   print(temp);
}

uint8_t HardwareSerial::available(void) {
    if (huart_->Instance->SR & 0x20) {
        return 1; // Return 1 if data is available
    }
    return 0; // Return 0 if no data is available
}

uint8_t HardwareSerial::read(void) {
		if (huart_->Instance->SR & 0x20)					// USART_SR_RXNE
		{
//					huart_->Instance->SR &= 0xBF;     // clear the flag
			return ((huart_->Instance->DR & (uint8_t)0x00FF));
		}
}

string HardwareSerial::readString(void) {
    string received_data;
    char received_char;

    while ((huart_->Instance->SR & 0x20) > 0) {
        received_char = read(); // Read a single character

        // Check for termination condition (newline character or max length)
        if (received_char == '\n' || received_data.length() >= 100) {
            break; // Stop reading
        }
        received_data += received_char; // Append the character to the string
        while ((huart_->Instance->SR & 0x20) <= 0);
//        print(received_char);
    }
    return received_data;
}

void HardwareSerial::print(const string& input_string) {
    for (char c : input_string) {
        write(&c); // Send each character to UART
    }
}
void HardwareSerial::println(const string& input_string) {
    for (char c : input_string) {
        write(&c); // Send each character to UART
    }
    println();
}

