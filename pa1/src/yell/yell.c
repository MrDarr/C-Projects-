#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



int main(int argc, char** argv)
{
 char* travisScott;
 int dog = strlen(argv[1]);
 travisScott = argv[1];
 int c = 0;
for(int i = 0; i < dog;i++){
  c++;
  int kanye = travisScott[i];
  int drake = toupper(kanye);
  printf("%c",drake);
  if( c == dog){
    printf("%s", "!!");

  }
 
}
//TS[i] -- int
//toupper(TS[i]) -- int
//printf("%c", toup)

}
