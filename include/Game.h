#define _USE_MATH_DEFINES
#ifndef GAME_H
#define GAME_H
#include <Graphics2D.h>
#include <math.h>
#include <Map.h>

#define sz 20

#define HYP sz/2

LRESULT CALLBACK gameProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class Game
{
    public:
        Game(HWND,int,int, int, int);
        virtual ~Game();
        void update(bool);
        void drawMap();
        int player_x = 75;
        int player_y = 0;
        float p_angle = 0.0f;
        void debug();
        void calcDist(float,bool);
        bool displayMap = true;
        void handleInput(WPARAM, LPARAM);

    private:

        Graphics2D* g2d;
        HWND windowHandle;
        Map* myMap;

        //Canvas width and height
        int width;
        int height;

        //GDI structs
        HDC m_hdc;
        PAINTSTRUCT ps;
        HDC Memhdc;


        int m_resolution = 20;
        // field of view is 60 degrees, which when divided by two is 30 degrees. 30 on left side and 30 on right side.
        const float depth = 30 * (M_PI/180);
        // The width of the view plan divided by the
        float divAngle = (2.0f * depth) / m_resolution;
        //Distance from the projection screen to the player
        float distanceFromScreen = (this->width/2) * tan(depth) * sz;

        //Keeping track of world co-ordinates
        int mapX;
        int mapY;

        //double ANGLES[8] = {0.0f, (float) M_PI_4, (float) M_PI_2, (float) (3.0f * M_PI_4), (float) M_PI, (float) (5 * M_PI_4), (float) 3* M_PI_2, (float) (7 * M_PI_4) };

        double ANGLES[4] = {0.0f, (float) M_PI_2, (float) M_PI, (float) 3* M_PI_2};

        //Helper utility
        int num = 0;
        byte idxOngle = 0;
        float colWidth = this->width/m_resolution;


};

#endif // GAME_H
