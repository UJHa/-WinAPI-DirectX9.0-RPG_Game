#include"NPC.h"
#include"Map.h"
#include"ComponentSystem.h"
NPC::NPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR pngName) : Character(name, scriptName, pngName)
{
}

NPC::~NPC()
{
}