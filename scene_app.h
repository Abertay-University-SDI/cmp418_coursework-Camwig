//#ifndef _SCENE_APP_H
//#define _SCENE_APP_H
//
//#include <system/application.h>
//#include <maths/vector2.h>
////#include <graphics/sprite.h>
//#include "maths/math_utils.h"
//#include <input/input_manager.h>
////#include <vector>
//
////#include <TexData.h>
////#include <TextureAtlas.h>
//
////#include <Anim.h>
//
////#include <TexData.h>
////#include <TextureAtlas.h>
////#include <SkinSlot.h>
////#include <Bone.h>
////#include <Animation_Parser.h>
//
////#include "rapidjson\document.h"
////#include "rapidjson/istreamwrapper.h"
//
////#include "TempSkeletalAnim.h"
//
//#include "Character.h"
//
//
//// FRAMEWORK FORWARD DECLARATIONS
//namespace gef
//{
//	class Platform;
//	class SpriteRenderer;
//	class Font;
//	class InputManager;
//}
//
//class SceneApp : public gef::Application
//{
//public:
//	SceneApp(gef::Platform& platform);
//	void Init();
//	void CleanUp();
//	bool Update(float frame_time);
//	void Render();
//private:
//	void InitFont();
//	void CleanUpFont();
//	void DrawHUD();
//
//	//void SetSpriteSizeAndPositionForFrame(gef::Sprite*,float,float,TextureAtlas*,int);
//
//	/*TextureAtlas* ReadTextureAtlasFromJSON(rapidjson::Document& tex_document);
//	TexData* ReadSubtextureFromJSON(const rapidjson::Value&);*/
//
//	gef::SpriteRenderer* sprite_renderer_;
//	gef::Font* font_;
//	gef::InputManager* input_manager_;
//
//	//gef::Texture* sprite_texture_;
//	//gef::Sprite sprite_;
//
//	//std::map<std::string,SkinSlot> skin_slots;
//	//std::map<std::string, Bone> bones_;
//
//	float fps_;
//
//
//	float animation_timer_;
//	int frame;
//
//	//TextureAtlas text_atlas;
//
//	//Anim* anim;
//
//	Character* character;
//
//	std::string this_s;
//
//	//TextureAtlas text_atlas;
//
//	//gef::Vector2 sprite_pos_;
//
//	//const float scale = 0.5f;
//
//	//gef::Matrix33 rig_transform_m_;
//	//gef::Matrix33 combined_transform_m_;
//
//
//	//Animation_Parser* anim_pars;
//
//	//TempSkeletalAnim* anim;
//
//};
//
//#endif // _SCENE_APP_H

#ifndef _ANIMATED_MESH_APP_H
#define _ANIMATED_MESH_APP_H

#include <system/application.h>
#include <graphics/sprite.h>
#include <maths/vector2.h>
#include <maths/vector4.h>
#include <maths/matrix44.h>
#include <vector>
#include <graphics/skinned_mesh_instance.h>
#include "motion_clip_player.h"
#include "ModelMesh.h"
#include "ThisHereAnimation.h"

#include "AnimatedModel.h"

#include "BlendTree.h"
#include "ClipNode.h"
#include "Linear2Blend.h"


// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class Renderer3D;
	class Mesh;
	class Scene;
	class Skeleton;
	class InputManager;
}

class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	void Init();

	//gef::Skeleton* GetFirstSkeleton(gef::Scene* scene);

	//gef::Mesh* GetFirstMesh(gef::Scene* scene);

	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();
	void SetupLights();
	void SetupCamera();

	void InitBlendTree();
	//gef::Animation* LoadAnimation(const char* anim_scene_filename, const char* anim_name);

	AnimatedModel* anim_model_;

	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;
	gef::InputManager* input_manager_;
	gef::Font* font_;

	float fps_;

	class gef::Mesh* mesh_;
	gef::SkinnedMeshInstance* player_;

	gef::Scene* model_scene_;

	gef::Vector4 camera_eye_;
	gef::Vector4 camera_lookat_;
	gef::Vector4 camera_up_;
	float camera_fov_;
	float near_plane_;
	float far_plane_;

	MotionClipPlayer anim_player_;

	gef::Animation* walk_anim_;
	MotionClipPlayer walk_anim_player;

	gef::Animation* run_anim_;
	MotionClipPlayer run_anim_player;

	gef::Animation* idle_anim_;
	MotionClipPlayer idle_anim_player;

	//const char* modelToLoad = "ybot/ybot.scn";
	//const char* AnimToLoad = "ybot/ybot@walking.scn";

	ModelMesh* model_mesh_;
	ThisHereAnimation* anim_;

	float min_walk_speed;
	float max_walk_speed;
	float walk_speed = 1.f;

	float min_run_speed;
	float max_run_speed;
	float run_speed = 4.f;;

	float anim_blend;

	float speed_;

	gef::SkeletonPose blended_pose;

	BlendTree* blend_tree_;
};

#endif // _ANIMATED_MESH_APP_H
