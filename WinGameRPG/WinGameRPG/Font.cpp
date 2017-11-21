#include"Font.h"
#include"GameSystem.h"
Font::Font(std::wstring fontName, int fontSize, D3DCOLOR color)
{
	_color = color;
	HRESULT hr = D3DXCreateFont(GameSystem::GetInstance()->GetDevice3d(), fontSize, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fontName.c_str(), &_dxFont);
	if (FAILED(hr))
	{
		MessageBox(0, L"Failed CreateFont", 0, 0);
	}
}

Font::~Font()
{
	RELEASE_COM(_dxFont);
}
void Font::SetRect(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}
void Font::SetPosition(int x, int y)
{
	_x = x;
	_y = y;
}
void Font::SetText(std::wstring text)
{
	_text = text;
}
void Font::Render()
{
	RECT rect;
	rect.left = _x;
	rect.right = _x + _width;
	rect.top = _y;
	rect.bottom = _y + _height;
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, NULL, 0.0f, NULL);
	GameSystem::GetInstance()->GetSprite()->SetTransform(&matrix);
	_dxFont->DrawTextW(GameSystem::GetInstance()->GetSprite(), _text.c_str(), -1, &rect, DT_CENTER, _color);
}