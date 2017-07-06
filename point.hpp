#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <string>
#include <cstdint>

class point
{
private:
	double x_;
	double y_;
	
public:
	point();
	point(double, double);
	double x() const;
	double y() const;
	bool operator==(const point&) const;
	bool operator!=(const point&) const;
	std::string to_string() const;
};

point::point()
{
	x_ = 0.0;
	y_ = 0.0;
}

point::point(double x, double y)
{
	this->x_ = x;
	this->y_ = y;
}

double point::x() const
{
	return x_;
}

double point::y() const
{
	return y_;
}

bool point::operator==(const point& a) const
{
	return (a.x_ == x_ && a.y_ == y_);
}

bool point::operator!=(const point& a) const
{
	return !(*this == a);
}

std::string point::to_string() const
{
	std::string ret = "(";

	ret.append(std::to_string(this->x_));
	ret.append(", ");
	ret.append(std::to_string(this->y_));
	ret.append(")");

	return ret;
}

#endif
