#pragma once

#include "Anim.h"
#include <maths/vector2.h>

enum Type
{
	Sheet = 0,
	Skeletal = 1
};


class Character
{
	//Load sprite - WORKING ON IT!
	//Update positions
	//render
public:
	Character();
	~Character();

	void LoadCharacter(std::string, int type,gef::Platform*);

	void Update(std::string tex_string, int frame);

	gef::Sprite* Render(std::string tex_string,std::string part);

	std::map<std::string, Anim*> animations;

	gef::Sprite* sprite_;

	std::vector<std::string> bone_parts;
	std::map<std::string, gef::Matrix33> Transforms_for_bone_;
	gef::Matrix33 Transform;

private:
	Type Chars_type;
	gef::Texture* sprite_texture_;

	gef::Vector2 Position;
};

