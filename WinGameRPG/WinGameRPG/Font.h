#pragma once
#include<D3DX9.h>
#include<string>
class Font
{
public:
	Font(std::wstring fontName, int fontSize, D3DCOLOR color);
	~Font();
private:
	ID3DXFont* _dxFont;
	D3DCOLOR _color;
	std::wstring _text;

	int _x;
	int _y;
	int _width;
	int _height;
public:
	void SetRect(int x, int y, int width, int height);
	void SetPosition(int x, int y);
	void SetText(std::wstring text);
	void Render();
};