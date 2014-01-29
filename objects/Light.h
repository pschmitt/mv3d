/*
 * Light.h
 *
 *  Created on: Jan 29, 2014
 *      Author: pschmitt
 */

#ifndef LIGHT_H_
#define LIGHT_H_
#include "DrawableObject.h"

namespace schmitt_co {

class Light : DrawableObject {
	public:
		Light();
		virtual ~Light();
		void draw();
		std::ostream& print(std::ostream& out) const;
};

} /* namespace schmitt_co */

#endif /* LIGHT_H_ */
