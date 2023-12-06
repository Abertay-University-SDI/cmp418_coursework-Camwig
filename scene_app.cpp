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
////#include "load_texture.h"
////#include "load_json.h"
//
//#include <iostream>
//#include <string>
//#include <fstream>
////#include "load_texture.h"
////#include "load_json.h"
//
//SceneApp::SceneApp(gef::Platform& platform) :
//	Application(platform),
//	sprite_renderer_(NULL),
//	input_manager_(NULL),
//	font_(NULL)
//	//sprite_texture_(NULL)
//{
//}
//
//void SceneApp::Init()
//{
//	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
//	InitFont();
//
//	animation_timer_ = 0;
//
//	//elapsed_time = 0;
//	//This is not correct for every animation just for this one
//	//sprite_speed = 1/30.0f;
//
//	frame = 0;
//
//	//this_s = "boy-attack";	
//	this_s = "Dragon";
//
//	//anim = new Anim(/*std::string("boy-attack_ske.json"), &platform_, &sprite_, this_s,frame*/);
//	//anim->Init(std::string("boy-attack_ske.json"), &platform_, &sprite_, this_s, frame);
//
//	// initialise input manager
//	input_manager_ = gef::InputManager::Create(platform_);
//	/*
//	sprite_texture_ = CreateTextureFromPNG("boy-attack_tex.png", platform_);
//
//	//std::ifstream ifs2("Dragon_ske.json");
//	//rapidjson::IStreamWrapper isw2(ifs2);
//	//rapidjson::Document doc_dragon_ske;
//	//doc_dragon_ske.ParseStream(isw2);
//
//	//skin_slots = anim->ReadSkinSlotsDataFromJSON(doc_dragon_ske);
//	//bones_ = anim->ReadBonesFromJSON(doc_dragon_ske);
//
//	//new_anim = anim->ReadAnimationDataFromJSON(doc_dragon_ske);
//
//	//text_atlas = *anim->ReadTextureAtlasFromJSON(rapidjson_doc);
//	/////////////////////////////////
//	sprite_.set_texture(sprite_texture_);
//	*/
//
//	//anim->Load_sprite_and_texture_2(&platform_,&sprite_, this_s);
//	//anim->Load_sprite_and_texture_(&platform_,&sprite_);
//
//
//	//sprite_pos_ = gef::Vector2(platform_.width()*0.5f, platform_.height()*0.5f);
//
//	//sprite_.set_position(gef::Vector4(sprite_pos_.x, sprite_pos_.y, 0.0f));
//	//sprite_.set_width(256.0f);
//	//sprite_.set_height(512.0f);
//	//SetSpriteSizeAndPositionForFrame(&sprite_, sprite_pos_.x, sprite_pos_.y, &text_atlas, frame);
//
//	//anim->SetSpriteSizeAndPositionForFrame(&sprite_, sprite_pos_.x, sprite_pos_.y, frame);
//	//anim->Update(frame,&sprite_);
//
//	character = new Character();
//	//Could I glue the strings together in here and output that?
//	character->SetWhichAnimation("walk");
//	character->LoadCharacter(this_s, &platform_);
//	//---------------------------------------
//	character->SetAnimation(this_s, &platform_);
//
//	//character->SetWhichAnimation("stand");
//	//character->SetAnimation(this_s, &platform_);
//	character->Update(this_s, 0);
//}
//
//void SceneApp::CleanUp()
//{
//	//delete sprite_texture_;
//	//sprite_texture_ = NULL;
//
//	delete input_manager_;
//	input_manager_ = NULL;
//
//	CleanUpFont();
//
//	delete sprite_renderer_;
//	sprite_renderer_ = NULL;
//
//	delete character;
//	character = NULL;
//
//	//delete anim;
//	//anim = NULL;
//}
//
//bool SceneApp::Update(float frame_time)
//{
//	fps_ = 1.0f / frame_time;
//
//	animation_timer_ += frame_time;
//
//	//SetSpriteSizeAndPositionForFrame(&sprite_, sprite_pos_.x, sprite_pos_.y, &text_atlas, frame);
//	//anim->SetSpriteSizeAndPositionForFrame(&sprite_, sprite_pos_.x, sprite_pos_.y, frame);
//	//Need to set this to be an animation frame rate
//	if (animation_timer_ >= (1.f / /*anim->FrameRate*/character->animations.at(this_s)->FrameRate))
//	{
//		frame++;
//		animation_timer_ = 0;
//	}
//
//	//Also need to set this to the animation duration
//	if (frame >= /*anim->Duration*/character->animations.at(this_s)->Duration)
//	{
//		frame = 0;
//	}
//
//	character->Update(std::string(this_s), frame);
//	//anim->Update(4, &sprite_);
//
//	input_manager_->Update();
//
//	return true;
//}
//
//
////TextureAtlas* SceneApp::ReadTextureAtlasFromJSON(rapidjson::Document& tex_document)
////{
////	TextureAtlas* tex_atlas = new TextureAtlas();
////	tex_atlas->name_ = tex_document["name"].GetString();
////	tex_atlas->width_ = tex_document["width"].GetFloat();
////	tex_atlas->height_ = tex_document["height"].GetFloat();
////
////	const rapidjson::Value& subtexture_array = tex_document["SubTexture"];
////	for (int subtex_num = 0; subtex_num < (int)subtexture_array.Size(); ++subtex_num)
////	{
////		TexData* texdata = ReadSubtextureFromJSON(subtexture_array[subtex_num]);
////		tex_atlas->subtextures.push_back(*texdata);
////		delete texdata;
////	}
////
////	return tex_atlas;
////}
////
////TexData* SceneApp::ReadSubtextureFromJSON(const rapidjson::Value& subtecture_array)
////{
////	TexData* subTextData = new TexData;
////	subTextData->name_ = subtecture_array["name"].GetString();
////	subTextData->width_ = subtecture_array["width"].GetFloat();
////	subTextData->height_ = subtecture_array["height"].GetFloat();
////	subTextData->x_ = subtecture_array["x"].GetFloat();
////	subTextData->y_ = subtecture_array["y"].GetFloat();
////	subTextData->frame_x_ = subtecture_array["frameX"].GetFloat();
////	subTextData->frame_y_ = subtecture_array["frameY"].GetFloat();
////	subTextData->frame_width_ = subtecture_array["frameWidth"].GetFloat();
////	subTextData->frame_height_ = subtecture_array["frameHeight"].GetFloat();
////
////	return subTextData;
////}
////
////void SceneApp::SetSpriteSizeAndPositionForFrame(gef::Sprite* sprite, float screen_x, float screen_y, TextureAtlas* texture_atlas,int frame)
////{
////	float width = texture_atlas->subtextures.at(frame).width_;
////	float height = texture_atlas->subtextures.at(frame).height_;
////	float x = texture_atlas->subtextures.at(frame).x_;
////	float y = texture_atlas->subtextures.at(frame).y_;
////	float frame_width = texture_atlas->subtextures.at(frame).frame_width_;
////	float frame_height = texture_atlas->subtextures.at(frame).frame_height_;
////	float frame_x = texture_atlas->subtextures.at(frame).frame_x_;
////	float frame_y = texture_atlas->subtextures.at(frame).frame_y_;
////
////	sprite->set_width(width);
////	sprite->set_height(height);
////	sprite->set_uv_width(width / texture_atlas->width_);
////	sprite->set_uv_height(width / texture_atlas->height_);
////
////	float u = x / texture_atlas->width_;
////	float v = y / texture_atlas->height_;
////	sprite->set_uv_position(gef::Vector2(u, v));
////
////	float sprite_x = width * 0.5f - (frame_width * 0.5f + frame_x);
////	float sprite_y = height * 0.5f - (frame_height * 0.5f + frame_y);
////
////	sprite->set_position(gef::Vector4(screen_x + sprite_x, screen_y + sprite_y, 0.0f));
////}
//
////Need to move alot of this still
//void SceneApp::Render()
//{
//	sprite_renderer_->Begin();
//
//	//for (auto i : anim->bone_parts)
//	//{
//	//	gef::Matrix33 sprite_offset_transform_m;
//	//	gef::Matrix33 world_bone_transforming_m;
//	//	gef::Matrix33 sub_texture_transform_m;
//	//	gef::Matrix33 local_home_transform_m;
//
//	//	anim->RenderUpdate(sprite_pos_, sprite_,i, sprite_offset_transform_m, world_bone_transforming_m, sub_texture_transform_m, local_home_transform_m);
//
//	//	//Doesnt actually spit out the new calculated values so they are all still null
//		//sprite_renderer_->DrawSprite(sprite_, sub_texture_transform_m * sprite_offset_transform_m * world_bone_transforming_m * anim->rig_transform_m_);
//	//}
//
//	//anim->Update(frame);
//	//anim->Update(4, &sprite_);
//
//	//sprite_renderer_->DrawSprite(*character->Render(this_s));
//
//	//character->Update(std::string(this_s), frame);
//
//	if (character->Type == "Sheet")
//	{
//		for (auto part : character->bone_parts)
//		{
//			//std::string str = "tailTip";
//			// 
//			//something is up with the transform
//			sprite_renderer_->DrawSprite(*character->Render(this_s, part));
//		}
//	}
//	else
//	{
//		for (auto part : character->bone_parts)
//		{
//			//std::string str = "tailTip";
//			// 
//			//something is up with the transform
//			sprite_renderer_->DrawSprite(*character->Render(this_s, part), *character->Transform);
//		}
//	}
//
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
//	if (font_)
//	{
//		// display frame rate
//		font_->RenderText(sprite_renderer_, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
//	}
//}

