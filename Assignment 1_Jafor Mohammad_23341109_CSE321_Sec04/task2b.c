#include <stdio.h>
#include <string.h>

int main(){
  FILE *inputFile, *outputFile;
  inputFile = fopen("input2b.txt", "r");
  outputFile = fopen("output2b.txt", "w");  
  char inp[100];
  char out[26];
  fgets(inp, 255, (FILE*)inputFile);
  int flag = 1;
  int idx = 0, i = 0;
  while(inp[i] != '.'){
    if(inp[i] == ' '){
      if(flag){
        out[idx] = inp[i];
        idx++;
        flag = 0;
      }
    }else{
      flag = 1;
      out[idx] = inp[i];
      idx++;
    }
    i++;
  }
  fputs(out, outputFile);
  fclose(inputFile);
  fclose(outputFile);
  return 0;
}