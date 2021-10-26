//
// Created by arzeo on 10/26/2021.
//

#include <windows.h>
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "Screen/Screen.h"

int main(int argc, char *argv[])
{
    int              width = 1920;
    int              height = 1080;
    sf::Sprite       sprite;
    sf::Image        image;
    sf::Texture      texture;
    Screen           screen;
    auto             *pixels  = new sf::Uint8[width * height * 4];
    sf::RenderWindow window(sf::VideoMode(1920, 1080, 32), "Test");
    texture.create(1920, 1080);

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
        RGBQUAD *pPixels = screen.getScreenPixels();
        for(int i = 0; i < width * height * 4; i+=4) {
            pixels[i] = pPixels[i / 4].rgbRed;
            pixels[i+1] = pPixels[i / 4].rgbGreen;
            pixels[i+2] = pPixels[i / 4].rgbBlue;
            pixels[i+3] = 255;
        }

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
