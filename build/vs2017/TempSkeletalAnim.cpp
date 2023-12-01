#include "TempSkeletalAnim.h"

#include <iostream>
#include <string>
#include <fstream>
#include "load_texture.h"
#include "load_json.h"


TempSkeletalAnim::TempSkeletalAnim()
{
}
TempSkeletalAnim::~TempSkeletalAnim()
{

}

void TempSkeletalAnim::Init(/*gef::Texture* sprite_texture_, gef::Platform* platform_*/)
{
	//std::string parts[] = { "tailTip","armUpperL","armL","handL","legL","body","tail","clothes","hair","head","eyeL","eyeR","legR","armUpperR","armR","handR","beardL","beardR" };

	//for (auto i : parts)
	//{
	//	bone_parts.push_back(i);
	//}

	sprite_speed = 1 / 30.0f;

	anim_pars = new Animation_Parser;

	char* JSON_Doc = LoadJSON("Dragon_tex.json");
	std::ifstream ifs("Dragon_tex.json");
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document rapidjson_doc;
	rapidjson_doc.ParseStream(isw);

	std::ifstream ifs2("Dragon_ske.json");
	rapidjson::IStreamWrapper isw2(ifs2);
	rapidjson::Document doc_dragon_ske;
	doc_dragon_ske.ParseStream(isw2);

	skin_slots = ReadSkinSlotsDataFromJSON(doc_dragon_ske);
	bones_ = ReadBonesFromJSON(doc_dragon_ske);

	//Does not like it returning it this way
	new_anim = ReadAnimationDataFromJSON(doc_dragon_ske);

	text_atlas = *ReadTextureAtlasFromJSON(rapidjson_doc);
}

TextureAtlas* TempSkeletalAnim::ReadTextureAtlasFromJSON(rapidjson::Document& tex_document)
{
	TextureAtlas* tex_atlas = new TextureAtlas();
	tex_atlas->name_ = tex_document["name"].GetString();
	tex_atlas->width_ = tex_document["width"].GetFloat();
	tex_atlas->height_ = tex_document["height"].GetFloat();

	const rapidjson::Value& subtexture_array = tex_document["SubTexture"];
	for (int subtex_num = 0; subtex_num < (int)subtexture_array.Size(); ++subtex_num)
	{
		TexData* texdata = ReadSubtextureFromJSON(subtexture_array[subtex_num]);
		//tex_atlas->subtextures.push_back(*texdata);

		tex_atlas->subtex_atlas.insert(std::make_pair(texdata->name_, *texdata));

		delete texdata;
	}

	return tex_atlas;
}

TexData* TempSkeletalAnim::ReadSubtextureFromJSON(const rapidjson::Value& subtecture_array)
{
	TexData* subTextData = new TexData;
	subTextData->name_ = subtecture_array["name"].GetString();
	subTextData->width_ = subtecture_array["width"].GetFloat();
	subTextData->height_ = subtecture_array["height"].GetFloat();
	subTextData->x_ = subtecture_array["x"].GetFloat();
	subTextData->y_ = subtecture_array["y"].GetFloat();

	if (subtecture_array.HasMember("frameX"))
	{
		subTextData->frame_x_ = subtecture_array["frameX"].GetFloat();
	}
	else
	{
		subTextData->frame_x_ = 0;
	}

	if (subtecture_array.HasMember("frameY"))
	{
		subTextData->frame_y_ = subtecture_array["frameY"].GetFloat();
	}
	else
	{
		subTextData->frame_y_ = 0;
	}

	if (subtecture_array.HasMember("frameWidth"))
	{
		subTextData->frame_width_ = subtecture_array["frameWidth"].GetFloat();
	}
	else
	{
		subTextData->frame_width_ = subTextData->width_;
	}

	if (subtecture_array.HasMember("frameHeight"))
	{
		subTextData->frame_height_ = subtecture_array["frameHeight"].GetFloat();
	}
	else
	{
		subTextData->frame_height_ = subTextData->height_;
	}

	subTextData->BuildTransform();

	return subTextData;
}

