#include <iostream>

#define BUFFER_SIZE 50

template <class T> void gcd(const polynomialT<T> &a, const polynomialT<T> &b, polynomialT<T> &g, polynomialT<T> &s, polynomialT<T> &t)
//void gcd(int a, int b, int &g, int &s, int &t)
{
   polynomialT<T> s_neg1 = 1;
   polynomialT<T> s_0 = 0;
   polynomialT<T> t_neg1 = 0;
   polynomialT<T> t_0 = 1;
   int i = 0;
   polynomialT<T> r_neg1 = a;
   polynomialT<T> r_0 = b;
   polynomialT<T> r_arr[BUFFER_SIZE];
   polynomialT<T> q_arr[BUFFER_SIZE];
   polynomialT<T> s_arr[BUFFER_SIZE];
   polynomialT<T> t_arr[BUFFER_SIZE];
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
