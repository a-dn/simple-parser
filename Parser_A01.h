/** 
@file Parser_A01.h
@author Attilio Di Nisio

Simple parser.
Alpha release.

Changelog 
- Parser_A01 20180121 ADN
- Created 20180120 ADN

*/

#ifndef Parser_A01
#define Parser_A01

#include "Arduino.h"
#include "Stream.h"

class Parser
{
public:
	Parser(Stream &serial);
	void read();
	bool isOverflow();
	char* nextToken();

private:
	Stream*  _serial;
	char _buf[64];
	uint_fast8_t _ind;
	uint_fast8_t _iL;
	uint_fast8_t _iR;
	bool _overflow;
	bool _finished; //false = accumulating characters; true = finished, hence process buffer
};

#endif