#include "OutputNode.h"

OutputNode::OutputNode(BlendTree* _tree) :
	BlendNode(_tree)
{
	inputs_.resize(1);
}

bool OutputNode::UpdateInternal(float deltaTime)
{
	OutputPose_ = inputs_[0].node->OutputPose_;
	return true;
}
