/*
 * HardwareSerial.hpp
 *
 *  Created on: Sep 2, 2023
 *      Author: Arsalan Ali Mujtaba
 */

#ifndef INC_HARDWARESERIAL_HPP_
#define INC_HARDWARESERIAL_HPP_

#include "stm32f4xx_hal.h"
#include"iostream"
using namespace std;

class HardwareSerial{
public:



	enum PrintFormat { HEX, DEC, BIN };

	HardwareSerial(UART_HandleTypeDef* huart);
    int begin(unsigned long int__baudrate);

    int println(const char* str);
    int println(int num);
    int println(double num, int __decimal= 2);
    int println(char holder = '\n');

	int print(int __pdata, int format);
    int write(char* __wdata, uint16_t __length=1);
    int print(const char* str);
    int print(char holder = '\0');
    int print(int num);
    int print(double num, int __decimal=2);

    uint8_t available(void);

	uint8_t read(void);
	string readString(void);
	void print(const string& input_string);
	void println(const string& input_string);

private:
    UART_HandleTypeDef* huart_;
};

#endif /* INC_HARDWARESERIAL_HPP_ */
