/*
 * DrawableObject.h
 *
 *  Created on: Dec 14, 2013
 *      Author: pschmitt
 */

#ifndef DRAWABLE_OBJECT_H_
#define DRAWABLE_OBJECT_H_

#include <ostream>
#include "Position.h"

namespace schmitt_co {

class DrawableObject {
	public:
		DrawableObject();
		virtual ~DrawableObject();
		friend std::ostream& operator<<(std::ostream& out, const DrawableObject& obj) {
			return obj.print(out);
		}
		Position position() const {
			return mPostion;
		}
		void set_position(Position pos) {
			mPostion = pos;
		}
		virtual void draw() = 0;
	protected:
		Position mPostion;
		virtual std::ostream& print(std::ostream&) const = 0;
};

} /* namespace schmitt_co */

#endif /* DRAWABLE_OBJECT_H_ */
