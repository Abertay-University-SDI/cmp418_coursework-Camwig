
//-----------------------------2D Version ----------------------------------------

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

//-----------------------------2D Version ----------------------------------------

//-----------------------------3D Version ----------------------------------------

//#include "scene_app.h"
//#include <system/platform.h>
//#include <graphics/sprite_renderer.h>
//#include <graphics/texture.h>
//#include <graphics/mesh.h>
//#include <graphics/primitive.h>
//#include <assets/png_loader.h>
//#include <graphics/image_data.h>
//#include <graphics/font.h>
//#include <maths/vector2.h>
//#include <input/input_manager.h>
//#include <input/sony_controller_input_manager.h>
//#include <input/keyboard.h>
////#include <maths/math_utils.h>
//#include <graphics/renderer_3d.h>
//#include <graphics/scene.h>
//#include <animation/skeleton.h>
//#include <animation/animation.h>
//
//SceneApp::SceneApp(gef::Platform& platform) :
//	Application(platform),
//	sprite_renderer_(NULL),
//	font_(NULL),
//	//Can be its own thing
//	//mesh_(NULL),
//	//Can be its own thing
//	//player_(NULL),
//	renderer_3d_(NULL),
//	model_scene_(NULL)
//	//Can be turned into a base animation class
//	//walk_anim_(NULL),
//	//run_anim_(NULL),
//	//idle_anim_(NULL)
//{
//}
//
//void SceneApp::Init()
//{
//	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
//	renderer_3d_ = gef::Renderer3D::Create(platform_);
//	input_manager_ = gef::InputManager::Create(platform_);
//
//	InitFont();
//	SetupCamera();
//	SetupLights();
//
//	model_mesh_ = new ModelMesh;
//	//anim_ = new ThisHereAnimation;
//
//	character_ = new ThreeDimensional_Character();
//
//	//blend_tree_ = new BlendTree;
//
//
//	// create a new scene object and read in the data from the file
//	// no meshes or materials are created yet
//	// we're not making any assumptions about what the data may be loaded in for
//	model_scene_ = new gef::Scene();
//	//model_scene_->ReadSceneFromFile(platform_, "tesla/tesla.scn");
//	model_scene_->ReadSceneFromFile(platform_, model_mesh_->modelToLoad);
//
//	// we do want to render the data stored in the scene file so lets create the materials from the material data present in the scene file
//	model_scene_->CreateMaterials(platform_);
//
//	//IN CHARACTER!!!---------------------
//	character_->Setup(model_mesh_,model_scene_,&platform_, "ybot/ybot.scn");
//
//
//	//Need this to hold multiple animations rather than the one!
//	character_->Init(model_mesh_, model_scene_, &platform_, AnimToLoad);
//	//character_->Init(model_mesh_, model_scene_, &platform_, AnimToLoad2);
//	character_->Init(model_mesh_, model_scene_, &platform_, AnimToLoad3);
//	//Need this to hold multiple animations rather than the one!
//
//
//	//max_walk_speed = walk_anim_->duration() / run_anim_->duration();//run anim duration
//	//character_->anim_model_->Anim_map.at(AnimToLoad).Anim_max_speed_ = character_->anim_model_->Anim_map.at(AnimToLoad).Anim_->duration() / character_->anim_model_->Anim_map.at(AnimToLoad2).Anim_->duration();
//	//min_run_speed = run_anim_->duration() / anim_model_->Anim_map.at("ybot/ybot").Anim_->duration();
//	//character_->anim_model_->Anim_map.at(AnimToLoad2).Anim_max_speed_ = character_->anim_model_->Anim_map.at(AnimToLoad2).Anim_->duration() / character_->anim_model_->Anim_map.at(AnimToLoad).Anim_->duration();
//
//	//InitBlendTree();
//	character_->AddBlendTree(tree_name_);
//	character_->InitBlendTree(tree_name_,AnimToLoad,AnimToLoad3);
//	//IN CHARACTER!!!---------------------
//
//	//Can move!-----------------------------------------------
//
//	//// if there is mesh data in the scene, create a mesh to draw from the first mesh
//	//anim_->mesh_ = model_mesh_->CreateMeshData(model_scene_, platform_);//GetFirstMesh(model_scene_);
//
//	//// get the first skeleton in the scene
//	//gef::Skeleton* skeleton = model_mesh_->CreateSkeleton(model_scene_);//GetFirstSkeleton(model_scene_);
//
//	//if (skeleton)
//	//{
//	//	player_1 = new gef::SkinnedMeshInstance(*skeleton);
//	//	anim_->anim_player_.Init(player_1->bind_pose());
//	//	anim_->walk_anim_player.Init(player_1->bind_pose());
//	//	anim_->run_anim_player.Init(player_1->bind_pose());
//	//	anim_->idle_anim_player.Init(player_1->bind_pose());
//	//	anim_->blended_pose = player_1->bind_pose();
//	//	player_1->set_mesh(anim_->mesh_);
//	//}
//
//
//	//// anims
//	////walk_anim_ = LoadAnimation("tesla/tesla@walk.scn", "");
//	//anim_->walk_anim_ = anim_->LoadAnimation(anim_->AnimToLoad, "", platform_);//LoadAnimation(AnimToLoad, "");
//
//	//anim_->run_anim_ = anim_->LoadAnimation(anim_->AnimToLoad2, "", platform_);
//
//	//anim_->idle_anim_ = anim_->LoadAnimation(anim_->AnimToLoad3, "", platform_);
//
//	//if (anim_->walk_anim_)
//	//{
//	//	anim_->walk_anim_player.set_clip(anim_->walk_anim_);
//	//	anim_->walk_anim_player.set_looping(true);
//	//	anim_->walk_anim_player.set_anim_time(0.0f);
//	//}
//
//	//if (anim_->run_anim_)
//	//{
//	//	anim_->run_anim_player.set_clip(anim_->run_anim_);
//	//	anim_->run_anim_player.set_looping(true);
//	//	anim_->run_anim_player.set_anim_time(0.0f);
//	//}
//
//	//if (anim_->idle_anim_)
//	//{
//	//	anim_->idle_anim_player.set_clip(anim_->idle_anim_);
//	//	anim_->idle_anim_player.set_looping(true);
//	//	anim_->idle_anim_player.set_anim_time(0.0f);
//	//}
//
//	//anim_->min_walk_speed = 1.f;
//	//anim_->max_walk_speed = anim_->walk_anim_->duration() / anim_->run_anim_->duration();//run anim duration
//
//	//anim_->min_run_speed = anim_->run_anim_->duration() / anim_->walk_anim_->duration();
//	//anim_->max_run_speed = 1.f;
//
//	//anim_->speed_ = 0.0f;
//
//	//anim_->anim_blend = 0.f;
//
//	//anim_model_ = new AnimatedModel;
//
//	//anim_model_->Model_Name_ = "Manbot";
//	//anim_model_->Model_PathWay_ = "ybot/ybot.scn";
//
//	//PlayableAnim* play_anim_ = new PlayableAnim;
//	//play_anim_->Anim_Name_ = "Walk";
//	//play_anim_->Anim_Pathway_ = "ybot/ybot@walking_inplace.scn";
//	//play_anim_->Anim_max_speed_ = anim_->max_walk_speed;
//	//play_anim_->Anim_min_speed_ = anim_->min_walk_speed;
//	//play_anim_->Anim_speed = 1.0f;
//	//play_anim_->Anim_player_ = anim_->walk_anim_player;
//	//play_anim_->Anim_ = anim_->walk_anim_;
//
//	//anim_model_->Anim_map.insert(std::make_pair(play_anim_->Anim_Name_, *play_anim_));
//	//delete play_anim_;
//	//play_anim_ = NULL;
//
//	//InitBlendTree();
//
//	//-------------------------------------------------
//}
//
//
//void SceneApp::CleanUp()
//{
//	CleanUpFont();
//
//	//delete player_;
//	//player_ = NULL;
//
//	//delete walk_anim_;
//	//walk_anim_ = NULL;
//
//	//delete run_anim_;
//	//run_anim_ = NULL;
//
//	//delete idle_anim_;
//	//idle_anim_ = NULL;
//
//	//delete mesh_;
//	//mesh_ = NULL;
//
//	delete model_scene_;
//	model_scene_ = NULL;
//
//	delete input_manager_;
//	input_manager_ = NULL;
//
//	delete sprite_renderer_;
//	sprite_renderer_ = NULL;
//
//	delete renderer_3d_;
//	renderer_3d_ = NULL;
//
//	//delete anim_model_;
//	//anim_model_ = NULL;
//
//	//delete blend_tree_;
//	//blend_tree_ = NULL;
//}
//
//bool SceneApp::Update(float frame_time)
//{
//	fps_ = 1.0f / frame_time;
//
//	// read input devices
//	if (input_manager_)
//	{
//		input_manager_->Update();
//
//		// controller input
//		gef::SonyControllerInputManager* controller_manager = input_manager_->controller_input();
//		if (controller_manager)
//		{
//		}
//
//		// keyboard input
//		gef::Keyboard* keyboard = input_manager_->keyboard();
//		if (keyboard)
//		{
//			float multiplier = 1.f;
//
//			if (keyboard->IsKeyDown(keyboard->KC_LSHIFT)) {
//				multiplier = 5.f;
//			}
//
//			if (keyboard->IsKeyDown(keyboard->KC_W)) {
//				character_->speed_ = (character_->speed_ >= character_->anim_model_.Anim_map.at(AnimToLoad).Anim_min_speed_) ? character_->anim_model_.Anim_map.at(AnimToLoad).Anim_min_speed_ : character_->speed_ + 0.02f * multiplier;
//			}
//
//			if (keyboard->IsKeyDown(keyboard->KC_S)) {
//				character_->speed_ = (character_->speed_ <= 0) ? 0 : character_->speed_ - 0.02f * multiplier;
//			}
//		}
//	}
//
//	character_->NewUpdate(frame_time, tree_name_);
//
//	//IN CHARACTER!!!---------------------
//	//anim_->Update(frame_time);
//	//IN CHARACTER!!!---------------------
//
//	//Can move!-----------------------------------------------
//
//	//if (player_)
//	//{
//	//	//blend_tree_->variables[""]
//	//	blend_tree_->variables["idle_anim_"] = speed_;
//	//	blend_tree_->Update(frame_time);
//	//	blended_pose = blend_tree_->output_.OutputPose_;
//
//	//	player_->UpdateBoneMatrices(blended_pose);
//	//}
//
//	//// build a transformation matrix that will position the character
//	//// use this to move the player around, scale it, etc.
//	//if (player_)
//	//{
//	//	gef::Matrix44 player_transform;
//	//	gef::Matrix44 player_scale;
//	//	gef::Matrix44 player_rotate;
//	//	gef::Matrix44 player_translate;
//
//	//	player_transform.SetIdentity();
//	//	player_scale.SetIdentity();
//	//	player_rotate.SetIdentity();
//	//	player_translate.SetIdentity();
//
//	//	player_scale.Scale(gef::Vector4(0.3f, 0.3f, 0.3f, 1.0f));
//	//	player_rotate.RotationY(gef::DegToRad(45.0f));
//	//	player_translate.SetTranslation(gef::Vector4(25.0f, -25.0f, -100.0f, 1.0f));
//
//	//	player_transform = player_scale * player_rotate * player_translate;
//
//	//	player_->set_transform(player_transform);
//	//}
//
//	return true;
//}
//
//void SceneApp::Render()
//{
//	// setup view and projection matrices
//	gef::Matrix44 projection_matrix;
//	gef::Matrix44 view_matrix;
//	projection_matrix = platform_.PerspectiveProjectionFov(camera_fov_, (float)platform_.width() / (float)platform_.height(), near_plane_, far_plane_);
//	view_matrix.LookAt(camera_eye_, camera_lookat_, camera_up_);
//	renderer_3d_->set_projection_matrix(projection_matrix);
//	renderer_3d_->set_view_matrix(view_matrix);
//
//	// draw meshes here
//	renderer_3d_->Begin();
//
//	// draw the player, the pose is defined by the bone matrices
//	if (character_->player_)
//		renderer_3d_->DrawSkinnedMesh(*character_->player_, character_->player_->bone_matrices());
//
//	renderer_3d_->End();
//
//	// setup the sprite renderer, but don't clear the frame buffer
//	// draw 2D sprites here
//	sprite_renderer_->Begin(false);
//	DrawHUD();
//	sprite_renderer_->End();
//}
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
//
//void SceneApp::SetupLights()
//{
//	gef::PointLight default_point_light;
//	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
//	default_point_light.set_position(gef::Vector4(-300.0f, -500.0f, 100.0f));
//
//	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();
//	default_shader_data.set_ambient_light_colour(gef::Colour(0.5f, 0.5f, 0.5f, 1.0f));
//	default_shader_data.AddPointLight(default_point_light);
//}
//
//void SceneApp::SetupCamera()
//{
//	// initialise the camera settings
//	camera_eye_ = gef::Vector4(-1.0f, 1.0f, 4.0f);
//	camera_lookat_ = gef::Vector4(0.0f, 1.0f, 0.0f);
//	camera_up_ = gef::Vector4(0.0f, 1.0f, 0.0f);
//	camera_fov_ = gef::DegToRad(45.0f);
//	near_plane_ = 0.01f;
//	far_plane_ = 1000.f;
//}
//
////Can move!-----------------------------------------------
////void SceneApp::InitBlendTree()
////{
////	if (player_1 && player_1->bind_pose().skeleton())
////	{
////		anim_->blend_tree_->Init(player_1->bind_pose());
////		ClipNode* idle_clip = new ClipNode(anim_->blend_tree_);
////		idle_clip->SetClip(anim_->idle_anim_);
////
////		ClipNode* walk_clip = new ClipNode(anim_->blend_tree_);
////		walk_clip->SetClip(anim_model_->Anim_map.at("Walk").Anim_);
////
////		Linear2Blend* l2b = new Linear2Blend(anim_->blend_tree_);
////		l2b->SetVariable(0, "idle_anim_");
////
////		l2b->SetInput(0, idle_clip);
////		l2b->SetInput(1, walk_clip);
////
////		anim_->blend_tree_->output_.SetInput(0, l2b);
////
////		anim_->blend_tree_->Start();
////	}
////}

