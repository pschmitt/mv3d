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
		WindTurbine(Color &color, Position &pos);
		virtual ~WindTurbine();
		void draw();
		std::ostream& print(std::ostream& out) const;
};

} /* namespace schmitt_co */

#endif /* WINDTURBINE_H_ */
