#include <Windows.h>
#include <iostream>
#include <ctime>
// OpenGL Includes
#include <gl\GL.h>
#include <gl\GLU.h>
// Screensaver Includes
#include <ScrnSave.h>
#include <CommCtrl.h>

// OpenGL Libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
// Screensaver Libraries
#pragma comment(lib, "scrnsave.lib")
#pragma comment(lib, "ComCtl32.lib")

using namespace std;

// Functions
void InitOpenGL();
void Initialize();
void ShutdownOpenGL();
void Shutdown();
void Update();
void Render();

// Animation flag
const bool ANIMATED = true;

LONG WINAPI ScreenSaverProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Timer for screensaver
	static UINT uTimer = 0;

	// Contexts for GDI and OpenGL
	static HDC hDC = NULL;
	static HGLRC hRC = NULL;

	// Handle screensaver messages
	switch (message)
	{
	case WM_CREATE:
		{
			// Create screensaver window
			 hDC = GetDC(hWnd);

			static PIXELFORMATDESCRIPTOR pfd = {
			  sizeof(PIXELFORMATDESCRIPTOR), // Size of struct
			  1, // Version of struct
			  PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			  PFD_TYPE_RGBA,
			  32, // Color buffer size
			  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			  16, // Z buffer depth
			  8, // Stencil buffer depth
			  0, 0, 0, 0, 0, 0
			};
			int nPF = ChoosePixelFormat(hDC, &pfd);

			SetPixelFormat(hDC, nPF, &pfd);

			// Create rendering context
			hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC, hRC);

			InitOpenGL();
			uTimer = (UINT)SetTimer(hWnd, 1, 1, NULL);
			Initialize();
		}
		break;
	case WM_ERASEBKGND:
		{
			// Erase screensaver background
		}
		break;
	case WM_TIMER:
		{
			// Handle timer
			Update();
		}
		break;
	case WM_DESTROY:
		{
			// Clean up screensaver window
			Shutdown();
			KillTimer(hWnd, uTimer);
			ShutdownOpenGL();

			wglMakeCurrent(hDC, NULL);
			wglDeleteContext(hRC);
			ReleaseDC(hWnd, hDC);

			PostQuitMessage(0);
		}
		break;
	case WM_PAINT:
		{
			// Draw to the window
			Render();
			SwapBuffers(hDC);
			if (!ANIMATED)
			{
				ValidateRect(hWnd, NULL);
			}
		}
		break;
	default:
		{
			   return DefScreenSaverProc(hWnd, message, wParam, lParam);
		}
		break;
	}

	return 0;
}

BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

BOOL WINAPI RegisterDialogClasses(HANDLE hInst)
{
	return TRUE;
}

void InitOpenGL()
{
	srand(time(0));
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Initialize()
{

}

void ShutdownOpenGL()
{

}

void Shutdown()
{

}

void Update()
{

}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float redColor = float(rand() % 255);
	float blueColor = float(rand() % 255);
	float greenColor = float(rand() % 255);
	glClearColor(redColor, greenColor, blueColor, 1.0f);
	printf("Red: %f, Blue: %f, Green: %f", redColor, blueColor, greenColor);
}