//-----------------------------3D Version ----------------------------------------

//-----------------------------Ragdoll Version ----------------------------------------

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
#include <system/debug_log.h>
#include "ragdoll.h"

//std::string model_name("xbot");


SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	font_(NULL),
	renderer_3d_(NULL),
	model_scene_(NULL),
	primitive_builder_(NULL),
	primitive_renderer_(NULL),
	dynamics_world_(NULL),
	solver_(NULL),
	overlapping_pair_cache_(NULL),
	dispatcher_(NULL),
	debug_drawer_(NULL),
	floor_mesh_(NULL),
	sphere_mesh_(NULL),
	sphere_rb_(NULL),
	character_(NULL),
	Sprite_character_(NULL),
	Sprite_character_2_(NULL)
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

	// create a new scene object and read in the data from the file
	// no meshes or materials are created yet
	// we're not making any assumptions about what the data may be loaded in for

	animation_timer_ = 0;
	animation_timer_2 = 0;

	frame = 0;
	frame2 = 0;

	this_s = "xbot";
	sprite_name_2_ = "boy-attack";	
	sprite_name_ = "Dragon";

	Sprite_character_ = new Character();
	Sprite_character_->SetWhichAnimation("walk");
	gef::Vector2 size = gef::Vector2(256.0f, 512.0f);
	gef::Vector2 pos = gef::Vector2(platform_.width() * 0.25f, platform_.height() * 0.5f);
	Sprite_character_->LoadCharacter(sprite_name_, &platform_, size,pos,0.40f);
	Sprite_character_->SetAnimation(sprite_name_, &platform_);
	Sprite_character_->Update(sprite_name_, 0);

	Sprite_character_2_ = new Character();
	size = gef::Vector2(256.0f, 512.0f);
	pos = gef::Vector2(platform_.width() * 0.75f, platform_.height() * 0.5f);
	Sprite_character_2_->LoadCharacter(sprite_name_2_, &platform_, size, pos, 0.40f);
	Sprite_character_2_->SetAnimation(sprite_name_2_, &platform_);
	Sprite_character_2_->Update(sprite_name_2_, 0);

	//std::string model_scene_name = this_s + "/" + this_s + ".scn";

	model_mesh_ = new ModelMesh;

	model_scene_ = new gef::Scene();
	//model_scene_->ReadSceneFromFile(platform_, model_scene_name.c_str());
	model_scene_->ReadSceneFromFile(platform_, model_mesh_->modelToLoad);

	// we do want to render the data stored in the scene file so lets create the materials from the material data present in the scene file
	model_scene_->CreateMaterials(platform_);

	character_ = new ThreeDimensional_Character();

	character_->Setup(model_mesh_, model_scene_, &platform_, this_s);
	character_->Init(model_mesh_, model_scene_, &platform_, AnimToLoad3);
	character_->Init(model_mesh_, model_scene_, &platform_, AnimToLoad);

	character_->AddBlendTree(tree_name_);
	character_->InitBlendTree(tree_name_,AnimToLoad,AnimToLoad3);

	//Can be in 3D Character!------------------------------------

	//// if there is mesh data in the scene, create a mesh to draw from the first mesh
	//mesh_ = GetFirstMesh(model_scene_);

	//// get the first skeleton in the scene
	//gef::Skeleton* skeleton = GetFirstSkeleton(model_scene_);

	//if (skeleton)
	//{
	//	player_ = new gef::SkinnedMeshInstance(*skeleton);
	//	player_->set_mesh(mesh_);
	//	player_->UpdateBoneMatrices(player_->bind_pose());

	//	// output skeleton joint names
	//	for (int joint_num = 0; joint_num < skeleton->joints().size(); ++joint_num)
	//	{
	//		std::string bone_name;
	//		model_scene_->string_id_table.Find(skeleton->joint(joint_num).name_id, bone_name);
	//		gef::DebugOut("%d: %s\n", joint_num, bone_name.c_str());
	//	}

	//	// animated model is scaled down to match the size of the physics ragdoll
	//	gef::Matrix44 player_transform;
	//	const float scale = 0.01f;
	//	player_transform.Scale(gef::Vector4(scale, scale, scale));
	//	player_->set_transform(player_transform);
	//}


	// anims

		//All animation setup---------------------------------------------------------------
		//std::string walk_anim_name = model_name + "/" + model_name + "@walking_inplace.scn";
		//std::string run_anim_name = model_name + "/" + model_name + "@running_inplace.scn";
		//std::string idle_anim_name = model_name + "/" + model_name + "@idle.scn";


		//walk_anim_ = LoadAnimation(walk_anim_name.c_str(), "");
		//run_anim_ = LoadAnimation(run_anim_name.c_str(), "");
		//idle_anim_ = LoadAnimation(idle_anim_name.c_str(), "");

		//clip_player_.Init(player_->bind_pose());
		//clip_player_.set_clip(idle_anim_);
		//clip_player_.set_looping(true);
		//clip_player_.set_anim_time(0.0f);
		//All animation setup---------------------------------------------------------------

	primitive_builder_ = new PrimitiveBuilder(platform_);
	primitive_renderer_ = new PrimitiveRenderer(platform_);

	InitPhysicsWorld();
	CreateRigidBodies();

	//InitRagdoll();

	//character_->InitRagdoll(dynamics_world_, this_s,is_ragdoll_simulating_);
	character_->SetupRagdoll(is_ragdoll_simulating_, dynamics_world_);

	//Can be in 3D Character!------------------------------------
}

