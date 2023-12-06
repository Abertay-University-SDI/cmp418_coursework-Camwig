#include "ThisHereAnimation.h"

ThisHereAnimation::ThisHereAnimation() :

	mesh_(NULL),
	//Can be its own thing
	player_(NULL),
	//Can be turned into a base animation class
	walk_anim_(NULL),
	run_anim_(NULL),
	idle_anim_(NULL)
{
}

ThisHereAnimation::~ThisHereAnimation()
{
	delete player_;
	player_ = NULL;

	delete walk_anim_;
	walk_anim_ = NULL;

	delete run_anim_;
	run_anim_ = NULL;

	delete idle_anim_;
	idle_anim_ = NULL;

	delete mesh_;
	mesh_ = NULL;

	delete anim_model_;
	anim_model_ = NULL;

	delete blend_tree_;
	blend_tree_ = NULL;
}

gef::Animation* ThisHereAnimation::LoadAnimation(const char* anim_scene_filename, const char* anim_name, gef::Platform& platform_)
{
	gef::Animation* anim = NULL;

	gef::Scene anim_scene;
	if (anim_scene.ReadSceneFromFile(platform_, anim_scene_filename))
	{
		// if the animation name is specified then try and find the named anim
		// otherwise return the first animation if there is one
		std::map<gef::StringId, gef::Animation*>::const_iterator anim_node_iter;
		if (anim_name)
			anim_node_iter = anim_scene.animations.find(gef::GetStringId(anim_name));
		else
			anim_node_iter = anim_scene.animations.begin();

		if (anim_node_iter != anim_scene.animations.end())
			anim = new gef::Animation(*anim_node_iter->second);
	}

	return anim;
}

void ThisHereAnimation::Setup(ModelMesh* ModelMesh_, gef::Scene* Model_scene, gef::Platform* platform_)
{
	// if there is mesh data in the scene, create a mesh to draw from the first mesh
	mesh_ = ModelMesh_->CreateMeshData(Model_scene, *platform_);//GetFirstMesh(model_scene_);

	// get the first skeleton in the scene
	gef::Skeleton* skeleton = ModelMesh_->CreateSkeleton(Model_scene);//GetFirstSkeleton(model_scene_);

	if (skeleton)
	{
		player_ = new gef::SkinnedMeshInstance(*skeleton);
		anim_player_.Init(player_->bind_pose());
		walk_anim_player.Init(player_->bind_pose());
		run_anim_player.Init(player_->bind_pose());
		idle_anim_player.Init(player_->bind_pose());
		blended_pose = player_->bind_pose();
		player_->set_mesh(mesh_);
	}


	// anims
	//walk_anim_ = LoadAnimation("tesla/tesla@walk.scn", "");
	walk_anim_ = LoadAnimation(AnimToLoad, "", *platform_);//LoadAnimation(AnimToLoad, "");

	run_anim_ = LoadAnimation(AnimToLoad2, "", *platform_);

	idle_anim_ = LoadAnimation(AnimToLoad3, "", *platform_);

	if (walk_anim_)
	{
		walk_anim_player.set_clip(walk_anim_);
		walk_anim_player.set_looping(true);
		walk_anim_player.set_anim_time(0.0f);
	}

	if (run_anim_)
	{
		run_anim_player.set_clip(run_anim_);
		run_anim_player.set_looping(true);
		run_anim_player.set_anim_time(0.0f);
	}

	if (idle_anim_)
	{
		idle_anim_player.set_clip(idle_anim_);
		idle_anim_player.set_looping(true);
		idle_anim_player.set_anim_time(0.0f);
	}

	min_walk_speed = 1.f;
	max_walk_speed = walk_anim_->duration() / run_anim_->duration();//run anim duration

	min_run_speed = run_anim_->duration() / walk_anim_->duration();
	max_run_speed = 1.f;

	speed_ = 0.0f;

	anim_blend = 0.f;

	anim_model_ = new AnimatedModel;

	anim_model_->Model_Name_ = "Manbot";
	anim_model_->Model_PathWay_ = "ybot/ybot.scn";

	PlayableAnim* play_anim_ = new PlayableAnim;
	play_anim_->Anim_Name_ = "Walk";
	play_anim_->Anim_Pathway_ = "ybot/ybot@walking_inplace.scn";
	play_anim_->Anim_max_speed_ = max_walk_speed;
	play_anim_->Anim_min_speed_ = min_walk_speed;
	play_anim_->Anim_speed = 1.0f;
	play_anim_->Anim_player_ = walk_anim_player;
	play_anim_->Anim_ = walk_anim_;

	anim_model_->Anim_map.insert(std::make_pair(play_anim_->Anim_Name_, *play_anim_));
	delete play_anim_;
	play_anim_ = NULL;

	//InitBlendTree();
}

void ThisHereAnimation::Update(float frameTime_)
{
	if (player_)
	{
		//blend_tree_->variables[""]
		blend_tree_->variables["idle_anim_"] = speed_;
		blend_tree_->Update(frameTime_);
		blended_pose = blend_tree_->output_.OutputPose_;

		player_->UpdateBoneMatrices(blended_pose);
	}

	// build a transformation matrix that will position the character
	// use this to move the player around, scale it, etc.
	if (player_)
	{
		gef::Matrix44 player_transform;
		gef::Matrix44 player_scale;
		gef::Matrix44 player_rotate;
		gef::Matrix44 player_translate;

		player_transform.SetIdentity();
		player_scale.SetIdentity();
		player_rotate.SetIdentity();
		player_translate.SetIdentity();

		player_scale.Scale(gef::Vector4(0.3f, 0.3f, 0.3f, 1.0f));
		player_rotate.RotationY(gef::DegToRad(45.0f));
		player_translate.SetTranslation(gef::Vector4(25.0f, -25.0f, -100.0f, 1.0f));

		player_transform = player_scale * player_rotate * player_translate;

		player_->set_transform(player_transform);
	}
}

void ThisHereAnimation::InitBlendTree()
{
	if (player_ && player_->bind_pose().skeleton())
	{
		//Issue here
		//gef::SkeletonPose  new_pose = player_->bind_pose();
		blend_tree_->Init(player_->bind_pose());

		ClipNode* idle_clip = new ClipNode(blend_tree_);
		idle_clip->SetClip(idle_anim_);

		ClipNode* walk_clip = new ClipNode(blend_tree_);
		walk_clip->SetClip(anim_model_->Anim_map.at("Walk").Anim_);

		Linear2Blend* l2b = new Linear2Blend(blend_tree_);
		l2b->SetVariable(0, "idle_anim_");

		l2b->SetInput(0, idle_clip);
		l2b->SetInput(1, walk_clip);

		blend_tree_->output_.SetInput(0, l2b);

		blend_tree_->Start();
	}
}
