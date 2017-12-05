#include"LifeNPC.h"
LifeNPC::LifeNPC(wstring name, wstring scriptName, wstring pngName) :
	Character(name, scriptName, pngName)
{
	_componentType = eComponentType::CT_NPC;
}

LifeNPC::~LifeNPC()
{
}
void LifeNPC::UpdateAI()
{

}
void LifeNPC::UpdateText()
{

}