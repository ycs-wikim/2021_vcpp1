#pragma once

#include <Windows.h>

// 동적으로 메모리를 할당받아 vector에 입력

class CMouseInfo
{
public:
	// 이벤트를 받은 위치의 좌표 값
	int				m_x;
	int				m_y;

	// 이벤트의 종류 : 윈도우 메시지
	UINT			m_msg;

	// 기준 시간 값
	int				m_time;

	// 시간 차이 값
	int				m_diff_time;

	// 디폴트 생성자
	CMouseInfo(){}
	
	// 인수가 있는 생성자
	CMouseInfo(
		LPARAM					lParam__,
		UINT					message__,
		int						time__
		);
};

