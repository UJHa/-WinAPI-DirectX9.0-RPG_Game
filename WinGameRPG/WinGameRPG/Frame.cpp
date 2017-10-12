#include "Frame.h"
#include "GameSystem.h"
Frame::Frame()
{
}

Frame::~Frame()
{
}
void Frame::Init(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite, LPDIRECT3DTEXTURE9 texture, int left, int top, int width, int height)
{
	_sprite = sprite;
	_texture = texture;
	_width = width;
	_height = height;
	/*for (int i = 0; i < 3; i++)
	{
	_srcTextureRect.left = textureInfo.Width / 3 * i;
	_srcTextureRect.top = 0;
	_srcTextureRect.right = textureInfo.Width / 3 * (i + 1);
	_srcTextureRect.bottom = textureInfo.Height / 4;
	}*/
	_srcTextureRect.left = left;
	_srcTextureRect.top = top;
	_srcTextureRect.right = _width;
	_srcTextureRect.bottom = _height;

	_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}
void Frame::DInit()
{

}
void Frame::Render()
{
	//스프라이트 출력 전 모양 조정(위치,크기,회전)
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)_width / 2.0f, (float)_height / 2.0f);
	D3DXVECTOR2 translate = D3DXVECTOR2((float)GameSystem::GetInstance()->GetWindowWidth() / 2.0f - (float)_width / 2.0f, (float)GameSystem::GetInstance()->GetWindowHeight() / 2.0f - (float)_height / 2.0f);
	D3DXVECTOR2 scaling = D3DXVECTOR2(1.0f, 1.0f);
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &scaling, &spriteCenter, 0.0f, &translate);
	_sprite->SetTransform(&matrix);
	
	_sprite->Draw(_texture, &_srcTextureRect, NULL, NULL, _textureColor);
}
void Frame::Release()
{

}
void Frame::Reset(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite)
{

}