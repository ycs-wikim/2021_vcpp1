// 2021_10_07.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "2021_10_07.h"

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
    LoadStringW(hInstance, IDC_MY20211007, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY20211007));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY20211007));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY20211007);
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

#define EX_01       0       /// 마우스 과제 예제
#define EX_02       0       // 5주차 과제 예제
#define EX_03       1       // 메뉴로 그림판 그리기

int g_flag;       /// 마우스가 클릭 되었는지 확인
int g_x, g_y;   /// 이전 좌표 보관

#if EX_03
int g_color;            // 1: 빨강, 2: 파랑, 3: 녹색
int g_draw_type;        // 그리기 종류를 보관
                        // 0이면 아무것도 하지 않는다.
                        // 1이면 선, 2면 사각형, 3이면 타원
#endif

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    // 각종 ID 값을 받아서 처리하는 메시지
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
#if EX_03
            // 리소스에 추가한 메뉴 아이디 값 확인
            case ID_123:
                MessageBox(hWnd, L"123", L"선그리기", MB_OK);
                // 이제부터 그리기 처리는 선으로 한다.
                g_draw_type = 1;
                break;
            case ID_124:
                MessageBox(hWnd, L"124", L"사각형 그리기", MB_OK);
                // 이제부터 그리기 처리는 사각형으로 한다.
                g_draw_type = 2;
                break;
            case ID_125:
                MessageBox(hWnd, L"125", L"원 그리기", MB_OK);
                // 이제부터 그리기 처리는 타원으로 한다.
                g_draw_type = 3;
                break;

            case ID_126:    // 빨간색
                g_color = 1;
                break;

            case ID_127:    // 파란색
                g_color = 2;
                break;

            case ID_128:    // 녹색
                g_color = 3;
                break;
#endif
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

#if EX_03
    case WM_LBUTTONDOWN:
    {
        g_x = LOWORD(lParam);
        g_y = HIWORD(lParam);
    }
        break;

    case WM_LBUTTONUP:
    {
        int x, y;
        HDC hdc;
        HPEN newPen, osPen;

        x = LOWORD(lParam);
        y = HIWORD(lParam);

        hdc = GetDC(hWnd);

        /// 선 색상 변경
        switch (g_color)
        {
        case 1:     /// 빨간색
            newPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
            break;

        case 2:     /// 파란색
            newPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
            break;

        case 3:     /// 녹색
            newPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
            break;
        default:
            newPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
            break;
        }

        osPen = (HPEN)SelectObject(hdc, newPen);

        /// 그리기 종류에 따라 그리기
        switch (g_draw_type)
        {
        case 1: /// 선 그리기
            MoveToEx(hdc, g_x, g_y, NULL);
            LineTo(hdc, x, y);
            break;

        case 2: /// 사각형 그리기
            Rectangle(hdc, g_x, g_y, x, y);
            break;

        case 3: /// 타원 그리기
            Ellipse(hdc, g_x, g_y, x, y);
            break;
        }

        SelectObject(hdc, osPen);
        DeleteObject(newPen);
        ReleaseDC(hWnd, hdc);
    }
        break;

    case WM_MOUSEMOVE:
        break;
#endif

#if EX_01
    // 이제부터 그리기 시작할거야.
    case WM_LBUTTONDOWN:
    {
        int x, y;

        // 좌표 값 획득
        x = LOWORD(lParam);
        y = HIWORD(lParam);

        // 현재 좌표를 바로 이전 과거 좌표로 변경
        g_x = x;
        g_y = y;

        // 그리기가 시작 되었음을 알림.
        g_flag = 1;
    }
        break;

    // 이제 그리기 그만할거야
    case WM_LBUTTONUP:
        // 그리기가 종료 되었다.
        g_flag = 0;
        break;

    // 움직일때마다 그릴거야.
    case WM_MOUSEMOVE:
    {
        int x, y;   // 현재 x, y 좌표 값
        HDC hdc;
        x = LOWORD(lParam);
        y = HIWORD(lParam);

        // 현재 상태 : 그릴 것인가?, 이전 좌표 값
        if (0 == g_flag)   // 그리기가 종료 되었는가?
            break;          // 그리기 완전 종료
        // 그리기 코드
        // 1. DC 획득
        hdc = GetDC(hWnd);

        // 2. 선을 그린다.
        MoveToEx(hdc, x, y, NULL);  // 현재 위치 기준
        LineTo(hdc, g_x, g_y);      // 과거 좌표로 섡을 그린다.

        // 3. DC 해제
        ReleaseDC(hWnd, hdc);

        g_x = x;        // 현재 좌표를 과거 좌표로 변경
        g_y = y;
    }
        break;
#endif

#if EX_02
    case WM_LBUTTONDOWN:
    {
        HDC hdc;
        RECT rect;
        rect.left = LOWORD(lParam);
        rect.top = HIWORD(lParam);
        rect.right = rect.left + 200;
        rect.bottom = rect.top + 200;

        hdc = GetDC(hWnd);

        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
        Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

        MoveToEx(hdc, rect.left, rect.top, NULL);
        LineTo(hdc, rect.right, rect.bottom);
        MoveToEx(hdc, rect.right, rect.top, NULL);
        LineTo(hdc, rect.left, rect.bottom);

        ReleaseDC(hWnd, hdc);
    }
        break;
#endif
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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
