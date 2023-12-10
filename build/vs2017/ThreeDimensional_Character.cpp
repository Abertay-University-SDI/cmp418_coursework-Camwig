#include "ThreeDimensional_Character.h"

ThreeDimensional_Character::ThreeDimensional_Character():	
	mesh_(NULL),
	player_(NULL),
	skeleton(NULL),
	anim_(NULL),/*,
	blend_tree_(NULL)*/
	ragdoll_(NULL)
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

	delete skeleton;
	skeleton = NULL;

	delete anim_;
	anim_ = NULL;

	delete ragdoll_;
	ragdoll_ = NULL;
}

//IN CHARACTER!!!
void ThreeDimensional_Character::Setup(ModelMesh* ModelMesh_, gef::Scene* Model_scene, gef::Platform* platform_, std::string model_name)
{
	anim_ = new Anim;

	//blend_tree_ = new BlendTree;

	// if there is mesh data in the scene, create a mesh to draw from the first mesh
	mesh_ = ModelMesh_->CreateMeshData(Model_scene, *platform_);//GetFirstMesh(model_scene_);

	//--------------------------------------

	// get the first skeleton in the scene
	skeleton = ModelMesh_->CreateSkeleton(Model_scene);

	if (&skeleton)
	{
		player_ = new gef::SkinnedMeshInstance(*skeleton);
		blended_pose = player_->bind_pose();
		player_->set_mesh(mesh_);
	}

	// animated model is scaled down to match the size of the physics ragdoll
	gef::Matrix44 player_transform;
	const float scale = 0.01f;
	player_transform.Scale(gef::Vector4(scale, scale, scale));
	player_->set_transform(player_transform);

	//--------------------------------------

	//skeleton = *GetFirstSkeleton(Model_scene);

	//if (&skeleton)
	//{
	//	player_ = new gef::SkinnedMeshInstance(skeleton);
	//	player_->set_mesh(mesh_);
	//	player_->UpdateBoneMatrices(player_->bind_pose());

	//	// output skeleton joint names
	//	for (int joint_num = 0; joint_num < skeleton.joints().size(); ++joint_num)
	//	{
	//		std::string bone_name;
	//		Model_scene->string_id_table.Find(skeleton.joint(joint_num).name_id, bone_name);
	//	}

	//	// animated model is scaled down to match the size of the physics ragdoll
	//	gef::Matrix44 player_transform;
	//	const float scale = 0.01f;
	//	player_transform.Scale(gef::Vector4(scale, scale, scale));
	//	player_->set_transform(player_transform);
	//}

	//--------------------------------------

	speed_ = 0.0f;

	char* model_file_path_ = new char[model_name.length()];

	strcpy(model_file_path_, model_name.c_str());

	anim_model_.Model_Name_ = model_name;
	anim_model_.Model_PathWay_ = model_file_path_;

	mesh_ = ModelMesh_->CreateMeshData(Model_scene, *platform_);
}

void ThreeDimensional_Character::Init(ModelMesh* ModelMesh_, gef::Scene* Model_scene, gef::Platform* platform_, std::string anim_name)
{
	anim_->SetupAnim(ModelMesh_, Model_scene, platform_,anim_name,*skeleton,player_,anim_model_, speed_);
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

		ClipNode* clip_1 = new ClipNode(&Map_o_blendtrees_.at(tree_name));
		clip_1->SetClip(anim_model_.Anim_map.at(Anim2_name_.c_str()).Anim_);

		ClipNode* clip_2 = new ClipNode(&Map_o_blendtrees_.at(tree_name));
		clip_2->SetClip(anim_model_.Anim_map.at(Anim1_name_.c_str()).Anim_);

		Linear2Blend* l2b = new Linear2Blend(&Map_o_blendtrees_.at(tree_name));
		//Need to rename
		l2b->SetVariable(0, "idle_anim_");

		l2b->SetInput(0, clip_1);
		l2b->SetInput(1, clip_2);

		Map_o_blendtrees_.at(tree_name).output_.SetInput(0, l2b);

		Map_o_blendtrees_.at(tree_name).Start();
	}
}

//gef::Skeleton* ThreeDimensional_Character::GetFirstSkeleton(gef::Scene* scene)
//{
//	gef::Skeleton* skeleton = NULL;
//	if (scene)
//	{
//		// check to see if there is a skeleton in the the scene file
//		// if so, pull out the bind pose and create an array of matrices
//		// that wil be used to store the bone transformations
//		if (scene->skeletons.size() > 0)
//			skeleton = scene->skeletons.front();
//	}
//
//	return skeleton;
//}

//--------------------------------------

void ThreeDimensional_Character::InitRagdoll(btDiscreteDynamicsWorld* dynamics_world_, std::string model_name, bool& is_ragdoll_simulating_)
{
	if (player_->bind_pose().skeleton())
	{
		ragdoll_ = new Ragdoll();
		ragdoll_->set_scale_factor(0.01f);

		std::string ragdoll_filename;
		ragdoll_filename = model_name + "/ragdoll.bullet";

		ragdoll_->Init(player_->bind_pose(), dynamics_world_, ragdoll_filename.c_str());
	}

	is_ragdoll_simulating_ = false;
}

void ThreeDimensional_Character::UpdateRagdoll(bool is_ragdoll_simulating_, std::string anim_name)
{
	if (player_ && ragdoll_)
	{
		if (is_ragdoll_simulating_)
		{
			ragdoll_->UpdatePoseFromRagdoll();
			player_->UpdateBoneMatrices(ragdoll_->pose());
		}
		else
		{
			//Should be current animation
			//Just pass it the current pose from animation
			ragdoll_->set_pose(anim_model_.Anim_map.at(anim_name).Anim_player_.pose());
			//--------------------------
			ragdoll_->UpdateRagdollFromPose();
		}
	}
}

//--------------------------------------
