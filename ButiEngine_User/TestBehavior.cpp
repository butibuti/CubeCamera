#include "stdafx_u.h"
#include "TestBehavior.h"

void ButiEngine::TestBehavior::OnUpdate()
{
	if (GameDevice::GetInput()->CheckKey(Keys::Space))
	{
		//‚±‚Á‚¿‚Ì‚Ù‚¤‚ª—Ç‚¢
		gameObject.lock()->transform->TranslateX(0.01f);
		//‚¾‚ß
		//gameObject.lock()->transform->SetLocalPosition().x += 0.01f;
	}
}

void ButiEngine::TestBehavior::OnSet()
{
}

void ButiEngine::TestBehavior::Start()
{
	//gameObject.lock()->SetGameObjectTag(gameObject.lock()->GetApplication().lock()->GetGameObjectTagManager()->CreateGameObjectTag("Test"));
}

std::shared_ptr<ButiEngine::Behavior> ButiEngine::TestBehavior::Clone()
{
	return ObjectFactory::Create<TestBehavior>();
}

void ButiEngine::TestBehavior::OnCollisionEnter(std::weak_ptr<GameObject> arg_other)
{
}

void ButiEngine::TestBehavior::OnCollision(std::weak_ptr<GameObject> arg_other)
{
	GUI::Begin("collision");
	GUI::Text(arg_other.lock()->GetGameObjectName());
	/*if (arg_other.lock()->GetGameObjectTag() == gameObject.lock()->GetGameObjectTag())
	{
		GUI::Text("tag");
	}*/
	GUI::End();
}

void ButiEngine::TestBehavior::OnCollisionEnd(std::weak_ptr<GameObject> arg_other)
{
}

void ButiEngine::TestBehavior::OnShowUI()
{
}
