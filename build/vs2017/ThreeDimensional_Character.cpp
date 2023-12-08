#include "ThreeDimensional_Character.h"

ThreeDimensional_Character::ThreeDimensional_Character():	
	mesh_(NULL),
	player_(NULL),
/*	skeleton(NULL),*/
	anim_(NULL)/*,
	blend_tree_(NULL)*/
{
	//anim_model_ = new AnimatedModel;
}


ThreeDimensional_Character::~ThreeDimensional_Character()
{
	delete player_;
	player_ = NULL;

	delete mesh_;
	mesh_ = NULL;

	//delete anim_model_;
	//anim_model_ = NULL;

	//delete blend_tree_;
	//blend_tree_ = NULL;

	//delete skeleton;
	//skeleton = NULL;

	delete anim_;
	anim_ = NULL;
}

//IN CHARACTER!!!
void ThreeDimensional_Character::Setup(ModelMesh* ModelMesh_, gef::Scene* Model_scene, gef::Platform* platform_, std::string model_name)
{
	anim_ = new Anim;

	//blend_tree_ = new BlendTree;

	// if there is mesh data in the scene, create a mesh to draw from the first mesh
	mesh_ = ModelMesh_->CreateMeshData(Model_scene, *platform_);//GetFirstMesh(model_scene_);

	// get the first skeleton in the scene
	skeleton = *ModelMesh_->CreateSkeleton(Model_scene);//GetFirstSkeleton(model_scene_);

	if (&skeleton)
	{
		player_ = new gef::SkinnedMeshInstance(skeleton);
		blended_pose = player_->bind_pose();
		player_->set_mesh(mesh_);
	}

	speed_ = 0.0f;

	char* model_file_path_ = new char[model_name.length()];

	strcpy(model_file_path_, model_name.c_str());

	anim_model_.Model_Name_ = model_name;
	anim_model_.Model_PathWay_ = model_file_path_;

	mesh_ = ModelMesh_->CreateMeshData(Model_scene, *platform_);
}

void ThreeDimensional_Character::Init(ModelMesh* ModelMesh_, gef::Scene* Model_scene, gef::Platform* platform_, std::string anim_name)
{
	anim_->SetupAnim(ModelMesh_, Model_scene, platform_,anim_name,skeleton,player_,anim_model_, speed_);
}

void ThreeDimensional_Character::NewUpdate(float frametime, std::string tree_name)
{
	anim_->Update(frametime,Map_o_blendtrees_.at(tree_name),*player_,blended_pose,speed_);
}

void ThreeDimensional_Character::AddBlendTree(std::string tree_name)
{
	BlendTree* temp_tree = new BlendTree;
	Map_o_blendtrees_.insert(std::make_pair(tree_name,*temp_tree));
	
	delete temp_tree;
	temp_tree = NULL;
}

void ThreeDimensional_Character::InitBlendTree(std::string tree_name, std::string Anim1_name_, std::string Anim2_name_)
{
	//ANIM MODEL SHOULD BE DONE HERE!!!

	if (player_ && player_->bind_pose().skeleton())
	{
		Map_o_blendtrees_.at(tree_name).Init(player_->bind_pose());

		ClipNode* idle_clip = new ClipNode(&Map_o_blendtrees_.at(tree_name));
		idle_clip->SetClip(anim_model_.Anim_map.at(Anim2_name_.c_str()).Anim_);

		ClipNode* walk_clip = new ClipNode(&Map_o_blendtrees_.at(tree_name));
		walk_clip->SetClip(anim_model_.Anim_map.at(Anim1_name_.c_str()).Anim_);

		Linear2Blend* l2b = new Linear2Blend(&Map_o_blendtrees_.at(tree_name));
		l2b->SetVariable(0, "idle_anim_");

		l2b->SetInput(0, idle_clip);
		l2b->SetInput(1, walk_clip);

		Map_o_blendtrees_.at(tree_name).output_.SetInput(0, l2b);

		Map_o_blendtrees_.at(tree_name).Start();
	}
}
