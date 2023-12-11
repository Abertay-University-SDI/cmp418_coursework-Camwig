#include "Sprite_anim.h"

#include <fstream>
#include "load_texture.h"
#include "load_json.h"

Sprite_anim::Sprite_anim()
{

}


Sprite_anim::~Sprite_anim()
{

}

//void Sprite_anim::SetupAnim(gef::Platform* platform_, gef::Sprite* sprite_, std::string tex_string, rapidjson::Document& tex_document, rapidjson::Document& ske_document)
//{
//	Load_sprite_and_texture_3(tex_string, tex_document, ske_document);
//	sprite_ = SetupAnimation(platform_, sprite_, tex_string, tex_document, ske_document);
//}

void Sprite_anim::Load_sprite_and_texture_3(std::string tex_string, rapidjson::Document& rapidjson_doc_tex, rapidjson::Document& rapidjson_doc_ske)
{
	//We can then move this to the sprite sheet version and load the tex
	
	//Will need to put and output alot of this stuff

	std::string tex_string_temp = tex_string + "_tex.json";

	char* JSON_Doc = LoadJSON(tex_string_temp.c_str());
	std::ifstream ifs(tex_string_temp.c_str());
	rapidjson::IStreamWrapper isw(ifs);
	//rapidjson::Document rapidjson_doc_tex;
	rapidjson_doc_tex.ParseStream(isw);

	tex_string_temp = tex_string + "_ske.json";

	char* JSON_Doc_2 = LoadJSON(tex_string_temp.c_str());
	std::ifstream ifs2(tex_string_temp.c_str());
	rapidjson::IStreamWrapper isw2(ifs2);
	//rapidjson::Document rapidjson_doc_ske;
	rapidjson_doc_ske.ParseStream(isw2);
}

TextureAtlas* Sprite_anim::ReadTextureAtlasFromJSON(rapidjson::Document& tex_document)
{
	//These need to be put in sheet and skeletal respectively


	//TextureAtlas* tex_atlas = new TextureAtlas();
	//tex_atlas->name_ = tex_document["name"].GetString();
	////Something to with this?
	//tex_atlas->width_ = tex_document["width"].GetFloat();
	//tex_atlas->height_ = tex_document["height"].GetFloat();
	/////--------------------------------------------

	//const rapidjson::Value& subtexture_array = tex_document["SubTexture"];
	//for (int subtex_num = 0; subtex_num < (int)subtexture_array.Size(); ++subtex_num)
	//{
	//	TexData* texdata = ReadSubtextureFromJSON(subtexture_array[subtex_num]);
	//	tex_atlas->subtextures.push_back(*texdata);
	//	delete texdata;
	//}

	//return tex_atlas;

	TextureAtlas* tex_atlas = new TextureAtlas();
	tex_atlas->name_ = tex_document["name"].GetString();
	tex_atlas->width_ = tex_document["width"].GetFloat();
	tex_atlas->height_ = tex_document["height"].GetFloat();

	const rapidjson::Value& subtexture_array = tex_document["SubTexture"];
	for (int subtex_num = 0; subtex_num < (int)subtexture_array.Size(); ++subtex_num)
	{
		TexData* texdata = ReadSubtextureFromJSON(subtexture_array[subtex_num]);
		//tex_atlas->subtextures.push_back(*texdata);

		tex_atlas->subtex_atlas.insert(std::make_pair(texdata->name_, *texdata));

		delete texdata;
	}

	return tex_atlas;
}

TexData* Sprite_anim::ReadSubtextureFromJSON(const rapidjson::Value& subtecture_array)
{
	TexData* subTextData = new TexData;
	subTextData->name_ = subtecture_array["name"].GetString();
	subTextData->width_ = subtecture_array["width"].GetFloat();
	subTextData->height_ = subtecture_array["height"].GetFloat();
	subTextData->x_ = subtecture_array["x"].GetFloat();
	subTextData->y_ = subtecture_array["y"].GetFloat();

	if (subtecture_array.HasMember("frameX"))
	{
		subTextData->frame_x_ = subtecture_array["frameX"].GetFloat();
	}
	else
	{
		subTextData->frame_x_ = 0;
	}

	if (subtecture_array.HasMember("frameY"))
	{
		subTextData->frame_y_ = subtecture_array["frameY"].GetFloat();
	}
	else
	{
		subTextData->frame_y_ = 0;
	}

	if (subtecture_array.HasMember("frameWidth"))
	{
		subTextData->frame_width_ = subtecture_array["frameWidth"].GetFloat();
	}
	else
	{
		subTextData->frame_width_ = subTextData->width_;
	}

	if (subtecture_array.HasMember("frameHeight"))
	{
		subTextData->frame_height_ = subtecture_array["frameHeight"].GetFloat();
	}
	else
	{
		subTextData->frame_height_ = subTextData->height_;
	}

	subTextData->BuildTransform();

	return subTextData;
}

