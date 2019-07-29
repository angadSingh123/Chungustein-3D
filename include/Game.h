#define _USE_MATH_DEFINES
#ifndef GAME_H
#define GAME_H
#include <Graphics2D.h>
#include <math.h>
#include <Map.h>

#define HYP 15
#define sz 64

LRESULT CALLBACK gameProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class Game
{
    public:
        Game(HWND,int,int, int, int);
        virtual ~Game();
        void update();
        void drawMap();
        int player_x = 75;
        int player_y = 0;
        float p_angle = 0.0f;
        void debug();
        void calcDist(float);
        bool displayMap = true;

    private:
        Graphics2D* g2d;
        HWND windowHandle;
        Map* myMap;
        int width = 800;
        int height = 500;
        HDC m_hdc;
        WCHAR array[10];
        PAINTSTRUCT ps;
        HDC Memhdc;
        const int m_resolution = 90;
        const float depth = 30 * (M_PI/180);
        const float div = 60 * (M_PI/180) / m_resolution;
        int mapX;
        int mapY;
        int num = 0;


};

#endif // GAME_H
