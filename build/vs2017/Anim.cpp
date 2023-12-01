#include "Anim.h"
#include "load_texture.h"
#include "load_json.h"
#include <fstream>

//This whole thing will have to be reworked a bit

Anim::Anim()
{

}

Anim::~Anim()
{
	//delete text_atlas;
	//text_atlas = NULL;

	delete sprite_animation_;
	sprite_animation_ = NULL;
}

//void Anim::Init(std::string file, gef::Platform* platform_, gef::Sprite* sprite_, std::string tex_string, int frame)
//{
//	text_atlas = new TextureAtlas;
//
//	//frame_ = frame;
//
//	sprite = sprite_;
//
//	///////////////// Ske Read Test
//	std::ifstream Ske_stream(file);
//	rapidjson::IStreamWrapper new_wrap(Ske_stream);
//	rapidjson::Document ske_doc;
//	ske_doc.ParseStream(new_wrap);
//
//	/*std::ifstream ifs2(tex_string_temp.c_str());
//	rapidjson::IStreamWrapper isw2(ifs2);
//	rapidjson::Document this_ske;
//	this_ske.ParseStream(isw2);*/
//
//	const rapidjson::Value& ske_array = ske_doc["armature"];
//	std::string bums = ske_array[0]["type"].GetString();
//
//	if (bums.find("Sheet") != std::string::npos)
//	{
//		//Need to put something in here to tell it that it is a 2D sprite sheet animation
//		//To run all there stuff!
//		FrameRate = ske_array[0]["frameRate"].GetInt();
//		Duration = ske_array[0]["animation"][0]["duration"].GetInt();
//		Setup_2D_anim(platform_, sprite, tex_string);
//	}
//	/////////////////
//}

//void Anim::Setup_2D_anim(gef::Platform* platform_, gef::Sprite* sprite_, std::string tex_string)
//{
//	Sheet_Sprite_anim* new_sheet;
//	new_sheet = new Sheet_Sprite_anim();
//	sprite_ = new_sheet->Load_sprite_and_texture_2(platform_, sprite_, tex_string);
//	sprite_animation_ = new_sheet;
//}

void Anim::Update(int frame, gef::Sprite* sprite_, gef::Vector2 position_)
{
	//sprite_ = sprite_animation_->SetSpriteSizeAndPositionForFrame(sprite_,screen_x,screen_y, frame);
	//sprite_animation_->SetSpriteSizeAndPositionForFrame(sprite_, position_.x, position_.y, frame);
	sprite_animation_->Update(frame,sprite_,position_);
}

//void Anim::SetupAnimSheet2D(gef::Platform* platform_, gef::Sprite* sprite_, std::string tex_string, rapidjson::Document& tex_document, rapidjson::Document& ske_document)
//{
//	//screen_x = platform_->width() * 0.5f;
//	//screen_y = platform_->height() * 0.5f;
//	Sheet_Sprite_anim* new_sheet;
//	new_sheet = new Sheet_Sprite_anim();
//	sprite_animation_ = new_sheet;
//	sprite_animation_->Load_sprite_and_texture_3(tex_string, tex_document, ske_document);
//	sprite_ = sprite_animation_->SetupAnimation(platform_,sprite_,tex_string,tex_document,ske_document);
//}

