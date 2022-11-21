#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <random>
#define _WIN32_WINNT 0x0A00
using namespace std;
#define masSize 3
RECT mas[masSize];
RECT rct;
POINT p;


void WinShow(HDC dc,int x,int y,int cx, int cy)
{
    HDC memDC = CreateCompatibleDC(dc);
    HBITMAP memBM = CreateCompatibleBitmap(dc,rct.right - rct.left, rct.bottom - rct.top);
    SelectObject(memDC,memBM);

    SelectObject(memDC,GetStockObject(DC_BRUSH));
	SetDCBrushColor(memDC,RGB(255,255,255));
	Rectangle(memDC,0,0,1920,1080);

    SelectObject(memDC,GetStockObject(DC_BRUSH));
	SetDCBrushColor(memDC,RGB(0,0,0));
	SelectObject(memDC,GetStockObject(DC_PEN));
	SetDCPenColor(memDC,RGB(0,0,0));

    POINT m;
    if (GetAsyncKeyState(81) != 0) //paint line
    {
        if (GetCursorPos(&m))
        {
            MoveToEx(memDC, x, y , &p);
            LineTo(memDC, m.x, m.y);
        }
    }
	Ellipse(memDC,x-20,y-20,x+20,y+20);
	BitBlt(dc,0,0,rct.right - rct.left, rct.bottom - rct.top,memDC,0,0,SRCCOPY);


	DeleteDC(memDC);
	DeleteObject(memBM);
}

LRESULT WndProc (HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){
    if (message == WM_DESTROY)
        PostQuitMessage(0);

    else if (message == WM_MOUSEMOVE)
    {
         int xPos = LOWORD(lparam);
         int yPos = HIWORD(lparam);
        //printf("mouse [%d,%d]\n",xPos,yPos);
        return 0;
    }
    else if (message == WM_SIZE)
        GetClientRect(hwnd,&rct);
    else return DefWindowProcA(hwnd,message,wparam,lparam);
}

int main()
{


	WNDCLASSA wcl;
	memset(&wcl, 0, sizeof(WNDCLASSA));

	wcl.lpszClassName = "my Window";
	wcl.lpfnWndProc = WndProc;
	RegisterClassA(&wcl);

    GetCursorPos(&p);
	HWND hwnd;


	hwnd = CreateWindow("my Window","Window Name", WS_OVERLAPPEDWINDOW, 0, 0, 1920, 1080,NULL, NULL, NULL, NULL);




	HDC dc = GetDC(hwnd);



	MSG msg;
    ShowWindow(hwnd,SW_SHOWNORMAL);

    int x=50, y=50,dx=0,dy=0,d=1,xPos,yPos,cx=0,cy=0;

	while (1) {
            if (PeekMessageA(&msg,NULL,0,0,PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            }
            else{

        if ((LOWORD(msg.lParam)<1900) && (LOWORD(msg.lParam)>10))
            cx=LOWORD(msg.lParam);
        if ((HIWORD(msg.lParam)<1060) && (HIWORD(msg.lParam)>10))
            cy=HIWORD(msg.lParam);
        x += dx;
        y += dy;
            GetCursorPos(&p);
        if (GetAsyncKeyState(16) != 0) { d = 3; }
        else { d = 1; }
        if (GetAsyncKeyState(83) != 0) {    //s
            dy += d;
        }
        else {
            if ((dy > 0) && (GetAsyncKeyState(88) == 0)) {
                dy -= d;
            }
        }
        if (GetAsyncKeyState(87) != 0) {    //w
            dy -= d;
        }
        else {
            if ((dy < 0) && (GetAsyncKeyState(88) == 0)) {
                dy += d;
            }
        }
        if (GetAsyncKeyState(68) != 0) {    //d
            dx += d;
        }
        else {
            if ((dx > 0) && (GetAsyncKeyState(88) == 0)) {
                dx -= d;
            }
        }
        if (GetAsyncKeyState(65) != 0) {    //a
            dx -= d;
        }
        else {
            if ((dx < 0) && (GetAsyncKeyState(88) == 0)) {
                dx += d;
            }
        }


        Sleep(10);
        WinShow(dc, x,y,cx,cy);

            }
	}

}
