//#include "scene_app.h"
//#include <system/platform.h>
//#include <graphics/sprite_renderer.h>
//#include <graphics/font.h>
//#include <system/debug_log.h>
//#include <graphics/renderer_3d.h>
//#include <graphics/mesh.h>
//#include <maths/math_utils.h>
//#include <input/sony_controller_input_manager.h>
//#include <graphics/sprite.h>
//#include "load_texture.h"
//
//SceneApp::SceneApp(gef::Platform& platform) :
//	Application(platform),
//	sprite_renderer_(NULL),
//	input_manager_(NULL),
//	font_(NULL),
//	sprite_texture_(NULL)
//{
//}
//
//void SceneApp::Init()
//{
//	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
//	InitFont();
//
//	// initialise input manager
//	input_manager_ = gef::InputManager::Create(platform_);
//
//	sprite_texture_ = CreateTextureFromPNG("Idle (1).png", platform_);
//
//	sprite_.set_texture(sprite_texture_);
//	sprite_.set_position(gef::Vector4(platform_.width()*0.5f, platform_.height()*0.5f, -0.99f));
//	sprite_.set_height(128.0f);
//	sprite_.set_width(128.0f);
//}
//
//void SceneApp::CleanUp()
//{
//	delete sprite_texture_;
//	sprite_texture_ = NULL;
//
//	delete input_manager_;
//	input_manager_ = NULL;
//
//	CleanUpFont();
//
//	delete sprite_renderer_;
//	sprite_renderer_ = NULL;
//}
//
//bool SceneApp::Update(float frame_time)
//{
//	fps_ = 1.0f / frame_time;
//
//
//	input_manager_->Update();
//
//	return true;
//}
//
//
//
//
//void SceneApp::Render()
//{
//	sprite_renderer_->Begin();
//
//	// Render button icon
//	sprite_renderer_->DrawSprite(sprite_);
//
//	DrawHUD();
//	sprite_renderer_->End();
//}
//
//void SceneApp::InitFont()
//{
//	font_ = new gef::Font(platform_);
//	font_->Load("comic_sans");
//}
//
//void SceneApp::CleanUpFont()
//{
//	delete font_;
//	font_ = NULL;
//}
//
//void SceneApp::DrawHUD()
//{
//	if(font_)
//	{
//		// display frame rate
//		font_->RenderText(sprite_renderer_, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
//	}
//}

#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <graphics/mesh.h>
#include <maths/math_utils.h>
#include <input/sony_controller_input_manager.h>
#include <graphics/sprite.h>
//#include "load_texture.h"
//#include "load_json.h"

#include <iostream>
#include <string>
#include <fstream>
//#include "load_texture.h"
//#include "load_json.h"

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	input_manager_(NULL),
	font_(NULL)
	//sprite_texture_(NULL)
{
}

void SceneApp::Init()
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
	InitFont();

	animation_timer_ = 0;

	//elapsed_time = 0;
	//This is not correct for every animation just for this one
	//sprite_speed = 1/30.0f;

	frame = 0;

	this_s = "boy-attack";

	//anim = new Anim(/*std::string("boy-attack_ske.json"), &platform_, &sprite_, this_s,frame*/);
	//anim->Init(std::string("boy-attack_ske.json"), &platform_, &sprite_, this_s, frame);

	// initialise input manager
	input_manager_ = gef::InputManager::Create(platform_);
	/*
	sprite_texture_ = CreateTextureFromPNG("boy-attack_tex.png", platform_);

	//std::ifstream ifs2("Dragon_ske.json");
	//rapidjson::IStreamWrapper isw2(ifs2);
	//rapidjson::Document doc_dragon_ske;
	//doc_dragon_ske.ParseStream(isw2);

	//skin_slots = anim->ReadSkinSlotsDataFromJSON(doc_dragon_ske);
	//bones_ = anim->ReadBonesFromJSON(doc_dragon_ske);

	//new_anim = anim->ReadAnimationDataFromJSON(doc_dragon_ske);

	//text_atlas = *anim->ReadTextureAtlasFromJSON(rapidjson_doc);
	/////////////////////////////////
	sprite_.set_texture(sprite_texture_);
	*/

	//anim->Load_sprite_and_texture_2(&platform_,&sprite_, this_s);
	//anim->Load_sprite_and_texture_(&platform_,&sprite_);


	//sprite_pos_ = gef::Vector2(platform_.width()*0.5f, platform_.height()*0.5f);

	//sprite_.set_position(gef::Vector4(sprite_pos_.x, sprite_pos_.y, 0.0f));
	//sprite_.set_width(256.0f);
	//sprite_.set_height(512.0f);
	//SetSpriteSizeAndPositionForFrame(&sprite_, sprite_pos_.x, sprite_pos_.y, &text_atlas, frame);

	//anim->SetSpriteSizeAndPositionForFrame(&sprite_, sprite_pos_.x, sprite_pos_.y, frame);
	//anim->Update(frame,&sprite_);

	character = new Character();
	character->LoadCharacter(this_s, 0, &platform_);
	character->Update(this_s, frame);
}