//Can be in 3D Character!------------------------------------
//void SceneApp::InitRagdoll()
//{
//	if (player_->bind_pose().skeleton())
//	{
//		ragdoll_ = new Ragdoll();
//		ragdoll_->set_scale_factor(0.01f);
//
//		std::string ragdoll_filename;
//		ragdoll_filename = model_name + "/ragdoll.bullet";
//
//		ragdoll_->Init(player_->bind_pose(), dynamics_world_, ragdoll_filename.c_str());
//	}
//
//	is_ragdoll_simulating_ = false;
//}
//Can be in 3D Character!------------------------------------

void SceneApp::CleanUp()
{
	CleanUpRigidBodies();

	CleanUpPhysicsWorld();

	CleanUpFont();

	delete primitive_renderer_;
	primitive_renderer_ = NULL;

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete model_scene_;
	model_scene_ = NULL;

	delete input_manager_;
	input_manager_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete character_;
	character_ = NULL;

	delete Sprite_character_;
	Sprite_character_ = NULL;

	delete Sprite_character_2_;
	Sprite_character_2_ = NULL;
}

bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	//----------------------------------Should be in 2D Character------------------------------------

	animation_timer_ += frame_time;
	animation_timer_2 += frame_time;

	if (animation_timer_ >= (1.f / /*anim->FrameRate*/Sprite_character_->animations.at(sprite_name_)->FrameRate))
	{
		frame++;
		animation_timer_ = 0;
	}

	//Also need to set this to the animation duration
	if (frame >= /*anim->Duration*/Sprite_character_->animations.at(sprite_name_)->Duration)
	{
		frame = 0;
	}

	if (animation_timer_2 >= (1.f / /*anim->FrameRate*/Sprite_character_2_->animations.at(sprite_name_2_)->FrameRate))
	{
		frame2++;
		animation_timer_2 = 0;
	}

	//Also need to set this to the animation duration
	if (frame2 >= /*anim->Duration*/Sprite_character_2_->animations.at(sprite_name_2_)->Duration)
	{
		frame2 = 0;
	}

	Sprite_character_->Update(std::string(sprite_name_), frame);
	Sprite_character_2_->Update(std::string(sprite_name_2_), frame2);

	//----------------------------------Should be in 2D Character------------------------------------

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
			if (keyboard->IsKeyPressed(gef::Keyboard::KC_SPACE))
			{
				is_ragdoll_simulating_ = !is_ragdoll_simulating_;
			}

			float multiplier = 1.f;

			if (keyboard->IsKeyDown(keyboard->KC_LSHIFT)) {
				multiplier = 5.f;
			}

			if (keyboard->IsKeyDown(keyboard->KC_W)) {
				character_->speed_ = (character_->speed_ >= character_->anim_model_.Anim_map.at(AnimToLoad).Anim_min_speed_) ? character_->anim_model_.Anim_map.at(AnimToLoad).Anim_min_speed_ : character_->speed_ + 0.02f * multiplier;
			}

			if (keyboard->IsKeyDown(keyboard->KC_S)) {
				character_->speed_ = (character_->speed_ <= 0) ? 0 : character_->speed_ - 0.02f * multiplier;
			}
		}
	}

	//	if (input_manager_)
