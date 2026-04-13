#include <stdio.h>

int fibo(int n) {
   int f1 = 1;
   int f2 = 1;

   if (n <= 1) {
      return f1;
   }
   else if (n <= 2) {
      return f2;
   }
   else {
      int fn;

         for (int i = 3; i <= n; i++) {
            fn = f1 + f2;

            f1 = f2;
            f2 = fn;
         }   

      return fn;
   }
   
}

int fibo_r(int n) {
   if (n <= 2) return 1;
   else return fibo_r(n - 1) + fibo_r(n - 2);
}

int main() {
   int n = fibo(1);
   printf("f(1); %d", n);
}
