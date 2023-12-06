#pragma once
#include <graphics/mesh.h>
#include <graphics/skinned_mesh_instance.h>
#include <graphics/primitive.h>
#include <graphics/scene.h>
//#include <animation/skeleton.h>
//#include <animation/animation.h>

class ModelMesh
{
public:
	ModelMesh();
	~ModelMesh();

	gef::Mesh* CreateMeshData(gef::Scene*,gef::Platform&);

	gef::Skeleton* CreateSkeleton(gef::Scene* scene);

	//gef::Animation* LoadAnimation(const char* anim_scene_filename, const char* anim_name, gef::Platform&);

	const char* modelToLoad = "ybot/ybot.scn";

	//Need to make a diffrent class that holds the meshes and the animations it can use in a single file

	/*	gef::Skeleton* GetFirstSkeleton(gef::Scene* scene);

	gef::Mesh* GetFirstMesh(gef::Scene* scene);*/
};

