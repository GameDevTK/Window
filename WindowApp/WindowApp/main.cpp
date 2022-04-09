#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

// ウィンドウプロシージャ（コールバック関数）
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_DESTROY:
        // 終了処理
        PostQuitMessage(0); // int nExitCode
        return 0;
    }

    return DefWindowProc(
        hwnd,       // HWND hWnd
        uMsg,       // UINT Msg
        wParam,     // WPARAM wParam
        lParam);    // LPARAM lParam
}

int WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    AllocConsole();
    freopen(
        "CONIN$",   // const char* _Filename
        "r",        // const char* _Mode
        stdin);     // FILE* _File

    freopen(
        "CONOUT$",  // const char* _Filename
        "w",        // const char* _Mode
        stdout);    // FILE* _File


    LPCWSTR ClassName = L"ClassName";

    // ウィンドウ構造体の作成
    WNDCLASSEX wc = {
        sizeof(WNDCLASSEX),     // UINT         cbSize
        CS_CLASSDC,             // UINT         style
        WndProc,                // WNDPROC      lpfnWndProc
        0,                      // int          cbClsExtra
        0,                      // int          cbWndExtra
        hInstance,              // HINSTANCE    hInstance
        NULL,                   // HICON        hIcon
        NULL,                   // HCURSOR      hCursor
        NULL,                   // HBRUSH       hbrBackground
        NULL,                   // LPCSTR       lpszMenuName
        ClassName,              // LPCSTR       lpszClassName
        NULL,                   // HICON        hIconSm
    };

    // ウィンドウ構造体の登録
    RegisterClassEx(&wc);   // CONST WNDCLASSEXA*

    // ウィンドウの作成
    // hWndは作成されたウィンドウのハンドル
    HWND hWnd = CreateWindowEx(
        0,                      // DWORD        dwExStyle
        ClassName,              // LPCSTR       lpClasName
        L"WindowName",          // LPCSTR       lpWindowName
        WS_OVERLAPPEDWINDOW,    // DWORD        dwStyle
        CW_USEDEFAULT,          // int          X
        CW_USEDEFAULT,          // int          Y
        CW_USEDEFAULT,          // int          nWidth
        CW_USEDEFAULT,          // int          nHeight
        NULL,                   // HWND         hWndParent
        NULL,                   // HMENU        hMenu
        hInstance,              // HINSTANCE    hInstance
        NULL);                  // LPVOID       lpParam

    // ウィンドウを表示
    ShowWindow(
        hWnd,                   // HWND         hWnd
        nShowCmd);              // int          nCmdShow

    MSG msg = {};
    while (msg.message != WM_QUIT) {
        // ウィンドウメッセージの取得
        auto isMsg = PeekMessage(
            &msg,       // LPMSG    lpMsg
            NULL,       // HWND     hWnd
            0,          // UINT     wMsgFilterMin
            0,          // UINT     wMsgFilterMax
            PM_REMOVE); // UINT     wRemoveMsg

        // メッセージ取得時
        if (isMsg)
        {
            // 仮想キーメッセージを文字メッセージに変換
            TranslateMessage(&msg); // CONST MSG* lpMsg

            // システムに送信→WndProcが呼ばれる
            DispatchMessage(&msg);  // CONST MSG* lpMsg
        }
    }


}
