#include "IdleState.h"
#include "Character.h"
IdleState::IdleState()
{
	_nowState = eStateType::ET_IDLE;
}
IdleState::~IdleState()
{

}
void IdleState::Init(Character* character)
{
	State::Init(character);
}
void IdleState::Update(float deltaTime)
{
	if (false == _character->IsLive())
		return;
	if (false == _character->IsMoving())
		_character->UpdateAI();
	State::Update(deltaTime);
}
void IdleState::Start()
{
	State::Start();
}
void IdleState::Stop()
{
	State::Stop();
}