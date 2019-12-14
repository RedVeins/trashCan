#include "TXLib.h"
#include <ctime>

const float dt = 1;
const int vmax = 8;

struct Ball
{
    float r = 0;
    float x = 0;
    float y = 0;
    float vx = 0;
    float vy = 0;
    float v = 0;
    float clrR = 0;
    float clrG = 0;
    float clrB = 0;
};

void newBall(Ball ball)
{
    for(float i = ball.r; i > 0; i = i - 2)
    {
        txSetColor(RGB(ball.clrR * (1 - i/ball.r), ball.clrG * (1 - i/ball.r), ball.clrB * (1 - i/ball.r)));
        txSetFillColor(RGB(ball.clrR * (1 - i/ball.r), ball.clrG * (1 - i/ball.r), ball.clrB * (1 - i/ball.r)));
        txCircle(ball.x, ball.y, ball.r);
        txSetFillColor(RGB(0, 0, 0));
    }
}

void moveBall(Ball* ball)
{
    (*ball).x += (*ball).vx * dt;
    (*ball).y += (*ball).vy * dt;
    if ((*ball).y > (600 - (*ball).r) or (*ball).y < (*ball).r)
        (*ball).vy = - (*ball).vy;
    if ((*ball).x > (800 - (*ball).r) or (*ball).x < (*ball).r)
        (*ball).vx = - (*ball).vx;
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

void clldBall(Ball* ball1, Ball* ball2)
{
    if ( ( abs((*ball1).x - (*ball2).x) < (2 * (*ball1).r) ) and ( abs((*ball1).y - (*ball2).y) < (2 * (*ball1).r) ) )
    {
        float v1 = sqrt(pow((*ball1).vx, 2) + pow((*ball1).vy, 2));
        float v2 = sqrt(pow((*ball2).vx, 2) + pow((*ball2).vy, 2));
        float cos = ((*ball1).vx * (*ball2).vx + (*ball1).vy * (*ball2).vy)/(v1 * v2);

        if ( ( ((*ball1).vx > 0) and ((*ball2).vx > 0) ) and ( (*ball1).vy * (*ball2).vy < 0 ) )
        {
            (*ball1).vy = - (*ball2).vy;
            (*ball2).vy = - (*ball1).vy;
        }

        else if ( (*ball1).vy > 0 and (*ball2).vy > 0 and ( (*ball1).vx * (*ball2).vx < 0 ) )
        {
            (*ball1).vx = - (*ball2).vx;
            (*ball2).vx = - (*ball1).vx;
        }

        else if ( ( ((*ball1).vx * (*ball2).vx) < 0 ) and ( (*ball1).vy * (*ball2).vy < 0 ) )
        {
            (*ball1).vx = (*ball2).vx;
            (*ball2).vx = (*ball1).vx;
            (*ball1).vy = (*ball2).vy;
            (*ball2).vy = (*ball1).vy;
        }
    }
}


int main()
{
    srand(time(NULL));

    txCreateWindow(800, 600);

    Ball *ball = new Ball[300];
    for (int i = 0; i < 15; i += 1)
    {
        for (int j = 0; j < 20; j += 1)
        {
            ball[i * 15 + j - 1].r = 8;
            ball[i * 15 + j - 1].x = (j + 1) * 45;
            ball[i * 15 + j - 1].y = (i + 1) * 35;
            ball[i * 15 + j - 1].vx = rand() % vmax + 1;
            ball[i * 15 + j - 1].vy = rand() % vmax + 1;
            ball[i * 15 + j - 1].clrR = (rand() % vmax) * 50;
            ball[i * 15 + j - 1].clrG = 0;
            ball[i * 15 + j - 1].clrB = 250;
        }
    }

    for (;;)
    {
        txBegin();
        txClear();

        for (int i = 0; i < 15; i += 1)
        {
            newBall(ball[i]);
            moveBall(&ball[i]);
            txSetFillColor(RGB(0, 0, 0));

            for (int j = 0; j < 20; j += 1)
            {
                clldBall(&ball[i], &ball[j]);
            }
        }


        txSleep(dt);

        txEnd();
    }


    return 0;
}
