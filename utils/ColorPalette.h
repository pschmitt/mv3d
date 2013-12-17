/*
 * ColorPalette.h
 *
 *  Created on: Dec 17, 2013
 *      Author: pschmitt
 */

#ifndef COLORPALETTE_H_
#define COLORPALETTE_H_

namespace schmitt_co {

static float WHITE[]  = { 1.0F, 1.0F, 1.0F, 1.0F };
static float BLACK[]  = { 0.0F, 0.0F, 0.0F, 1.0F };
static float RED[]    = { 1.0F, 0.0F, 0.0F, 1.0F };
static float GREEN[]  = { 0.0F, 1.0F, 0.0F, 1.0F };
static float BLUE[]   = { 0.0F, 0.0F, 1.0F, 1.0F };
static float YELLOW[] = { 1.0F, 1.0F, 0.0F, 1.0F };

class ColorPalette {
	public:
		ColorPalette();
		virtual ~ColorPalette();
		static float* black()  { return BLACK;  };
		static float* white()  { return WHITE;  };
		static float* red()    { return RED;    };
		static float* green()  { return GREEN;  };
		static float* blue()   { return BLUE;   };
		static float* yellow() { return YELLOW; };
};

} /* namespace schmitt_co */

#endif /* COLORPALETTE_H_ */
