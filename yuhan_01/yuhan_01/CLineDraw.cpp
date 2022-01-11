#include "CLineDraw.h"


// 생성자
CLineDraw::CLineDraw(LPARAM lParam__)
{
	initDrawLine(lParam__);
}


void CLineDraw::drawLine(HWND hWnd__, LPARAM lParam__)
{
	HDC hdc;

	initDrawLine(lParam__);

	hdc = GetDC(hWnd__);
	// 선그리기 1. 시작 점 설정, 2. 실제로 선 그리기
	MoveToEx(hdc, m_start_x, m_start_y, NULL);
	LineTo(hdc, m_end_x, m_end_y);
	// 수정

	ReleaseDC(hWnd__, hdc);
}


void CLineDraw::initDrawLine(LPARAM lParam__)
{
	// 시작 점 정보는 기본 값
	m_start_x = 134;
	m_start_y = 123;
	// 끝점 정보는 전달된 정보를 활용
	m_end_x = LOWORD(lParam__);
	m_end_y = HIWORD(lParam__);
}