void TempSkeletalAnim::SetSpriteSizeAndPositionForFrame(gef::Sprite* sprite, float screen_x, float screen_y, TextureAtlas* texture_atlas, std::string subtext_name)
{
	float width = texture_atlas->subtex_atlas.at(subtext_name).width_;
	float height = texture_atlas->subtex_atlas.at(subtext_name).height_;
	float x = texture_atlas->subtex_atlas.at(subtext_name).x_;
	float y = texture_atlas->subtex_atlas.at(subtext_name).y_;
	float frame_width = texture_atlas->subtex_atlas.at(subtext_name).frame_width_;
	float frame_height = texture_atlas->subtex_atlas.at(subtext_name).frame_height_;
	float frame_x = texture_atlas->subtex_atlas.at(subtext_name).frame_x_;
	float frame_y = texture_atlas->subtex_atlas.at(subtext_name).frame_y_;

	sprite->set_width(width);
	sprite->set_height(height);
	sprite->set_uv_width(width / texture_atlas->width_);
	sprite->set_uv_height(height / texture_atlas->height_);

	float u = x / texture_atlas->width_;
	float v = y / texture_atlas->height_;
	sprite->set_uv_position(gef::Vector2(u, v));

	float sprite_x = width * 0.5f - (frame_width * 0.5f + frame_x);
	float sprite_y = height * 0.5f - (frame_height * 0.5f + frame_y);

	sprite->set_position(gef::Vector4(screen_x + sprite_x, screen_y + sprite_y, 0.0f));
}

std::map <std::string, SkinSlot> TempSkeletalAnim::ReadSkinSlotsDataFromJSON(rapidjson::Document& ske_document)
{
	const rapidjson::Value& slots_array = ske_document["armature"][0]["skin"][0]["slot"];

	std::map<std::string, SkinSlot> slots;

	for (int slot_num = 0; slot_num < (int)slots_array.Size(); ++slot_num)
	{
		SkinSlot* slot = new SkinSlot();
		slot->name_ = slots_array[slot_num]["name"].GetString();
		slot->part_name_ = slots_array[slot_num]["display"][0]["name"].GetString();
		slot->x_ = slots_array[slot_num]["display"][0]["transform"]["x"].GetFloat();
		slot->y_ = slots_array[slot_num]["display"][0]["transform"]["y"].GetFloat();
		if (slot->rot_ = slots_array[slot_num]["display"][0]["transform"].HasMember("skY"))
		{
			slot->rot_ = slots_array[slot_num]["display"][0]["transform"]["skY"].GetFloat();
		}
		else
		{
			slot->rot_ = 0;
		}

		slot->BuildTransform();

		slots.insert(std::make_pair(slot->name_, *slot));

		delete slot;
	}

	return slots;

}

