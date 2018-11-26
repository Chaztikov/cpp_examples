#include "./helpers.h"

int main()
{
  auto x = linspace(0, 2 * 3.14, 100);
  plot(x, sin(x) + sin(3.f * x) / 3.f + sin(5.f * x) / 5.f);
}
