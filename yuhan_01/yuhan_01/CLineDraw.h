#pragma once

// 클래스 단위로 파일을 생성하여 작업할 때,
// 포함되어야하는 헤더 파일을 항상 추가해야 한다.
// 자바에서 import와 동일한 개념
#include <Windows.h>

/// 선을 그리는 클래스( 정보 + 기능 )
///		* 정보 : 멤버 변수
///		* 기능 : 멤버 함수(메서드)
/// * 선을 그리려면 2가지가 필요 : 시작점과 끝점
/// 클래스 == 구조체
/// 클래스와 구조체가 궁극적으로 다른 속성 : 권한
/// * public 권한 : 누구나 인스턴스를 생성하고, 접근할 수 이 있음
/// * protected 권한 : 특별한 관계에 놓인 클래스만 접근 가능
/// * private 권한 : 나만 접근 가능
class CLineDraw
{
// C 계열 클래스에서 권한을 주지 않으면 자동으로 권한은 private으로 설정됨
// 비기능적인 요구사항
	// 시작 점의 x, y 좌표
	int m_start_x;
	int m_start_y;
	// 끝 점의 x, y 좌표
	int m_end_x;
	int m_end_y;

public:
// 기능적인 요구사항
	// Doxygen 문법
	/**
	 * @brief	실제로 선을 그리는 멤버 함수
	 * 
	 * @param	hWnd__		윈도우 핸들
	 * @param	lParam__	마우스의 x, y 좌표 값
	 */
	void drawLine(HWND hWnd__, LPARAM lParam__);

	// 클래스의 초기화 작업을 수행하는 함수 : 생성자
	// 생성자 특징 : 클래스 이름과 동일, 반환 값이 없음, 오버라이딩 가능, 사용자가 의도하여 호출 가능,
	//			호출 코드가 없어도 자동으로 호출
	CLineDraw(LPARAM lParam__);

	// 비어있는 생성자 -> 디폴트 생성자
	CLineDraw(){}

private:
// 비기능 요구사항
	/**
	 * @brief	모든 생성자에서 초기화가 필요할 때 호출하는 함수
	 * 
	 * @param	lParam__	마우스의 x, y 좌표 값
	 */
	void initDrawLine(LPARAM lParam__);
};

