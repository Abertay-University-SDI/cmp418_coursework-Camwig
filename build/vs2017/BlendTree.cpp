#include "BlendTree.h"

BlendTree::BlendTree() : 
	output_(this)
{

}

BlendTree::~BlendTree()
{

}

void BlendTree::Init(const gef::SkeletonPose& bind_pose_)
{
	//bind_pose = new gef::SkeletonPose
	bind_pose = bind_pose_;
	output_.OutputPose_ = bind_pose;
}

bool BlendTree::Update(float deltaTime)
{
	bool valid = output_.Update(deltaTime);
	return valid;
}

void BlendTree::Cleanup()
{

}

void BlendTree::Start()
{
	output_.Start();
}