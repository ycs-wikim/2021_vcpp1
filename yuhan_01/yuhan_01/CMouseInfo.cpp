#include "CMouseInfo.h"

// �μ��� �ִ� �������� ����
CMouseInfo::CMouseInfo(
	LPARAM					lParam__,
	UINT					message__,
	int						time__
)
{
	m_x = LOWORD(lParam__);
	m_y = HIWORD(lParam__);
	m_msg = message__;
	m_time = time__;
}



