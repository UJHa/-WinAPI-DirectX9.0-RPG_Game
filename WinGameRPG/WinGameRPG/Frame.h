#pragma once
#include<D3DX9.h>
class Texture;
class Frame
{
private:
	Texture* _texture;
	LPD3DXSPRITE _sprite;

	RECT _srcTextureRect;
	D3DCOLOR _textureColor;

private:
	int _width;
	int _height;
	float _rotate;
	float _frameDelay;

	float _x;
	float _y;
public:
	Frame();
	~Frame();
	void Init(Texture* texture, int left, int top, int width, int height, float rotate, float frameDelay);
	void DInit();
	void Render();
	void Release();
	void Reset(Texture* texture, int left, int top, int width, int height, float rotate, float frameDelay);
	float GetFrameDelay();
	void SetPosition(float x, float y);
};