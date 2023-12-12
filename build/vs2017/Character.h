#pragma once

#include "Anim_manager.h"
#include <maths/vector2.h>
#include <graphics/sprite_renderer.h>

namespace gef
{
	class SpriteRenderer;
}

class Character
{
public:
	Character();
	~Character();

	//Sets up the character
	void LoadCharacter(std::string,gef::Platform*,gef::Vector2 position_,float scale_);
	//Update the character
	void Update(std::string tex_string, int frame);
	//Render the correct part of the sprite
	gef::Sprite* Render(std::string tex_string,std::string part);
	//Render the updated animated character
	void RenderAnimation(std::string sprite_name_, gef::SpriteRenderer* sprite_renderer_);
	//Sets which animation to perform if there are multiple
	void SetWhichAnimation(std::string tex_string);
	//Creates an animation and added to the character
	void SetAnimation(std::string& tex_string, gef::Platform* platform_);
	//Updates the given animation
	void UpdateAnimation(float frame_time, std::string sprite_name_);
private:
	float Scale;
	int frame;
	float animation_timer_;

	gef::Texture* sprite_texture_;
	gef::Vector2 Position;
	rapidjson::Document rapidjson_doc_tex;
	rapidjson::Document rapidjson_doc_ske;
	

	std::map<std::string, Anim_manager*> animations;


	gef::Sprite* sprite_;
	std::string Type;
	std::vector<std::string> bone_parts;
	std::map<std::string, gef::Matrix33> Transforms_for_bone_;
	gef::Matrix33* Transform;
	std::string* WhichAnim_;
};

