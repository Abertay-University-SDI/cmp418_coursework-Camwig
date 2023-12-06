#pragma once
//#include "BlendNode.h"
#include <map>
#include <string>
#include <animation/skeleton.h>
#include <vector>
#include "OutputNode.h"
//#include "BlendNode.h"

//class BlendTree;
//class OutputNode;
//class BlendNode;

class BlendTree
{
public:
	BlendTree();
	~BlendTree();
	void Init(const gef::SkeletonPose& pose_);
	bool Update(float deltaTime);
	void Cleanup();
	void Start();

	OutputNode output_;
	gef::SkeletonPose bind_pose;

	std::map<std::string, float> variables;

};

