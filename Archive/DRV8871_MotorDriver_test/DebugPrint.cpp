/*
  Name:    DebugPrint.cpp
  Created: 12/16/2021 10:32:45 PM
  Author:  Lem Davis
*/
#include <Arduino.h>
#include "DebugPrint.h"

extern bool debugOn;

DebugPrint::DebugPrint()
{
  useTelnet = false;
}

DebugPrint::~DebugPrint()
{
}

void DebugPrint::print(const String &argument)
{
  if (debugOn)
    serialStream.print(argument);
}

void DebugPrint::print(const char* argument)
{
  if (debugOn)
    serialStream.print(argument);
}

void DebugPrint::print(char argument)
{
  if (debugOn)
    serialStream.print(argument);
}

void DebugPrint::print(unsigned char argument, int s)
{
  if (debugOn)
    serialStream.print(argument,s);
}

void DebugPrint::print(int argument, int s)
{
  if (debugOn)
    serialStream.print(argument,s);
}

void DebugPrint::print(unsigned int argument, int s)
{
  if (debugOn)
    serialStream.print(argument,s);
}

void DebugPrint::print(long argument, int s)
{
  if (debugOn)
    serialStream.print(argument,s);
}
void DebugPrint::print(unsigned long argument, int s)
{
  if (debugOn)
    serialStream.print(argument,s);
}

void DebugPrint::print(double argument, int s)
{
  if (debugOn)
    serialStream.print(argument,s);
}

void DebugPrint::print(const Printable& argument)
{
  if (debugOn)
    serialStream.print(argument);
}
//*********************************************************************
void DebugPrint::println(const String &argument)
{
  if (debugOn)
    serialStream.println(argument);
}

void DebugPrint::println(const char* argument)
{
  if (debugOn)
    serialStream.println(argument);
}

void DebugPrint::println(char argument)
{
  if (debugOn)
    serialStream.println(argument);
}

void DebugPrint::println(unsigned char argument, int s)
{
  if (debugOn)
    serialStream.println(argument,s);
}

void DebugPrint::println(int argument, int s)
{
  if (debugOn)
    serialStream.println(argument,s);
}

void DebugPrint::println(unsigned int argument, int s)
{
  if (debugOn)
    serialStream.println(argument,s);
}

void DebugPrint::println(long argument, int s)
{
  if (debugOn)
    serialStream.println(argument,s);
}

void DebugPrint::println(unsigned long argument, int s)
{
  if (debugOn)
    serialStream.println(argument);
}

void DebugPrint::println(double argument, int s)
{
  if (debugOn)
    serialStream.println(argument,s);
}

void DebugPrint::println(const Printable& argument)
{
  if (debugOn)
    serialStream.println(argument);
}

void DebugPrint::println(void)
{
  if (debugOn)
    serialStream.println();  
}
