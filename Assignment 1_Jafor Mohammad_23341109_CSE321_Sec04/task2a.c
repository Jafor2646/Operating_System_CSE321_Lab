#include <stdio.h>

int main(){
  int num1, num2, res;
  char op;
  printf("Enter two numbers and an operator: ");
  scanf("%d %d %c", &num1, &num2, &op);
  if(num1>num2){
    res = num1-num2;
  }else if(num1 < num2){
    res = num1+num2;
  }else{
    res = num1*num2;
  }
  printf("%d", res);
  return 0;
}