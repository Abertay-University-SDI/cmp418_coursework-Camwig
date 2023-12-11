#pragma once

#include "Anim.h"
#include <maths/vector2.h>
#include <graphics/sprite_renderer.h>

//enum Type
//{
//	Sheet = 0,
//	Skeletal = 1
//};


namespace gef
{
	class SpriteRenderer;
}

class Character
{
	//Load sprite - WORKING ON IT!
	//Update positions
	//render
public:
	Character();
	~Character();

	void LoadCharacter(std::string,gef::Platform*,gef::Vector2 position_,gef::Vector2 size_,float scale_);

	void Update(std::string tex_string, int frame);

	gef::Sprite* Render(std::string tex_string,std::string part);
	void RenderAnimation(std::string sprite_name_, gef::SpriteRenderer* sprite_renderer_);

	void SetWhichAnimation(std::string tex_string);

	void SetAnimation(std::string& tex_string, gef::Platform* platform_);

	void UpdateAnimation(float frame_time, std::string sprite_name_);


	std::map<std::string, Anim*> animations;

	gef::Sprite* sprite_;

	std::string Type;

	std::vector<std::string> bone_parts;
	std::map<std::string, gef::Matrix33> Transforms_for_bone_;
	gef::Matrix33* Transform;

	std::string* WhichAnim_;

private:
	//Type Chars_type;
	gef::Texture* sprite_texture_;

	gef::Vector2 Position;
	float Scale;
	rapidjson::Document rapidjson_doc_tex;
	rapidjson::Document rapidjson_doc_ske;

	int frame;
	float animation_timer_;
};

