#include "TXLib.h"

const float dt = 1;

struct Ball
{
    float r = 0;
    float x = 0;
    float y = 0;
    float vx = 0;
    float vy = 0;
    float clrR = 0;
    float clrG = 0;
    float clrB = 0;
};

void newBall(Ball ball)
{
    for(int i = ball.r; ball.r > 0; ball.r = ball.r - 2)
    {
        txSetColor(RGB(ball.clrR - ball.clrR*ball.r/i, ball.clrG - ball.clrG*ball.r/i, ball.clrB - ball.clrB*ball.r/i));
        txSetFillColor(RGB(ball.clrR - ball.clrR*ball.r/i, ball.clrG - ball.clrG*ball.r/i, ball.clrB - ball.clrB*ball.r/i));
        txCircle(ball.x, ball.y, ball.r);
        txSetFillColor(RGB(0, 0, 0));
    }
}

void moveBall(Ball* ball)
{
    if ((*ball).y > (400 - (*ball).r) || (*ball).y < (*ball).r)
        (*ball).vy = - (*ball).vy;
    if ((*ball).x > (600 - (*ball).r) || (*ball).x < (*ball).r)
        (*ball).vx = - (*ball).vx;
    (*ball).x += (*ball).vx * dt;
    (*ball).y += (*ball).vy * dt;
}

void cntrlBall(Ball* ball)
{
    if (GetAsyncKeyState(VK_LEFT))
        (*ball).vx -= 0.05;
    if (GetAsyncKeyState(VK_RIGHT))
        (*ball).vx += 0.05;
    if (GetAsyncKeyState(VK_UP))
        (*ball).vy -= 0.05;
    if (GetAsyncKeyState(VK_DOWN))
        (*ball).vy += 0.05;
}

void collide(Ball* ball1, Ball* ball2)
{
    if ((abs((*ball1).x - (*ball2).x) < (*ball1).r + (*ball2).r) and (abs((*ball1).y - (*ball2).y) < (*ball1).r + (*ball2).r))
    {
        (*ball1).vx = - (*ball1).vx;
        (*ball1).vy = - (*ball1).vy;
        (*ball2).vx = - (*ball2).vx;
        (*ball2).vy = - (*ball2).vy;
    }
}

int main()
{
    txCreateWindow(600, 400);

    Ball ball1;
    ball1.r = 10;
    ball1.x = 100;
    ball1.y = 100;
    ball1.vx = 1;
    ball1.vy = 1;
    ball1.clrR = 200;
    ball1.clrG = 200;
    ball1.clrB = 0;

    Ball ball2;
    ball2.r = 10;
    ball2.x = 120;
    ball2.y = 120;
    ball2.vx = -2;
    ball2.vy = 2;
    ball2.clrR = 200;
    ball2.clrG = 0;
    ball2.clrB = 200;

    Ball ball3;
    ball3.r = 10;
    ball3.x = 140;
    ball3.y = 140;
    ball3.vx = 1;
    ball3.vy = -2;
    ball3.clrR = 0;
    ball3.clrG = 200;
    ball3.clrB = 200;

    for (;;)
    {
        txClear();

        newBall(ball1);
        cntrlBall(&ball1);
        moveBall(&ball1);

        newBall(ball2);
        cntrlBall(&ball2);
        moveBall(&ball2);

        newBall(ball3);
        cntrlBall(&ball3);
        moveBall(&ball3);

        collide(&ball1, &ball2);
        collide(&ball1, &ball3);
        collide(&ball2, &ball3);

        txSleep(dt);
    }


    return 0;
}
