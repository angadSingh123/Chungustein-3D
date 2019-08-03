#include "Game.h"
#include <tchar.h>
#include <string>
#include <stdio.h>
#include <math.h>

LRESULT CALLBACK gameProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l){

    switch (msg)                  /* handle the messages */
        {

            case WM_ERASEBKGND:
                return TRUE;
                break;

            default:                   /* for messages that we don't deal with */
                return DefWindowProc (hwnd, msg, w, l);
                break;
        }



}


Game::Game(HWND handle, int width, int height, int x, int y) : width(width), height(height)
{
    TCHAR szClassName[ ] = _T("BIGCHUNGUS");

    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = NULL;
    wincl.lpszClassName = szClassName;
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.lpfnWndProc = gameProc;
    wincl.hbrBackground = NULL;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl)){}

    this->windowHandle = CreateWindowEx(0, szClassName, _T("Big Chunugs 3: Revenge of the son"),WS_EX_LAYERED | WS_CHILD | WS_VISIBLE, x,y, width, height, handle, NULL, NULL, NULL);

    myMap = new Map("res/mad.txt");

    myMap->Initialise();

    m_hdc = GetDC(windowHandle);

    Memhdc = m_hdc;

    this->g2d = new Graphics2D(Memhdc);

    mapX = width - myMap->getCols()*sz;

    mapY = height - myMap->getRows()*sz;

    for (int i = 0 ; i < sizeof(ANGLES)/sizeof(ANGLES[0]) ; i++) std::cout << ANGLES[i] << std::endl;

    std::cout << width << " " << height << " " << (float) this->depth << " " << (float) this->divAngle << " " << (float) this->distanceFromScreen << std::endl;

}

Game::~Game()
{
    CloseHandle(windowHandle);

    delete windowHandle;

    g2d->~Graphics2D();

    delete g2d;

    myMap->~Map();

    delete myMap;

}

void Game::update(bool debug){


	m_hdc = BeginPaint(windowHandle, &ps);

	Memhdc = CreateCompatibleDC(m_hdc);

	g2d->fill(255,255,255);

    g2d->drawFillRect(0,0,width, height);

    num = 0;

    for (float x = p_angle - depth; x < p_angle + depth; x+= divAngle) calcDist(x, false);

    if (displayMap)drawMap();

	BitBlt(m_hdc, 0, 0, width, height, Memhdc, 0, 0, SRCCOPY);

	EndPaint(windowHandle, &ps);

	DeleteDC    (Memhdc);

	ReleaseDC(windowHandle, m_hdc);

}

void Game::drawMap(){

    g2d->fill(0,0,0);

    for (int i = 0; i < myMap->getRows(); i++){

        for (int j = 0 ; j < myMap->getCols(); j++){

            if (myMap->getData(i,j) == 'W'){

                g2d->fill(0,0,0);

            }
            else {
                g2d->fill(255,0,255);
            }

            g2d->drawFillRect(mapX + sz*j, mapY + sz*i, sz,sz);
        }

    }

    g2d->drawFillRect(mapX + player_x, mapY + player_y, 5,5);

    g2d->drawLine(mapX + player_x, mapY + player_y, HYP*cos(p_angle) + player_x + mapX, HYP*sin(p_angle) + player_y + mapY);

}

void Game::calcDist(float angle, bool debug) {

    //horizontal

    float gridX, gridY;

    float x_add = tan(angle) * sz;

    float y_add = sz;

    float y_init = (((int)(player_y /sz) + 1) * sz) ;

    float x_init = (y_init - player_y) * tan(angle) + player_x;

    gridX = y_init/sz;

    gridY = x_init/sz;

    if (myMap->getData(gridX, gridY) != 'W') {

        do {

            x_init += x_add;

            y_init += y_add;

            gridX = y_init/sz;

            gridY = x_init/sz;

            if (gridX >= myMap->getRows() || gridY >= myMap->getCols() || gridX < 0 || gridY < 0) break;

        } while(myMap->getData(gridX, gridY) != 'W');
    }

    //if (debug) printf("x_add %f y_addd %f  x_init %f y_init %f \n", x_add, y_add, x_init, y_init);

    //vertical

    x_add = sz;

    y_add = tan(angle) * x_add;

    float dx = (((int) (player_x/sz) + 1) * sz) - player_x;

    float dy = tan(angle) * dx;

    float inX = player_x + dx;

    float inY = player_y + dy;

    //printf("x_add %f y_addd %f  inX %f inY %f  %c\n", x_add, y_add, inX, inY, myMap->getData(inY/sz,inX/sz));

    gridX = inY/sz;

    gridY = inX/sz;

    if (myMap->getData(gridX,gridY) != 'W'){

        do {

            inX += x_add;

            inY += y_add;

            gridX = inY/sz;

            gridY = inX/sz;

            if (gridX >= myMap->getRows() || gridY >= myMap->getCols() || gridX < 0 || gridY < 0) break;

            //printf("x %.2f y %.2f %c\n", gridX, gridY, myMap->getData(inY/sz,inX/sz));

        } while (myMap->getData(gridX, gridY) != 'W');

   }


    float distH = sqrt((player_x - x_init) * (player_x - x_init)  + (player_y - y_init) * (player_y - y_init) );

    //float distV = sqrt((player_x - inX) * (player_x - inX)  + (player_y - inY) * (player_y - inY) );

    float distV = 0;


    g2d->stroke(0.4f);

    if ( distH > distV ){

        g2d->drawLine(player_x + mapX, player_y + mapY, x_init + mapX, y_init + mapY);

        float proj = distanceFromScreen  / distH;

        g2d->fill(0, proj, 0);

        g2d->drawFillRect(colWidth * num, (height-proj)/2, colWidth, proj);

    }

    else {


        g2d->fill(0,255,0);

        g2d->drawLine(player_x + mapX, player_y + mapY, inX + mapX, inY +mapY);

        g2d->fill(0,0,0);

        float proj = distanceFromScreen  / distV;

        g2d->drawFillRect(colWidth* num, (height-proj)/2, colWidth, proj);


    }

    num++;
}

void Game::debug(){

    std::cout << p_angle * (180/M_PI) << " " <<   std::endl;

    update(true);

}


void Game::handleInput(WPARAM input, LPARAM args) {

    switch (input){


            case VK_LEFT:
                this->player_x-=5;
                break;

            case VK_RIGHT:
                this->player_x+= 5;
                break;

            case VK_DOWN:
                this->player_y+= 5;
                break;

            case VK_UP:
                this->player_y-= 5;
                break;

            case VK_RETURN:
                idxOngle += ( idxOngle ==  4 ) ? -4 : 1;
                this->p_angle = ANGLES[idxOngle];  //(  (  (int) ((2*g->p_angle +  0.78f)/PI - 1)   /  2) % 2   != 0) ? g->p_angle + 0.1f : g->p_angle + 0.78f;
                break;

            case VK_SPACE:
                this->displayMap = !this->displayMap;
                break;

            case 0x58:
                m_resolution ++;
                divAngle = (2.0f * depth) / m_resolution;
                colWidth = this->width/m_resolution;
                break;

            case 0x5A:
                m_resolution -= (m_resolution == 20) ? 0 : 1;
                divAngle = (2.0f * depth) / m_resolution;
                colWidth = this->width/m_resolution;
                break;

            case 0x49:
                this->debug();
                break;

    }


}




