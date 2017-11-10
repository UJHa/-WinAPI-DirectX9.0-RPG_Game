#pragma once
#include"Character.h"
struct sComponentMsgParam;
class NPC : public Character
{
private:
public:
	NPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR pngName);
	~NPC();
	void UpdateAI();
	void ReceiveMessage(std::wstring message, const sComponentMsgParam msgParam);
};