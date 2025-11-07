#include <iostream>

#define BUFFER_SIZE 50

void gcd(int a, int b, int &g, int &s, int &t)
{
   int s_neg1 = 1;
   int s_0 = 0;
   int t_neg1 = 0;
   int t_0 = 1;
   int i = 0;
   int r_neg1 = a;
   int r_0 = b;
   int r_arr[BUFFER_SIZE];
   int q_arr[BUFFER_SIZE];
   int s_arr[BUFFER_SIZE];
   int t_arr[BUFFER_SIZE];
   r_arr[0] = r_0;
   s_arr[0] = s_0;
   t_arr[0] = t_0;
   while(r_arr[i] != 0)
   {
      i++;
      if (i == 1)
      {
         q_arr[i] = r_neg1/r_0;
         r_arr[i] = r_neg1 - q_arr[i] * r_0;
         s_arr[i] = s_neg1 - q_arr[i] * s_0;
         t_arr[i] = t_neg1 - q_arr[i] * t_0;
      }
      else
      {
         q_arr[i] = r_arr[i-2]/r_arr[i-1];
         r_arr[i] = r_arr[i-2] - q_arr[i] * r_arr[i-1];
         s_arr[i] = s_arr[i-2] - q_arr[i] * s_arr[i-1];
         t_arr[i] = t_arr[i-2] - q_arr[i] * t_arr[i-1];
      }
   }

   g = r_arr[i-1];
   t = t_arr[i-1];
   s = s_arr[i-1];
}

int main(int argc, char* argv[])
{
   printf("Test on a=24, b=18\n");
   int a = 24;
   int b = 18;
   int g,s,t;
   gcd(a, b, g, s, t);
   printf("g = %d, s = %d, t = %d\n", g, s, t);
   printf("a*s + b*t = %d\n", a*s+b*t);
   printf("Test on a=851, b=966\n");
   a = 851;
   b = 966;
   gcd(a, b, g, s, t);
   printf("g = %d, s = %d, t = %d\n", g, s, t);
   printf("a*s + b*t = %d\n", a*s+b*t);
   return 0;
}
