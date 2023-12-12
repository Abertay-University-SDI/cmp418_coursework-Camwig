#include "Anim.h"
#include "load_texture.h"
#include "load_json.h"
#include <fstream>

Anim::Anim()
{
	WhichAnim_ = NULL;
	ThreeD_animation_ = NULL;
	sprite_animation_ = NULL;
	ragdoll_ = NULL;
}

Anim::~Anim()
{
	delete sprite_animation_;
	sprite_animation_ = NULL;

	delete WhichAnim_;
	WhichAnim_ = NULL;

	delete ThreeD_animation_;
	ThreeD_animation_ = NULL;

	delete ragdoll_;
	ragdoll_ = NULL;
}

//2D Sprite animation Update
void Anim::Update(int frame, gef::Sprite* sprite_, gef::Vector2 position_, std::map<std::string, gef::Matrix33>& Transforms_for_bone_)
{
	sprite_animation_->Update(frame, sprite_, position_, Transforms_for_bone_);
}

//3D BlendTree Update
void Anim::Update(float frameTime_, BlendTree& blend_tree, gef::SkinnedMeshInstance& player_, gef::SkeletonPose& blended_pose, float speed_)
{
	ThreeD_animation_->Update(frameTime_, blend_tree, player_, blended_pose, speed_);
}

//3D Standard Animation
void Anim::Update(float frameTime_, gef::SkinnedMeshInstance& player_, AnimatedModel_new& anim_model, std::string anim_name)
{
	ThreeD_animation_->Update(frameTime_, player_, anim_model, anim_name);
}

//3D Ragdoll Animation
void Anim::Update(bool is_ragdoll_simulating_, gef::SkinnedMeshInstance* player_, const gef::SkeletonPose* curr_pose)
{
	ragdoll_->UpdateRagdoll(is_ragdoll_simulating_, player_, curr_pose);
}

//Sprite Render
void Anim::Sprite_Render(gef::Sprite* sprite_, gef::Matrix33& transform, std::string part, gef::Vector2 Position)
{
	sprite_animation_->Render(sprite_,transform,part,Position);
}

//2D Sprite Animation Setup
void Anim::SetupAnim(gef::Platform* platform_, gef::Sprite* sprite_, std::string tex_string, rapidjson::Document& tex_document, rapidjson::Document& ske_document, gef::Vector2 Position, std::vector<std::string>& bone_parts, std::string& type_, std::string* WhichAnim1, float scale_)
{
	if (WhichAnim1 != NULL)
	{
		//Defines the animation that is to be loaded if there are multiple in the one Ske
		WhichAnim_ = new std::string(*WhichAnim1);
	}

	//Gets the type of sprite animation that is being performed
	const rapidjson::Value& ske_array = ske_document["armature"];
	std::string test_string = ske_array[0]["type"].GetString();

	//Gets the Framerate and duration
	int temp;
	temp = ske_array[0]["frameRate"].GetInt();
	FrameRate = temp;
	temp = ske_array[0]["animation"][0]["duration"].GetInt();
	Duration = temp;

	//Checks the type of animation
	if (test_string.find("Sheet") != std::string::npos)
	{
		//Defines the type of sprite animation to call
		Sheet_Sprite_anim* new_sheet;
		new_sheet = new Sheet_Sprite_anim();
		sprite_animation_ = new_sheet;

		//Calls the appropriate setup
		type_ = test_string;
		sprite_ = sprite_animation_->SetupAnimation(platform_, sprite_, tex_string, tex_document, ske_document,Position,bone_parts,WhichAnim_,scale_);
	}
	else if (test_string.find("Armature") != std::string::npos)
	{
		Skeletal_Sprite_anim* new_sheet;
		new_sheet = new Skeletal_Sprite_anim();
		sprite_animation_ = new_sheet;

		type_ = test_string;
		sprite_ = sprite_animation_->SetupAnimation(platform_, sprite_, tex_string, tex_document, ske_document, Position, bone_parts, WhichAnim_,scale_);
	}
}

//3D animation Setup
void Anim::SetupAnim(ModelMesh* ModelMesh_, gef::Scene* Model_scene, gef::Platform* platform_, std::string anim_name, gef::Skeleton& skeleton_, gef::SkinnedMeshInstance* player_, AnimatedModel_new& anim_model, float speed_)
{
	ThreeD_animation_ = new ThisHereAnimation;
	ThreeD_animation_->CallAnimationSetup(ModelMesh_, Model_scene, platform_, anim_name, skeleton_, anim_model, *player_, speed_);
}

//3D Ragdol Animation Setup
void Anim::SetupAnim(btDiscreteDynamicsWorld* dynamics_world_, std::string model_name, bool& is_ragdoll_simulating_, gef::SkinnedMeshInstance* player_)
{
	ragdoll_ = new Ragdoll;
	ragdoll_->InitRagdoll(dynamics_world_, model_name, is_ragdoll_simulating_, player_);
}

void Anim::SetFrameRate(float new_frame_rate_)
{
	FrameRate = new_frame_rate_;
}

float Anim::GetFrameRate()
{
	return FrameRate;
}

void Anim::SetDuration(float new_duration_)
{
	Duration = new_duration_;
}

float Anim::GetDuration()
{
	return Duration;
}

void Anim::SetWhichAnim(std::string new_WhichAnim_)
{
	WhichAnim_ = &new_WhichAnim_;
}

std::string* Anim::GetWhichAnim()
{
	return WhichAnim_;
}
