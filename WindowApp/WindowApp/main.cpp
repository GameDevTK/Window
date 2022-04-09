#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

// �E�B���h�E�v���V�[�W���i�R�[���o�b�N�֐��j
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_DESTROY:
        // �I������
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

    // �E�B���h�E�\���̂̍쐬
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

    // �E�B���h�E�\���̂̓o�^
    RegisterClassEx(&wc);   // CONST WNDCLASSEXA*

    // �E�B���h�E�̍쐬
    // hWnd�͍쐬���ꂽ�E�B���h�E�̃n���h��
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

    // �E�B���h�E��\��
    ShowWindow(
        hWnd,                   // HWND         hWnd
        nShowCmd);              // int          nCmdShow

    MSG msg = {};
    while (msg.message != WM_QUIT) {
        // �E�B���h�E���b�Z�[�W�̎擾
        auto isMsg = PeekMessage(
            &msg,       // LPMSG    lpMsg
            NULL,       // HWND     hWnd
            0,          // UINT     wMsgFilterMin
            0,          // UINT     wMsgFilterMax
            PM_REMOVE); // UINT     wRemoveMsg

        // ���b�Z�[�W�擾��
        if (isMsg)
        {
            // ���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�
            TranslateMessage(&msg); // CONST MSG* lpMsg

            // �V�X�e���ɑ��M��WndProc���Ă΂��
            DispatchMessage(&msg);  // CONST MSG* lpMsg
        }
    }


}