std::map<std::string, Animation> TempSkeletalAnim::ReadAnimationDataFromJSON(rapidjson::Document& ske_document)
{
	const rapidjson::Value& anims_array = ske_document["armature"][0]["animation"];

	std::map<std::string, Animation> anims;

	for (int anim_num = 0; anim_num < (int)anims_array.Size(); ++anim_num)
	{
		Animation* anim = new Animation();
		anim->name = anims_array[anim_num]["name"].GetString();
		anim->duration = anims_array[anim_num]["duration"].GetFloat();
		if (anims_array[anim_num].HasMember("bone"))
		{
			const rapidjson::Value& anim_bones_array = ske_document["armature"][0]["animation"][anim_num]["bone"];

			for (int it = 0; it < anim_bones_array.Size(); ++it)
			{
				BoneKey* bKey = new BoneKey;

				if (anim_bones_array[it]["name"].GetString() == NULL)
				{
					int i = 0;
				}

				bKey->name = anim_bones_array[it]["name"].GetString();
				//Need a nested loop

				if (anim_bones_array[it].HasMember("translateFrame"))
				{
					const rapidjson::Value& anim_bones_trans_array = ske_document["armature"][0]["animation"][anim_num]["bone"][it]["translateFrame"];

					for (int it2 = 0; it2 < anim_bones_trans_array.Size(); ++it2)
					{
						//Issue also here!
						TranslationKey* trans_key = anim_pars->ReadTranslationKeyDataFromJSON(anim_bones_trans_array[it2]);

						//Issue here abouts
						bKey->translation_keys.push_back(trans_key);

					}
				}
				else
				{
					TranslationKey* trans_key = new TranslationKey;
					trans_key->start_time = 0.0f;
					trans_key->time_to_next_key = 0.0f;
					trans_key->translation = gef::Vector2(0, 0);
					bKey->translation_keys.push_back(trans_key);
				}

				//Do it again for rotation keys

				//Error here for some reason?
				//Seems to have issues redefining it
				//But doesnt have the same problem as the ither one though
				//Its because there is no rotation data its not a constant


				if (anim_bones_array[it].HasMember("rotateFrame"))
				{
					const rapidjson::Value& anim_bones_rot_array = ske_document["armature"][0]["animation"][anim_num]["bone"][it]["rotateFrame"];

					for (int it3 = 0; it3 < anim_bones_rot_array.Size(); ++it3)
					{
						RotationKey* rot_key = anim_pars->ReadRotationKeyDataFromJSON(anim_bones_rot_array[it3]);

						bKey->rotation_keys.push_back(rot_key);
					}
				}
				else
				{
					RotationKey* rot_key = new RotationKey;
					rot_key->rotation = 0.0f;
					rot_key->start_time = 0.0f;
					rot_key->time_to_next_key = 0.0f;
					bKey->rotation_keys.push_back(rot_key);
				}

				anim->bone_keys.push_back(bKey);
			}

			anims.insert(std::make_pair(anim->name, *anim));

			delete anim;
		}
	}

	return anims;
}

std::map<std::string, Bone> TempSkeletalAnim::ReadBonesFromJSON(rapidjson::Document& ske_document)
{
	const rapidjson::Value& bones_array = ske_document["armature"][0]["bone"];

	std::map<std::string, Bone> bones;

	for (int bone_num = 0; bone_num < (int)bones_array.Size(); ++bone_num)
	{
		Bone* bone = new Bone();
		bone->name_ = bones_array[bone_num]["name"].GetString();

		if (bones_array[bone_num].HasMember("parent"))
		{
			bone->parent_name_ = bones_array[bone_num]["parent"].GetString();
		}
		else
		{
			bone->parent_name_ = "none";
		}

		if (bones_array[bone_num].HasMember("transform"))
		{
			bone->x_ = bones_array[bone_num]["transform"]["x"].GetFloat();
			bone->y_ = bones_array[bone_num]["transform"]["y"].GetFloat();
			bone->rot_ = bones_array[bone_num]["transform"]["skY"].GetFloat();
		}
		else
		{
			bone->x_ = 0.f;
			bone->y_ = 0.f;
			bone->rot_ = 0.f;

		}

		bone->BuildLocalTransform();
		bones.insert(std::make_pair(bone->name_, *bone));

		delete bone;
	}

	//BuildWorldTransforms(&bones);
	SetParentsOfBones(&bones);

	return bones;
}

void TempSkeletalAnim::SetParentsOfBones(std::map<std::string, Bone>* bones)
{
	for (auto bone_ : *bones)
	{
		if (bone_.second.parent_name_ != "none");
		{
			std::string parent_name, name;
			parent_name = bone_.second.parent_name_;
			name = bone_.first;
			for (auto i: *bones)
			{
				//Changes with the pointer changing
				if (i.first == parent_name)
				{
					//Bone* b = new Bone;
					//b = *i.second;
					//bone_.second.parent_ = i.second;
					bones->at(name).parent_ = &bones->at(i.first);
					//break;
				}
			}
		}
	}

	for (auto bone_ : *bones)
	{
		if (bone_.second.parent_name_ != "none")
		{
			bones->at(bone_.first).world_transform_m = bones->at(bone_.first).local_transform_m * bones->at(bone_.first).parent_->local_transform_m;
			//bone_.second.world_transform_m = bone_.second.local_transform_m * bone_.second.parent_->local_transform_m;
		}
		else
		{
			bones->at(bone_.first).world_transform_m = bones->at(bone_.first).local_transform_m;
			//bone_.second.world_transform_m = bone_.second.local_transform_m;
		}
	}
}