#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/texture.h>
#include <graphics/mesh.h>
#include <graphics/primitive.h>
#include <assets/png_loader.h>
#include <graphics/image_data.h>
#include <graphics/font.h>
#include <maths/vector2.h>
#include <input/input_manager.h>
#include <input/sony_controller_input_manager.h>
#include <input/keyboard.h>
#include <maths/math_utils.h>
#include <graphics/renderer_3d.h>
#include <graphics/scene.h>
#include <animation/skeleton.h>
#include <animation/animation.h>

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	font_(NULL),
	//Can be its own thing
	mesh_(NULL),
	//Can be its own thing
	player_(NULL),
	renderer_3d_(NULL),
	model_scene_(NULL),
	//Can be turned into a base animation class
	walk_anim_(NULL),
	run_anim_(NULL),
	idle_anim_(NULL)
{
}

void SceneApp::Init()
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
	renderer_3d_ = gef::Renderer3D::Create(platform_);
	input_manager_ = gef::InputManager::Create(platform_);

	InitFont();
	SetupCamera();
	SetupLights();

	model_mesh_ = new ModelMesh;
	anim_ = new Animation;

	blend_tree_ = new BlendTree;


	// create a new scene object and read in the data from the file
	// no meshes or materials are created yet
	// we're not making any assumptions about what the data may be loaded in for
	model_scene_ = new gef::Scene();
	//model_scene_->ReadSceneFromFile(platform_, "tesla/tesla.scn");
	model_scene_->ReadSceneFromFile(platform_, model_mesh_->modelToLoad);

	// we do want to render the data stored in the scene file so lets create the materials from the material data present in the scene file
	model_scene_->CreateMaterials(platform_);

	// if there is mesh data in the scene, create a mesh to draw from the first mesh
	mesh_ = model_mesh_->CreateMeshData(model_scene_, platform_);//GetFirstMesh(model_scene_);

	// get the first skeleton in the scene
	gef::Skeleton* skeleton = model_mesh_->CreateSkeleton(model_scene_);//GetFirstSkeleton(model_scene_);

	if (skeleton)
	{
		player_ = new gef::SkinnedMeshInstance(*skeleton);
		anim_player_.Init(player_->bind_pose());
		walk_anim_player.Init(player_->bind_pose());
		run_anim_player.Init(player_->bind_pose());
		idle_anim_player.Init(player_->bind_pose());
		blended_pose = player_->bind_pose();
		player_->set_mesh(mesh_);
	}


	// anims
	//walk_anim_ = LoadAnimation("tesla/tesla@walk.scn", "");
	walk_anim_ = anim_->LoadAnimation(anim_->AnimToLoad, "", platform_);//LoadAnimation(AnimToLoad, "");

	run_anim_ = anim_->LoadAnimation(anim_->AnimToLoad2, "", platform_);

	idle_anim_ = anim_->LoadAnimation(anim_->AnimToLoad3, "", platform_);

	if (walk_anim_)
	{
		walk_anim_player.set_clip(walk_anim_);
		walk_anim_player.set_looping(true);
		walk_anim_player.set_anim_time(0.0f);
	}

	if (run_anim_)
	{
		run_anim_player.set_clip(run_anim_);
		run_anim_player.set_looping(true);
		run_anim_player.set_anim_time(0.0f);
	}

	if (idle_anim_)
	{
		idle_anim_player.set_clip(idle_anim_);
		idle_anim_player.set_looping(true);
		idle_anim_player.set_anim_time(0.0f);
	}

	min_walk_speed = 1.f;
	max_walk_speed = walk_anim_->duration() / run_anim_->duration();//run anim duration

	min_run_speed = run_anim_->duration() / walk_anim_->duration();
	max_run_speed = 1.f;

	speed_ = 0.0f;

	anim_blend = 0.f;

	anim_model_ = new AnimatedModel;

	anim_model_->Model_Name_ = "Manbot";
	anim_model_->Model_PathWay_ = "ybot/ybot.scn";

	PlayableAnim* play_anim_ = new PlayableAnim;
	play_anim_->Anim_Name_ = "Walk";
	play_anim_->Anim_Pathway_ = "ybot/ybot@walking_inplace.scn";
	play_anim_->Anim_max_speed_ = max_walk_speed;
	play_anim_->Anim_min_speed_ = min_walk_speed;
	play_anim_->Anim_speed = 1.0f;
	play_anim_->Anim_player_ = walk_anim_player;
	play_anim_->Anim_ = walk_anim_;

	anim_model_->Anim_map.insert(std::make_pair(play_anim_->Anim_Name_, *play_anim_));
	delete play_anim_;
	play_anim_ = NULL;

	InitBlendTree();
}


