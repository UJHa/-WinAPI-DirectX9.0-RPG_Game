#include "DefenseState.h"
#include "Character.h"
DefenseState::DefenseState()
{
	_nowState = eStateType::ET_DEFENSE;
}

DefenseState::~DefenseState()
{
}
void DefenseState::Init(Character* character)
{
	State::Init(character);
}
void DefenseState::DInit()
{
	State::DInit();
}
void DefenseState::Update(float deltaTime)
{
	State::Update(deltaTime);
}
void DefenseState::Render()
{
	State::Render();
}
void DefenseState::Release()
{
	State::Release();
}
void DefenseState::Reset()
{
	State::Reset();
}

void DefenseState::Start()
{
	State::Start();
	int attackPoint = _character->GetRecevieAttackPoint();
	wchar_t timeCheck[256];
	swprintf(timeCheck, L"DefenseState attacked %d, type : %d\n", attackPoint, _character->GetType());
	OutputDebugString(timeCheck);
	_character->DecreaseHP(attackPoint);
	if (false == _character->IsLive())
	{
		_character->SetCanMove(true);
		_character->MoveStop();
		_nextState = eStateType::ET_DEAD;
	}
	else
	{
		//_nextState = eStateType::ET_IDLE;
		_nextState = eStateType::ET_MOVE;
	}
}
void DefenseState::Stop()
{

}