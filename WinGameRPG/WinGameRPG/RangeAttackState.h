#pragma once
#include<queue>
#include<vector>
#include<map>
#include"State.h"
#include"TileCell.h"
using namespace std;
class RangeAttackState : public State
{
public:
	RangeAttackState();
	~RangeAttackState();
public:
	void Update(float deltaTime);

	void Start();
	void Stop();
private:
	queue<TileCell*> _attackTileQueue;
	map<int, vector<TileCell*>> _waveTileCellList;
	int _waveIndex;
	int _range;
public:
	void SetWaveAttack(int range);
	void AttackEffectWave(int waveIndex);
	void RemoveEffectWave(int waveIndex);
};