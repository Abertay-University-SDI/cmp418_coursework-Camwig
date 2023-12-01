#pragma once
#include "Sprite_anim.h"

//#include <maths/matrix33.h>
#include <math.h>
#include <string>
#include "maths/math_utils.h"
#include <maths/vector2.h>
#include <Animation_Parser.h>

struct SkinSlot
{
	std::string name_;
	std::string part_name_;
	float x_;
	float y_;
	float rot_;

	gef::Matrix33 transform_m_;

	//Can probably fix the build trnsforms to one thing but we will see
	void BuildTransform()
	{
		gef::Matrix33 rotation_m;
		gef::Matrix33 translation_m;

		rotation_m.SetIdentity();
		translation_m.SetIdentity();
		transform_m_.SetIdentity();

		rotation_m.Rotate(gef::DegToRad(rot_));
		translation_m.SetTranslation(gef::Vector2(x_, y_));

		transform_m_ = rotation_m * translation_m;
	}
};

struct Bone
{
	Bone* parent_;
	std::string name_;
	std::string parent_name_;
	float x_;
	float y_;
	float rot_;
	gef::Matrix33 local_transform_m;
	gef::Matrix33 New_local_transform_m;
	gef::Matrix33 world_transform_m;

	void BuildLocalTransform()
	{
		gef::Matrix33 rotation_m;
		gef::Matrix33 translation_m;

		rotation_m.SetIdentity();
		translation_m.SetIdentity();
		local_transform_m.SetIdentity();

		rotation_m.Rotate(gef::DegToRad(rot_));
		translation_m.SetTranslation(gef::Vector2(x_, y_));

		local_transform_m = rotation_m * translation_m;
	}
};

class Skeletal_Sprite_anim : public Sprite_anim
{
	Skeletal_Sprite_anim();
	~Skeletal_Sprite_anim();

	//void Init(/*gef::Texture*, gef::Platform**/);

	//void SetSpriteSizeAndPositionForFrame(gef::Sprite*, float, float, TextureAtlas*, std::string);

	std::map<std::string, SkinSlot> ReadSkinSlotsDataFromJSON(rapidjson::Document&);
	std::map<std::string, Bone> ReadBonesFromJSON(rapidjson::Document&);

	void SetParentsOfBones(std::map<std::string, Bone>*);

	//void BuildWorldTransforms(std::map<std::string, Bone>*);

	//TextureAtlas* ReadTextureAtlasFromJSON(rapidjson::Document& tex_document);
	//TexData* ReadSubtextureFromJSON(const rapidjson::Value&);

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

	//void RenderUpdate(const gef::Vector2, gef::Sprite&, const std::string, gef::Matrix33&, gef::Matrix33&, gef::Matrix33&, gef::Matrix33&);

	std::map<std::string, SkinSlot> skin_slots;
	std::map<std::string, Bone> bones_;

	TextureAtlas text_atlas;

	std::vector<std::string> bone_parts;
	void SetupRig(gef::Vector2);

	std::map<std::string, Animation> new_anim;

	virtual void Update(int frame, gef::Sprite* sprite_, gef::Vector2 position_) override;
	virtual gef::Sprite* SetupAnimation(gef::Platform*, gef::Sprite*, std::string tex_string, rapidjson::Document& tex_document, rapidjson::Document& ske_document) override;
};

