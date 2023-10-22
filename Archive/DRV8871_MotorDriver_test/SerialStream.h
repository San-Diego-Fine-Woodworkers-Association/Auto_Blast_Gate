/*
  Name:    SerialStream.h
  Created: 12/21/2021 10:32:45 PM
  Author:  Lem Davis
*/

#ifndef _SerialStream_h
#define _SerialStream_h

#include <Arduino.h>
#include <stdio.h>

#define DEC 10
#define HEX 16
#define OCT 8
#ifdef BIN // Prevent warnings if BIN is previously defined in "iotnx4.h" or similar
#undef BIN
#endif
#define BIN 2

class SerialStream
{
  private:
    int bogus;
    bool serialOn;  // Use a serial (USB) connection instead of telnet

  public:
    SerialStream(void);
    ~SerialStream();
    void enableSerial();
    void enableTelnet();
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

    void setTimeout(long);
    String readStringUntil(char);
    size_t readBytesUntil(char,char*,size_t);
    size_t readBytes(char*,size_t);
    String readString();
    int available();
};
#endif
