#include <stdio.h>
#include <assert.h>

/**
   Searches the first element of an array greater 
   than the specified value.

   @param ar is an input array.
   @param n denotes the size of an array.
   @param v is a specified value for searching.
   @return if such element is found that returns its index
           and -1 otherwise.
*/
int bsearch(const int ar[], int n, int v);

int main(void)
{
  int ar0[] = {}; 
  assert(bsearch(ar0, 0, 10) == -1);
  int ar1[] = {10}; 
  assert(bsearch(ar1, 1, 0) == 0);
  assert(bsearch(ar1, 1, 11) == -1);
  int ar2a[] = {10, 10}; 
  assert(bsearch(ar2a, 2, 9) == 0);
  assert(bsearch(ar2a, 2, 10) == -1);
  int ar2b[] = {10, 12}; 
  assert(bsearch(ar2b, 2, 9) == 0);
  assert(bsearch(ar2b, 2, 11) == 1);
  assert(bsearch(ar2b, 2, 13) == -1);
  int ar3[] = {10, 11, 12}; 
  assert(bsearch(ar3, 3, 11) == 2);
  assert(bsearch(ar3, 3, 12) == -1);
  int ar10[] = {1, 1, 3, 3, 5, 6, 6, 6, 22, 44}; 
  assert(bsearch(ar10, 10, 5) == 5);
  return 0;
}

int bsearch(const int ar[], int n, int v)
{
  assert(n >= 0);  
  assert(ar);

  if (n == 0 || ar[n-1] <= v)
    return -1;

  int left = 0, right = n - 1, middle;
  while (left < right) {
    middle = left + (right - left) / 2;
    if (ar[middle] <= v)
      left = middle + 1;
    else 
      right = middle;
  }
  return left;
}
