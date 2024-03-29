#include "TXLib.h"

const float dt = 1;

void newBall(int x, int y, int R, int clrR, int clrG, int clrB)
{
    for(int r = R; r > 0; r = r - 2)
    {
        txSetColor(RGB(clrR - clrR*r/R, clrG - clrG*r/R, clrB - clrB*r/R));
        txSetFillColor(RGB(clrR - clrR*r/R, clrG - clrG*r/R, clrB - clrB*r/R));
        txCircle(x, y, r);
        txSetFillColor(RGB(0, 0, 0));
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
        *vx -= 0.05;
    if (GetAsyncKeyState(VK_RIGHT))
        *vx += 0.05;
    if (GetAsyncKeyState(VK_UP))
        *vy -= 0.05;
    if (GetAsyncKeyState(VK_DOWN))
        *vy += 0.05;
}

void collide(float r,float x1,float y1, float* vx1, float* vy1,float x2,float y2, float* vx2, float* vy2)
{
    if ((abs(x1 - x2) < 2*r) and (abs(y1 - y2) < 2*r))
    {
        *vx1 = - *vx1;
        *vy1 = - *vy1;
        *vx2 = - *vx2;
        *vy2 = - *vy2;
    }
}

int main()
{
    txCreateWindow(600, 400);
    float x = 100;
    float y = 100;
    float vx = 1;
    float vy = 1;
    float r = 50;
    float x1 = 500;
    float y1 = 300;
    float vx1 = 1;
    float vy1 = 1;

    for (;;)
    {
        txClear();

        newBall(x, y, r, 200, 50, 200);
        cntrlBall(&vx, &vy);
        moveBall(r, &x, &y, &vx, &vy, dt);

        newBall(x1, y1, r, 50, 200, 50);
        moveBall(r, &x1, &y1, &vx1, &vy1, dt);

        collide(r, x, y, &vx, &vy, x1, y1, &vx1, &vy1);

        txSleep(dt);
    }


    return 0;
}
