#pragma once

#include <Windows.h>

// �������� �޸𸮸� �Ҵ�޾� vector�� �Է�

class CMouseInfo
{
public:
	// �̺�Ʈ�� ���� ��ġ�� ��ǥ ��
	int				m_x;
	int				m_y;

	// �̺�Ʈ�� ���� : ������ �޽���
	UINT			m_msg;

	// ���� �ð� ��
	int				m_time;

	// �ð� ���� ��
	int				m_diff_time;

	// ����Ʈ ������
	CMouseInfo(){}
	
	// �μ��� �ִ� ������
	CMouseInfo(
		LPARAM					lParam__,
		UINT					message__,
		int						time__
		);
};

