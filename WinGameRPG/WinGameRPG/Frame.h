#pragma once
#include<D3DX9.h>
class Texture;
class Frame
{
private:
	Texture* _texture;

	RECT _srcTextureRect;
	D3DCOLOR _textureColor;

private:
	int _width;
	int _height;
	float _frameDelay;
public:
	Frame();
	~Frame();
	void Init(Texture* texture, int left, int top, int width, int height,float frameDelay);
	void DInit();
	void Render();
	void Release();
	void Reset();
	float GetFrameDelay();
};