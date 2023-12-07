#include "ThreeDimensional_Character.h"

ThreeDimensional_Character::ThreeDimensional_Character():	
	mesh_(NULL),
	player_(NULL),
	skeleton(NULL),
	anim_(NULL),
	blend_tree_(NULL)
{
	anim_model_ = new AnimatedModel;
}


ThreeDimensional_Character::~ThreeDimensional_Character()
{
	delete player_;
	player_ = NULL;

	delete mesh_;
	mesh_ = NULL;

	delete anim_model_;
	anim_model_ = NULL;

	delete blend_tree_;
	blend_tree_ = NULL;

	delete skeleton;
	skeleton = NULL;

	delete anim_;
	anim_ = NULL;
}

//IN CHARACTER!!!
void ThreeDimensional_Character::Setup(ModelMesh* ModelMesh_, gef::Scene* Model_scene, gef::Platform* platform_, std::string model_name)
{
	anim_ = new ThisHereAnimation;

	blend_tree_ = new BlendTree;

	// if there is mesh data in the scene, create a mesh to draw from the first mesh
	mesh_ = ModelMesh_->CreateMeshData(Model_scene, *platform_);//GetFirstMesh(model_scene_);

	// get the first skeleton in the scene
	skeleton = ModelMesh_->CreateSkeleton(Model_scene);//GetFirstSkeleton(model_scene_);

	if (skeleton)
	{
		player_ = new gef::SkinnedMeshInstance(*skeleton);
		blended_pose = player_->bind_pose();
		player_->set_mesh(mesh_);
	}

	speed_ = 0.0f;

	anim_blend = 0.f;

	char* model_file_path_ = new char[model_name.length()];

	strcpy(model_file_path_, model_name.c_str());

	anim_model_->Model_Name_ = model_name;
	anim_model_->Model_PathWay_ = model_file_path_;

	mesh_ = ModelMesh_->CreateMeshData(Model_scene, *platform_);
}

void ThreeDimensional_Character::Init(ModelMesh* ModelMesh_, gef::Scene* Model_scene, gef::Platform* platform_, std::string anim_name)
{
	anim_->CallAnimationSetup(ModelMesh_, Model_scene, platform_, anim_name,*skeleton,*anim_model_,*player_, speed_);
}

void ThreeDimensional_Character::NewUpdate(float frametime)
{
	anim_->Update(frametime,*blend_tree_,*player_,blended_pose,speed_);
}

void ThreeDimensional_Character::InitBlendTree(std::string Anim1_name_, std::string Anim2_name_)
{
	if (player_ && player_->bind_pose().skeleton())
	{
		blend_tree_->Init(player_->bind_pose());

		ClipNode* idle_clip = new ClipNode(blend_tree_);
		idle_clip->SetClip(anim_model_->Anim_map.at(Anim2_name_.c_str()).Anim_);

		ClipNode* walk_clip = new ClipNode(blend_tree_);
		walk_clip->SetClip(anim_model_->Anim_map.at(Anim1_name_.c_str()).Anim_);

		Linear2Blend* l2b = new Linear2Blend(blend_tree_);
		l2b->SetVariable(0, "idle_anim_");

		l2b->SetInput(0, idle_clip);
		l2b->SetInput(1, walk_clip);

		blend_tree_->output_.SetInput(0, l2b);

		blend_tree_->Start();
	}
}
