/*
 * Light.h
 *
 *  Created on: Jan 29, 2014
 *      Author: pschmitt
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "DrawableObject.h"
#include "Position.h"

namespace schmitt_co {

class Light {
	public:
		Light(unsigned int lightId, Position pos);
		virtual ~Light();
		void lightUp();
		void toggle();
		void enable();
		void disable();
		bool enabled() const;
		unsigned int lightid() const;
		void set_lightid(unsigned int lightId);
		const Position& pos() const;
		void set_pos(const Position& pos);
		friend std::ostream& operator<<(std::ostream& out, const Light& obj);
	private:
		bool mEnabled;
		Position mPos;
		unsigned int mLightId;
};

} /* namespace schmitt_co */

#endif /* LIGHT_H_ */
