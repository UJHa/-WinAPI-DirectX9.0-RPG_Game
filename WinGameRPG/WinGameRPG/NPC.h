#pragma once
#include"Character.h"
struct sComponentMsgParam;
class NPC : public Character
{
private:
public:
	NPC(wstring name, wstring scriptName, wstring pngName);
	~NPC();
	void UpdateAI();
};