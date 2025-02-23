#include "Arduboy2.h"
#include "ab_printer.h"

AbPrinter::AbPrinter(Arduboy2 &ab)
{
	arduboy = &ab;

	// font rendering
	cursor_x = 0;
	cursor_y = 0;
	size = 1;
}

// seths hack, for compatibility with 1.1
AbPrinter::AbPrinter()
{
	arduboy = NULL;

	// font rendering
	cursor_x = 0;
	cursor_y = 0;
	size = 1;
}

size_t AbPrinter::write(uint8_t c)
{
	if (c == '\n')
	{
		cursor_y += size * 8;
		cursor_x = 0;
	}
	else if (c == '\r')
	{
		// skip em
	}
	else
	{
		// LogMsg("Draw char: %d, %d, %d, size: %d", cursor_x, cursor_y, c, size);
		arduboy->drawChar(cursor_x, cursor_y, c, 1, 0, size);
		cursor_x += size * 6;
		if (wrap && (cursor_x > (WIDTH - size * 6)))
		{
			// calling ourselves recursively for 'newline' is
			// 12 bytes smaller than doing the same math here
			write('\n');
		}
	}
	return 1;
}

void AbPrinter::setCursor(int16_t x, int8_t y)
{
	cursor_x = x;
	cursor_y = y;
}

void AbPrinter::setSize(uint8_t s)
{
	// size must always be 1 or higher
	size = max(1, s);
}

void AbPrinter::setWrap(boolean w)
{
	wrap = w;
}