void Anim::SetupAnim(gef::Platform* platform_, gef::Sprite* sprite_, std::string tex_string, rapidjson::Document& tex_document, rapidjson::Document& ske_document,int& FrameRate, int& Duration)
{
	Sprite_anim* new_sheet;
	new_sheet = new Sprite_anim();
	sprite_animation_ = new_sheet;
	sprite_animation_->Load_sprite_and_texture_3(tex_string, tex_document, ske_document);

	sprite_animation_ = nullptr;

	const rapidjson::Value& ske_array = ske_document["armature"];
	std::string bums = ske_array[0]["type"].GetString();

	if (bums.find("Sheet") != std::string::npos)
	{
		//Need to put something in here to tell it that it is a 2D sprite sheet animation
		//To run all there stuff!
		Sheet_Sprite_anim* new_sheet;
		new_sheet = new Sheet_Sprite_anim();
		sprite_animation_ = new_sheet;
		//sprite_animation_->Load_sprite_and_texture_3(tex_string, tex_document, ske_document);

		int temp;
		temp = ske_array[0]["frameRate"].GetInt();
		FrameRate = temp;
		temp = ske_array[0]["animation"][0]["duration"].GetInt();
		Duration = temp;
		sprite_ = sprite_animation_->SetupAnimation(platform_, sprite_, tex_string, tex_document, ske_document);
	}
}

//
//TextureAtlas* Anim::ReadTextureAtlasFromJSON(rapidjson::Document& tex_document)
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
//TexData* Anim::ReadSubtextureFromJSON(const rapidjson::Value& subtecture_array)
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
//void Anim::SetSpriteSizeAndPositionForFrame(gef::Sprite* sprite, float screen_x, float screen_y, int frame)
//{
//	float width = text_atlas->subtextures.at(frame).width_;
//	float height = text_atlas->subtextures.at(frame).height_;
//	float x = text_atlas->subtextures.at(frame).x_;
//	float y = text_atlas->subtextures.at(frame).y_;
//	float frame_width = text_atlas->subtextures.at(frame).frame_width_;
//	float frame_height = text_atlas->subtextures.at(frame).frame_height_;
//	float frame_x = text_atlas->subtextures.at(frame).frame_x_;
//	float frame_y = text_atlas->subtextures.at(frame).frame_y_;
//
//	sprite->set_width(width);
//	sprite->set_height(height);
//	sprite->set_uv_width(width / text_atlas->width_);
//	sprite->set_uv_height(width / text_atlas->height_);
//
//	float u = x / text_atlas->width_;
//	float v = y / text_atlas->height_;
//	sprite->set_uv_position(gef::Vector2(u, v));
//
//	float sprite_x = width * 0.5f - (frame_width * 0.5f + frame_x);
//	float sprite_y = height * 0.5f - (frame_height * 0.5f + frame_y);
//
//	sprite->set_position(gef::Vector4(screen_x + sprite_x, screen_y + sprite_y, 0.0f));
//}
//
//void Anim::Load_sprite_and_texture_(gef::Platform* platform_ ,gef::Sprite* sprite_)
//{
//	//We can then move this to the sprite sheet version and load the tex
//
//	sprite_texture_ = CreateTextureFromPNG("boy-attack_tex.png", *platform_);
//
//	char* JSON_Doc = LoadJSON("boy-attack_tex.json");
//	std::ifstream ifs("boy-attack_tex.json");
//	rapidjson::IStreamWrapper isw(ifs);
//	rapidjson::Document rapidjson_doc;
//	rapidjson_doc.ParseStream(isw);
//
//	text_atlas = ReadTextureAtlasFromJSON(rapidjson_doc);
//	sprite_->set_texture(sprite_texture_);
//}
//
//void Anim::Load_sprite_and_texture_2(gef::Platform* platform_, gef::Sprite* sprite_,std::string tex_string)
//{
//	//We can then move this to the sprite sheet version and load the tex
//
//	std::string tex_string_temp = tex_string + ".png";
//
//	sprite_texture_ = CreateTextureFromPNG(tex_string_temp.c_str(), *platform_);
//
//	tex_string_temp = tex_string + ".json";
//
//	char* JSON_Doc = LoadJSON(tex_string_temp.c_str());
//	std::ifstream ifs(tex_string_temp.c_str());
//	rapidjson::IStreamWrapper isw(ifs);
//	rapidjson::Document rapidjson_doc;
//	rapidjson_doc.ParseStream(isw);
//
//	text_atlas = ReadTextureAtlasFromJSON(rapidjson_doc);
//	sprite_->set_texture(sprite_texture_);
//}
