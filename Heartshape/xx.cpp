#include <windows.h>
#include <commctrl.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

int main()
{
	HWND hd;
	RECT Desk;
	HWND hShellViewWin = NULL;

	GetWindowRect(GetDesktopWindow(), &Desk);

	int hor = Desk.right;
	int ver = Desk.bottom;

	
	hd = FindWindowA("Progman", NULL);
	hd = FindWindowExA(hd, 0, "SHELLDLL_DefView", NULL);
	do
	{
    hd = FindWindowExA(0, hd, "WorkerW", NULL);
    hShellViewWin = FindWindowExA(hd, 0, "SHELLDLL_DefView", 0);
	} 
	while (hShellViewWin == NULL && hd != NULL);

	if (hShellViewWin != NULL)
	{
		hd = hShellViewWin;
		hd = FindWindowExA(hd, 0, "SysListView32", NULL);
	}
	else
	{
		hd = FindWindowA("Progman", NULL);
		hd = FindWindowExA(hd, 0, "SHELLDLL_DefView", NULL);
		hd = FindWindowExA(hd, 0, "SysListView32", NULL);
	}

	
	int count;
	count = SendMessage(hd, LVM_GETITEMCOUNT, 0, 0);
	if (count < 4)
	{
		cout << "You need a few more Icons on the Desktop";
		Sleep(2000);
		exit(0);
	}
	POINT pt;
	int radius = hor / 10;
	int middle1X = hor/2 + hor/10;
	int middle2X = hor/2 - hor/10;
	if (count % 2 == 1)
	{count--;}
	int spacing = count / 4;
	int spacing2 = (count - 2) / 4 + 1;
	int spacingX = hor/5;
	int spacingY = ver/3;
	count--;

		ListView_SetItemPosition(hd, count--, hor/2, ver/2);
		ListView_SetItemPosition(hd, count--, hor/2 + hor/5, ver/2); 
		ListView_SetItemPosition(hd, count--, hor/2 - hor/5, ver/2);
		ListView_SetItemPosition(hd, count--, hor/2 , ver/2 + ver/3);
		for (int i = 1; i < spacing; i++)
		{
			ListView_SetItemPosition(hd, count--, hor/2 + (spacingX/spacing) * i, ver/2 + ver/3 - (spacingY/spacing) * i);
			ListView_SetItemPosition(hd, count--, hor/2 - (spacingX/spacing) * i, ver/2 + ver/3 - (spacingY/spacing) * i);
		}
		for (int i = 1; i < spacing2; i++)
		{
			ListView_SetItemPosition(hd, count--, middle1X + cos(M_PI/spacing2*i)*radius, ver/2 - sin(M_PI/spacing2*i)*radius);
			ListView_SetItemPosition(hd, count--, middle2X - cos(M_PI/spacing2*i)*radius, ver/2 - sin(M_PI/spacing2*i)*radius);
		}
	

}


//
//huge thanks to Easy Programming for the Tutorial on how to move icons https://www.youtube.com/watch?v=N40txXKwAaA