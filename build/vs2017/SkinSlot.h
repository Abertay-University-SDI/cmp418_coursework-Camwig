#pragma once

#include <maths/matrix33.h>
#include <math.h>
#include <string>

class SkinSlot
{
public:
	SkinSlot();
	~SkinSlot();

	std::string name_;
	std::string part_name_;
	float x_;
	float y_;
	float rot_;

	gef::Matrix33 transform_m_;

	void BuildTransform();
};

