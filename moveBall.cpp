#include "TXLib.h"

const float dt = 1;

void newBall(int x, int y, int R, int clrR, int clrG, int clrB)
{
    for(int r = R; r > 0; r = r - 2)
    {
        txSetColor(RGB(clrR - clrR*r/R, clrG - clrG*r/R, clrB - clrB*r/R));
        txSetFillColor(RGB(clrR - clrR*r/R, clrG - clrG*r/R, clrB - clrB*r/R));
        txCircle(x, y, r);
    }
}

void moveBall(float r, float* x, float* y, float* vx, float* vy, float dt)
{
    if (*y > (400 - r) || *y < r)
        *vy = - *vy;
    if (*x > (600 - r) || *x < r)
        *vx = - *vx;
    *x += *vx * dt;
    *y += *vy * dt;
}

void cntrlBall(float* vx, float* vy)
{
    if (GetAsyncKeyState(VK_LEFT))
        *vx -= 0.1;
    if (GetAsyncKeyState(VK_RIGHT))
        *vx += 0.1;
    if (GetAsyncKeyState(VK_UP))
        *vy -= 0.1;
    if (GetAsyncKeyState(VK_DOWN))
        *vy += 0.1;
}

int main()
{
    txCreateWindow(600, 400);
    float x = 100;
    float y = 100;
    float vx = 5;
    float vy = 10;
    float r = 50;
    float x1 = 200;
    float y1 = 200;
    float vx1 = 2;
    float vy1 = 3;
    float r1 = 50;

    for (;;)
    {
        cntrlBall(&vx, &vy);
        moveBall(r, &x, &y, &vx, &vy, dt);
        moveBall(r1, &x1, &y1, &vx1, &vy1, dt);

        txSetFillColor(RGB(0, 0, 0));
        txClear();

        newBall(x, y, r, 200, 50, 200);
        newBall(x1, y1, r1, 50, 200, 200);
        txSleep(dt);
    }


    return 0;
}
