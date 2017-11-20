#include "IdleState.h"
#include "Character.h"
IdleState::IdleState()
{

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
	State::Update(deltaTime);
	if (false == _character->IsLive())
		return;
	if (false == _character->IsMoving())
		_character->UpdateAI();
}
void IdleState::Start()
{
	State::Start();
}
void IdleState::Stop()
{
	State::Stop();
}