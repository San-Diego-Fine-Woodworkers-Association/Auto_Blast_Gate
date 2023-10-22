/*
  Name:    SerialStream.cpp
  Created: 12/21/2021 10:32:45 PM
  Author:  Lem Davis
*/
#include "SerialStream.h"
#ifdef TELNET
#include <TelnetStream.h>
#endif

extern bool serialOn;

SerialStream::SerialStream()
{
  serialOn = Serial;
}

SerialStream::~SerialStream()
{
}

void SerialStream::enableSerial()
{
  serialOn = true;
}

void SerialStream::enableTelnet()
{
#ifdef TELNET
  serialOn = false;
#endif
}

void SerialStream::print(const String &argument)
{
  if (serialOn)
    Serial.print(argument);

#ifdef TELNET
  else
    TelnetStream.print(argument);
#endif
}

void SerialStream::print(const char* argument)
{
  if (serialOn)
    Serial.print(argument);
#ifdef TELNET
  else
    TelnetStream.print(argument);
#endif
}

void SerialStream::print(char argument)
{
  if (serialOn)
    Serial.print(argument);
#ifdef TELNET
  else
    TelnetStream.print(argument);
#endif
}

void SerialStream::print(unsigned char argument, int s)
{
  if (serialOn)
    Serial.print(argument, s);
#ifdef TELNET
  else
    TelnetStream.print(argument, s);
#endif
}

void SerialStream::print(int argument, int s)
{
  if (serialOn)
    Serial.print(argument, s);
#ifdef TELNET
  else
    TelnetStream.print(argument, s);
#endif
}

void SerialStream::print(unsigned int argument, int s)
{
  if (serialOn)
    Serial.print(argument, s);
#ifdef TELNET
  else
    TelnetStream.print(argument, s);
#endif
}

void SerialStream::print(long argument, int s)
{
  if (serialOn)
    Serial.print(argument, s);
#ifdef TELNET
  else
    TelnetStream.print(argument, s);
#endif
}
void SerialStream::print(unsigned long argument, int s)
{
  if (serialOn)
    Serial.print(argument, s);
#ifdef TELNET
  else
    TelnetStream.print(argument, s);
#endif
}

void SerialStream::print(double argument, int s)
{
  if (serialOn)
    Serial.print(argument, s);
#ifdef TELNET
  else
    TelnetStream.print(argument, s);
#endif
}

void SerialStream::print(const Printable& argument)
{
  if (serialOn)
    Serial.print(argument);
#ifdef TELNET
  else
    TelnetStream.print(argument);
#endif
}
//*********************************************************************
void SerialStream::println(const String &argument)
{
  if (serialOn)
    Serial.println(argument);
#ifdef TELNET
  else
    TelnetStream.println(argument);
#endif
}

void SerialStream::println(const char* argument)
{
  if (serialOn)
    Serial.println(argument);
#ifdef TELNET
  else
    TelnetStream.println(argument);
#endif
}

void SerialStream::println(char argument)
{
  if (serialOn)
    Serial.println(argument);
#ifdef TELNET
  else
    TelnetStream.println(argument);
#endif
}

void SerialStream::println(unsigned char argument, int s)
{
  if (serialOn)
    Serial.println(argument, s);
#ifdef TELNET
  else
    TelnetStream.println(argument, s);
#endif
}

void SerialStream::println(int argument, int s)
{
  if (serialOn)
    Serial.println(argument, s);
#ifdef TELNET
  else
    TelnetStream.println(argument, s);
#endif
}

void SerialStream::println(unsigned int argument, int s)
{
  if (serialOn)
    Serial.println(argument, s);
#ifdef TELNET
  else
    TelnetStream.println(argument, s);
#endif
}

void SerialStream::println(long argument, int s)
{
  if (serialOn)
    Serial.println(argument, s);
#ifdef TELNET
  else
    TelnetStream.println(argument, s);
#endif
}

void SerialStream::println(unsigned long argument, int s)
{
  if (serialOn)
    Serial.println(argument);
#ifdef TELNET
  else
    TelnetStream.println(argument);
#endif
}

void SerialStream::println(double argument, int s)
{
  if (serialOn)
    Serial.println(argument, s);
#ifdef TELNET
  else
    TelnetStream.println(argument, s);
#endif
}

void SerialStream::println(const Printable& argument)
{
  if (serialOn)
    Serial.println(argument);
#ifdef TELNET
  else
    TelnetStream.println(argument);
#endif
}

void SerialStream::println(void)
{
  if (serialOn)
    Serial.println();
#ifdef TELNET
  else
    TelnetStream.println();
#endif
}

void SerialStream::setTimeout(long timeVal)
{
  if (serialOn)
    Serial.setTimeout(timeVal);
#ifdef TELNET
  else
    TelnetStream.setTimeout(timeVal);
#endif
}

String SerialStream::readStringUntil(char term)
{
  if (serialOn) {
    return Serial.readStringUntil(term);
  }

#ifdef TELNET
  return TelnetStream.readStringUntil(term);
#else
  return "";
#endif
}

size_t SerialStream::readBytes(char* buf, size_t bufSize)
{
  if (serialOn) {
    return Serial.readBytes(buf, bufSize);
  }

#ifdef TELNET
  return TelnetStream.readBytes(buf, bufSize);
#else
  return 0;
#endif
}

size_t SerialStream::readBytesUntil(char term, char* buf, size_t bufSize)
{
  if (serialOn) {
    return Serial.readBytesUntil(term, buf, bufSize);
  }

#ifdef TELNET
  return TelnetStream.readBytesUntil(term, buf, bufSize);
#else
  return 0;
#endif
}

String SerialStream::readString()
{
  if (serialOn) {
    return Serial.readString();
  }

#ifdef TELNET
  return TelnetStream.readString();
#else
  return "";
#endif
}

int SerialStream::available()
{
  if (serialOn) {
    return Serial.available();
  }

#ifdef TELNET
  return TelnetStream.available();  
#else
  return 0;
#endif
}
