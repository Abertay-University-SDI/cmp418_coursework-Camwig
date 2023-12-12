#include "Character.h"

#include <fstream>
#include "load_texture.h"
#include "load_json.h"

Character::Character() :
	sprite_texture_(NULL),sprite_(NULL)
{
	Transform = NULL;
	WhichAnim_ = NULL;
}

Character::~Character()
{
	delete sprite_texture_;
	sprite_texture_ = NULL;

	delete sprite_;
	sprite_ = NULL;

	delete Transform;
	Transform = NULL;

	delete WhichAnim_;
	WhichAnim_ = NULL;
}

void Character::LoadCharacter(std::string tex_string, gef::Platform* platform_, gef::Vector2 position_, float scale_)
{
	animation_timer_ = 0;
	frame = 0;

	sprite_ = new gef::Sprite();

	Position.x = position_.x;
	Position.y = position_.y;

	std::string tex_string_temp = tex_string + "_tex.png";
	Scale = scale_;

	sprite_texture_ = CreateTextureFromPNG(tex_string_temp.c_str(), *platform_);

	sprite_->set_texture(sprite_texture_);

	Sprite_anim* new_sprite;
	new_sprite = new Sprite_anim();
	new_sprite->Load_sprite_and_texture_3(tex_string, rapidjson_doc_tex, rapidjson_doc_ske);

	delete new_sprite;
}

void Character::SetAnimation(std::string& tex_string, gef::Platform* platform_)
{
	Anim_manager* new_animantion;
	new_animantion = new Anim_manager();

	new_animantion->SetupAnim(platform_, sprite_, tex_string, rapidjson_doc_tex, rapidjson_doc_ske, Position, bone_parts, Type, WhichAnim_,Scale);

	if (new_animantion->GetWhichAnim() != NULL)
	{
		std::string new_string = tex_string;
		new_string = tex_string + "_" + *new_animantion->GetWhichAnim();
		animations.insert(std::make_pair(new_string, new_animantion));
	}
	else
	{
		animations.insert(std::make_pair(tex_string, new_animantion));
	}
}

void Character::SetWhichAnimation(std::string tex_string)
{
	WhichAnim_ = new std::string(tex_string);
}

void Character::Update(std::string tex_string, int frame)
{
	animations.at(tex_string)->Update(frame, sprite_,Position, Transforms_for_bone_);
}

void Character::UpdateAnimation(float frame_time, std::string sprite_name_)
{
	animation_timer_ += frame_time;

	if (animation_timer_ >= (1.f / animations.at(sprite_name_)->GetFrameRate()))
	{
		frame++;
		animation_timer_ = 0;
	}

	if (frame >= animations.at(sprite_name_)->GetDuration())
	{
		frame = 0;
	}

	Update(sprite_name_, frame);
}

void Character::RenderAnimation(std::string sprite_name_,gef::SpriteRenderer* sprite_renderer_)
{
	if (Type == "Sheet")
	{
		for (auto part : bone_parts)
		{
			sprite_renderer_->DrawSprite(*Render(sprite_name_, part));
		}
	}
	else
	{
		for (auto part : bone_parts)
		{
			sprite_renderer_->DrawSprite(*Render(sprite_name_, part), *Transform);
		}
	}
}

gef::Sprite* Character::Render(std::string tex_string, std::string part)
{
	gef::Matrix33 NewTransform;
	animations.at(tex_string)->Sprite_Render(sprite_, NewTransform, part,Position);
	Transform = &NewTransform;
	return sprite_;
}