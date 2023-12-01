#include "Bone.h"
#include <iostream>

Bone::Bone()
{

}

Bone::~Bone()
{

}

void Bone::BuildLocalTransform()
{
	gef::Matrix33 rotation_m;
	gef::Matrix33 translation_m;

	rotation_m.SetIdentity();
	translation_m.SetIdentity();
	local_transform_m.SetIdentity();

	rotation_m.Rotate(gef::DegToRad(rot_));
	translation_m.SetTranslation(gef::Vector2(x_, y_));

	local_transform_m = rotation_m * translation_m;
}
