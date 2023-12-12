#include "ThreeDimensional_Character.h"

ThreeDimensional_Character::ThreeDimensional_Character():	
	mesh_(NULL),
	player_(NULL),
	skeleton(NULL),
	anim_(NULL)/*,
	blend_tree_(NULL)*/
{
	//anim_model_ = new AnimatedModel;
	scale = 0.01f;
	speed_ = 0.0f;
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
}

//IN CHARACTER!!!
void ThreeDimensional_Character::Setup(gef::Scene& Model_scene, gef::Platform* platform_, std::string model_name,int Skeleton_num, gef::Vector4 Rotation,gef::Vector4 Translation)
{
	model_name_ = model_name;
	std::string model_scene_name = model_name + "/" + model_name + ".scn";

	model_mesh_ = new ModelMesh();

	Model_scene.ReadSceneFromFile(*platform_, model_scene_name.c_str());
	Model_scene.CreateMaterials(*platform_);

	anim_ = new Anim_manager;

	//blend_tree_ = new BlendTree;

	// if there is mesh data in the scene, create a mesh to draw from the first mesh
	mesh_ = model_mesh_->CreateMeshData(&Model_scene, *platform_);//GetFirstMesh(model_scene_);

	//--------------------------------------

	// get the first skeleton in the scene
	//skeleton = model_mesh_->CreateSkeleton(&Model_scene, Skeleton_num);

	//if (&skeleton)
	//{
	//	player_ = new gef::SkinnedMeshInstance(*skeleton);
	//	blended_pose = player_->bind_pose();
	//	curr_pose = &player_->bind_pose();
	//	player_->set_mesh(mesh_);
	//}

	// animated model is scaled down to match the size of the physics ragdoll
	//gef::Matrix44 player_transform;
	//player_transform.Scale(gef::Vector4(scale, scale, scale));
	//player_->set_transform(player_transform);

	//--------------------------------------

	skeleton = GetFirstSkeleton(&Model_scene);

	if (skeleton)
	{
		player_ = new gef::SkinnedMeshInstance(*skeleton);
		player_->set_mesh(mesh_);
		player_->UpdateBoneMatrices(player_->bind_pose());

		// output skeleton joint names
		for (int joint_num = 0; joint_num < skeleton->joints().size(); ++joint_num)
		{
			std::string bone_name;
			Model_scene.string_id_table.Find(skeleton->joint(joint_num).name_id, bone_name);
		}

		// animated model is scaled down to match the size of the physics ragdoll
		gef::Matrix44 player_transform;
		const float scale = 0.01f;
		player_transform.Scale(gef::Vector4(scale, scale, scale));
		player_->set_transform(player_transform);
	}

	//--------------------------------------

	if (&player_)
	{
		gef::Matrix44 player_transform;
		gef::Matrix44 player_scale;
		gef::Matrix44 player_rotate;
		gef::Matrix44 player_translate;

		player_transform.SetIdentity();
		player_scale.SetIdentity();
		player_rotate.SetIdentity();
		player_translate.SetIdentity();

		player_scale.Scale(gef::Vector4(scale, scale, scale, 1.0f));

		if (Rotation.x() != 0.0f)
		{
			player_rotate.RotationX(gef::DegToRad(Rotation.x()));
		}

		if (Rotation.y() != 0.0f)
		{
			player_rotate.RotationY(gef::DegToRad(Rotation.y()));
		}

		if (Rotation.z() != 0.0f)
		{
			player_rotate.RotationZ(gef::DegToRad(Rotation.z()));
		}

		player_translate.SetTranslation(gef::Vector4(Translation.x(), Translation.y(), Translation.z(), Translation.z()/*25.0f, -25.0f, -100.0f, 1.0f*/));

		player_transform = player_scale * player_rotate * player_translate;

		player_->set_transform(player_transform);
	}


	char* model_file_path_ = new char[model_scene_name.length()];

	strcpy(model_file_path_, model_scene_name.c_str());

	//model_name = model_name.substr(0,pos);

	anim_model_.Model_Name_ = model_name_;
	anim_model_.Model_PathWay_ = model_file_path_;

	mesh_ = model_mesh_->CreateMeshData(&Model_scene, *platform_);
}

void ThreeDimensional_Character::Init(gef::Scene* Model_scene, gef::Platform* platform_, std::string anim_name)
{
	anim_->SetupAnim(model_mesh_, Model_scene, platform_,anim_name,*skeleton,player_,anim_model_, speed_);
}

void ThreeDimensional_Character::TreeUpdate(float frametime, std::string tree_name)
{
	anim_->Update(frametime,Map_o_blendtrees_.at(tree_name),*player_,blended_pose,speed_);
	curr_pose = &blended_pose;
}

void ThreeDimensional_Character::AnimUpdate(float frametime, std::string anim_name)
{
	anim_->Update(frametime,*player_,anim_model_,anim_name);
	curr_pose = &anim_model_.Anim_map.at(anim_name).Anim_player_.pose();
}

void ThreeDimensional_Character::AddBlendTree(std::string tree_name)
{
	//Sometimes fails here on release
	BlendTree* temp_tree = new BlendTree(player_->bind_pose());
	//temp_tree->Init(player_->bind_pose());
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
		l2b->SetVariable(0, "speed");
		Map_o_blendtrees_.at(tree_name).variables["speed"] = speed_;

		l2b->SetInput(0, clip_1);
		l2b->SetInput(1, clip_2);

		Map_o_blendtrees_.at(tree_name).output_.SetInput(0, l2b);

		Map_o_blendtrees_.at(tree_name).Start();
	}
}

gef::Skeleton* ThreeDimensional_Character::GetFirstSkeleton(gef::Scene* scene)
{
	gef::Skeleton* skeleton = NULL;
	if (scene)
	{
		// check to see if there is a skeleton in the the scene file
		// if so, pull out the bind pose and create an array of matrices
		// that wil be used to store the bone transformations
		if (scene->skeletons.size() > 0)
			skeleton = scene->skeletons.front();
	}

	return skeleton;
}

void ThreeDimensional_Character::UpdateCurrentPoseBoneMatrices_()
{
	player_->UpdateBoneMatrices(*curr_pose);
}

void ThreeDimensional_Character::SetupRagdoll(bool& is_ragdoll_simulating, btDiscreteDynamicsWorld* dynamics_world_)
{
	anim_->SetupAnim(dynamics_world_, anim_model_.Model_Name_, is_ragdoll_simulating, player_);
}

void ThreeDimensional_Character::CallUpdateRagdoll(bool is_ragdoll_simulating_)
{
	anim_->Update(is_ragdoll_simulating_, player_, curr_pose);
}