void SceneApp::CleanUp()
{
	CleanUpFont();

	delete player_;
	player_ = NULL;

	delete walk_anim_;
	walk_anim_ = NULL;

	delete run_anim_;
	run_anim_ = NULL;

	delete idle_anim_;
	idle_anim_ = NULL;

	delete mesh_;
	mesh_ = NULL;

	delete model_scene_;
	model_scene_ = NULL;

	delete input_manager_;
	input_manager_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete anim_model_;
	anim_model_ = NULL;

	delete blend_tree_;
	blend_tree_ = NULL;
}

bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	// read input devices
	if (input_manager_)
	{
		input_manager_->Update();

		// controller input
		gef::SonyControllerInputManager* controller_manager = input_manager_->controller_input();
		if (controller_manager)
		{
		}

		// keyboard input
		gef::Keyboard* keyboard = input_manager_->keyboard();
		if (keyboard)
		{
			float multiplier = 1.f;

			if (keyboard->IsKeyDown(keyboard->KC_LSHIFT)) {
				multiplier = 5.f;
			}

			if (keyboard->IsKeyDown(keyboard->KC_W)) {
				speed_ = (speed_ >= walk_speed) ? walk_speed : speed_ + 0.02f * multiplier;
			}

			if (keyboard->IsKeyDown(keyboard->KC_S)) {
				speed_ = (speed_ <= 0) ? 0 : speed_ - 0.02f * multiplier;
			}
		}
	}

	//if(player_)
	//{
	//	if (speed_ < anim_model_->Anim_map.at("Walk").Anim_min_speed_)
	//	{
	//		// update the pose in the anim player from the animation
	//		idle_anim_player.Update(frame_time, player_->bind_pose());

	//		// update the bone matrices that are used for rendering the character
	//		// from the newly updated pose in the anim player
	//		anim_blend = speed_;

	//		//Issue here
	//		player_->UpdateBoneMatrices(idle_anim_player.pose());
	//	}
	//	else
	//	{
	//		anim_model_->Anim_map.at("Walk").Anim_player_.Update(frame_time, player_->bind_pose());
	//		run_anim_player.Update(frame_time, player_->bind_pose());

	//		anim_blend = (speed_ - anim_model_->Anim_map.at("Walk").Anim_speed) / (run_speed - anim_model_->Anim_map.at("Walk").Anim_speed);

	//		float walk_speed_mod = (anim_model_->Anim_map.at("Walk").Anim_max_speed_ - anim_model_->Anim_map.at("Walk").Anim_min_speed_) * anim_blend;
	//		float run_speed_mod = (max_run_speed - min_run_speed) * anim_blend;

	//		anim_model_->Anim_map.at("Walk").Anim_player_.set_playback_speed(anim_model_->Anim_map.at("Walk").Anim_speed + walk_speed_mod);
	//		run_anim_player.set_playback_speed(min_run_speed + run_speed_mod);

	//		blended_pose.Linear2PoseBlend(anim_model_->Anim_map.at("Walk").Anim_player_.pose(),run_anim_player.pose(),anim_blend);
	//		player_->UpdateBoneMatrices(blended_pose);
	//	}
	//}

	if (player_)
	{
		//blend_tree_->variables[""]
		blend_tree_->variables["idle_anim_"] = speed_;
		blend_tree_->Update(frame_time);
		blended_pose = blend_tree_->output_.OutputPose_;

		player_->UpdateBoneMatrices(blended_pose);
	}

	// build a transformation matrix that will position the character
	// use this to move the player around, scale it, etc.
	if (player_)
	{
		gef::Matrix44 player_transform;
		gef::Matrix44 player_scale;
		gef::Matrix44 player_rotate;
		gef::Matrix44 player_translate;

		player_transform.SetIdentity();
		player_scale.SetIdentity();
		player_rotate.SetIdentity();
		player_translate.SetIdentity();

		player_scale.Scale(gef::Vector4(0.3f, 0.3f, 0.3f, 1.0f));
		player_rotate.RotationY(gef::DegToRad(45.0f));
		player_translate.SetTranslation(gef::Vector4(25.0f, -25.0f, -100.0f, 1.0f));

		player_transform = player_scale * player_rotate * player_translate;

		player_->set_transform(player_transform);
	}

	return true;
}

