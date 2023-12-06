#pragma once
#include <animation/skeleton.h>
#include <animation/animation.h>
#include <graphics/primitive.h>
#include <graphics/scene.h>


#include "ModelMesh.h"
#include "motion_clip_player.h"
#include "AnimatedModel.h"

#include "BlendTree.h"
#include "ClipNode.h"
#include "Linear2Blend.h"

#include <maths/math_utils.h>

class ThisHereAnimation
{
public:
	ThisHereAnimation();
	~ThisHereAnimation();

	gef::Animation* LoadAnimation(const char* anim_scene_filename, const char* anim_name, gef::Platform&);

	void Setup(ModelMesh* ModelMesh_,gef::Scene* Model_scene,gef::Platform* platform_);
	void InitBlendTree();
	void Update(float frameTime_);

	class gef::Mesh* mesh_;
	gef::SkinnedMeshInstance* player_;

	MotionClipPlayer anim_player_;

	AnimatedModel* anim_model_;

	gef::Animation* walk_anim_;
	MotionClipPlayer walk_anim_player;

	gef::Animation* run_anim_;
	MotionClipPlayer run_anim_player;

	gef::Animation* idle_anim_;
	MotionClipPlayer idle_anim_player;

	gef::SkeletonPose blended_pose;

	BlendTree* blend_tree_;

	float min_walk_speed;
	float max_walk_speed;
	float walk_speed = 1.f;

	float min_run_speed;
	float max_run_speed;
	float run_speed = 4.f;;

	float anim_blend;

	float speed_;

	//Can use maps to store multiple of these
	const char* AnimToLoad = "ybot/ybot@walking_inplace.scn";
	const char* AnimToLoad2 = "ybot/ybot@running_inplace.scn";
	const char* AnimToLoad3 = "ybot/ybot@idle.scn";
};

