#include "SkinSlot.h"
#include "maths/math_utils.h"
#include <maths/vector2.h>

SkinSlot::SkinSlot()
{

}

SkinSlot::~SkinSlot()
{

}

void SkinSlot::BuildTransform()
{
	gef::Matrix33 rotation_m;
	gef::Matrix33 translation_m;

	rotation_m.SetIdentity();
	translation_m.SetIdentity();
	transform_m_.SetIdentity();

	rotation_m.Rotate(gef::DegToRad(rot_));
	translation_m.SetTranslation(gef::Vector2(x_, y_));

	transform_m_ = rotation_m * translation_m;
}