void SceneApp::Render()
{
	// setup view and projection matrices
	gef::Matrix44 projection_matrix;
	gef::Matrix44 view_matrix;
	projection_matrix = platform_.PerspectiveProjectionFov(camera_fov_, (float)platform_.width() / (float)platform_.height(), near_plane_, far_plane_);
	view_matrix.LookAt(camera_eye_, camera_lookat_, camera_up_);
	renderer_3d_->set_projection_matrix(projection_matrix);
	renderer_3d_->set_view_matrix(view_matrix);

	// draw meshes here
	renderer_3d_->Begin();

	// draw the player, the pose is defined by the bone matrices
	if (player_)
		renderer_3d_->DrawSkinnedMesh(*player_, player_->bone_matrices());

	renderer_3d_->End();

	// setup the sprite renderer, but don't clear the frame buffer
	// draw 2D sprites here
	sprite_renderer_->Begin(false);
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

void SceneApp::SetupLights()
{
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-300.0f, -500.0f, 100.0f));

	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();
	default_shader_data.set_ambient_light_colour(gef::Colour(0.5f, 0.5f, 0.5f, 1.0f));
	default_shader_data.AddPointLight(default_point_light);
}

void SceneApp::SetupCamera()
{
	// initialise the camera settings
	camera_eye_ = gef::Vector4(-1.0f, 1.0f, 4.0f);
	camera_lookat_ = gef::Vector4(0.0f, 1.0f, 0.0f);
	camera_up_ = gef::Vector4(0.0f, 1.0f, 0.0f);
	camera_fov_ = gef::DegToRad(45.0f);
	near_plane_ = 0.01f;
	far_plane_ = 1000.f;
}


void SceneApp::InitBlendTree()
{
	if (player_ && player_->bind_pose().skeleton())
	{
		blend_tree_->Init(player_->bind_pose());
		ClipNode* idle_clip = new ClipNode(blend_tree_);
		idle_clip->SetClip(idle_anim_);

		ClipNode* walk_clip = new ClipNode(blend_tree_);
		walk_clip->SetClip(anim_model_->Anim_map.at("Walk").Anim_);

		Linear2Blend* l2b = new Linear2Blend(blend_tree_);
		l2b->SetVariable(0, "idle_anim_");

		l2b->SetInput(0, idle_clip);
		l2b->SetInput(1, walk_clip);

		blend_tree_->output_.SetInput(0, l2b);

		blend_tree_->Start();
	}
}