//	{
//		input_manager_->Update();
//
//		// controller input
//		gef::SonyControllerInputManager* controller_manager = input_manager_->controller_input();
//		if (controller_manager)
//		{
//		}
//
//		// keyboard input
//		gef::Keyboard* keyboard = input_manager_->keyboard();
//		if (keyboard)
//		{
//			float multiplier = 1.f;
//
//			if (keyboard->IsKeyDown(keyboard->KC_LSHIFT)) {
//				multiplier = 5.f;
//			}
//
//			if (keyboard->IsKeyDown(keyboard->KC_W)) {
//				character_->speed_ = (character_->speed_ >= character_->anim_model_.Anim_map.at(AnimToLoad).Anim_min_speed_) ? character_->anim_model_.Anim_map.at(AnimToLoad).Anim_min_speed_ : character_->speed_ + 0.02f * multiplier;
//			}
//
//			if (keyboard->IsKeyDown(keyboard->KC_S)) {
//				character_->speed_ = (character_->speed_ <= 0) ? 0 : character_->speed_ - 0.02f * multiplier;
//			}
//		}
//	}

	//Can be in 3D Character!------------------------------------

	// update the current animation that is playing
	if (character_->player_)
	{
		character_->TreeUpdate(frame_time, tree_name_);
		//character_->AnimUpdate(frame_time,AnimToLoad);
		character_->UpdateCurrentPoseBoneMatrices_();
		//Need to give this the current pose from the blend tree
		//character_->player_->UpdateBoneMatrices(character_->anim_model_.Anim_map.at(AnimToLoad3).Anim_player_.pose());
	}

	//character_->NewUpdate(frame_time, tree_name_);

	//This is the only one that might be a problem
	UpdatePhysicsWorld(frame_time);

	//The blow only effects the sphere
	UpdateRigidBodies();

	//character_->UpdateRagdoll(is_ragdoll_simulating_,AnimToLoad3);
	character_->CallUpdateRagdoll(is_ragdoll_simulating_);

	//if (player_ && ragdoll_)
	//{
	//	if (is_ragdoll_simulating_)
	//	{
	//		ragdoll_->UpdatePoseFromRagdoll();
	//		player_->UpdateBoneMatrices(ragdoll_->pose());
	//	}
	//	else
	//	{
	//		ragdoll_->set_pose(clip_player_.pose());
	//		ragdoll_->UpdateRagdollFromPose();
	//	}
	//}

	//Can be in 3D Character!------------------------------------

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
	if (character_->player_)
	{
		renderer_3d_->DrawSkinnedMesh(*character_->player_, character_->player_->bone_matrices());
	}

	renderer_3d_->DrawMesh(floor_gfx_);
	renderer_3d_->DrawMesh(sphere_gfx_);

	if (dynamics_world_)
		dynamics_world_->debugDrawWorld();

	renderer_3d_->End();

	// setup the sprite renderer, but don't clear the frame buffer
	// draw 2D sprites here
	sprite_renderer_->Begin(false);

	//----------------------------------Should be in 2D Character------------------------------------
	if (Sprite_character_->Type == "Sheet")
	{
		for (auto part : Sprite_character_->bone_parts)
		{
			//std::string str = "tailTip";
			// 
			//something is up with the transform
			sprite_renderer_->DrawSprite(*Sprite_character_->Render(sprite_name_, part));
		}
	}
	else
	{
		for (auto part : Sprite_character_->bone_parts)
		{
			//std::string str = "tailTip";
			// 
			//something is up with the transform
			sprite_renderer_->DrawSprite(*Sprite_character_->Render(sprite_name_, part), *Sprite_character_->Transform);
		}
	}

	if (Sprite_character_2_->Type == "Sheet")
	{
		for (auto part2 : Sprite_character_2_->bone_parts)
		{
			//std::string str = "tailTip";
			// 
			//something is up with the transform
			sprite_renderer_->DrawSprite(*Sprite_character_2_->Render(sprite_name_2_, part2));
		}
	}
	else
	{
		for (auto part2 : Sprite_character_2_->bone_parts)
		{
			//std::string str = "tailTip";
			// 
			//something is up with the transform
			sprite_renderer_->DrawSprite(*Sprite_character_2_->Render(sprite_name_2_, part2), *Sprite_character_2_->Transform);
		}
	}
	//----------------------------------Should be in 2D Character------------------------------------

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
	camera_eye_ = gef::Vector4(0.0f, 2.0f, 5.0f);
	camera_lookat_ = gef::Vector4(0.0f, 0.0f, 0.0f);
	camera_up_ = gef::Vector4(0.0f, 1.0f, 0.0f);
	camera_fov_ = gef::DegToRad(45.0f);
	near_plane_ = 0.01f;
	far_plane_ = 100.0f;
}


