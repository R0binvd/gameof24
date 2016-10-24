#include <stdio.h>

#define Plus 10
#define Min 11
#define Times 12
#define Div 13

int printedString[20];  //I'll make this one global so I can check if the combination I'm printing is the one I JUST printed, since the two formulas overlap sometimes

int printLayout1(int printable[]){    //I first place the parenthesis where needed, then fill the blanks with a for loop
  int i, j=0, upto=7;
  for(i=0; i<7; i++) scanf("%d", &printable[i]);
  if(printable[2]<12 && printable[4]>11){printedString[0]=-8; printedString[4]=-7; upto=9;}
  if(printable[2]<12 && printable[4]<12 && printable[6]>11){printedString[0]=-8; printedString[6]=-7; upto=9;}
  if(printable[2]>11 && printable[4]<12 && printable[6]>11){printedString[0]=-8; printedString[6]=-7; upto=9;}
  for(i=0; i<9; i++){
     if(printedString[i]!=-8 && printedString[i]!=-7){
          if(j==0) printedString[i]=printable[0];
          else if(j%2!=0) printedString[i]=printable[j+1];
          else if(j%2==0) printedString[i]=printable[j-1];;
          j++;
        }
  }
  return upto;
}

int printLayout2(int printable[]){
  int i, j=0, upto=7;
  if(printable[2]<12 && printable[5]<12 && printable[6]<12) return 0;                                              //checking if... 
  if(printable[2]<12 && printable[5]>11) return 0;                                                                 //...already printed
  if(printable[2]<12 && printable[6]>11){printedString[0]=-8; printedString[4]=-7; upto+=2;}                       //here i plave the parenthesis in the right spot...
  if(printable[5]<12 && printable[6]>11){                                                                          //
       if(upto==9)   {printedString[6]=-8; printedString[10]=-7; upto+=2;}                                         //
       else          {printedString[4]=-8; printedString[8]=-7; upto+=2;}                                          //...all the way down here
  }
  if(upto==9){printedString[3]=printable[6]; printedString[1]=printable[2]; printedString[6]=printable[5];}
  if(upto==11){printedString[5]=printable[6]; printedString[2]=printable[2]; printedString[8]=printable[5];}
  for(i=0; i<upto; i++){
       if(printedString[i]<10 && printedString[i]>0){
           if(printable[j]<10) printedString[i]=printable[j];
           else printedString[i]=printable[j+1];
           j++;
       }
  }
  return upto;
}

//input is an array of length 7;
//10:+ 11:- 12:* 13:/
int math(int arr[]) {
  int i,current=0;
  float stack[4];
  for (i=0; i<7; i++) {
    if (arr[i] < 10) {
      stack[current] = arr[i];
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

//Rearrange and print reverse polish notation in normal notation, input is a 7 elements array, also checks if string has been already printed 
void printp(int sequence[]) {
     int i, upto;
     if(sequence[4]>=10)  upto=printLayout1(sequence);     //print the ab?c?d? form
     else upto=printLayout2(sequence);                     //print the ab?cd?? form
     for(i=0; i<upto; i++){
         if(printedString[i]<10)  printf("%c", printedString[i]+48);
         else{
          switch(printedString[i]){
            case Add: printf("+");
            break;
            case Sub: printf("-");
            break;
            case Mul: printf("*");
            break;
            case Div: printf("/");
            break;
          }
         }
     }
}          

int main() {
  //testcase for the math function, should output -1;
  int arr[7] = {1,2,3,4,Div,Plus,Plus};
  printf("%d\n", math(arr));
}
