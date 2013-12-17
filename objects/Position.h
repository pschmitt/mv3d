/*
 * Position.h
 *
 *  Created on: Dec 14, 2013
 *      Author: pschmitt
 */

#ifndef POSITION_H_
#define POSITION_H_

#include <ostream>
#include <GL/gl.h>

namespace schmitt_co {

class Position {
	friend std::ostream& operator<<(std::ostream& out, const Position& wt);
	public:
		Position(GLdouble x = 0, GLdouble y = 0, GLdouble z = 0);
		virtual ~Position();

		GLdouble x() const {
			return xPos;
		}
		
		void set_x(GLdouble x = 0) {
			this->xPos = x;
		}
		
		GLdouble y() const {
			return yPos;
		}
		
		void set_y(GLdouble y = 0) {
			this->yPos = y;
		}
		
		GLdouble z() const {
			return zPos;
		}
		
		void set_z(GLdouble z = 0) {
			this->zPos = z;
		}

	private:
		GLdouble xPos;
		GLdouble yPos;
		GLdouble zPos;
};

} /* namespace schmitt_co */

#endif /* POSITION_H_ */
