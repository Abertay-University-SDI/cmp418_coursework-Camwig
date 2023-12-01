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

	gef::Sprite* Render();

	std::map<std::string, Anim*> animations;

	gef::Sprite* sprite_;
private:
	Type Chars_type;
	gef::Texture* sprite_texture_;

	gef::Vector2 Position;
};

