#include "TXLib.h"
#include <ctime>
#include "vec.h"

const float dt = 1;
const int vmax = 8;

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
    (*ball).pos.x += (*ball).vel.x * dt;
    (*ball).pos.y += (*ball).vel.y * dt;
    if ((*ball).pos.y > (wY - (*ball).r) or (*ball).pos.y < (*ball).r)
        (*ball).vel.y = - (*ball).vel.y;
    if ((*ball).pos.x > (wX - (*ball).r) or (*ball).pos.x < (*ball).r)
        (*ball).vel.x = - (*ball).vel.x;
}

void collision(Ball* ball1, Ball* ball2)
{
    if ( sub((*ball1).pos, (*ball2).pos) == 2 * (*ball1).r )
    {
        Vec center = sub((*ball1).pos, (*ball2).pos);
        Vec v1proect = mul(norm(center), ((scal((*ball1).vel, center)) / len(center)));
        Vec v2proect = mul(norm(center), ((scal((*ball2).vel, center)) / len(center)));

        (*ball1).vel = sub((*ball1).vel, v1proect);
        (*ball2).vel = sub((*ball2).vel, v2proect);

        if (len(center) < (*ball1).r + (*ball2).r)
        {
            (*ball1).pos = add((*ball2).pos, mul(norm(center), ((*ball1).r + (*ball2).r - len(center)/2)));
            (*ball2).pos = sub((*ball1).pos, mul(norm(center), ((*ball1).r + (*ball2).r - len(center)/2)));
        }
    }
}

void clldBalls(Ball* ball, int num)
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
           if (i != j)
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
    float wX = 800;
    float wY = 600;
    int num = 300;

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
