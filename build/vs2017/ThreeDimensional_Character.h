#pragma once

/*#include <animation/skeleton.h>
#include <animation/animation.h>
#include <graphics/primitive.h>
#include <graphics/scene.h>

#include <graphics/skinned_mesh_instance.h>

#include "ModelMesh.h"
#include "motion_clip_player.h"
#include "AnimatedModel.h"

#include "BlendTree.h"
#include "ClipNode.h"
#include "Linear2Blend.h"*/

#include "ThisHereAnimation.h"

class ThreeDimensional_Character
{
public:
	ThreeDimensional_Character::ThreeDimensional_Character();
	ThreeDimensional_Character::~ThreeDimensional_Character();

	void Setup(ModelMesh* ModelMesh_, gef::Scene* Model_scene, gef::Platform* platform_, std::string model_name);
	void InitBlendTree(std::string Anim1_name_, std::string Anim2_name_);

	void Init(ModelMesh* ModelMesh_, gef::Scene* Model_scene, gef::Platform* platform_, std::string anim_name);

	void NewUpdate(float frametime);

	class gef::Mesh* mesh_;

	gef::SkinnedMeshInstance* player_;

	AnimatedModel* anim_model_;

	gef::SkeletonPose blended_pose;

	gef::Skeleton* skeleton;

	BlendTree* blend_tree_;

	float anim_blend;

	float speed_;

	ThisHereAnimation* anim_;
};

