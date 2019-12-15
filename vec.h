#include <cmath>

struct Vec
{
  float x = 0;
  float y = 0;
}

Vec add(Vec a, Vec b)
{
  Vec res;
  res.x = a.x + b.x;
  res.y = a.y + b.y;
  return res;
}

Vec sub(Vec b, Vec b)
{
  Vec res;
  res.x = a.x - b.x;
  res.y = a.y - b.y;
  return res;
}

Vec mul(Vec a, float n)
{
  Vec res;
  res.x = a.x * n;
  res.y = a.y * n;
  return res;
}

float len(Vec a)
{
  float res;
  res = sqrt(a.x * a.x + a.y * a.y);
  return res;
}

float scal(Vec a, Vec b)
{
  float res;
  res = a.x * b.x + a.y * b.y;
  return res;  
}

Vec norm(Vec a)
{
  Vec res;
  res = mul(a, 1/len(a));
  return res;  
}

float angle(Vec a, Vec b)
{
  float res;
  Vec c = sub(a, b);
  if (len(c) != 0);
    return res = scal(a, b) / ( len(a) * len(b) );
  else
    return res = 0;
  
}
