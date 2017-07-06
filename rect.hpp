#ifndef _RECT_HPP_
#define _RECT_HPP_

#include <string>
#include <cstdint>

class rect
{
private:
	double x0_;
	double x1_;
	double y0_;
	double y1_;
	
public:
	rect() : 
		x0_(0.0), x1_(0.0), y0_(0.0), y1_(0.0) {};
	rect(double x0, double x1, double y0, double y1) :
		x0_(x0), x1_(x1), y0_(y0), y1_(y1) {};
	bool contains(double, double) const;
	int32_t contains_x(double) const;
	int32_t contains_y(double) const;
};

bool rect::contains(double x, double y) const
{
	return (x >= x0_ && x <= x1_ && y >= y0_ && y <= y1_);
}

int32_t rect::contains_x(double x) const
{
	if (x >= x0_ && x <= x1_) {
		return 0;
	} else if (x < x0_) {
		return -1;
	} else {
		return 1;
	}
}

int32_t rect::contains_y(double y) const
{
	if (y >= y0_ && y <= y1_) {
		return 0;
	} else if (y < y0_) {
		return -1;
	} else {
		return 1;
	}
}

#endif
