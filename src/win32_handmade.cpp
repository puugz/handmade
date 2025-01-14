#include <windows.h>

LRESULT CALLBACK
main_window_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
  LRESULT result = 0;

  switch (message) {
    case WM_SIZE: {
      OutputDebugString("WM_SIZE\n");
    } break;
    
    case WM_DESTROY: {
      OutputDebugString("WM_DESTROY\n");
    } break;

    case WM_CLOSE: {
      OutputDebugString("WM_CLOSE\n");
    } break;

    case WM_ACTIVATEAPP: {
      OutputDebugString("WM_ACTIVATEAPP\n");
    } break;

    case WM_PAINT: {
      PAINTSTRUCT paint;
      HDC device_context = BeginPaint(window, &paint);
      
      int x      = paint.rcPaint.left;
      int y      = paint.rcPaint.top;
      int height = paint.rcPaint.bottom - paint.rcPaint.top;
      int width  = paint.rcPaint.right  - paint.rcPaint.left;

      static DWORD operation = WHITENESS;
      PatBlt(device_context, x, y, width, height, operation);
      if (operation == WHITENESS) {
        operation = BLACKNESS;
      } else {
        operation = WHITENESS;
      }

      EndPaint(window, &paint);
    } break;

    default: {
      // OutputDebugString("default\n");
      result = DefWindowProc(window, message, w_param, l_param);
    } break;
  }

  return result;
}

int CALLBACK
WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR command_line, int show_code) {
  WNDCLASS window_class      = {};
  window_class.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
  window_class.lpfnWndProc   = main_window_callback;
  window_class.hInstance     = instance;
  window_class.lpszClassName = "HandmadeHeroWindowClass";

  if (!RegisterClass(&window_class)) {
    OutputDebugString("Error registering window class\n");
    return 1;
  }

  HWND window_handle = CreateWindowEx(
    0,
    window_class.lpszClassName,
    "Handmade Hero",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    0,
    0,
    instance,
    0
  );

  if (!window_handle) {
    OutputDebugString("Could not create window handle\n");
    return 1;
  }

  for (;;) {
    MSG message;
    BOOL message_result = GetMessage(&message, NULL, 0, 0);
    if (message_result < 0) {
      break;
    }

    TranslateMessage(&message);
    DispatchMessage(&message);
  }

  return 0;
}