void TempSkeletalAnim::CalculateWorldBoneTransform(Animation* anim, int current_frame)
{
	/*Un sure how this has been setup so unsure how to continue*/

	//Is this correct?

	//only get key start times if anim is valid
	if (anim != NULL)
	{
		//Set intial start time to 0
		float start_time_T = 0.f;

		//Set intial start time to 0
		float start_time_R = 0.f;


		//Start times are not being added properly

		//Loop through each of the bone keys
		for (int i = 0; i < anim->bone_keys.size(); i++)
		{
			//check if bone has translation or rotation

			//How does current frame relate?


			for (int j = 0; j < anim->bone_keys[i]->translation_keys.size(); j++)
			{
				//if (anim->bone_keys[i]->translation_keys.size() > current_frame)
				//{
					//	if (anim->bone_keys[i]->translation_keys[current_frame] != NULL)
					//	{
							//set each bone 
				anim->bone_keys[i]->translation_keys[j]->start_time = start_time_T;
				start_time_T += anim->bone_keys[i]->translation_keys[j]->time_to_next_key;
				//	}
			//}
			}

			start_time_T = 0.0f;


			for (int l = 0; l < anim->bone_keys[i]->rotation_keys.size(); l++)
			{
				//if (anim->bone_keys[i]->rotation_keys.size() > current_frame)
				//{

				//	if (anim->bone_keys[i]->rotation_keys[current_frame] != NULL)
				//	{
						//set each bone 
				anim->bone_keys[i]->rotation_keys[l]->start_time = start_time_R;
				start_time_R += anim->bone_keys[i]->rotation_keys[l]->time_to_next_key;
				//	}
				//}
			}

			start_time_R = 0.0f;
		}


		////Loop through each of the bone keys
		//for (int i = 0; i < anim->bone_keys.size(); i++)
		//{
		//	//check if bone has translation or rotation

		//	for (int j = 0; j < anim->bone_keys[i]->rotation_keys.size(); j++)
		//	{
		//		//if (anim->bone_keys[i]->rotation_keys.size() > current_frame)
		//		//{

		//		//	if (anim->bone_keys[i]->rotation_keys[current_frame] != NULL)
		//		//	{
		//				//set each bone 
		//		anim->bone_keys[i]->rotation_keys[j]->start_time = start_time_R;
		//		start_time_R += anim->bone_keys[i]->rotation_keys[j]->time_to_next_key;
		//		//	}
		//		//}
		//	}

		//	start_time_R = 0.0f;
		//}
	}

	////Look at the video for the rest going from 30 mins onward etc

	//What is sprite_anim->bones
	for (auto& bone : bones_)
	{

		//Bone* bone = new Bone();


		gef::Matrix33 translation, rotation;
		translation.SetIdentity();
		rotation.SetIdentity();

		float localX = bone.second.x_;
		float localY = bone.second.y_;
		float localRot = bone.second.rot_;

		rotation.Rotate(gef::DegToRad(localRot));
		translation.SetTranslation(gef::Vector2(localX, localY));
		bone.second.local_transform_m = rotation * translation;




		/*Going to get down the rest and ask later how he set it up*/

		//Only porceed if anim is valid



		if (anim != NULL)
		{
			//loop through all bone keys in the animatiom
			for (auto& bKey : anim->bone_keys)
			{
				// If bone name mathces bone key name
				if (bone.second.name_ == bKey->name)
				{
					//calculate rotation from rotation keys
					for (int currKey = 0; currKey < bKey->rotation_keys.size(); currKey++)
					{
						//if (bKey->rotation_keys[currKey] != NULL)
						//{
							//loop through all rotation keys
						int nextKey = currKey >= bKey->rotation_keys.size() - 1 ? 0 : currKey + 1;
						if (current_frame >= bKey->rotation_keys[currKey]->start_time && current_frame < bKey->rotation_keys[nextKey]->start_time)
						{
							//Get lerp between rotation data
							float time = (current_frame - bKey->rotation_keys[currKey]->start_time) / (bKey->rotation_keys[nextKey]->start_time - bKey->rotation_keys[currKey]->start_time);
							localRot += (anim_pars->lerp(bKey->rotation_keys[currKey]->rotation, bKey->rotation_keys[nextKey]->rotation, time));
						}
						//End of cycle
						else if (currKey == nextKey)
						{
							localRot += bKey->rotation_keys[currKey]->rotation;
						}
						//}
					}

					//Calculate translation from translation keys
					for (int currKey = 0; currKey < bKey->translation_keys.size(); currKey++)
					{
						//loop through all rotation keys
						//if (bKey->translation_keys[currKey]!=NULL)
						//{
						int nextKey = currKey >= bKey->translation_keys.size() - 1 ? 0 : currKey + 1;
						if (current_frame >= bKey->translation_keys[currKey]->start_time && current_frame < bKey->translation_keys[nextKey]->start_time)
						{
							//Get lerp between translation key data
							float time = (current_frame - bKey->translation_keys[currKey]->start_time) / (bKey->translation_keys[nextKey]->start_time - bKey->translation_keys[currKey]->start_time);
							gef::Vector2 lerp_anim_pos;
							lerp_anim_pos.x = anim_pars->lerp(bKey->translation_keys[currKey]->translation.x, bKey->translation_keys[nextKey]->translation.x, time);
							lerp_anim_pos.y = anim_pars->lerp(bKey->translation_keys[currKey]->translation.y, bKey->translation_keys[nextKey]->translation.y, time);
							localX += lerp_anim_pos.x;
							localY += lerp_anim_pos.y;
						}
						//end of cycle
						else if (currKey == nextKey)
						{
							localX += bKey->translation_keys[currKey]->translation.x;
							localY += bKey->translation_keys[currKey]->translation.y;
						}
						//}
					}

					break;

				}
			}
		}
		rotation.Rotate(gef::DegToRad(localRot));
		translation.SetTranslation(gef::Vector2(localX, localY));
		bone.second.New_local_transform_m = rotation * translation;

	}

	for (auto& bone : bones_)
	{
		for (auto& child_bone : bones_)
		{
			if (bone.second.name_ == child_bone.second.parent_name_)
			{
				child_bone.second.world_transform_m = child_bone.second.New_local_transform_m * bone.second.world_transform_m;
			}
		}
	}

	//return bones_;

}

