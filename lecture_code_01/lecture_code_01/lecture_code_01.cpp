// lecture_code_01.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "lecture_code_01.h"

/// #define A B		// 앞으로 A는 B로 사용하겠다.
#define MAX_LOADSTRING 100

// 전역 변수: 인스턴스 -> 실행될 수 있도록 메모리에 적재된 상태
/// H --> Handle의 첫글자 : 인스턴스를 제어할 수 있는 변수
HINSTANCE hInst;                                // 현재 인스턴스입니다.
/// wchar_t : 유니코드 지원
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM	MyRegisterClass(HINSTANCE hInstance);
// 가장 작은 크기의 자료형 : bool -> 내부적으로 int 형이다. (패딩이 필요 없다)
BOOL	InitInstance(HINSTANCE, int);



// WndProc : VC++ 강의 진행 중에 항상 보게될 함수(main)
// WPARAM : Word Parameter -> char :: 키보드 입력 값, 특수 값
// LPARAM : Long Parameter -> int  :: 마우스 입력 값



LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 기존의 main( )과 동일한 역할
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,				// 인스턴스
                     _In_opt_ HINSTANCE hPrevInstance,		// 인스턴스
                     _In_ LPWSTR    lpCmdLine,				// argv
                     _In_ int       nCmdShow)				// 요청 값
{
    UNREFERENCED_PARAMETER(hPrevInstance);		// 사용하지 않는 인수를 자동 처리
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LECTURECODE01, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LECTURECODE01));

	// 메시지
    MSG msg;

    // 기본 메시지 루프입니다: 프로그램 종료시까지 항상 동작
	// OS가 메시지를 줄때까지 대기 -> 이벤트가 올때까지 대기
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	// 프로그램 종료
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
    wcex.lpfnWndProc    = WndProc;		// OS에게 이벤트가 발생하면 호출할 함수 포인터
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LECTURECODE01));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LECTURECODE01);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	// 윈도우 클래스를 등록 -> 윈도우 OS에게
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

   // 메인 윈도우를 설정대로 실제로 생성
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   // 오류 체크
   if (!hWnd)
   {
	  // 실패 반환
      return FALSE;
   }

   // 화면에 보이도록 표시
   ShowWindow(hWnd, nCmdShow);
   // 최신 상태로 보이도록 해달라
   UpdateWindow(hWnd);

   // 성공 반환
   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//		OS에 등록한 함수. 필요한 경우(이벤트 발생) OS가 항상 호출한다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

/*
 * VS.의 실행 모드와 방법
 * Ctrl + F5 : 실행 파일이 단독으로 실행
 * F5 : 로컬 윈도우 디버거가 기본으로 동작
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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

	// 마우스와 관련된 윈도우 메시지 : lParam의 정보에서 좌표 값을 획득
	case WM_LBUTTONDOWN:
	{
		int x;
		int y;

		x = LOWORD(lParam);
		y = HIWORD(lParam);

		HDC hdc = GetDC(hWnd); //BeginPaint(hWnd, &ps);

		// 시작점 설정: 0, 0
		MoveToEx(hdc, 0, 0, NULL);
		// 선 그리기
		LineTo(hdc, x, y);

		ReleaseDC(hWnd, hdc);
		//EndPaint(hWnd, &ps);

		// Break Point를 설정/해제 : F9
		// 디버깅 상태에서 한줄씩 실행 : F10
		// 디버깅 상태 강제 종료 : Shift + F5

		//MessageBox(hWnd, L"201807001 김원일", L"2주차 과제", MB_OK);
	}
		break;

	case WM_RBUTTONUP:
		MessageBox(hWnd, L"201807001 김원일\n오른쪽 버튼 클릭", L"확인", MB_OK);
		break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
			WCHAR string[32] = { 0, };
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			TextOut(hdc, 10, 10, L"202007001 김원일", lstrlenW(L"202007001 김원일"));
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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