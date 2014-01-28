/*
 * Color.h
 *
 *  Created on: Dec 17, 2013
 *      Author: pschmitt
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <string>
#include <ostream>

namespace schmitt_co {

class Color {
	friend std::ostream& operator<<(std::ostream& out, const Color& color);
	public:
		Color();
		Color(std::string n, float r, float g, float b);
		virtual ~Color();
		float b() const;
		void set_b(float b);
		float g() const;
		void set_g(float g);
		std::string name() const;
		void set_name(std::string name);
		float r() const;
		void set_r(float r);
		const float* color();
		const float* color(float alpha);
	private:
		std::string mName;
		float rValue;
		float gValue;
		float bValue;
};

} /* namespace schmitt_co */

#endif /* COLOR_H_ */
