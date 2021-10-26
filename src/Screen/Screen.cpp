//
// Created by arzeo on 10/26/2021.
//

#include "Screen.h"

Screen::Screen() {
    SelectObject(_hCaptureDC, _hCaptureBitmap);
}

Screen::~Screen() {
    delete [] _pPixels;

    ReleaseDC(_hDesktopWnd, _hDesktopDC);
    DeleteDC(_hCaptureDC);
    DeleteObject(_hCaptureBitmap);
}

RGBQUAD *Screen::getScreenPixels() const {
    BitBlt(_hCaptureDC, 0, 0, _nScreenWidth, _nScreenHeight, _hDesktopDC, 0,0, SRCCOPY|CAPTUREBLT);

    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = _nScreenWidth;
    bmi.bmiHeader.biHeight = _nScreenHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    GetDIBits(
            _hCaptureDC,
            _hCaptureBitmap,
            0,
            _nScreenHeight,
            _pPixels,
            &bmi,
            DIB_RGB_COLORS
    );
    return  _pPixels;
}