//Can be in 3D Character!------------------------------------
//gef::Skeleton* SceneApp::GetFirstSkeleton(gef::Scene* scene)
//{
//	gef::Skeleton* skeleton = NULL;
//	if (scene)
//	{
//		// check to see if there is a skeleton in the the scene file
//		// if so, pull out the bind pose and create an array of matrices
//		// that wil be used to store the bone transformations
//		if (scene->skeletons.size() > 0)
//			skeleton = scene->skeletons.front();
//	}
//
//	return skeleton;
//}
//Can be in 3D Character!------------------------------------

//Can be in 3D Character!------------------------------------
//gef::Mesh* SceneApp::GetFirstMesh(gef::Scene* scene)
//{
//	gef::Mesh* mesh = NULL;
//
//	if (scene)
//	{
//		// now check to see if there is any mesh data in the file, if so lets create a mesh from it
//		if (scene->mesh_data.size() > 0)
//			mesh = model_scene_->CreateMesh(platform_, scene->mesh_data.front());
//	}
//
//	return mesh;
//}
//Can be in 3D Character!------------------------------------

//Can be in 3D Character!------------------------------------
//gef::Animation* SceneApp::LoadAnimation(const char* anim_scene_filename, const char* anim_name)
//{
//	gef::Animation* anim = NULL;
//
//	gef::Scene anim_scene;
//	if (anim_scene.ReadSceneFromFile(platform_, anim_scene_filename))
//	{
//		// if the animation name is specified then try and find the named anim
//		// otherwise return the first animation if there is one
//		std::map<gef::StringId, gef::Animation*>::const_iterator anim_node_iter;
//		if (anim_name)
//			anim_node_iter = anim_scene.animations.find(gef::GetStringId(anim_name));
//		else
//			anim_node_iter = anim_scene.animations.begin();
//
//		if (anim_node_iter != anim_scene.animations.end())
//			anim = new gef::Animation(*anim_node_iter->second);
//	}
//
//	return anim;
//}
//Can be in 3D Character!------------------------------------

