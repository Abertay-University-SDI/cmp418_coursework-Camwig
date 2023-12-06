#include "ClipNode.h"
#include "BlendTree.h"

ClipNode::ClipNode(BlendTree* _tree) :
	BlendNode(_tree)
{
	if (tree_)
		clip_player_.Init(tree_->bind_pose);
	clip_player_.set_looping(true);
}

void ClipNode::SetClip(const gef::Animation* anim)
{
	clip_player_.set_clip(anim);
}

void ClipNode::StartInternal()
{
	clip_player_.set_anim_time(0.f);
}

bool ClipNode::UpdateInternal(float deltaTime)
{
	bool valid = false;

	if (clip_player_.clip())
	{
		clip_player_.Update(deltaTime, tree_->bind_pose);
		OutputPose_ = clip_player_.pose();
		valid = true;
	}
	return valid;
}