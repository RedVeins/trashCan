#include "TXLib.h"

void newBall(int x, int y, int R, int clrR, int clrG, int clrB)
{
    for(int r = R; r > 0; r = r - 2)
    {
        txSetColor(RGB(clrR - clrR*r/R, clrG - clrG*r/R, clrB - clrB*r/R));
        txSetFillColor(RGB(clrR - clrR*r/R, clrG - clrG*r/R, clrB - clrB*r/R));
        x = x - 1;
        y = y - 1;
        txCircle(x, y, r);
    }
}

int main()
{
    txCreateWindow(900, 700);
    newBall(400, 300, 100, 200, 100, 0);
    newBall(500, 500, 200, 0, 100, 200);
    return 0;
}