void SceneApp::InitPhysicsWorld()
{
	/// collision configuration contains default setup for memory , collision setup . Advanced users can create their own configuration .
	btDefaultCollisionConfiguration* collision_configuration = new btDefaultCollisionConfiguration();

	/// use the default collision dispatcher . For parallel processing you can use a diffent dispatcher(see Extras / BulletMultiThreaded)
	dispatcher_ = new btCollisionDispatcher(collision_configuration);

	/// btDbvtBroadphase is a good general purpose broadphase . You can also try out btAxis3Sweep .
	overlapping_pair_cache_ = new btDbvtBroadphase();

	/// the default constraint solver . For parallel processing you can use a different solver (see Extras / BulletMultiThreaded)
	solver_ = new btSequentialImpulseConstraintSolver;

	dynamics_world_ = new btDiscreteDynamicsWorld(dispatcher_, overlapping_pair_cache_, solver_, collision_configuration);
	dynamics_world_->setGravity(btVector3(0, -9.8f, 0));


	debug_drawer_ = new GEFDebugDrawer(renderer_3d_);
	debug_drawer_->setDebugMode(btIDebugDraw::DBG_DrawAabb | btIDebugDraw::DBG_DrawFrames);
	dynamics_world_->setDebugDrawer(debug_drawer_);
}