void TempSkeletalAnim::RenderUpdate(const gef::Vector2 sprite_pos_,gef::Sprite& sprite_, const std::string part, gef::Matrix33& sprite_offset_transform_m, gef::Matrix33& world_bone_transforming_m, gef::Matrix33& sub_texture_transform_m, gef::Matrix33& local_home_transform_m)
{
	sprite_offset_transform_m = skin_slots.at(part).transform_m_;
	world_bone_transforming_m = bones_.at(part).world_transform_m;
	std::string part_name = skin_slots.at(part).part_name_;
	sub_texture_transform_m = text_atlas.subtex_atlas.at(part_name).transform_m_;
	local_home_transform_m = bones_.at(part).local_transform_m;

	SetSpriteSizeAndPositionForFrame(&sprite_, sprite_pos_.x, sprite_pos_.y, &text_atlas, part_name);
		

	//sprite_renderer_->DrawSprite(sprite_, sub_texture_transform_m * sprite_offset_transform_m * world_bone_transforming_m * rig_transform_m_);
		
}

void TempSkeletalAnim::SetupRig(gef::Vector2 sprite_pos_)
{
	rig_transform_m_.SetIdentity();
	rig_transform_m_.Scale(gef::Vector2(scale, scale));
	rig_transform_m_.SetTranslation(gef::Vector2(sprite_pos_.x, sprite_pos_.y));
}