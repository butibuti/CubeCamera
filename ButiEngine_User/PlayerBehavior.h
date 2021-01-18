#pragma once
#include"Header/BehaviorHeader.h"
namespace ButiEngine {

	class MapComponent;
	class PlayerCameraComponent;

	enum class MoveDirection
	{
		Up,
		Normal,
		Down,
		Fall,
		No,
	};

	class PlayerBehavior :public Behavior
	{
	public:
		std::string GetBehaviorName()override {
			return "PlayerBehavior";
		}
		void OnUpdate()override;
		void OnSet()override;
		void Start()override;
		std::shared_ptr<Behavior> Clone()override;
		void OnCollisionEnter(std::weak_ptr<GameObject> arg_other)override;
		void OnCollision(std::weak_ptr<GameObject> arg_other)override;
		void OnCollisionEnd(std::weak_ptr<GameObject> arg_other)override;
		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(isActive);
		}
		void OnShowUI()override;

		bool GetGoal() { return goal; }

		bool IsRollFinish();
		Vector3 GetMapPos() { return mapPos; }
	private:
		float length;
		std::shared_ptr<MapComponent> shp_map;
		std::shared_ptr<PlayerCameraComponent> shp_playerCamera;
		Vector3 mapPos;
		bool goal;
		bool fall;
		Vector3 afterFallPos;

		std::shared_ptr<RelativeTimer> timer;

		void Contoroll();
		void OnPushD();
		void OnPushA();
		void OnPushW();
		void OnPushS();
		void MoveRightUp();
		void MoveRight();
		void MoveRightDown();
		void MoveLeftUp();
		void MoveLeft();
		void MoveLeftDown();
		void MoveUpFront();
		void MoveFront();
		void MoveDownFront();
		void MoveUpBack();
		void MoveBack();
		void MoveDownBack();
		void RotationRight();
		void RotationLeft();
		void RotationFront();
		void RotationBack();
		void Fall();
		MoveDirection CheckMoveDirection(Vector3 movePos);
		bool CheckExistUnderBlock(Vector3 movePos);
		
		void CheckGoal();
	};

}

BUTI_REGIST_BEHAVIOR(ButiEngine::PlayerBehavior);