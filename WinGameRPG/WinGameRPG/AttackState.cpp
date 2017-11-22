#include"AttackState.h"
#include"sComponentMsgParam.h"
#include"ComponentSystem.h"
#include"Character.h"
AttackState::AttackState()
{
	_nowState = eStateType::ET_ATTACK;
}
AttackState::~AttackState()
{

}

void AttackState::Init(Character* character)
{
	State::Init(character);
}
void AttackState::DInit()
{
	State::DInit();
}
void AttackState::Update(float deltaTime)
{
	State::Update(deltaTime);
	_character->ResetTarget();
	if (eStateType::ET_NONE != _nextState)
	{
		_nextState = eStateType::ET_IDLE;
	}
}
void AttackState::Render()
{
	State::Render();
}
void AttackState::Release()
{
	State::Release();
}
void AttackState::Reset()
{
	State::Reset();
}

void AttackState::Start()
{
	State::Start();
	sComponentMsgParam msgParam;
	msgParam.sender = (Component*)_character;
	msgParam.attackPoint = _character->GetAttackPoint();
	wchar_t timeCheck[256];
	swprintf(timeCheck, L"GetAttackPoint %d\n", _character->GetAttackPoint());
	OutputDebugString(timeCheck);
	msgParam.receiver = _character->GetTarget();
	msgParam.message = L"Attack";
	ComponentSystem::GetInstance()->SendMsg(msgParam);
}
void AttackState::Stop()
{

}