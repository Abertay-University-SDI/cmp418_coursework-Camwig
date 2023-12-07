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

#include "Anim.h"

class ThreeDimensional_Character
{
public:
	ThreeDimensional_Character::ThreeDimensional_Character();
	ThreeDimensional_Character::~ThreeDimensional_Character();

	void Setup(ModelMesh* ModelMesh_, gef::Scene* Model_scene, gef::Platform* platform_, std::string model_name);
	void InitBlendTree(std::string tree_name,std::string Anim1_name_, std::string Anim2_name_);

	void Init(ModelMesh* ModelMesh_, gef::Scene* Model_scene, gef::Platform* platform_, std::string anim_name);
	void NewUpdate(float frametime, std::string tree_name);

	void AddBlendTree(std::string tree_name);

	class gef::Mesh* mesh_;

	gef::SkinnedMeshInstance* player_;

	AnimatedModel_new anim_model_;

	gef::SkeletonPose blended_pose;

	gef::Skeleton skeleton;

	std::map<std::string, BlendTree> Map_o_blendtrees_;

	//BlendTree* blend_tree_;

	//The thing below seems useless?
	float anim_blend;

	float speed_;

	Anim* anim_;
};

