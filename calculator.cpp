#include <windows.h>
#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include<stdio.h>
#include <tchar.h>
#include<commctrl.h>

double Num1 ;
double Num2 ;
double result;
char show[100];
#define BTN_PLUS 1
#define BTN_MINUS 2
#define BTN_MULTI 3
#define BTN_DIVIDE 4
#define TXT_INPUT1 100
#define TXT_INPUT2 100
HWND textfield,BTNPLUS,BTNMINUS,BTNMULTI,BTNDIVIDE,Textbox1,Textbox2;
HBRUSH hBrushBk;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

	switch(Message) {
		case WM_CREATE:
		textfield = CreateWindow("STATIC","Please input two number",WS_VISIBLE|WS_CHILD|WS_BORDER,20,20,200,25,hwnd,NULL,NULL,NULL);
		BTNPLUS = CreateWindow("BUTTON","+",WS_VISIBLE|WS_CHILD|WS_BORDER,20,120,30,25,hwnd,(HMENU)BTN_PLUS ,NULL,NULL);
		BTNMINUS = CreateWindow("BUTTON","-",WS_VISIBLE|WS_CHILD|WS_BORDER,80,120,30,25,hwnd,(HMENU)BTN_MINUS,NULL,NULL);
		BTNMULTI = CreateWindow("BUTTON","*",WS_VISIBLE|WS_CHILD|WS_BORDER,140,120,30,25,hwnd,(HMENU)BTN_MULTI,NULL,NULL);
		BTNDIVIDE = CreateWindow("BUTTON","/",WS_VISIBLE|WS_CHILD|WS_BORDER,200,120,30,25,hwnd,(HMENU)BTN_DIVIDE,NULL,NULL);
		Textbox1 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,20, 50, 200, 25, hwnd, (HMENU)TXT_INPUT1, NULL, NULL);
		Textbox2 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,20, 80, 200, 25, hwnd, (HMENU)TXT_INPUT2, NULL, NULL);
		hBrushBk = CreateSolidBrush(RGB(0, 255, 0));
		break;
		/* Upon destruction, tell the main thread to stop */
		case WM_ERASEBKGND: {
            HDC hdc = (HDC)wParam;
            RECT rc;
            GetClientRect(hwnd, &rc);
            FillRect(hdc, &rc, hBrushBk);
            return 1;
        }
		case WM_COMMAND:
		char inputnum1[100];
		char inputnum2[100];
		GetWindowText(Textbox1, inputnum1, 100);
		GetWindowText(Textbox2, inputnum2, 100);
		Num1 = atof(inputnum1);
		Num2 = atof(inputnum2);
			switch (LOWORD(wParam))
			{
				case BTN_PLUS:
				result = Num1+Num2;
				sprintf(show, "%f", result);
				MessageBox(hwnd, show, "Result", MB_OK);
				
				break;
			case BTN_MINUS:
			result = Num1-Num2;
			sprintf(show, "%f", result);
				MessageBox(hwnd, show, "Result", MB_OK);
				break;
			case BTN_MULTI:
			result = Num1*Num2;
			sprintf(show, "%f", result);
				MessageBox(hwnd, show, "Result", MB_OK);
				break;
			case BTN_DIVIDE:
			result = Num1/Num2;
			sprintf(show, "%f", result);
				MessageBox(hwnd, show, "Result", MB_OK);
				break;
			}
			break;

		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */
	
	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = TEXT("WindowClass");
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"WindowClass",
		"My Calculator",
		WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,
		NULL,
		hInstance,
		NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}


