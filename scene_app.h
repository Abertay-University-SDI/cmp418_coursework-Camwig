//#ifndef _SCENE_APP_H
//#define _SCENE_APP_H
//
//#include <system/application.h>
//#include <maths/vector2.h>
//#include <graphics/sprite.h>
//#include <input/input_manager.h>
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
//	gef::SpriteRenderer* sprite_renderer_;
//	gef::Font* font_;
//	gef::InputManager* input_manager_;
//
//	gef::Texture* sprite_texture_;
//	gef::Sprite sprite_;
//
//	float fps_;
//
//	void FrontendInit();
//	void FrontendRelease();
//	void FrontendUpdate(float frame_time);
//	void FrontendRender();
//};
//
//#endif // _SCENE_APP_H

#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system/application.h>
#include <maths/vector2.h>
//#include <graphics/sprite.h>
#include "maths/math_utils.h"
#include <input/input_manager.h>
//#include <vector>

//#include <TexData.h>
//#include <TextureAtlas.h>

//#include <Anim.h>

//#include <TexData.h>
//#include <TextureAtlas.h>
//#include <SkinSlot.h>
//#include <Bone.h>
//#include <Animation_Parser.h>

//#include "rapidjson\document.h"
//#include "rapidjson/istreamwrapper.h"

#include "TempSkeletalAnim.h"

#include "Character.h"


// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
}

class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();

	//void SetSpriteSizeAndPositionForFrame(gef::Sprite*,float,float,TextureAtlas*,int);

	/*TextureAtlas* ReadTextureAtlasFromJSON(rapidjson::Document& tex_document);
	TexData* ReadSubtextureFromJSON(const rapidjson::Value&);*/

	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;
	gef::InputManager* input_manager_;

	//gef::Texture* sprite_texture_;
	//gef::Sprite sprite_;

	//std::map<std::string,SkinSlot> skin_slots;
	//std::map<std::string, Bone> bones_;

	float fps_;


	float animation_timer_;
	int frame;

	//TextureAtlas text_atlas;

	//Anim* anim;

	Character* character;

	std::string this_s;

	//TextureAtlas text_atlas;

	//gef::Vector2 sprite_pos_;

	//const float scale = 0.5f;

	//gef::Matrix33 rig_transform_m_;
	//gef::Matrix33 combined_transform_m_;


	//Animation_Parser* anim_pars;

	//TempSkeletalAnim* anim;

};

#endif // _SCENE_APP_H
