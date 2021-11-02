#include <iostream>
using namespace std;

void NumSeries(int num)
{
   if (num == 0)
      cout << 1 << " ";
   else
   {
      NumSeries(num - 1);
      num = num + 1;
      cout << num * 2 << " ";
   }
}

int main()
{
   NumSeries(2);
   return 0;
}