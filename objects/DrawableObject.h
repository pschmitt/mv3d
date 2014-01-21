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
#include "Color.h"

namespace schmitt_co {

class DrawableObject {
	public:
		DrawableObject();
		virtual ~DrawableObject();
		friend std::ostream& operator<<(std::ostream& out, const DrawableObject& obj) {
			return obj.print(out);
		}
		Position position() const;
		void set_position(Position pos);
		void set_color(Color color);
	    Color color() const;
		virtual void draw() = 0;
		float size() const;
		void set_size(float size);
	protected:
		float mSize;
		Position mPostion;
		Color mColor;
		virtual std::ostream& print(std::ostream&) const = 0;

};

} /* namespace schmitt_co */

#endif /* DRAWABLE_OBJECT_H_ */
