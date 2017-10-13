#include "Frame.h"
#include "GameSystem.h"
#include "Texture.h"
Frame::Frame() :_frameDelay(0.0f)
{
}

Frame::~Frame()
{
}
void Frame::Init(Texture* texture, int left, int top, int width, int height, float frameDelay)
{
	_texture = texture;
	_width = width;
	_height = height;
	_srcTextureRect.left = left;
	_srcTextureRect.top = top;
	_srcTextureRect.right = left + _width;
	_srcTextureRect.bottom = top + _height;

	_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	
	_frameDelay = frameDelay;
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
	GameSystem::GetInstance()->GetSprite()->SetTransform(&matrix);
	
	GameSystem::GetInstance()->GetSprite()->Draw(_texture->GetTextureDX(), &_srcTextureRect, NULL, NULL, _textureColor);
}
void Frame::Release()
{

}
void Frame::Reset()
{

}
float Frame::GetFrameDelay()
{
	return _frameDelay;
}