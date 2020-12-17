#pragma once
#include"stdafx.h"
#include"../Vertex.h"
#include"IDrawObject.h"
#include"../../Common/CArrayBuffer.h"
namespace ButiEngine {
	

	struct DrawInformation :public IObject {
		DrawInformation() {}
		DrawInformation(const DrawSettings arg_DrawSettings) :drawSettings(arg_DrawSettings) {}
		DrawSettings drawSettings;
		bool isAlpha = false;
		bool isDepth = true;
		void Initialize()override {}
		void PreInitialize()override {}
		std::vector<std::shared_ptr<ICBuffer>> vec_exCBuffer;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isAlpha);
			archive(isDepth);
			archive(drawSettings);
			archive(vec_exCBuffer);
		}
		bool IsContainExCBuffer(const std::string& arg_cbufferName) {
			for (auto itr = vec_exCBuffer.begin(); itr != vec_exCBuffer.end(); itr++) {
				if ((*itr)->GetExName() == arg_cbufferName) {
					return true;
				}
			}
			return false;
		}
		void RemoveExCBuffer(const std::string& arg_cbufferName) {
			for (auto itr = vec_exCBuffer.begin(); itr != vec_exCBuffer.end(); ) {
				if ((*itr)->GetExName() == arg_cbufferName) {
					vec_exCBuffer.erase(itr);
					return;
				}
				else
					itr++;
			}
		}
		std::shared_ptr<ICBuffer> GetExCBuffer(const std::string& arg_cbufferName) {
			for (auto itr = vec_exCBuffer.begin(); itr != vec_exCBuffer.end(); ) {
				if ((*itr)->GetExName() == arg_cbufferName) {
					return *itr;
				}
				else {
					itr++;
				}
			}
			return nullptr;
		}

		std::shared_ptr< DrawInformation > Clone() {
			auto output = ObjectFactory::Create<DrawInformation>();

			output->drawSettings = drawSettings;
			output->isAlpha = isAlpha;
			output->isDepth = isDepth;
			for (auto itr = vec_exCBuffer.begin(); itr != vec_exCBuffer.end(); itr++) {
				output->vec_exCBuffer.push_back((*itr)->Clone());
			}

			return output;
		}
	};
	struct DrawData {
		

		void SetBlendMode(const BlendMode& arg_BlendMode);

		std::shared_ptr<Transform> transform;

		inline float GetMaxZ(const Matrix4x4& arg_viewMatrix){
			
			auto viewPos = transform->GetWorldPosition() * arg_viewMatrix;

			return viewPos.z;
		}
		
		ModelTag modelTag;
		
		MeshTag meshTag;
		
		ShaderTag shaderTag;

		std::vector < MaterialTag> vec_materialTags;
		std::vector<UINT> subset;

		std::shared_ptr< DrawInformation >shp_drawInfo;

		std::shared_ptr<IRenderer> shp_renderer;
		virtual std::shared_ptr<ICBuffer> AddICBuffer(std::shared_ptr<ICBuffer> arg_cbuffer) {
			shp_drawInfo-> vec_exCBuffer.push_back(arg_cbuffer);
			return arg_cbuffer;
		}

		inline std::shared_ptr<ICBuffer> GetICBuffer(const std::string& arg_bufferName) {

			for (auto itr =shp_drawInfo-> vec_exCBuffer.begin(); itr !=shp_drawInfo-> vec_exCBuffer.end(); itr++) {
				if ((*itr)->GetExName() == arg_bufferName) {
					return *itr;
				}
			}

			return nullptr;
		}

		template <class T>
		inline std::shared_ptr<CBuffer<T>> GetCBuffer(const std::string& arg_bufferName) {

			auto out = GetICBuffer(arg_bufferName);
			if (out && out->IsThis<CBuffer<T>>()) {
				return out->GetThis<CBuffer<T>>();
			}

			return nullptr;
		}
		template <class T>
			inline std::shared_ptr<CArrayBuffer<T>> GetCArrayBuffer(const std::string& arg_bufferName) {

			auto out = GetICBuffer(arg_bufferName);
			if (out && out->IsThis<CArrayBuffer<T>>()) {
				return out->GetThis<CArrayBuffer<T>>();
			}

			return nullptr;
		}
	protected:
		UINT cBufferCount = 0;
		std::shared_ptr < CBuffer<ShaderVariable>> cbuffer;
		std::shared_ptr<Collision::CollisionPrimitive>shp_primitive;
		unsigned int* collisionRegistPtr;
	};

	struct MeshDrawData:public DrawData,public IDrawObject,public IObject {
		void PreInitialize() override{}

		virtual void ChangeCullMode(const CullMode& arg_cull) = 0;
		virtual void ChangeFillMode(const bool isFill) = 0;
		virtual void ChangeSwitchFillMode() = 0;

		virtual void SetTransform(std::shared_ptr<Transform>& arg_transform) = 0;
		virtual void SetBlendMode(const BlendMode& arg_blendMode) = 0;

		std::shared_ptr<Collision::CollisionPrimitive_Box_AABB> GetMeshAABB()override;
		std::shared_ptr<Collision::CollisionPrimitive_Box_OBB> GetMeshOBB()override;

		void SetPrimitive(std::shared_ptr<Collision::CollisionPrimitive>arg_prim) override;
		void SetOctRegistPtr(unsigned int* arg_ptr) override;
		std::shared_ptr<Collision::CollisionPrimitive> GetPrimitive() override;
		unsigned int* GetOctRegistPtr() override;
	};
	struct ModelDrawData :public IBoneDrawObject
	{

		std::shared_ptr< CArrayBuffer<Matrix4x4>> cbuffer_bone;
	};
}

