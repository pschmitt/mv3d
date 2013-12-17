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

namespace schmitt_co {

class Wind : public DrawableObject {
	friend std::ostream& operator<<(std::ostream& out,
				const Wind& wt);

	public:
		enum Strength {
			NONE = 0, WEAK, NORMAL, STRONG
		};
		enum Direction {
			NORTH = 0, SOUTH, WEST, EAST
		};
		Wind();
		virtual ~Wind();
		void draw();
		Direction direction() const {
			return mDirection;
		}

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
