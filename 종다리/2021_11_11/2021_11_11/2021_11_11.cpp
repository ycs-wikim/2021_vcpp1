// 2021_11_11.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "2021_11_11.h"

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

// mutex 변수 선언
HANDLE g_mux;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    g_mux = OpenMutex(MUTEX_ALL_ACCESS, TRUE, L"asdf");
    if (NULL == g_mux)
    {
        MessageBox(NULL, L"외로워요...", L"asdf", MB_OK);
    }
    else
    {
        MessageBox(NULL, L"아.. 누군가 있군요.", L"asdf", MB_OK);
        return 0;
    }
    g_mux = CreateMutex(NULL, FALSE, L"asdf");

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY20211111, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY20211111));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY20211111));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY20211111);
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

#define CRITICALSECTION     0
#define SEMAPHORE           0
#define MUTEX               0

HWND g_hWnd;
int g_x;

#if CRITICALSECTION
BOOL g_flag;
CRITICAL_SECTION g_cs;
#endif

HANDLE g_Mux;

HANDLE g_SEM;
int g_y;

DWORD WINAPI Pig(LPVOID Param)
{
    int x = (int) Param;
    HDC hdc;
    int i; // 반복문에 사용
    int j;
    int y;
    WCHAR Buffer[128] = { 0, };

    hdc = GetDC(g_hWnd);
#if SEMAPHORE
    WaitForSingleObject(g_SEM, INFINITE);
#endif
    g_y += 20;
    y = g_y;
    TextOut(hdc, 10, y, L"wait...", 8);
    GdiFlush();
    for (i = 0; i < 100; i++)
    {
#if CRITICALSECTION
        //while (g_flag == TRUE) // 다른 애가 사용중이라는 뜻.
        //{
        //    // 여기에 만약 sleep 함수를 넣는다면?
        //    // g_flag가 false가 되는 시점을 놓칠 수 있기 때문에
        //    // 아무것도 안하는게 좋다.
        //} // g_flag가 FALSE가 되면 반복문을 빠져나온다.
        //g_flag = TRUE;
        // 임계영역 시작.
        EnterCriticalSection(&g_cs);

        g_x = x;
        MoveToEx(hdc, g_x, 0, NULL);
        Sleep(30);
        LineTo(hdc, g_x, i);
        //// 임계영역 종료
#endif
        WaitForSingleObject(g_Mux, INFINITE);
        wsprintfW(Buffer, L"%d%%", i + 1);
        for (j = 0; j < i; j++)
        {
            lstrcatW(Buffer, L"|");
        }
        TextOut(hdc, 10, y, Buffer, lstrlenW(Buffer));
        Sleep(30);
        ReleaseMutex(g_Mux);
#if CRITICALSECTION
        //g_flag = FALSE;
        LeaveCriticalSection(&g_cs);
#endif
        
    }
#if SEMAPHORE
    ReleaseSemaphore(g_SEM, 1, NULL);
#endif
    ReleaseDC(g_hWnd, hdc);
    ExitThread(0);
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            g_hWnd = hWnd;
            g_Mux = CreateMutex(NULL, FALSE, NULL);
#if CRITICALSECTION
            InitializeCriticalSection(&g_cs);
#endif
#if SEMAPHORE
            g_SEM = CreateSemaphore(NULL, 3, 3, NULL);
#endif
        }
        break;
    case WM_LBUTTONDOWN:
        {
            int x = LOWORD(lParam);
            CreateThread(NULL, 0, Pig, (LPVOID)x, 0, NULL);
        }
        break;
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        CloseHandle(g_Mux);
#if CRITICALSECTION
        DeleteCriticalSection(&g_cs);
#endif
#if SEMAPHORE
        CloseHandle(g_SEM);
#endif
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
