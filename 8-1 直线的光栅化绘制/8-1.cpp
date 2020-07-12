#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include <graphics.h>
#endif // !_GRAPHICS_H_

#ifndef _CONIO_H_
#define _CONIO_H_
#include <conio.h>
#endif // !_CONIO_H_

#include "canva.h"

/**
 * 8    ͼ����ˮ��
 * 8-1  ֱ�ߵĹ�դ������
 *
 * ʹ�ù�դ���������ƴ��������߿����Ե�ֱ�ߡ�
 *
 * ���л�����Windows��Visual Studio 2019
 * EasyX ͼ�ο�汾��20200520��beta��
 *
 * ****  �����������Ӧ���볢�������豸��  ****
 * ****  �����ֱ��������ȷ������ȷ��װEasyXͼ�ο⡣  ****
 *
 * Last Edit: 2020/07/12
 */

/*
 initFullscreen  ��ʼ��ȫ����ͼ����

 ***  ��Щ������ͼ��ѧ�޹�  ***
 */
void initFullscreen() {
    int rW = GetSystemMetrics(SM_CXSCREEN); // ��Ļ��� ����
    int rH = GetSystemMetrics(SM_CYSCREEN); // ��Ļ�߶� ����
    initgraph(rW, rH);
    HWND hwnd = GetHWnd();// EasyX�⺯������ȡ���ھ��
    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);
    SetWindowLong(hwnd, GWL_STYLE,
        (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, rW, rH, 0);
}

int main()
{
    initFullscreen();
    Canva c;
    srand(0);
    Vector3 color[3] = {
        Vector3(0xea / 255.0, 0x86 / 255.0, 0xcc / 255.0),
        Vector3(0xe5 / 255.0, 0xe5 / 255.0, 0xcb / 255.0),
        Vector3(0xc0 / 255.0, 0xe4 / 255.0, 0xc8 / 255.0)
    };
    for (int i = 0; i < 10000; i++)
    {
        int x = rand() % c.width,
            y = rand() % c.height;
        if (x + 200 >= c.width || y - 124 < 0)
        {
            continue;
        }
        Gemobj&& g = Line2D(Point2D(x, y, color[rand() % 3]), Point2D(x + 200, y - 124, color[rand() % 3]));
        c.draw(g);
    }
    saveimage(L"line10000.png");
    _getch();
}