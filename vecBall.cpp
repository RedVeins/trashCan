#include "TXLib.h"
#include <ctime>
#include "vec.h"

const float dt = 0.01;
const int vmax = 200;

struct Ball
{
    Vec pos;
    Vec vel;
    float r = 0;
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
        txCircle(ball.pos.x, ball.pos.y, ball.r);
        txSetFillColor(RGB(0, 0, 0));
    }
}

void moveBall(Ball* ball, int wX, int wY)
{
    (*ball).pos = add((*ball).pos, mul((*ball).vel, dt));

    if ((*ball).pos.y > (wY - (*ball).r))
    {
        (*ball).pos.y = wY - (*ball).r;
        (*ball).vel.y = - (*ball).vel.y;
    }
    if ((*ball).pos.y < (*ball).r)
    {
        (*ball).pos.y = (*ball).r;
        (*ball).vel.y = - (*ball).vel.y;
    }
    if ((*ball).pos.x > (wX - (*ball).r))
    {
        (*ball).pos.x = wX - (*ball).r;
        (*ball).vel.x = - (*ball).vel.x;
    }

    if ((*ball).pos.x < (*ball).r)
    {
        (*ball).pos.x = (*ball).r;
        (*ball).vel.x = - (*ball).vel.x;
    }

}

void collision(Ball* ball1, Ball* ball2)
{
    if ( abs(len(sub((*ball1).pos, (*ball2).pos)) < 2 * (*ball1).r) )
    {
        std::swap((*ball1).vel, (*ball2).vel);
        float dist = len(sub((*ball1).pos, (*ball2).pos));
        float h = (*ball1).r - dist/2;
        Vec delta = mul(norm(sub((*ball1).pos, (*ball2).pos)), h);
        (*ball1).pos = add((*ball1).pos, delta);
        (*ball2).pos = add((*ball2).pos, delta);
    }
}

void clldBalls(Ball* ball, int num)
{
    for (int i = 0; i < num; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
              collision(&ball[i], &ball[j]);
        }
    }
}

void array(Ball* ball, int num, float wX, float wY)
{
    srand(time(NULL));
    float radius = 8;
    float x = radius * 3, y = radius * 3;
    for (int i = 0; i < num; i++)
    {
        ball[i].r = radius;
        ball[i].pos.x = x;
        ball[i].pos.y = y;
        ball[i].vel.x = rand() % vmax;
        ball[i].vel.y = rand() % vmax;
        ball[i].clrR = (rand() % vmax) * 50;
        ball[i].clrG = 0;
        ball[i].clrB = 250;
        x += 5 * radius;
        if (x + radius >= wX) {
            x = 3 * radius;
            y += 5 * radius;
        }
    }
}

int main()
{
    float wX = 300;
    float wY = 300;
    int num = 25;

    txCreateWindow(wX, wY);

    Ball *ball = new Ball[num];
    array(ball, num, wX, wY);

    for (;;)
    {
        txBegin();
        txClear();

        for (int i = 0; i < num; i += 1)
        {
            newBall(ball[i]);
            moveBall(&ball[i], wX, wY);
            txSetFillColor(RGB(0, 0, 0));
        }
        clldBalls(ball, num);

        txSleep(dt);
        txEnd();
    }

    delete[] ball;

    return 0;
}
