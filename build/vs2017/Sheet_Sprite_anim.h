#pragma once

#include "Sprite_anim.h"

class Sheet_Sprite_anim : public Sprite_anim
{
public:
	Sheet_Sprite_anim();
	~Sheet_Sprite_anim();

	//TextureAtlas* ReadTextureAtlasFromJSON(rapidjson::Document& tex_document) override;
	//TexData* ReadSubtextureFromJSON(const rapidjson::Value&) override;
	//void SetSpriteSizeAndPositionForFrame(gef::Sprite*, float, float, int) override;
	gef::Sprite* Load_sprite_and_texture_2(gef::Platform*, gef::Sprite*, std::string tex_string) override;

	gef::Sprite* SetupAnimation(gef::Platform*, gef::Sprite*, std::string tex_string, rapidjson::Document& tex_document, rapidjson::Document& ske_document) override;

	void Update(int frame, gef::Sprite* sprite_, gef::Vector2 position_) override;

private:
	std::map<int, std::string> run_order;

	gef::Texture* sprite_texture_;
	TextureAtlas* text_atlas;

	std::map<int, std::string> SetupOrder(rapidjson::Document&);
	std::vector<TexData> ReOrganiseSubtextures();
};

