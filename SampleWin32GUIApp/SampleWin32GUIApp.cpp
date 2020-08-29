// SampleWin32GUIApp.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "SampleWin32GUIApp.h"


#define MAX_LOADSTRING 100

constexpr int H_MENU_BUTTON_ID1 = 0;

constexpr int INCREMENT_BUTTON = 1;

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

D2DRenderClass d2dclass;

// このコード モジュールに含まれる関数の宣言を転送します:
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

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SAMPLEWIN32GUIAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAMPLEWIN32GUIAPP));

    MSG msg;

    // メイン メッセージ ループ:
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
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAMPLEWIN32GUIAPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SAMPLEWIN32GUIAPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   HWND button = CreateWindow(L"BUTTON", L"OK", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
       0, 60, 40, 60, hWnd, (HMENU)H_MENU_BUTTON_ID1, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

   HWND increment_button = CreateWindow(L"BUTTON", L"Increment", 
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
       0, 120, 80, 60, hWnd, (HMENU)INCREMENT_BUTTON, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);


   d2dclass = D2DRenderClass(hWnd);

   int check = 0;
  
   check = CoInitialize(NULL);

   auto dpi = GetDpiForWindow(hWnd);


   HRESULT isSuccess = d2dclass.CreateD2Ddevice();

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   CoUninitialize();

   return TRUE;
}

int count = 0;
HWND hdlg;
INT_PTR CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
   

    switch (msg) {

    case WM_CLOSE:
        EndDialog(hwnd, IDOK);
        return TRUE;

    case WM_INITDIALOG:

        return TRUE;

    case WM_COMMAND:
        int wmid = LOWORD(wp);

        switch (wmid)
        {
        case IDOK:
            EndDialog(hwnd, IDOK);
            return TRUE;
        }

        return TRUE;
    
    }

    return FALSE;
}

void MyOpenFile()
{
    OPENFILENAME filename;
    TCHAR size[256] = { 0 };

    ZeroMemory(&filename, sizeof(filename));
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:


        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case H_MENU_BUTTON_ID1:
                // MessageBox(hWnd, L"Clicked button", L"H_MENU_BUTTON_ID1", MB_OK);
                

                // hdlg = CreateDialog(hInst, L"test", hWnd, put_msg_box);

                // MessageBox(hWnd, L"msg box", L"hook", MB_OK);

                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DialogProc);


            case INCREMENT_BUTTON:
                count++;

                RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...

            LPCWSTR str = L"ハローワールド";
            size_t n = wcslen(str);

            BOOL result = TextOut(hdc, 0, 0, str, (int)n);

            auto s = std::to_wstring(count);

            result = TextOut(hdc, 0, 20, s.c_str(), s.length());

            auto textStruct = d2dclass.CreateTextStructData(L"Meyrio", L"Dwrite rendered textです", 12);
      


            auto hr = d2dclass.OnRenderText(textStruct);

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

// バージョン情報ボックスのメッセージ ハンドラーです。
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
