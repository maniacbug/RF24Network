
/*
 Copyright (C) 2011 James Coliz, Jr. <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __RF24_CONFIG_H__
#define __RF24_CONFIG_H__

#ifdef ARDUINO
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif
#endif

#include <stddef.h>

#if defined(ARDUINO)

#if !defined(ENERGIA)
// Progmem is Arduino-specific
#include <avr/pgmspace.h>
#else
#define prog_char char
#define PSTR(s) (s)
#define __FlashStringHelper char
#endif

#else
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define _BV(x) (1<<(x))
typedef char const prog_char;
typedef uint16_t prog_uint16_t;
#define PSTR(x) (x)
#define strlen_P strlen
#define PROGMEM
#define pgm_read_word(p) (*(p)) 
#define min(a,b) (a<b?a:b)
#endif

#endif // __RF24_CONFIG_H__
// vim:ai:cin:sts=2 sw=2 ft=cpp
