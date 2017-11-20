#include"AttackState.h"
#include"sComponentMsgParam.h"
#include"ComponentSystem.h"
#include"Character.h"
AttackState::AttackState()
{

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
	_nextState = eStateType::ET_IDLE;
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
	msgParam.receiver = _character->GetTarget();
	msgParam.message = L"Attack";
	ComponentSystem::GetInstance()->SendMsg(msgParam);
	wchar_t timeCheck[256];
	swprintf(timeCheck, L"GetCoolTimeDur %f\n", _character->GetCoolTime());
	OutputDebugString(timeCheck);
}
void AttackState::Stop()
{

}