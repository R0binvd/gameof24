#include <stdio.h>

#define Plus 10
#define Min 11
#define Times 12
#define Div 13

int printedString[20]  //I'll make this one global so I can check if the combination I'm printing is the one I JUST printed, since the two formulas overlap sometimes

void printLayout1(int printable[]){    //I first place the parenthesis where needed, then fill the blanks with a for loop
  int i, j=0, upto=7;
  for(i=0; i<7; i++) scanf("%d", &printable[i]);
  if(printable[2]<12 && printable[4]>11){printedString[0]=40; printedString[4]=41; upto=9;}
  if(printable[2]<12 && printable[4]<12 && printable[6]>11){printedString[0]=40; printedString[6]=41; upto=9;}
  if(printable[2]>11 && printable[4]<12 && printable[6]>11){printedString[0]=40; printedString[6]=41; upto=9;}
  for(i=0; i<9; i++){
     if(printedString[i]!=40 && printedString[i]!=41){
          if(j==0) printedString[i]=printable[0];
          else if(j%2!=0) printedString[i]=printable[j+1];
          else if(j%2==0) printedString[i]=printable[j-1];;
          j++;
        }
  }
}

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
  if (stack[0] - (int)stack[0] == 0) {
    return stack[0];
  } else {
    return -1;
  }
}

//Rearrange and print reverse polish notation in normal notation, input is a 7 elements array 
void printp(int sequence[]) {
     if(sequence[3]>=10)  printLayout1(sequence);     //print the ab?c?d? form
     else printLayout2(sequence);                     //print the ab?cd?? form
}

int main() {
  //testcase for the math function, should output -1;
  int arr[7] = {1,2,3,4,Div,Plus,Plus};
  printf("%d\n", math(arr));
}
