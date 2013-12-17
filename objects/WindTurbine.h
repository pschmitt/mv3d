/*
 * WindTurbine.h
 *
 *  Created on: Dec 13, 2013
 *      Author: pschmitt
 */

#ifndef WINDTURBINE_H_
#define WINDTURBINE_H_
#include <ostream>
#include "DrawableObject.h"
#include "Position.h"

namespace schmitt_co {

class WindTurbine : public DrawableObject {
	public:
		enum Color {
			WHITE = 0, BLACK, RED, BLUE, GREEN, YELLOW
		};
		WindTurbine(Color color, Position &pos);
		virtual ~WindTurbine();
		Color color() const {
			return mColor;
		}
		void set_color(Color color) {
			mColor = color;
		}
		void draw();
		std::ostream& print(std::ostream& out) const;
	private:
		Color mColor;
};


} /* namespace schmitt_co */

#endif /* WINDTURBINE_H_ */
