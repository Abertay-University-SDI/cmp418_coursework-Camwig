#pragma once

#include <maths/matrix33.h>
#include <string>
#include "maths/math_utils.h"
#include <maths/vector2.h>

class Bone
{
public:
	Bone();
	~Bone();

	Bone* parent_;
	std::string name_;
	std::string parent_name_;
	float x_;
	float y_;
	float rot_;
	gef::Matrix33 local_transform_m;
	gef::Matrix33 New_local_transform_m;
	gef::Matrix33 world_transform_m;



	void BuildLocalTransform();
	void BuildWorldTransfrom();
};

