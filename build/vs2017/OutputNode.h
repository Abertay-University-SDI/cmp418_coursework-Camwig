#pragma once
//#include "BlendTree.h"
#include "BlendNode.h"

//class BlendNode;
//class BlendTree;

class OutputNode : public BlendNode
{
public:
	OutputNode(BlendTree* _tree);
	bool UpdateInternal(float) override;
};

