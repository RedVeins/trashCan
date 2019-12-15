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
        txCircle(ball.x, ball.y, ball.r);
        txSetFillColor(RGB(0, 0, 0));
    }
}

void moveBall(Ball* ball, int wX, int wY)
{
    (*ball).(*pos).x += (*ball).(*vel).x * dt;
    (*ball).(*pos).y += (*ball).(*vel).y * dt;
    if ((*ball).(*pos).y > (wY - (*ball).r) or (*ball).(*pos).y < (*ball).r)
        (*ball).(*vel).y = - (*ball).(*vel).y;
    if ((*ball).(*pos).x > (wX - (*ball).r) or (*ball).(*pos).x < (*ball).r)
        (*ball).(*vel).x = - (*ball).(*vel).x;
}

void collision(Ball* ball1, Ball* ball2)
{
    if ( ( abs((*ball1).(*pos).x - (*ball2).(*pos).x) < (2 * (*ball1).r) ) and ( abs((*ball1).(*pos).y - (*ball2).(*pos).y) < (2 * (*ball1).r) ) )
    {
        Vec center = sub((*ball1).pos, (*ball2).pos);
        Vec v1 = mul(norm(center), ((scal((*ball1).vel, center)) / len(center)));
        Vec v2 = mul(norm(center), ((scal((*ball2).vel, center)) / len(center)));
        
        (*ball1).(*vel) = sub((*ball1).vel, v1);
        (*ball2).(*vel) = sub((*ball2).vel, v2);        
}

void clldBalls(Ball* ball, num)
{
  for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
           if (i != j)
              CollideBall(&ball[i], &ball[j]);
        }
    }  
}

void array(Ball* ball, int num)
{
    srand(time(NULL));
    for (int i = 0; i < num/20; i += 1)
    {
        for (int j = 1; j < 20; j += 1)
        {
            ball[i * (num/20) + j - 1].r = 8;
            ball[i * (num/20) + j - 1].pos.x = (j + 1) * 45;
            ball[i * (num/20) + j - 1].pos.y = (i + 1) * 35;
            ball[i * (num/20) + j - 1].vel.x = rand() % vmax;
            ball[i * (num/20) + j - 1].vel.y = rand() % vmax;
            ball[i * (num/20) + j - 1].clrR = (rand() % vmax) * 50;
            ball[i * (num/20) + j - 1].clrG = 0;
            ball[i * (num/20) + j - 1].clrB = 250;
        }
    }
}

int main()
{
    float wX = 800;
    float xY = 600;
    num = 300;
    
    txCreateWindow(wX, wY);

    Ball *ball = new Ball[num];
    array(ball, num);

    for (;;)
    {
        txBegin();
        txClear();

        for (int i = 0; i < 15; i += 1)
        {
            newBall(ball[i]);
            moveBall(&ball[i]);
            txSetFillColor(RGB(0, 0, 0));
        }
        clldBalls(ball, num);

        txSleep(dt);
        txEnd();
    }
    
    delete[] ball;

    return 0;
}
