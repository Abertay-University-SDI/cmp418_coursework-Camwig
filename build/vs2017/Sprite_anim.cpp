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
	TextureAtlas* tex_atlas = new TextureAtlas();
	tex_atlas->name_ = tex_document["name"].GetString();
	//Something to with this?
	tex_atlas->width_ = tex_document["width"].GetFloat();
	tex_atlas->height_ = tex_document["height"].GetFloat();
	///--------------------------------------------

	const rapidjson::Value& subtexture_array = tex_document["SubTexture"];
	for (int subtex_num = 0; subtex_num < (int)subtexture_array.Size(); ++subtex_num)
	{
		TexData* texdata = ReadSubtextureFromJSON(subtexture_array[subtex_num]);
		tex_atlas->subtextures.push_back(*texdata);
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
	subTextData->frame_x_ = subtecture_array["frameX"].GetFloat();
	subTextData->frame_y_ = subtecture_array["frameY"].GetFloat();
	subTextData->frame_width_ = subtecture_array["frameWidth"].GetFloat();
	subTextData->frame_height_ = subtecture_array["frameHeight"].GetFloat();

	return subTextData;
}

template <typename Value> void Sprite_anim::SetSpriteSizeAndPositionForFrame(gef::Sprite* sprite, float screen_x, float screen_y, int frame, TextureAtlas* texture_atlas,Value subtext_)
{

	float width = texture_atlas->subtextures.at(subtext_).width_;
	float height = texture_atlas->subtextures.at(subtext_).height_;
	float x = texture_atlas->subtextures.at(subtext_).x_;
	float y = texture_atlas->subtextures.at(subtext_).y_;
	float frame_width = texture_atlas->subtextures.at(subtext_).frame_width_;
	float frame_height = texture_atlas->subtextures.at(subtext_).frame_height_;
	float frame_x = texture_atlas->subtextures.at(subtext_).frame_x_;
	float frame_y = texture_atlas->subtextures.at(subtext_).frame_y_;

	sprite->set_width(width);
	sprite->set_height(height);
	//This guy here
	sprite->set_uv_width(width / texture_atlas->width_);
	sprite->set_uv_height(height / texture_atlas->height_);
	///////////////////////////

	float u = x / texture_atlas->width_;
	float v = y / texture_atlas->height_;
	sprite->set_uv_position(gef::Vector2(u, v));


	float sprite_x = width * 0.5f - (frame_width * 0.5f + frame_x);
	float sprite_y = height * 0.5f - (frame_height * 0.5f + frame_y);

	sprite->set_position(gef::Vector4(screen_x + sprite_x, screen_y + sprite_y, 0.0f));
}

gef::Sprite* Sprite_anim::Load_sprite_and_texture_2(gef::Platform*, gef::Sprite* sprite, std::string)
{
	return sprite;
}

gef::Sprite* Sprite_anim::SetupAnimation(gef::Platform*, gef::Sprite* sprite, std::string tex_string, rapidjson::Document& tex_document, rapidjson::Document& ske_document)
{
	return sprite;
}

void Sprite_anim::Update(int frame, gef::Sprite* sprite_, gef::Vector2 position_)
{
}

template void Sprite_anim::SetSpriteSizeAndPositionForFrame<int>(gef::Sprite* sprite, float screen_x, float screen_y, int frame, TextureAtlas* texture_atlas, int subtext_);

//TextureAtlas* Sprite_anim::ReadTextureAtlasFromJSON(rapidjson::Document& tex_document)
//{
//	TextureAtlas* tex_atlas = new TextureAtlas();
//	tex_atlas->name_ = tex_document["name"].GetString();
//	tex_atlas->width_ = tex_document["width"].GetFloat();
//	tex_atlas->height_ = tex_document["height"].GetFloat();
//
//	const rapidjson::Value& subtexture_array = tex_document["SubTexture"];
//	for (int subtex_num = 0; subtex_num < (int)subtexture_array.Size(); ++subtex_num)
//	{
//		TexData* texdata = ReadSubtextureFromJSON(subtexture_array[subtex_num]);
//		tex_atlas->subtextures.push_back(*texdata);
//		delete texdata;
//	}
//
//	return tex_atlas;
//}
//
//TexData* Sprite_anim::ReadSubtextureFromJSON(const rapidjson::Value& subtecture_array)
//{
//	TexData* subTextData = new TexData;
//	subTextData->name_ = subtecture_array["name"].GetString();
//	subTextData->width_ = subtecture_array["width"].GetFloat();
//	subTextData->height_ = subtecture_array["height"].GetFloat();
//	subTextData->x_ = subtecture_array["x"].GetFloat();
//	subTextData->y_ = subtecture_array["y"].GetFloat();
//	subTextData->frame_x_ = subtecture_array["frameX"].GetFloat();
//	subTextData->frame_y_ = subtecture_array["frameY"].GetFloat();
//	subTextData->frame_width_ = subtecture_array["frameWidth"].GetFloat();
//	subTextData->frame_height_ = subtecture_array["frameHeight"].GetFloat();
//
//	return subTextData;
//}
//
//void Sprite_anim::SetSpriteSizeAndPositionForFrame(gef::Sprite* sprite, float screen_x, float screen_y, TextureAtlas* texture_atlas, int frame)
//{
//	float width = texture_atlas->subtextures.at(frame).width_;
//	float height = texture_atlas->subtextures.at(frame).height_;
//	float x = texture_atlas->subtextures.at(frame).x_;
//	float y = texture_atlas->subtextures.at(frame).y_;
//	float frame_width = texture_atlas->subtextures.at(frame).frame_width_;
//	float frame_height = texture_atlas->subtextures.at(frame).frame_height_;
//	float frame_x = texture_atlas->subtextures.at(frame).frame_x_;
//	float frame_y = texture_atlas->subtextures.at(frame).frame_y_;
//
//	sprite->set_width(width);
//	sprite->set_height(height);
//	sprite->set_uv_width(width / texture_atlas->width_);
//	sprite->set_uv_height(width / texture_atlas->height_);
//
//	float u = x / texture_atlas->width_;
//	float v = y / texture_atlas->height_;
//	sprite->set_uv_position(gef::Vector2(u, v));
//
//	float sprite_x = width * 0.5f - (frame_width * 0.5f + frame_x);
//	float sprite_y = height * 0.5f - (frame_height * 0.5f + frame_y);
//
//	sprite->set_position(gef::Vector4(screen_x + sprite_x, screen_y + sprite_y, 0.0f));
//}