/*
  Name:    DebugPrint.h
  Created: 12/16/2021 10:32:45 PM
  Author:  Lem Davis
*/

#ifndef _Debug_Print_h
#define _Debug_Print_h

#include <Arduino.h>
#include "SerialStream.h"

#define DEC 10
#define HEX 16
#define OCT 8
#ifdef BIN // Prevent warnings if BIN is previously defined in "iotnx4.h" or similar
#undef BIN
#endif
#define BIN 2

class DebugPrint
{
  private:
    int bogus;
    bool useTelnet;  // Use a telnet network connection instead of serial (USB)
    SerialStream serialStream;

  public:
    DebugPrint(void);
    ~DebugPrint();
    void print(const String &);
    void print(const char*);
    void print(char);
    void print(unsigned char, int = DEC);
    void print(int, int = DEC);
    void print(unsigned int, int = DEC);
    void print(long, int = DEC);
    void print(unsigned long, int = DEC);
    void print(double, int = 2);
    void print(const Printable&);

    void println(const String &s);
    void println(const char*);
    void println(char);
    void println(unsigned char, int = DEC);
    void println(int, int = DEC);
    void println(unsigned int, int = DEC);
    void println(long, int = DEC);
    void println(unsigned long, int = DEC);
    void println(double, int = 2);
    void println(const Printable&);
    void println(void);
};
#endif
