#include "framework.h"
#include "Editor_Window.h"
#include "..\\MyEngine_SOURCE\\MyApplication.h"
#include "..\\MyEngine_Window\\MyLoadScenes.h"
#include "..\\MyEngine_Window\\MyLoadResources.h"


// ========================= 무조건 여기서 제거하기 =========================
#include "..\\MyEngine_SOURCE\\MyResources.h"
#include "..\\MyEngine_SOURCE\\MyTexture.h"
#include "..\\MyEngine_Window\\MyToolScene.h"
// ========================= 무조건 여기서 제거하기 =========================



//#pragma comment (lib, "..\\x64\\Debug\\MyEngine_Window.lib")

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE CurrentInstance;                      // 현재 인스턴스
WCHAR WindowTitle[MAX_LOADSTRING];              // 기본 창 제목 표시줄 텍스트
WCHAR WindowClass[MAX_LOADSTRING];              // 기본 창 클래스 이름

WCHAR ToolWindowClass[MAX_LOADSTRING];          // 툴 창 제목 표시줄 텍스트
WCHAR ToolTitle[MAX_LOADSTRING];                // 툴 창 클래스 이름

Source::Application application;

ULONG_PTR gpToken;
Gdiplus::GdiplusStartupInput gpsi;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance, WNDPROC procedure, const wchar_t* className);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WindowProcedure(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, //프로그램의 인스턴스 핸들(포인터 같은 개념)
                     _In_opt_ HINSTANCE hPrevInstance, //직전 실행된 프로그램의 핸들, 없으면 NULL
                     _In_ LPWSTR    lpCmdLine, //명령행으로 입력된 실행 인자
                     _In_ int       nCmdShow) //프로그램이 실행될 형태, 보통 모양 정보 등
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //메모리 누수 체크
    //_CrtSetBreakAlloc(n); 으로 어디서 누수가 일어나는지 확인 가능
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(494);
    
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, WindowTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EDITORWINDOW, WindowClass, MAX_LOADSTRING);

    wcscpy_s(ToolWindowClass, MAX_LOADSTRING, L"TOOLWINDOW");
    wcscpy_s(ToolTitle, MAX_LOADSTRING, L"ToolWindow");

    MyRegisterClass(hInstance, WindowProcedure, WindowClass);
	MyRegisterClass(hInstance, ToolWindowProcedure, ToolWindowClass);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDITORWINDOW));

    MSG msg;
    //GetMessage(&msg, nullptr, 0, 0) 프로세스에서 발생한 메시지를 메시지 큐에서 가져옴
    //큐에 없다면 아무 메시지도 받아오지 않는다.

    //PeekMessage : 메시지 큐가 비었어도 함수가 리턴됨
    //              메시지가 있으면 true, 없으면 false
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            //메시지가 없을 때
            //게임 기본 로직
            application.Run();
        }
    }

    Gdiplus::GdiplusShutdown(gpToken);
    application.Release();

    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance, WNDPROC procedure, const wchar_t* className)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = procedure;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITORWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EDITORWINDOW);
    wcex.lpszClassName  = className;
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
   CurrentInstance = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   const UINT width = 1600;
   const UINT height = 900;

   //메인 윈도우
   HWND hWnd = CreateWindowW(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   application.Initialize(hWnd, width, height);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   //툴 윈도우
   HWND toolHWnd = CreateWindowW(ToolWindowClass, ToolTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInstance, nullptr);

   if (!toolHWnd)
   {
       return FALSE;
   }

   //ShowWindow(toolHWnd, nCmdShow);
   //UpdateWindow(toolHWnd);

   Gdiplus::GdiplusStartup(&gpToken, &gpsi, NULL);

   //씬 로드
   Client::LoadResources();
   Client::LoadScenes();

   //Tile 윈도우 크기 조정
   // ========================= 무조건 여기서 제거하기 =========================
   Source::Graphics::Texture* texture = Source::Resources::Find<Source::Graphics::Texture>(L"SpringFloor");
       RECT rect = { 0, 0, texture->GetWidth(), texture->GetHeight() };
   AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

   UINT toolWidth = rect.right - rect.left;
   UINT toolHeight = rect.bottom - rect.top;

   SetWindowPos(toolHWnd, nullptr, width, 0, toolWidth, toolHeight, 0);
   ShowWindow(toolHWnd, nCmdShow);
   UpdateWindow(toolHWnd);
   // ========================= 무조건 여기서 제거하기 =========================

   return TRUE;
}

//  함수: WindowProcedure(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int windowMenuId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (windowMenuId)
            {
            case IDM_ABOUT:
                DialogBox(CurrentInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
            //DC란 화면의 출력에 필요한 모든 데이터를 가지는 구조체
            //GDI 모듈에 의해 관리된다
            //폰트, 색상, 선의 굵기 등 화면 출력에 필요한 모든 경우 WINAPI에서는 DC를 통해 진행

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_MOVE:
        {

        }
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
