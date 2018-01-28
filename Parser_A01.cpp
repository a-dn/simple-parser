/** 
@file Parser_A01.cpp
@author Attilio Di Nisio

Simple parser.
*/

#include "Parser_A01.h"

Parser::Parser(Stream &serial)
{
	_serial = &serial;
	_iL = 0;
	_iR = 0;
	_overflow = false;
	_finished = false;
	_ind = 0;
}

// Delete last completely received command from buffer and aggregate new charcaters of new command.
// When buffer overflow occurs, '\0' is written to first element of buffer.
void Parser::read()
{
	int in_char;
	if (_finished) {
		_overflow = false;
		_finished = false;
		_ind = 0;
		_iL = 0;
		_iR = 0;
	}

	while ((in_char = _serial->read()) >= 0)
	{
		//digitalWrite(ledPin, HIGH);delay(500);digitalWrite(ledPin, LOW);delay(500);
		if (!_overflow)
		{
			if (_ind < (sizeof(_buf)/sizeof(*_buf))-1 )
			{
				_buf[_ind++] = in_char;
			}
			else
			{
				_overflow = true;
				_ind = 0;
			}
		}
		if (in_char == '\n')
		{
			_buf[_ind] = '\0';
			_finished = true;
		}
	}
}

bool Parser::isOverflow()
{
	return (_finished & (_overflow == true));

}

// Set passed pointer to null terminated token string in buffer.
// String doesn't include trailing and leading spaces and /n.
// Return null pointer if command is not complete in receive buffer or no token available.
// Since an overlowed buffer contains just '\0', a null pointer is returned in that case.
char * Parser::nextToken()
{
	if (!_finished) {
		return(nullptr);
	}
	_iL = _iR;
	if (_iL >= _ind) _iL = _ind;
	while (_iL < _ind)
	{
		if (_buf[_iL] != ' ') break;
		_iL++;
	}
	_iR = _iL;
	while (_iR < _ind) 
	{
		if (_buf[_iR] == ' ' || _buf[_iR] == '\n')
		{
			_buf[_iR] = '\0';
			break;
		}
		_iR++;
	}
	_iR++;
	if (_iL == _ind || _iL+1 == _iR)
	{
		return(nullptr);
	}
	else
	{
		return(&_buf[_iL]);
	}
}