void SceneApp::CleanUpPhysicsWorld()
{
	delete debug_drawer_;
	debug_drawer_ = NULL;

	for (int i = dynamics_world_->getNumConstraints() - 1; i >= 0; i--)
	{
		btTypedConstraint* constraint = dynamics_world_->getConstraint(i);
		dynamics_world_->removeConstraint(constraint);
		delete constraint;
	}


	// remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamics_world_->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamics_world_->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamics_world_->removeCollisionObject(obj);
		delete obj;
	}

	// delete collision shapes
	for (int j = 0; j < collision_shapes_.size(); j++)
	{
		btCollisionShape* shape = collision_shapes_[j];
		collision_shapes_[j] = 0;
		delete shape;
	}

	// delete dynamics world
	delete dynamics_world_;

	// delete solver
	delete solver_;

	// delete broadphase
	delete overlapping_pair_cache_;

	// delete dispatcher
	delete dispatcher_;

	dynamics_world_ = NULL;
	solver_ = NULL;
	overlapping_pair_cache_ = NULL;
	dispatcher_ = NULL;

	// next line is optional : it will be cleared by the destructor when the array goes out of scope
	collision_shapes_.clear();
}

void SceneApp::UpdatePhysicsWorld(float delta_time)
{
	const btScalar simulation_time_step = 1.0f / 60.0f;
	const int max_sub_steps = 1;
	dynamics_world_->stepSimulation(simulation_time_step, max_sub_steps);
}

