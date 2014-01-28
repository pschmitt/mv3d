/*
 * WindTurbine.h
 *
 *  Created on: Dec 13, 2013
 *      Author: pschmitt
 */

#ifndef WINDTURBINE_H_
#define WINDTURBINE_H_
#include <ostream>
#include <GL/glut.h>
#include "DrawableObject.h"
#include "Position.h"
#include "Wind.h"

namespace schmitt_co {

class WindTurbine : public DrawableObject {
	public:
		WindTurbine(const Color& color, const Position& pos, const Wind& wind);
		virtual ~WindTurbine();
		void draw();
		std::ostream& print(std::ostream& out) const;
		const Wind& wind() const;
		void set_wind(const Wind& wind);
	private:
		void drawBase(GLUquadric*& quad);
		void drawMotor(GLUquadric*& quad);
		void drawRotors(GLUquadric*& quad);
		Wind mWind;
};

} /* namespace schmitt_co */

#endif /* WINDTURBINE_H_ */
