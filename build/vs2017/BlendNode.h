#pragma once
#include <animation/skeleton.h>
#include <vector>
//#include "BlendTree.h"

class BlendNode;
class BlendTree;

struct BlendNodeInput
{
	BlendNode* node;

	BlendNodeInput() :
		node(nullptr)
	{

	}
};

class BlendNode
{
public:
	BlendNode(BlendTree* _tree);
	//~BlendNode();
	//virtual bool Process(float deltaTime);

	//gef::SkeletonPose;
	std::vector<BlendNodeInput>inputs_;
	std::vector<std::string> variables_;
	gef::SkeletonPose OutputPose_;
	BlendTree* tree_;
	

	bool Update(float deltaTime);
	void SetInput(int InputNum, BlendNode* BlendNode);
	void SetVariable(int variable_num, const std::string& variable);

	virtual bool UpdateInternal(float deltaTime) = 0;
	virtual void StartInternal() {}

	void Start();
};

