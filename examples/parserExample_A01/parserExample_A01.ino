/** 
@file parserExample_A01.ino
@author Attilio Di Nisio

Parser usage example.

Changelog 
- parserExample_A01 20180121 ADN
- Created 20180120 ADN
*/

#include <Parser_A01.h>

Parser parser(Serial);
char* s_ptr = nullptr;
char ccmd;
int par_int;
double par_double;

void setup()
{
	Serial.begin(38400);
	Serial.println("Started");
}

void loop()
{
	parser.read();
	if (parser.isOverflow())
	{
		Serial.println("Error: command buffer overflow.");
	}
	s_ptr = parser.nextToken();
	if (s_ptr && strlen(s_ptr) == 1) {
		//Serial.print(parser._iL);Serial.print(" ");Serial.println(parser._iR);
		ccmd = s_ptr[0];
		switch (ccmd)
		{
		case 'a':
			Serial.println("Command a");
			break;
		case 'c':
			s_ptr = parser.nextToken();
			//Serial.print(parser._iL);Serial.print(" ");Serial.println(parser._iR);
			if (!s_ptr)
			{
				Serial.println("Error: Command c, missing argument.");
				break;
			}
			par_int = atoi(s_ptr);
			Serial.print("Commnand c, par1 = ");
			Serial.println(par_int);
			break;
		}
	}

	if (s_ptr && strlen(s_ptr) > 1)
	{
		if (strcmp(s_ptr, "cmd1") == 0)
		{
			s_ptr = parser.nextToken();
			//Serial.print(parser._iL);Serial.print(" ");Serial.println(parser._iR);
			if (!s_ptr)
			{
				Serial.println("Error: Command cmd1, missing argument.");
			}
			else
			{
				par_double = atof(s_ptr);
				Serial.print("Commnand cmd1, par1 = ");
				Serial.println(par_double, 3);
			}
		}
	}

}

