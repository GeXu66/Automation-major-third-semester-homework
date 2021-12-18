#include <windows.h>
#include<iostream>
#include<stdio.h>

using namespace std;

const char g_szClassName[] = "myWindowClass";
int x,y,key;
int draw;

// Step 4: the Window Procedure

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            cout<<" WM_CLOSE"<<endl;
            DestroyWindow(hwnd);
        break;

        case WM_DESTROY:
            cout<<" WM_DESTROY"<<endl;
            PostQuitMessage(0);
        break;

        case WM_CREATE:
            cout<<" WM_CREATE"<<endl;
            SetTimer(hwnd,1,200,NULL);
            draw=1;
        break;

        case WM_MOVE:
            cout<<" WM_MOVING"<<endl;
        break;

        case WM_SIZE:
            cout<<" WM_SIZE"<<endl;
        break;

        case WM_LBUTTONDOWN:
            x=LOWORD(lParam);
            y=HIWORD(lParam);
            cout<<" WM_LBUTTONDOWN at "<<x<<" "<<y<<endl;
        break;

        case WM_LBUTTONUP:
            x=LOWORD(lParam);
            y=HIWORD(lParam);
            cout<<" WM_LBUTTONUP at "<<x<<" "<<y<<endl;
        break;

        case WM_MOUSEMOVE:
            x=LOWORD(lParam);
            y=HIWORD(lParam);
            cout<<" WM_MOUSEMOVE at "<<x<<" "<<y<<endl;
        break;

        case WM_RBUTTONDOWN:
            x=LOWORD(lParam);
            y=HIWORD(lParam);
            cout<<" WM_RBUTTONDOWN at "<<x<<" "<<y<<endl;
        break;

        case WM_KEYDOWN:
            key=wParam;
            cout<<" WM_KEYDOWN : "<<key<<endl;
        break;

        case WM_KEYUP:
            key=wParam;
            cout<<" WM_KEYUP : "<<key<<endl;
        break;

        case WM_TIMER:
            cout<<" WM_TIMER"<<endl;
            if(draw)
            {
                static int ind=10;
                static int flag=1;
                char c[128];
                int len=sprintf(c,"%d",ind);

                HDC hdc=GetDC(hwnd);

                HBRUSH hBrush;
                RECT rect;
                SetRect(&rect, 0, 0,800,800);
                hBrush = CreateSolidBrush(RGB(255, 0, 0));
                FillRect(hdc, &rect, hBrush);
                hBrush = NULL;

                MoveToEx(hdc,10+ind,10+ind,NULL);
                LineTo(hdc,50+ind,50+ind);

                Rectangle(hdc, 60+ind,60+ind,120+ind,120+ind);

                Ellipse(hdc, 150+ind,300+ind,450+ind,600+ind);

                TextOut(hdc,100+ind,100,TEXT(c),len);

                ReleaseDC(hwnd,hdc);

                if (ind==50)
                    flag=-1;
                if (ind==0)
                    flag=1;

                ind+=flag;

            }
        break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "The title of my window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}




