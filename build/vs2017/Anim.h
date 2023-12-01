#pragma once


#include "Sheet_Sprite_anim.h"
//#include <graphics/sprite.h>

//#include "rapidjson\document.h"
//#include "rapidjson/istreamwrapper.h"

namespace gef
{
	class Platform;
}

class Anim
{
public:
	Anim();
	~Anim();

	//void Init(std::string, gef::Platform* platform_, gef::Sprite* sprite_, std::string tex_string, int frame);
	
	//TextureAtlas* ReadTextureAtlasFromJSON(rapidjson::Document& tex_document);
	//TexData* ReadSubtextureFromJSON(const rapidjson::Value&);
	//void SetSpriteSizeAndPositionForFrame(gef::Sprite*, float, float, int);

	//void Load_sprite_and_texture_(gef::Platform*, gef::Sprite*);
	//void Load_sprite_and_texture_2(gef::Platform*, gef::Sprite*, std::string tex_string);
	//TextureAtlas* text_atlas;

	void Update(int frame_, gef::Sprite* sprite_,gef::Vector2 position_);

	//void Setup_2D_anim(gef::Platform* platform_, gef::Sprite* sprite_, std::string tex_string);
	//void SetupAnimSheet2D(gef::Platform* platform_, gef::Sprite* sprite_, std::string tex_string, rapidjson::Document& tex_document, rapidjson::Document& ske_document);

	void SetupAnim(gef::Platform* platform_, gef::Sprite* sprite_, std::string tex_string, rapidjson::Document& tex_document, rapidjson::Document& ske_document, int& FrameRate,int& Duration);

	void Render(gef::Sprite* sprite_);

	float FrameRate;
	float Duration;
private:
	//gef::Texture* sprite_texture_;
	Sprite_anim* sprite_animation_;
	//void Setup_2D_anim(gef::Platform* platform_, gef::Sprite* sprite_, std::string tex_string);
	//int frame_;

	//gef::Sprite* sprite;
};