//Can get rid of the sphere that falls!---------------------------------------

void SceneApp::CreateRigidBodies()
{
	//the ground is a cube of side 100 at position y = 0.
	{
		btVector3 groundHalfExtents(btScalar(50.), btScalar(1.), btScalar(50.));
		btCollisionShape* groundShape = new btBoxShape(groundHalfExtents);

		collision_shapes_.push_back(groundShape);

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -groundHalfExtents.y(), 0));

		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass, localInertia);

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		dynamics_world_->addRigidBody(body);

		floor_mesh_ = primitive_builder_->CreateBoxMesh(gef::Vector4(groundHalfExtents.x(), groundHalfExtents.y(), groundHalfExtents.z()));
		floor_gfx_.set_mesh(floor_mesh_);
		floor_gfx_.set_transform(btTransform2Matrix(groundTransform));
	}

	//	if(0)
	{
		//create a dynamic rigidbody

		const btScalar  sphereRadius = 1.f;
		btCollisionShape* colShape = new btSphereShape(sphereRadius);

		collision_shapes_.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass(1.f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);

		startTransform.setOrigin(btVector3(2, 10, 0));

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		dynamics_world_->addRigidBody(body);

		sphere_rb_ = body;
		sphere_mesh_ = primitive_builder_->CreateSphereMesh(sphereRadius, 20, 20);
		sphere_gfx_.set_mesh(sphere_mesh_);
		sphere_gfx_.set_transform(btTransform2Matrix(startTransform));
	}
}

void SceneApp::CleanUpRigidBodies()
{
	delete sphere_mesh_;
	sphere_mesh_ = NULL;
	delete floor_mesh_;
	floor_mesh_ = NULL;
}

void SceneApp::UpdateRigidBodies()
{
	if (sphere_rb_)
	{
		btTransform world_transform;
		sphere_rb_->getMotionState()->getWorldTransform(world_transform);
		sphere_gfx_.set_transform(btTransform2Matrix(world_transform));
	}
}

//Can get rid of the sphere that falls!---------------------------------------

//-----------------------------Ragdoll Version ----------------------------------------