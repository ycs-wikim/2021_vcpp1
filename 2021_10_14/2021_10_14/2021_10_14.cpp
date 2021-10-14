// 2021_10_14.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "2021_10_14.h"

#include <stdlib.h>     // 랜덤 값 획득 함수 호출
#include <time.h>       // SEED 값 조절을 위해 현재 시간 값 이용

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
    LoadStringW(hInstance, IDC_MY20211014, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY20211014));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY20211014));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY20211014);
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

// 전역 변수로 나와 상대의 좌표 자료형 선언. 아이템의 좌료 선언
RECT g_me, g_item;
RECT g_you[3];

// 상대의 속도를 가질 변수
int g_speed;

// 점수
int g_score;

// 타이머
int g_timer;

// 타이머 아이디를 선언
#define TIMER_ID_1          1       // 상대 이동을 위한 타이머 아이디
#define TIMER_ID_2          2

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

    // 나와 상대의 위치 초기 값 설정
    case WM_CREATE:
        // 나는 40 * 40의 정사각형 좌표로 구성
        g_me.left = 10;
        g_me.top = 10;
        g_me.right = 50;
        g_me.bottom = 50;
        // 상대는 40 * 40 정사각형 좌표 구성
        g_you[0].left = 300;
        g_you[0].top = 300;
        g_you[0].right = g_you[0].left + 40;
        g_you[0].bottom = g_you[0].top + 40;

        // SEED 값 초기화
        srand(time(NULL));

        g_you[1].left = rand() % 450;
        g_you[1].top = rand() % 450;
        g_you[1].right = g_you[1].left + 40;
        g_you[1].bottom = g_you[1].top + 40;

        g_you[2].left = rand( ) % 300;
        g_you[2].top = rand() %300;
        g_you[2].right = g_you[2].left + 40;
        g_you[2].bottom = g_you[2].top + 40;

        // 아이템 좌표 구성 : 40 * 40 좌표
        g_item.left = rand() % 400;     // 아이템의 left 값 무작위 설정
        g_item.top = rand() % 400;      // 아이템의 top 값 무작위 설정. 0 ~ 399
        g_item.right = g_item.left + 40;
        g_item.bottom = g_item.top + 40;

        // 초기 상대 속도 설정. 1초
        g_speed = 1000;
        // 타이머를 기동 --> 주기적으로 WM_TIMER를 OS가 호출해준다.
        SetTimer(hWnd, TIMER_ID_1, g_speed, NULL);

        // 게임 타이머 시간 설정. 무조건 1초에 한번씩만 불려야 함
        g_timer = 10;       // 제한 시간 10초
        SetTimer(hWnd, TIMER_ID_2, 1000, NULL);
        break;

        // 상대의 이동
    case WM_TIMER:
    {
        int i = 0;
        RECT dst;       // 겹침 영역의 좌표를 획득

        // WM_TIMER 메시지는 wParam에 SetTimer에서 설정한 ID 값이 넘겨져 온다!
        switch (wParam)
        {
            // 상대가 주기적으로 이동하는 타이머가 도착했다!
        case TIMER_ID_1:
            if (g_speed != 100)
            {
                g_speed -= 100;     // 0.1초씩 감소

                // 먼저 현재 동작 중인 타이머를 제거
                KillTimer(hWnd, TIMER_ID_1);
                // 다시 새롭게 타이머를 설정
                SetTimer(hWnd, TIMER_ID_1, g_speed, NULL);
            }

            for (i = 0; i < 3; i++)
            {
                // x 좌표에 대한 비교 : 나와 상대 값을 이용
                if (g_me.left < g_you[i].left)     // 참: 나는 상대의 왼쪽에 있다!
                {
                    // 상대는 추적하기 위해 왼쪽으로 이동해야 한다.
                    // x좌표의 감소
                    g_you[i].left -= 10;
                    g_you[i].right -= 10;
                }   // 거짓 : 나는 상대의 오른쪽에 있다.
                else
                {
                    // 상대는 추적하기 위해 오른쪽으로 이동해야 한다.
                    // x좌표의 증가
                    g_you[i].left += 10;
                    g_you[i].right += 10;
                }

                // y 좌표에 대한 비교 : 나와 상대 값을 이용
                if (g_me.top < g_you[i].top)        // 참: 나는 상대의 위쪽에 있다.
                {
                    // 상대는 추적을 위해 위쪽으로 이동
                    g_you[i].top -= 10;
                    g_you[i].bottom -= 10;
                }
                else
                {
                    g_you[i].top += 10;
                    g_you[i].bottom += 10;
                }

                // 좌표 겹침을 확인
                if (TRUE == IntersectRect(&dst, &g_me, &g_you[i]))     // 좌표 겹침이 존재한다면
                {
                    // 주기적인 WM_TIMER의 호출을 중단
                    KillTimer(hWnd, TIMER_ID_1);
                    // 메시지 박스는 OK 버튼 클릭 전까지는 아래 코드가 실행되지 않는다.
                    MessageBox(hWnd, L"아이쿠.. 당했네", L"게임오버", MB_OK);

                    // WndProc 자체를 종료
                    return 0;
                }
            }
        break;

        // 게임 타이머 감소
        case TIMER_ID_2:
            g_timer--;
            if (0 == g_timer)
            {
                KillTimer(hWnd, TIMER_ID_1);
                KillTimer(hWnd, TIMER_ID_2);
                MessageBox(hWnd, L"시간으로 종료", L"게임오버", MB_OK);
            }
            break;
        }
        // 화면 무효화
        InvalidateRect(hWnd, NULL, TRUE);
    }
        break;

    // 나의 이동
    case WM_KEYDOWN:
    {
        RECT dst;

        switch (wParam)
        {
            // 좌, 상, 우, 하 키가 입력되었는지 확인
        case VK_LEFT:   // x 좌표의 이동 (left, right) -> 감소
            g_me.left -= 10;
            g_me.right -= 10;
            break;

        case VK_RIGHT:  // x 좌표의 이동 (left, right) -> 증가
            g_me.left += 10;
            g_me.right += 10;
            break;

        case VK_UP:     // y 좌표의 이동 (top, botoom) -> 감소
            g_me.top -= 10;
            g_me.bottom -= 10;
            break;

        case VK_DOWN:   // y 좌표의 이동 (top, botoom) -> 증가
            g_me.top += 10;
            g_me.bottom += 10;
            break;
        }
        // 좌표 값을 변경하고 난 다음 위치
        // 내가 아이템을 먹을 수 있는 위치인가?
        if (TRUE == IntersectRect(&dst, &g_me, &g_item))
        {
            /*
            // 1. 아이템을 사라지게 한다.
            g_item.left = -10;
            g_item.top -= 10;
            g_item.right = g_item.left + 5;
            g_item.bottom = g_item.top + 5;
            */

            // 2. 아이템을 다른 위치에 다시 표시
            g_item.left = rand() % 400;
            g_item.top = rand() % 400;
            g_item.right = g_item.left + 40;
            g_item.bottom = g_item.top + 40;

            // 아이템 획득 시 점수 100점 추가
            g_score += 100;
        }
        // WM_PAINT를 강제로 프로그래머가 호출하는 방법
        InvalidateRect(hWnd, NULL, TRUE);
    }
        break;

    case WM_PAINT:
        {
            int i = 0;
            WCHAR score[64] = { 0, };
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            // 점수 출력
            wsprintfW(score, L"Score : %d\t Timer: %d", g_score, g_timer);
            TextOut(hdc, 10, 500, score, lstrlenW(score));

            // 나 그리기
            Ellipse(hdc, g_me.left, g_me.top, g_me.right, g_me.bottom);
            // 상대 그리기
            for( i  = 0; i < 3; i++)
                Rectangle(hdc, g_you[i].left, g_you[i].top, g_you[i].right, g_you[i].bottom);
            // 아이템 그리기
            Rectangle(hdc, g_item.left, g_item.top, g_item.right, g_item.bottom);
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