void SceneApp::CleanUp()
{
	//delete sprite_texture_;
	//sprite_texture_ = NULL;

	delete input_manager_;
	input_manager_ = NULL;

	CleanUpFont();

	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete character;
	character = NULL;

	//delete anim;
	//anim = NULL;
}

bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	animation_timer_ += frame_time;

	//SetSpriteSizeAndPositionForFrame(&sprite_, sprite_pos_.x, sprite_pos_.y, &text_atlas, frame);
	//anim->SetSpriteSizeAndPositionForFrame(&sprite_, sprite_pos_.x, sprite_pos_.y, frame);
	//Need to set this to be an animation frame rate
	if (animation_timer_ >= (1.f / /*anim->FrameRate*/character->animations.at(this_s)->FrameRate))
	{
		frame++;
		animation_timer_ = 0;
	}

	//Also need to set this to the animation duration
	if (frame >= /*anim->Duration*/character->animations.at(this_s)->Duration)
	{
		frame = 0;
	}

	character->Update(std::string(this_s), frame);
	//anim->Update(4, &sprite_);

	input_manager_->Update();

	return true;
}


//TextureAtlas* SceneApp::ReadTextureAtlasFromJSON(rapidjson::Document& tex_document)
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
//TexData* SceneApp::ReadSubtextureFromJSON(const rapidjson::Value& subtecture_array)
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
//void SceneApp::SetSpriteSizeAndPositionForFrame(gef::Sprite* sprite, float screen_x, float screen_y, TextureAtlas* texture_atlas,int frame)
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

//Need to move alot of this still
void SceneApp::Render()
{
	sprite_renderer_->Begin();

	//for (auto i : anim->bone_parts)
	//{
	//	gef::Matrix33 sprite_offset_transform_m;
	//	gef::Matrix33 world_bone_transforming_m;
	//	gef::Matrix33 sub_texture_transform_m;
	//	gef::Matrix33 local_home_transform_m;

	//	anim->RenderUpdate(sprite_pos_, sprite_,i, sprite_offset_transform_m, world_bone_transforming_m, sub_texture_transform_m, local_home_transform_m);

	//	//Doesnt actually spit out the new calculated values so they are all still null
	//	sprite_renderer_->DrawSprite(sprite_, sub_texture_transform_m * sprite_offset_transform_m * world_bone_transforming_m * anim->rig_transform_m_);
	//}

	//anim->Update(frame);
	//anim->Update(4, &sprite_);

	sprite_renderer_->DrawSprite(*character->Render(this_s));


	DrawHUD();
	sprite_renderer_->End();
}

void SceneApp::InitFont()
{
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SceneApp::CleanUpFont()
{
	delete font_;
	font_ = NULL;
}

void SceneApp::DrawHUD()
{
	if (font_)
	{
		// display frame rate
		font_->RenderText(sprite_renderer_, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
	}
}

