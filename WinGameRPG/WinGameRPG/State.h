#pragma once
class Character;
class State
{
public:
	State();
	~State();
protected:
	Character* _character;
public:
	virtual void Init(Character* character);
	virtual void Update(float deltaTime);

	virtual void Start();
	virtual void Stop();
};