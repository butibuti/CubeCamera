#pragma once
#include"Header/GameComponentHeader.h"
namespace ButiEngine {

	class MapComponent;
	namespace Collision
	{
		class CollisionPrimitive_Box_AABB;
	}

	class InvisibleBlockComponent :public GameComponent
	{
	public:
		InvisibleBlockComponent() {}

		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::string GetGameComponentName()override {
			return "InvisibleBlockComponent";
		}
		std::shared_ptr<GameComponent> Clone()override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
		}
		void OnShowUI();

		void SetID(int i) { id = i; }
		int GetID() { return id; }
		void SetActive(bool active);
		bool IsActive() { return active; }
		void SetSeen(bool flag) { seen = flag; }
		bool IsSeen() { return seen; }
		bool IsHitPlayer() { return hitPlayer; }
		void SetMapPos(Vector3 mapPos) { this->mapPos = mapPos; }
	private:
		std::shared_ptr<MapComponent> shp_map;
		Vector3 mapPos;
		int id;
		std::shared_ptr<Collision::CollisionPrimitive_Box_AABB> shp_AABB;
		bool active;
		bool seen;
		bool hitPlayer;
	};

}
BUTI_REGIST_GAMECOMPONENT(ButiEngine::InvisibleBlockComponent)