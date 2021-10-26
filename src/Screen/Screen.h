//
// Created by arzeo on 10/26/2021.
//

#ifndef SCREENSHARE_SCREEN_H
#define SCREENSHARE_SCREEN_H

#include <windows.h>
#include <winuser.h>
#include <SFML/Config.hpp>

class Screen {
public:
    Screen();
    ~Screen();

    RGBQUAD *getScreenPixels() const;

private:
    int _nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int _nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
    HWND _hDesktopWnd = GetDesktopWindow();
    HDC _hDesktopDC = GetDC(_hDesktopWnd);
    HDC _hCaptureDC = CreateCompatibleDC(_hDesktopDC);
    HBITMAP _hCaptureBitmap = CreateCompatibleBitmap(_hDesktopDC, _nScreenWidth, _nScreenHeight);
    RGBQUAD *_pPixels = new RGBQUAD[_nScreenWidth * _nScreenHeight];

};


#endif //SCREENSHARE_SCREEN_H
