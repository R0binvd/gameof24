#include <stdio.h>
#include <stdlib.h>

#define NumtoChar(x) ((x==11) ? '+' : (x==12) ? '-' : (x==13) ? '*' : '/')
#define MaxNum 10
#define Add 11
#define Sub 12
#define Mul 13
#define Div 14

/*node either has just a int value, or an operator and a left and right node*/
struct node {
  int value;
  struct node *left;
  struct node *right;
} node;

void swap(int *a, int *b) {
  int swap;
  swap = *a;
  *a = *b;
  *b = swap;
  return;
}

/*from postfix to infix tree. return a pointer to the top of the tree*/
struct node *conv(int **stack) {
  struct node *x;
  if (**stack > 10) {
    x = malloc(sizeof(struct node));
    x -> value = **stack;
    *stack = *stack - 1;
    x -> right = conv(stack);
    *stack = *stack - 1;
    x -> left = conv(stack);
    return x;
  } else {
    x = malloc(sizeof(struct node));
    x -> value = **stack;
    return x;
  }
}


/*from infix tree to stdout*/
void printp(struct node x) {
  if (x.value >= MaxNum) {
    putchar('(');
    printp(*x.left);
    putchar(NumtoChar(x.value));
    printp(*x.right);
    putchar(')');
  } else {
    printf("%d", x.value);
  }
}

//input is an array of length 7;
int math(int arr[]) {
  int i,current=0;
  float stack[4];
  for (i=0; i<7; i++) {
    if (arr[i] <= MaxNum) {
      stack[current] = arr[i];
      current++;
    } else {
      switch (arr[i]){
        case Add:
          stack[current-2] = stack[current-2] + stack[current-1];
        break;
        case Sub:
          stack[current-2] = stack[current-2] - stack[current-1];
        break;
        case Mul:
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


void gennumbers(int input[4], int n) {
  int j;
  struct node *x;
  if (n==4) {
    int operators;
    for (operators=0; operators<64; operators++) {
      int arr[7]= {input[0], input[1], 0, input[2], 0, input[3], 0};
      int *ptr = arr + 6;
      int tmp;
      tmp = operators;
      arr [2] = tmp % 4 + Add;
      tmp /= 4;
      arr [4] = tmp % 4 + Add;
      tmp /= 4;
      arr [6] = tmp % 4 + Add;
      if (math(arr)==24) {
        x = conv(&ptr);
        printp(*x);              //ab?c?d?
        //todo free the tree
        exit(0);
      }
      swap(arr + 4, arr + 5);
      /*if (math(arr)==24) {*/
        /*x = conv(arr);*/
        /*printp(x);              //ab?cd??*/
        /*exit(0);*/
      /*}*/
    }
  } else {
    for (j=n; j<4; j++) {
      swap(input + n, input + j);
      gennumbers(input, n+1);
      swap(input + n , input + j);
    }
  }
}

int main() {
  int input[4];
  int i;
  for (i=0; i<4; i++)
    scanf("%d", input+i);

  /*int arr[7] = {1,2,'+',3,4,'+','*'};*/
  /*printf("%d\n", math(arr));*/

  gennumbers(input, 0);
  return 0;
}
