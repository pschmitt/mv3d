/*
 * Wind.h
 *
 *  Created on: Dec 13, 2013
 *      Author: pschmitt
 */

#ifndef WIND_H_
#define WIND_H_
#include <ostream>
#include "DrawableObject.h"
#include "../utils/ColorPalette.h"

namespace schmitt_co {

class Wind : public DrawableObject {
	public:
		enum Strength {
			NONE = 0, WEAK, NORMAL, STRONG
		};
		enum Direction {
			NORTH = 1, SOUTH, WEST, EAST, NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST
		};
		Wind(Strength strength = NONE, Direction direction = NORTH);
		virtual ~Wind();
		void draw();
		Direction direction() const {
			return mDirection;
		}

		double glDirection() const;
		void next_direction();
		void next_strength();
		void set_direction(Direction direction = NORTH) {
			mDirection = direction;
		}

		Strength strength() const {
			return mStrength;
		}

		void set_strength(Strength strength = NONE) {
			mStrength = strength;
		}

		std::ostream& print(std::ostream& out) const;
	private:
		Strength mStrength;
		Direction mDirection;
};

} /* namespace schmitt_co */

#endif /* WIND_H_ */
