// yuhan_01.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "yuhan_01.h"
#include "CLineDraw.h"
#include "CMouseInfo.h"

// 시간 값 획득을 위한 헤더 추가
#include <ctime>

// 표준 이름 공간을 사용함!
using namespace std;

// vector 컨테이너를 사용함!
#include <vector>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_YUHAN01, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_YUHAN01));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_YUHAN01));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_YUHAN01);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

//////////////////////////// 동적 생성 메모리와 STL 설명 코드 시작
// 동적 메모리 할당으로 사용하기 위해 포인터 선언
// 프로그램 시작 시 동적 메모리를 할당, 종료 시 메모리 해제
// WM_CREATE, WM_DESTROY
CLineDraw *g_ld;

// vector 컨테이너 선언, 들어갈 내용은 WCHAR*의 자료형. 접근 컨테이너 명 g_vec
vector<WCHAR*> g_vec;
vector<int> g_int;
vector<char> g_char;
vector<CLineDraw> g_dl;
//////////////////////////// 동적 생성 메모리와 STL 설명 코드 끝

// 방명록 관련 기능 구현
// *로 자료형이 선언되어 있기 때문에 동적으로 생성해서 보관
vector<CMouseInfo*> g_vector;

// 그리기 시작 여부 확인 변수
BOOL g_draw = FALSE;
// 자유선의 이전 좌표 값
int g_x, g_y;
// 스레드 핸들
HANDLE g_tid;

/**
 * @brief	사용자 입력 정보를 재현한다.
 * 
 * @param	param	HWND
 * 
 * @return	스레드 종료 상태 값
 */
DWORD WINAPI replay(LPVOID param__)
{
	int i = 0;
	int time = 0;
	HDC hdc;
	HWND hWnd = (HWND)param__;
	// vector의 노드를 가리킬 포인터
	CMouseInfo *tmp = nullptr;
	CMouseInfo *next = nullptr;

	hdc = GetDC(hWnd);
	// vector는 배열과 동일하게 사용 가능!!!
	// 0 < -1
	if (0 != g_vector.size())
	{
		for (; i < (g_vector.size() - 1); i++)
		{
			tmp = g_vector[i];
			next = g_vector[i + 1];

			MoveToEx(hdc, tmp->m_x, tmp->m_y, NULL);
			LineTo(hdc, next->m_x, next->m_y);

			time = next->m_time - tmp->m_time;
			Sleep(time);
		}
	}
	ReleaseDC(hWnd, hdc);

	ExitThread(0);
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 동적 할당을 위한 임시 포인터
	CMouseInfo *ptr = nullptr;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

		// 재현 스레드 기동
	case WM_RBUTTONDOWN:
		g_tid = CreateThread(NULL, 0, replay, (LPVOID)hWnd, 0, NULL);
		break;
		// 스레드 종료
	case WM_KEYDOWN:
		TerminateThread(g_tid, 0);
		break;
	// 기준 시간이 초기화 되어야 한다.
	case WM_LBUTTONDOWN:
		// 1. 그리기가 시작 되었다!
		g_draw = TRUE;
		g_x = LOWORD(lParam);
		g_y = HIWORD(lParam);

		// 동적 메모리 할당 및 현재 정보 전달로 초기화
		// 2. 정보 구현체에 들어갈 내용을 이용하여 동적 메모리를 할당
		ptr = new CMouseInfo(lParam, message, GetCurrentTime());
		// 3. 할당된 정보 구현체를 vector에 보관한다.
		g_vector.push_back(ptr);
		break;

	case WM_LBUTTONUP:
		// 1. 그리기를 하지 않는다.
		g_draw = FALSE;
		// 2. 정보 구현체 내용 생성 및 동적 메모리 할당
		ptr = new CMouseInfo(lParam, message, GetCurrentTime());
		// 3. 할당된 정보 구현체를 vector에 보관한다.
		g_vector.push_back(ptr);
		break;

	case WM_MOUSEMOVE:
	{
		int x, y;
		HDC hdc;

		// 1. 그리기가 시작되었을 경우에만 동작한다.
		if (FALSE == g_draw)
			break;
		// 2. 정보 구현체 내용 생성 및 동적 메모리 할당
		ptr = new CMouseInfo(lParam, message, GetCurrentTime());
		// 3. 할당된 정보 구현체를 vector에 보관한다.
		g_vector.push_back(ptr);
		// 4. 실제로 자유선을 화면에 그린다.
		x = LOWORD(lParam);
		y = HIWORD(lParam);

		// 현재 좌표부터 이전 좌표로 선을 그려 자유선을 실제로 그린다.
		hdc = GetDC(hWnd);
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, g_x, g_y);
		ReleaseDC(hWnd, hdc);

		// 현재 위치는 항상 다음 WM의 이전 위치
		g_x = x;
		g_y = y;
	}
		break;
/*
	///////////////// 클래스의 동적 메모리 생성 코드 시작
	case WM_CREATE:
		g_ld = new CLineDraw;
		break;

	case WM_LBUTTONDOWN:
	{
		// 요구사항 : 기능, 비기능 요구사항 -> 문서화 -> 각자 개발
		//CLineDraw ld(lParam);
		// WCHAR 변수 선언
		WCHAR d1[16] = L"asdf111";
		WCHAR d2[16] = L"asdf222";
		WCHAR d3[16] = L"asdf333";

		g_ld->drawLine(hWnd, lParam);
		
		// vector에 값을 입력
		g_vec.push_back(d1);
		g_vec.push_back(d2);
		g_vec.push_back(d3);
	}
		break;

	case WM_RBUTTONDOWN:
	{
		int i = 0;

		// vector의 내용 출력
		for (; i < g_vec.size(); i++)
		{
			MessageBox(hWnd, g_vec[i], g_vec[i], MB_OK);
		}
	}
		break;
*/
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		// 동적 생성 메모리 삭제
		delete g_ld;
		// 실제로 프로그램이 종료 처리를 진행하도록 만들어주는 함수
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
