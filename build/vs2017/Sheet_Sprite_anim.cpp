#include "Sheet_Sprite_anim.h"

#include "load_texture.h"
#include "load_json.h"
#include <fstream>

Sheet_Sprite_anim::Sheet_Sprite_anim()
{
	text_atlas = new TextureAtlas;
	RighasbeenSet = false;
}

Sheet_Sprite_anim::~Sheet_Sprite_anim()
{
	delete text_atlas;
	text_atlas = NULL;
}

//TextureAtlas* Sheet_Sprite_anim::ReadTextureAtlasFromJSON(rapidjson::Document& tex_document)
//{
//	TextureAtlas* tex_atlas = new TextureAtlas();
//	tex_atlas->name_ = tex_document["name"].GetString();
//	//Something to with this?
//	tex_atlas->width_ = tex_document["width"].GetFloat();
//	tex_atlas->height_ = tex_document["height"].GetFloat();
//	///--------------------------------------------
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
//TexData* Sheet_Sprite_anim::ReadSubtextureFromJSON(const rapidjson::Value& subtecture_array)
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
//void Sheet_Sprite_anim::SetSpriteSizeAndPositionForFrame(gef::Sprite* sprite, float screen_x, float screen_y, int frame)
//{
//
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
//	//This guy here
//	sprite->set_uv_width(width / text_atlas->width_);
//	sprite->set_uv_height(height / text_atlas->height_);
//	///////////////////////////
//
//	float u = x / text_atlas->width_;
//	float v = y / text_atlas->height_;
//	sprite->set_uv_position(gef::Vector2(u, v));
//
//
//	float sprite_x = width * 0.5f - (frame_width * 0.5f + frame_x);
//	float sprite_y = height * 0.5f - (frame_height * 0.5f + frame_y);
//
//	sprite->set_position(gef::Vector4(screen_x + sprite_x, screen_y + sprite_y, 0.0f));
//}

void Sheet_Sprite_anim::Update(int frame, gef::Sprite* sprite_, gef::Vector2 position_, std::map<std::string, gef::Matrix33>& Transforms_for_bone_)
{
	//Transforms_for_bone_1.insert(std::make_pair(bone_parts1[0], rig_transform_m_));

	//SetupRig(&rig_transform_m_, position_, scale);
	//sub_texture_transform_m = text_atlas->subtextures.at(frame).transform_m_;
	//sub_texture_transform_m1 = text_atlas->subtextures.at(frame).translate_m_;

	//Needs to be a better way to do this

	//Get the size of the word
	//take a away one letter 
	//and then add the frame to it!



	std::string name = this_string + std::to_string(frame);
	SetSpriteSizeAndPositionForFrame(sprite_, position_.x, position_.y, frame,text_atlas, name);
	//Transforms_for_bone_ = Transforms_for_bone_1;
	//DeleteTransforms();
}

gef::Sprite* Sheet_Sprite_anim::Render(gef::Sprite* sprite, gef::Matrix33& transform, std::string part, gef::Vector2 Position)
{
	//gef::Matrix33 sub_texture_transform_m = text_atlas->subtextures.at(0).transform_m_;
	//transform = sub_texture_transform_m * sub_texture_transform_m1 * rig_transform_m_;
	//SetSpriteSizeAndPositionForFrame(sprite, Position.x, Position.y, 0, text_atlas, frame);
	return sprite;
}

gef::Sprite* Sheet_Sprite_anim::Load_sprite_and_texture_2(gef::Platform* platform_, gef::Sprite* sprite_, std::string tex_string)
{
	//We can then move this to the sprite sheet version and load the tex

	std::string tex_string_temp = tex_string + "_tex.png";

	sprite_texture_ = CreateTextureFromPNG(tex_string_temp.c_str(), *platform_);

	tex_string_temp = tex_string + "_tex.json";

	char* JSON_Doc = LoadJSON(tex_string_temp.c_str());
	//std::ifstream ifs(tex_string_temp.c_str());
	//rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document rapidjson_doc;
	//rapidjson_doc.ParseStream(isw);
	rapidjson_doc.Parse(JSON_Doc);

	tex_string_temp = tex_string + "_ske.json";

	std::ifstream ifs2(tex_string_temp.c_str());
	rapidjson::IStreamWrapper isw2(ifs2);
	rapidjson::Document this_ske;
	this_ske.ParseStream(isw2);

	text_atlas = ReadTextureAtlasFromJSON(rapidjson_doc);
	sprite_->set_texture(sprite_texture_);

	run_order = SetupOrder(this_ske);

	text_atlas->subtextures = ReOrganiseSubtextures();

	return sprite_;
}

gef::Sprite* Sheet_Sprite_anim::SetupAnimation(gef::Platform* platform_, gef::Sprite* sprite_, std::string tex_string, rapidjson::Document& tex_document, rapidjson::Document& ske_document, gef::Vector2 Position, std::vector<std::string>& bone_parts, std::string* WhichAnim1)
{
	scale = 1.0f;

	bone_parts1.push_back("Default");
	bone_parts = bone_parts1;

	SetupRig(&rig_transform_m_, Position, scale);

	std::string tex_string_temp = tex_string + "_tex.png";

	sprite_texture_ = CreateTextureFromPNG(tex_string_temp.c_str(), *platform_);

	text_atlas = ReadTextureAtlasFromJSON(tex_document);
	//sprite_->set_texture(sprite_texture_);

	run_order = SetupOrder(ske_document);

	//Need to do this with subtext_atlas
	//text_atlas->subtextures = ReOrganiseSubtextures();
	text_atlas->subtex_atlas = ReOrganiseSubtextures1();

	return sprite_;
}

std::map<int, std::string> Sheet_Sprite_anim::SetupOrder(rapidjson::Document& ske_document)
{
	const rapidjson::Value& order_array = ske_document["armature"][0]["skin"][0]["slot"][0]["display"];
	std::string s = order_array[0]["name"].GetString();
	std::map<int,std::string> new_order;
	
	for (int order_num = 0; order_num < (int)order_array.Size(); ++order_num)
	{
		//new_order.push_back(order_array[order_num].GetString());
		new_order.insert(std::make_pair(order_num, order_array[order_num]["name"].GetString()));
	}
	
	return new_order;

}

std::vector<TexData> Sheet_Sprite_anim::ReOrganiseSubtextures()
{
	std::vector<TexData> new_vec;
	for (int i = 0; i < run_order.size(); i++)
	{
		for (int j = 0; j < text_atlas->subtextures.size(); j++)
		{
			if (text_atlas->subtextures.at(j).name_ == run_order[i])
			{
				new_vec.push_back(text_atlas->subtextures.at(j));
			}
		}
	}

	return new_vec;

}

std::map<std::string, TexData> Sheet_Sprite_anim::ReOrganiseSubtextures1()
{
	std::map<std::string,TexData> new_vec;
	bool got_string = false;
	for (int i = 0; i < run_order.size(); i++)
	{
		for (auto j : text_atlas->subtex_atlas)
		{
			if (text_atlas->subtex_atlas.at(j.first).name_ == run_order[i])
			{
				new_vec.insert(std::make_pair(j.first, j.second));
			}

			if (!got_string)
			{
				int string_length_ = j.first.size();
				int new_length = string_length_ - 1;
				this_string = j.first.substr(0, new_length);
				got_string = true;
			}
		}
	}
	return new_vec;
}

void Sheet_Sprite_anim::DeleteTransforms()
{
	Transforms_for_bone_1.clear();
}
