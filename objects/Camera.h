/*
 * Camera.h
 *
 *  Created on: Jan 15, 2014
 *      Author: pschmitt
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include <cmath>
#include <GL/glu.h>
#include "Position.h"

// #define ROTATION_RADIUS 20.0f;
#define ANGLE_STEPS 1.00f

namespace schmitt_co {

class Camera {
	public:
		Camera(Position pos, Position target);
		virtual ~Camera();
		void update();
		void increase_angle();
		void decrease_angle();
		friend std::ostream& operator<<(std::ostream& out, const Camera& cam);
		float angle() const;
		void set_angle(float angle);
		const Position& position() const;
		void set_position(const Position& position);
		const Position& target() const;
		void set_target(const Position& target);

	private:
		Position mPosition; // Where the camera is located at
		Position mTarget; // Where to look
		float mAngle;
		void update_position();
		void correct_angle();
};

} /* namespace schmitt_co */

#endif /* CAMERA_H_ */
