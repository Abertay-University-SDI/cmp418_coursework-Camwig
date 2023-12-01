#pragma once
#include "Sprite_anim.h"
#include <SkinSlot.h>
#include <Bone.h>
#include <Animation_Parser.h>
#include <graphics/sprite.h>

#include "rapidjson\document.h"
#include "rapidjson/istreamwrapper.h"
#include "maths/math_utils.h"
#include <vector>
#include <array>
#include <map>

#include <system/application.h>
#include <graphics/sprite.h>


class TempSkeletalAnim
{
public:
	TempSkeletalAnim(/*gef::Texture*,gef::Platform**/);
	~TempSkeletalAnim();

	void Init(/*gef::Texture*, gef::Platform**/);

	void SetSpriteSizeAndPositionForFrame(gef::Sprite*, float, float, TextureAtlas*, std::string);

	std::map<std::string, SkinSlot> ReadSkinSlotsDataFromJSON(rapidjson::Document&);
	std::map<std::string, Bone> ReadBonesFromJSON(rapidjson::Document&);

	void SetParentsOfBones(std::map<std::string, Bone>*);

	//void BuildWorldTransforms(std::map<std::string, Bone>*);

	TextureAtlas* ReadTextureAtlasFromJSON(rapidjson::Document& tex_document);
	TexData* ReadSubtextureFromJSON(const rapidjson::Value&);

	//
	void CalculateWorldBoneTransform(Animation*, int);
	//void AnimUpdate(float);

	std::map<std::string, Animation> ReadAnimationDataFromJSON(rapidjson::Document&);

	//float elapsed_time;
	float sprite_speed;

	//std::map<std::string, Animation> new_anim;

	Animation_Parser* anim_pars;

	gef::Matrix33 rig_transform_m_;
	gef::Matrix33 combined_transform_m_;

	const float scale = 0.5f;

	void RenderUpdate(const gef::Vector2,gef::Sprite&, const std::string, gef::Matrix33&, gef::Matrix33&, gef::Matrix33&, gef::Matrix33&);

	std::map<std::string, SkinSlot> skin_slots;
	std::map<std::string, Bone> bones_;

	TextureAtlas text_atlas;

	std::vector<std::string> bone_parts;
	void SetupRig(gef::Vector2);

	std::map<std::string, Animation> new_anim;
};

