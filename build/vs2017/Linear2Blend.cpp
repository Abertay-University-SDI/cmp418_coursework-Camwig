#include "Linear2Blend.h"
#include "BlendTree.h"

Linear2Blend::Linear2Blend(BlendTree* _tree)
	:BlendNode(_tree)
{
	inputs_.resize(2);
	variables_.resize(1);
}

bool Linear2Blend::UpdateInternal(float deltaTime)
{
	float blend_value = tree_->variables[variables_[0]];
	OutputPose_.Linear2PoseBlend(inputs_[0].node->OutputPose_, inputs_[1].node->OutputPose_, blend_value);

	return true;
}
