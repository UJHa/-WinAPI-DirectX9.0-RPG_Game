#pragma once
#include<D3DX9.h>
#include<vector>
struct Frame;
struct Texture;
class Sprite
{
//DirectX
private:
	LPDIRECT3DTEXTURE9 _texture;
	RECT _srcTextureRect;
	D3DCOLOR _textureColor;
	D3DXIMAGE_INFO _textureInfo;
	Texture* _srcTexture;
private:
	//Frame* _frame;
	std::vector<Frame*> _frameList;
	int _currentFrame;
	float _frameTime;

	LPCWSTR _textureFileName;
	LPCWSTR _scriptFileName;

	float _x;
	float _y;
public:
	Sprite(LPCWSTR textureFileName, LPCWSTR scriptFileName);
	~Sprite();

	void Init();
	void DInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();
	void SetPosition(float x, float y);
};