#include <windows.h>
#include <winuser.h>
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>


//int main() {
//    CaptureScreen("test.bmp");
//}

int main(int argc, char *argv[])
{
    int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
    HWND hDesktopWnd = GetDesktopWindow();
    HDC hDesktopDC = GetDC(hDesktopWnd);
    HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
    HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, nScreenWidth, nScreenHeight);
    SelectObject(hCaptureDC, hCaptureBitmap);



    auto *pPixels = new RGBQUAD[nScreenWidth * nScreenHeight];
    int width = 1920;
    int height = 1080;
    sf::RenderWindow window(sf::VideoMode(1920, 1080, 32), "Test");
    sf::Sprite       sprite;
    sf::Texture texture;
    texture.create(1920, 1080);
    auto        *pixels  = new sf::Uint8[width * height * 4];

    while(window.isOpen())
    {
        unsigned __int64 begin = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        BitBlt(hCaptureDC, 0, 0, nScreenWidth, nScreenHeight, hDesktopDC, 0,0, SRCCOPY|CAPTUREBLT);

        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
        bmi.bmiHeader.biWidth = nScreenWidth;
        bmi.bmiHeader.biHeight = nScreenHeight;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        GetDIBits(
                hCaptureDC,
                hCaptureBitmap,
                0,
                nScreenHeight,
                pPixels,
                &bmi,
                DIB_RGB_COLORS
        );
        for(int i = 0; i < width * height * 4; i+=4) {
            pixels[i] = pPixels[i / 4].rgbRed;
            pixels[i+1] = pPixels[i / 4].rgbGreen;
            pixels[i+2] = pPixels[i / 4].rgbBlue;
            pixels[i+3] = 255;
        }
        sf::Image        image;

        image.create(width,height, pixels );
        image.flipVertically();

        texture.update(image);
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
        unsigned __int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        std:: cout << 1000 / (now - begin) << std::endl;

    }

    delete [] pixels;
    return 0;
}
