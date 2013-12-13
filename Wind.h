/*
 * Wind.h
 *
 *  Created on: Dec 13, 2013
 *      Author: pschmitt
 */

#ifndef WIND_H_
#define WIND_H_

namespace schmitt_co {

class Wind {
public:
	enum strength { NONE = 0, WEAK = 1, NORMAL = 2, STRONG = 3};
	enum direction { NORTH = 0, SOUTH = 1, WEST = 2 , EAST = 3 };
	Wind();
	virtual ~Wind();

	direction getDirection() const {
		return mDirection;
	}

	void setDirection(direction direction = NORTH) {
		mDirection = direction;
	}

	strength getStrength() const {
		return mStrength;
	}

	void setStrength(strength strength = NONE) {
		mStrength = strength;
	}

private:
	strength mStrength;
	direction mDirection;
};

} /* namespace schmitt_co */

#endif /* WIND_H_ */
