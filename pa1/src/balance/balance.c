#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node
{
    char data;
    struct node *next;
};

struct node *top = NULL;

void push(char);
void pop();

void push(char item)
{
    struct node *nptr = malloc(sizeof(struct node));
    nptr->data = item;
    nptr->next = top;
    top = nptr;
}


void pop()
{
    if (top == NULL)
    {
        printf("\n\nStack is empty ");
    }
    else
    {
        struct node *temp;
        temp = top;
        top = top->next;
        //printf("\n\n%d deleted", temp->data);
        free(temp);
    }
}





//     int checking( char first_char, char second_char){
//          if((first_char == '(') && (second_char ==')')){
//              printf("they are equal");
//        return 0;
//  }
//  else if((first_char == '[') && (second_char ==']')){
//         printf("they are equal");
//            return 0;
//   }
//   else if((first_char == '(') && (second_char ==')')){
//         printf("they are equal");
//        return 0;
//    }else{
//         printf("they are not equal");
//      return 1;
//    }
  
//      }

int main(int argc, char** argv){

  //  char other_char;
  
 for(int i = 0; i <= strlen(argv[1])+1;i++){
     char now_char = *(argv[1]+i);//traversing
    // char* p;
    
   // char other_char = *(argv[i]);
   
    if(now_char == '{' || now_char== '[' || now_char == '('){
         push(now_char);
     } 
    else if(now_char =='}' && top-> data != '{'){
         printf("%d: %c\n",i,now_char);
         return 1;
     }
     else if(now_char == ')' && top->data != '('){
         printf("%d: %c\n", i,now_char);
         return 1;
     }
     else if(now_char == ']' && top->data !='['){
         printf("%d: %c\n",i,now_char);
         return 1;
     }
     if(now_char == '}' && top-> data == '{') { //compares then pops 
         pop();
     }
     else if(now_char == ')' && top-> data == '(') { //pushes {,(,[
         pop();

     }
     else if(now_char == ']' && top-> data == '[') { //pushes {,(,[
         pop();
     
     }

    
 
      
 
 

 }
 for(int j = 0; j <= strlen(argv[1])+1;j++){
     char new_other_char = *(argv[1]+1);
         if(new_other_char == '}' && top-> data == '{') { //compares then pops 
         pop();
     }
     else if(new_other_char == ')' && top-> data == '(') { //pushes {,(,[
         pop();

     }
     else if(new_other_char == ']' && top-> data == '[') { //pushes {,(,[
         pop();
     
     }
    
 }
 if(top!=NULL){
     if(top!=NULL){
         printf("open: ");
    while(top != NULL){
        if(top->data == '('){
            printf(")");

        }
          if(top->data == '{'){
            printf("}");
    }
      if(top->data == '['){
            printf("]");

     }
     pop();
     
 }
 return 1;
}
 }else{
//      if(top!=NULL){
//          printf("open: ");
//     while(top != NULL){
//         if(print_top() == '('){
//             printf(")");

//         }
//           if(print_top() == '{'){
//             printf("}");
//     }
//       if(print_top() == '['){
//             printf("]");

//      }
//      pop();
     
//  }
//  return 1;
// }
    if(top==NULL){
        return 0;
    }
 }

}
