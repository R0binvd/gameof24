#include <stdio.h>

#define Plus 10
#define Min 11
#define Times 12
#define Div 13

//input is an array of length 7;
//10:+ 11:- 12:* 13:/
int math(int arr[]) {
  int i,current=0;
  float stack[4];
  for (i=0; i<7; i++) {
    if (arr[i] < 10) {
      stack[i] = arr[i];
      current++;
    } else {
      switch (arr[i]){
        case Plus:
          stack[current-2] = stack[current-2] + stack[current-1];
        break;
        case Min:
          stack[current-2] = stack[current-2] - stack[current-1];
        break;
        case Times:
          stack[current-2] = stack[current-2] * stack[current-1];
        break;
        case Div:
          stack[current-2] = stack[current-2] / stack[current-1];
      
      }
      current--;
    }
  }
  printf("%f %d\n",stack[0], (int)stack[0]);
  if (stack[0] - (int)stack[0] == 0) {
    return stack[0];
  } else {
    return -1;
  }
}

void printp() {
                       //robin fag
}

int main() {
  int arr[7] = {1,2,3,4,Div,Plus,Plus};
  printf("%d\n", math(arr));
}
