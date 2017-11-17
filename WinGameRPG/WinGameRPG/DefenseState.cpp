#include "DefenseState.h"
#include "Character.h"
DefenseState::DefenseState()
{
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
	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}
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
	_character->DecreaseHP(attackPoint);
	if (false == _character->IsLive())
	{
		_character->SetCanMove(true);
		_character->MoveStop();
		//_character->ChangeState(eStateType::ET_DEAD);
		_nextState = eStateType::ET_DEAD;
	}
	else
	{
		//_character->ChangeState(eStateType::ET_IDLE);
		_nextState = eStateType::ET_IDLE;
	}
}
void DefenseState::Stop()
{

}