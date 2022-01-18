#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}node;

node* root_ptr;

void insertion(int value, node* pointer){
    if(pointer== NULL){//if pointer to root = NULL
        pointer= malloc(sizeof(node));
       pointer-> data= value;
        pointer->right =NULL;
        pointer->left=NULL;
        root_ptr =pointer;
        printf("inserted\n");
        return;
    }
    else if(value < pointer->data){// LEFT SIDE OF ROOT
       if(pointer->left==NULL){
        node* goes_left = malloc(sizeof(node));
        goes_left->data = value;
        pointer->left=goes_left;
        goes_left->right=NULL;
        goes_left->left=NULL;
        printf("inserted\n");
        return;
       }
       insertion(value,pointer->left);
    }
    else if(value > pointer->data){//RIGHT SIDE of the ROOT
       if(pointer->right==NULL){
         node* goes_right= malloc(sizeof(node));
        goes_right->data=value;
        pointer->right=goes_right;
        goes_right->right=NULL;
        goes_right->left=NULL;
        printf("inserted\n");
        return;
       }
       insertion(value,pointer->right);
    }
    else if(value == pointer->data){//IF VALUE IS ALREADY INSIDE RETURN ORIGINAL
        printf("not inserted\n");
        return;
    }
    else{
          printf("insert error %d %d\n",pointer->data, value);
    }
    return;
}

// void search(int val, node* pointer){
//     if(pointer== NULL){
//         printf("absent\n");
//         return;
 
//     }
//     else if(val == pointer->data){
//         printf("present\n");
//         return;
//     }
 
//     else if(val > pointer->data){
//             //go right subtree
//             if(pointer->right == NULL){
//                 printf("absent\n");
//                 return;
//             }
//             search(val, pointer->right);
 
//     }
//     else if(val < pointer->data){
//             //go to left subtree
//             if(pointer->left == NULL){
//                 printf("absent\n");
//                 return;
//             }
//             search(val, pointer->left);
 
//         }
//     }
int search(node* pointer,int value){
  while(pointer!=NULL){
      if(value > pointer->data){
          return search(pointer->right,value);
      }
      else if(value < pointer->data){
          return search(pointer->left,value);
      }else{
          return 1;
      }
  }  
    return 0;
}


 void delete(node* pointer, int value){
     node* null_ptr =NULL;
     if(pointer==NULL){
         printf("absent\n");
         return;
     }
     if(pointer!=NULL){
         if(pointer->data ==value){
             if(pointer->right== NULL && pointer->left==NULL){
                 pointer=null_ptr;
                 free(pointer);
             }
         }
     }
//          if(pointer->data < value){
//         if(pointer->right ==NULL && pointer->left==NULL){
//             pointer= null_ptr;
//             free(pointer);
//             printf("deleted\n");
//             return pointer;
//         }
//          }
//          else if(value > pointer->data){
//              pointer->right = delete(pointer->right,value);
//          }
//          else if( value< pointer->data){
//              pointer->left = delete(pointer->left,value);
//          }
//          else if(pointer->left != NULL && pointer->right ==NULL){
//              node* other = pointer->right;
//              free(pointer);
//              return other;
//          }
//          else if(pointer->left ==NULL && pointer->right != NULL){
//              node* other = pointer->left;
//              free(pointer);
//              return other;
//          }else{
//              node* other = findMax(pointer->left);
//             pointer->data = other->data;
//             pointer->left= delete(pointer->left,other->data);
             
//          }
      
//      }
//     return pointer;
    printf("absent\n");
    return;
  }
void printNodes( node* pointer){
    if(pointer != NULL){
        printf("(");
        if(pointer->left != NULL){
            printNodes(pointer->left);
        }
        printf("%d", pointer->data);
        if(pointer->right != NULL){
            printNodes(pointer->right);
        }
        
        printf(")");
    }
    
    return;
}

void free_stuff(node* pointer){
    if(pointer == NULL){
        return;
        }
    free_stuff(pointer->left);
    free_stuff(pointer->right);
    free(pointer);
    return;
}

int main(int argc, char**argv){
 int data;
    char c;
    int flag =0;
    while(scanf("%c", &c) != -1){
    
      if(c == 'i'){
          scanf("%d", &data);
          insertion(data, root_ptr);
      }
      else if(c == 's'){ 
          scanf("%d", &data);
           flag =search(root_ptr,data);
           if(flag){
               printf("present\n");
           }else{
               printf("absent\n");
           }
          //search(root_ptr,data);     
      }
      else if(c == 'd'){
        printf("B\n");
        scanf("%d", &data);
      delete(root_ptr, data);
        printNodes(root_ptr);
      }
       else if(c == 'p'){
           printNodes(root_ptr);
           printf("\n");     
       }
    }
    free_stuff(root_ptr);
    return EXIT_SUCCESS;
}
 

