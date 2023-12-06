#pragma once
#include <animation/skeleton.h>
#include <animation/animation.h>
#include <graphics/primitive.h>
#include <graphics/scene.h>

class Animation
{
public:
	Animation();
	~Animation();

	gef::Animation* LoadAnimation(const char* anim_scene_filename, const char* anim_name, gef::Platform&);

	//Can use maps to store multiple of these
	const char* AnimToLoad = "ybot/ybot@walking_inplace.scn";
	const char* AnimToLoad2 = "ybot/ybot@running_inplace.scn";
	const char* AnimToLoad3 = "ybot/ybot@idle.scn";
};