void Sprite_anim::SetSpriteSizeAndPositionForFrame(gef::Sprite* sprite, float screen_x, float screen_y, int frame, TextureAtlas* texture_atlas, std::string subtext_)
{

	float width = texture_atlas->subtex_atlas.at(subtext_).width_;
	float height = texture_atlas->subtex_atlas.at(subtext_).height_;
	float x = texture_atlas->subtex_atlas.at(subtext_).x_;
	float y = texture_atlas->subtex_atlas.at(subtext_).y_;
	float frame_width = texture_atlas->subtex_atlas.at(subtext_).frame_width_;
	float frame_height = texture_atlas->subtex_atlas.at(subtext_).frame_height_;
	float frame_x = texture_atlas->subtex_atlas.at(subtext_).frame_x_;
	float frame_y = texture_atlas->subtex_atlas.at(subtext_).frame_y_;

	sprite->set_width(width);
	sprite->set_height(height);
	sprite->set_uv_width(width / texture_atlas->width_);
	sprite->set_uv_height(height / texture_atlas->height_);

	float u = x / texture_atlas->width_;
	float v = y / texture_atlas->height_;
	sprite->set_uv_position(gef::Vector2(u, v));

	float sprite_x = width * 0.5f - (frame_width * 0.5f + frame_x);
	float sprite_y = height * 0.5f - (frame_height * 0.5f + frame_y);

	sprite->set_position(gef::Vector4(screen_x + sprite_x, screen_y + sprite_y, 0.0f));
	sprite->set_position(gef::Vector4(screen_x + sprite_x, screen_y + sprite_y, 0.0f));
}

gef::Sprite* Sprite_anim::Load_sprite_and_texture_2(gef::Platform*, gef::Sprite* sprite, std::string)
{
	return sprite;
}

gef::Sprite* Sprite_anim::SetupAnimation(gef::Platform*, gef::Sprite* sprite, std::string tex_string, rapidjson::Document& tex_document, rapidjson::Document& ske_document, gef::Vector2 Position, std::vector<std::string>& bone_parts,std::string* WhichAnim1, float scale_)
{
	return sprite;
}

void Sprite_anim::Update(int frame, gef::Sprite* sprite_, gef::Vector2 position_, std::map<std::string, gef::Matrix33>& Transforms_for_bone_)
{
}

gef::Sprite* Sprite_anim::Render(gef::Sprite* sprite)
{
	return sprite;
}

gef::Sprite* Sprite_anim::Render(gef::Sprite* sprite,gef::Matrix33& transform, std::string part, gef::Vector2 Position)
{
	return sprite;
}

void Sprite_anim::SetupRig(gef::Matrix33* rig_transform_m_,gef::Vector2 sprite_pos_,float scale)
{
	//gef::Matrix33 rig_transform_m_;

	rig_transform_m_->SetIdentity();
	rig_transform_m_->Scale(gef::Vector2(scale, scale));
	rig_transform_m_->SetTranslation(gef::Vector2(sprite_pos_.x, sprite_pos_.y));
}


//Dont know why this wouldnt work?
//Does not work with string!!!! FUN
//template void Sprite_anim::SetSpriteSizeAndPositionForFrame<int>(gef::Sprite* sprite, float screen_x, float screen_y, int frame, TextureAtlas* texture_atlas, int subtext_);
//template void Sprite_anim::SetSpriteSizeAndPositionForFrame<char*>(gef::Sprite* sprite, float screen_x, float screen_y, int frame, TextureAtlas* texture_atlas, char* subtext_);
