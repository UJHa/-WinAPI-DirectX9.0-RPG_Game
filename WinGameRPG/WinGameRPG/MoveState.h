#pragma once
class Character;
class MoveState
{
public:
	MoveState();
	~MoveState();
private:
	bool _isMoving;
	float _movingDuration;
	Character* _character;
public:
	bool IsMoving();
	void Init(Character* character);
	void SetMoving(bool isMoving);
	float GetMovingDuration();
	void Start();
	void Stop();
	void Update(float deltaTime);
	void UpdateMove(float deltaTime);
};