#include "Character.h"

#include <fstream>
#include "load_texture.h"
#include "load_json.h"

Character::Character() :
	sprite_texture_(NULL),sprite_(NULL)
{
}

Character::~Character()
{
	delete sprite_texture_;
	sprite_texture_ = NULL;

	delete sprite_;
	sprite_ = NULL;
}

void Character::LoadCharacter(std::string tex_string,int type, gef::Platform* platform_)
{

	sprite_ = new gef::Sprite();

	sprite_->set_width(256.0f);
	sprite_->set_height(512.0f);

	Position.x = platform_->width() * 0.5f;
	Position.y = platform_->height() * 0.5f;

	std::string tex_string_temp = tex_string + "_tex.png";

	sprite_texture_ = CreateTextureFromPNG(tex_string_temp.c_str(), *platform_);

	sprite_->set_texture(sprite_texture_);

	Anim* new_animantion;
	new_animantion = new Anim();

	rapidjson::Document rapidjson_doc_tex;

	rapidjson::Document rapidjson_doc_ske;

	int Framerate, duration;
	new_animantion->SetupAnim(platform_, sprite_, tex_string, rapidjson_doc_tex, rapidjson_doc_ske, Framerate, duration,Position,bone_parts);

	new_animantion->FrameRate = Framerate;
	new_animantion->Duration = duration;

	animations.insert(std::make_pair(tex_string,new_animantion));
}

void Character::Update(std::string tex_string, int frame)
{
	animations.at(tex_string)->Update(frame, sprite_,Position, Transforms_for_bone_);
}

gef::Sprite* Character::Render(std::string tex_string)
{
	//return sprite_;
	animations.at(tex_string)->Render(sprite_);
	return sprite_;
}