// 2021_11_18.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "2021_11_18.h"

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


// 1. 시작 인수
// --> notepad.exe PID 값을 획득해라.
// --> M 프로그램은 바로 실행이기 때문에 실행 인수가 없음: 0 (M)
//  --> M`를 실행할 때 pid 값을 인수로 줘야 한다!
// --> M` 프로그램은 M이 실행시켜 줄 때 notepad.exe PID를 전달 : PID (M`). 항상 0이 아닌 값

// ! 시작 인수는 전역 변수로 선언되어야 한다 ! --> notepad.exe의 PID 값을 보관
int g_pid;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //int pidz;
    WCHAR buf[128] = { 0, };

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 전달된 첫번째 인수를 숫자로 변환
    g_pid = _wtoi(lpCmdLine);
    // 인수 정보 확인
    wsprintfW(buf, L"cmd: %d", g_pid);
    MessageBox(NULL, buf, buf, MB_OK);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY20211118, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY20211118));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY20211118));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY20211118);
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

PROCESS_INFORMATION g_pi, pi;
STARTUPINFO g_si, si;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:
    {
        ResumeThread(g_pi.hThread);
    }
        break;
    case WM_RBUTTONDOWN:
    {
        if (0 == g_pid)
            break;
        HANDLE handle;
        // 4. PID를 이용해 프로세스의 HANDLE 획득
        handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, g_pid);
        TerminateProcess(handle, 0);
        //SuspendThread(g_pi.hThread);
        //TerminateProcess(g_pi.hProcess, 0);
        //TerminateProcess(GetCurrentProcess(), 0);
    }
        break;
    case WM_LBUTTONDOWN:
    {
        if (0 != g_pid)
            break;
        WCHAR buf[128] = L"C:\\Windows\\System32\\notepad.exe";
        WCHAR me[128] = L"D:\\2021_wikim\\2021_vcpp1\\2021_11_18\\Debug\\2021_11_18.exe";
        // 내 프로그램의 경로 + notepad.exe PID 값을 조합할 버퍼
        WCHAR mbuf[128] = { 0, };   
        // g_pi.dwProcessId : 생성한 프로세스의 PID 값
        // g_pi.hProcess : 생성한 프로세스의 핸들
        // g_pi.dwThreadId : Base Thread ID 값
        // g_pi.hThread : 생성한 프로세스의 Base Thread 핸들

        // 2. notepad 생성
        CreateProcess(NULL, buf,NULL, NULL, FALSE, 0, NULL, NULL, &g_si, &g_pi);

        // 3. 생성된 notepad의 pid를 M`가 실행될 때 같이 전달해야 함!
        wsprintfW(mbuf, L"%s %d", me, g_pi.dwProcessId);

        CreateProcess(NULL, mbuf, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
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
            WCHAR buf[128] = { 0, };
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            wsprintfW(buf, L"Child - PID[ %d ], TID[ %d ]", g_pi.dwProcessId, g_pi.dwThreadId);
            TextOut(hdc, 10, 10, buf, lstrlen(buf));
            wsprintfW(buf, L"My Info - PID[ %d ], TID[ %d ]",
                GetCurrentProcessId( ), GetCurrentThreadId( ));
            TextOut(hdc, 10, 30, buf, lstrlen(buf));
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
