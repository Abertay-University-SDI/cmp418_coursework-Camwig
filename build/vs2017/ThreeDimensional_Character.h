#pragma once

#include "Anim_manager.h"

class ThreeDimensional_Character
{
public:
	ThreeDimensional_Character::ThreeDimensional_Character();
	ThreeDimensional_Character::~ThreeDimensional_Character();

	void Setup(gef::Scene& Model_scene, gef::Platform* platform_, std::string model_name, int Skeleton_num,gef::Vector4 Rotation, gef::Vector4 Translation);
	void InitBlendTree(std::string tree_name,std::string Anim1_name_, std::string Anim2_name_);

	void Init(gef::Scene* Model_scene, gef::Platform* platform_, std::string anim_name);
	void TreeUpdate(float frametime, std::string tree_name);
	void AnimUpdate(float frametime, std::string anim_name);

	gef::Skeleton* GetFirstSkeleton(gef::Scene* scene);

	void SetupRagdoll(bool& is_ragdoll_simulating, btDiscreteDynamicsWorld* dynamics_world_);
	void CallUpdateRagdoll(bool is_ragdoll_simulating_);

	void AddBlendTree(std::string tree_name);

	void UpdateCurrentPoseBoneMatrices_();

	float GetAnimMinSpeed(std::string anim_name);
	void SetAnimMinSpeed(std::string anim_name, float new_speed);

	float GetAnimMaxSpeed(std::string anim_name);
	void SetAnimMaxSpeed(std::string anim_name, float new_speed);

	gef::SkinnedMeshInstance* GetPlayer();

	float GetSpeed();
	void SetSpeed(float new_speed);

private:
	gef::SkeletonPose blended_pose;
	const gef::SkeletonPose* curr_pose;
	gef::Animation* curr_anim;
	std::string model_name_;

	float scale;
	Anim_manager* anim_;
	float speed_;
	ModelMesh* model_mesh_;
	class gef::Mesh* mesh_;

	gef::SkinnedMeshInstance* player_;

	AnimatedModel_new anim_model_;

	gef::Skeleton* skeleton;

	std::map<std::string, BlendTree> Map_o_blendtrees_;
};

