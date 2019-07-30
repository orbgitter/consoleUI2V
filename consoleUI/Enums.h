#ifndef ENUMS_H
#define ENUMS_H


typedef enum BorderType { None, Dotted, Solid, Double } BorderType;

typedef enum Color {
	Black = 0x0000, Blue = 0x0001, Green = 0x0002, Red = 0x0004, Cyan = 0x0003, Purple = 0x0005, Orange = 0x0006, White = 0x0007
	, BrightBlue = 0x0009, BrightGreen = 0x000A, BrightRed = 0x000B, BrightCyan = 0x000C, BrightPurple = 0x000D, BrightOrange = 0x000E, BrightWhite = 0x000F
} Color;

#endif