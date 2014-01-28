/*
 * ColorPalette.h
 *
 *  Created on: Dec 17, 2013
 *      Author: pschmitt
 */

#ifndef COLORPALETTE_H_
#define COLORPALETTE_H_

#include <iostream>
#include "../objects/Color.h"

namespace schmitt_co {

// static float WHITE[]  = { 1.0F, 1.0F, 1.0F, 1.0F };
// static float BLACK[]  = { 0.0F, 0.0F, 0.0F, 1.0F };
// static float RED[]    = { 1.0F, 0.0F, 0.0F, 1.0F };
// static float GREEN[]  = { 0.0F, 1.0F, 0.0F, 1.0F };
// static float BLUE[]   = { 0.0F, 0.0F, 1.0F, 1.0F };
// static float YELLOW[] = { 1.0F, 1.0F, 0.0F, 1.0F };

class ColorPalette {
	public:
		ColorPalette();
		virtual ~ColorPalette();
		static Color black()  { return Color("black" , 0.0F, 0.0F, 0.0F); };
		static Color white()  { return Color("white" , 1.0F, 1.0F, 1.0F); };
		static Color red()    { return Color("red"   , 1.0F, 0.0F, 0.0F); };
		static Color green()  { return Color("green" , 0.0F, 1.0F, 0.0F); };
		static Color blue()   { return Color("blue"  , 0.0F, 0.0F, 1.0F); };
		static Color yellow() { return Color("yellow", 1.0F, 1.0F, 0.0F); };
		static Color orange() { return Color("orange", 1.0F, 0.5F, 0.0F); };
};

} /* namespace schmitt_co */

#endif /* COLORPALETTE_H_ */
