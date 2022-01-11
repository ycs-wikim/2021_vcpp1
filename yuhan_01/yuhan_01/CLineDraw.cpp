#include "CLineDraw.h"


// ������
CLineDraw::CLineDraw(LPARAM lParam__)
{
	initDrawLine(lParam__);
}


void CLineDraw::drawLine(HWND hWnd__, LPARAM lParam__)
{
	HDC hdc;

	initDrawLine(lParam__);

	hdc = GetDC(hWnd__);
	// ���׸��� 1. ���� �� ����, 2. ������ �� �׸���
	MoveToEx(hdc, m_start_x, m_start_y, NULL);
	LineTo(hdc, m_end_x, m_end_y);
	// ����

	ReleaseDC(hWnd__, hdc);
}


void CLineDraw::initDrawLine(LPARAM lParam__)
{
	// ���� �� ������ �⺻ ��
	m_start_x = 134;
	m_start_y = 123;
	// ���� ������ ���޵� ������ Ȱ��
	m_end_x = LOWORD(lParam__);
	m_end_y = HIWORD(lParam__);
}
