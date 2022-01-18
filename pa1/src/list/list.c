#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//struct that creates linked lists
typedef struct node{
    int data;
   struct node* next;
}node;


// points to the head of the linked lists 
struct node* head ;
struct node* prev = NULL;
struct node* addition(int otherData);
struct node* deletion(int newData);
void traverseList();

node* nodes_more(int data){
    int count = 0;
    node* ton= (node*)malloc(sizeof(node*));
    ton->data = data;
    ton->next=NULL;
    count++;
    return ton;
}

 struct node* addition(int otherData){
     node* more_more= (node*)malloc(sizeof(node*));
     if((head==NULL)){  //checks if head of linked list is empty
        struct node* moreNode= malloc(sizeof(struct node));// allocates space for a nodde
        moreNode -> data = otherData;   // assigns node a value
        moreNode->next = NULL;  
        head = moreNode; //makes the allocated node space equal to the head
        return head;
     }
     else if( head!= NULL){ //if linked it list not empty
   // struct node* additionalNode =malloc(sizeof(struct node));
     node* pointer =head;
    while(pointer!=NULL){//checks to see if linked list is NOT empty whether it is less then or greater or equal then the value already inside
        if((pointer->data = otherData)){
            return head;
       // }
         if(otherData < pointer->data){//checks less then
             //creates a new node
             node* additionalNode = (node*)malloc(sizeof(node));
          additionalNode-> data =otherData; //gives it val less then head
            additionalNode ->next = pointer; //makes head go to the right
            pointer=additionalNode;
             return head;
         }
           //additionalNode-> prev = NULL; //makes the previous NULL

       // if(additionalNode->prev == NULL){ //checks to see if there is  a node before
       //     additionalNode->prev ==NULL; //this is the  first Node in the list
       // }
      //  else if(additionalNode->prev !=NULL){ //if there is a node before then let additional node be the next one
       //     prev->next = additionalNode;
       // }
       
     }
         if(otherData > head->data){ //if the val is more then add to the end
            struct node*  newNode = malloc(sizeof(struct node));
            newNode->data = otherData;
            newNode->next = NULL;
            head-> next =newNode; 
            if(pointer->next ==NULL){
                pointer->next=newNode;
                return newNode;
            }
            more_more=head;
            head
        }
        
    }
        
     }
     more_more->next = nodes_more(otherData);
     return head; //return the head node at the end
 }
 void delete(int val){
    if(head == NULL){

    }
    else if(head->data == val){
        struct node *headcpy = head;
        head = head->next;
        free(headcpy);
    }
    else{
        struct node *prev;
        struct node *ahead;
        prev = head;
        ahead = head->next;
        while(ahead != NULL){
            if(ahead->data == val){
                prev->next = ahead->next;
                ahead->next = NULL;
                free(ahead);
                break;
            }
            prev = prev->next;
            ahead = ahead->next;
        }
    }
   
} 


struct node* deletion(int deletedData){
    node* afterHead = head->next;
       node* headBefore = head;
        if((head = NULL)){
            return head;
        }
        // struct node*temp = head->next;
        //  if(temp->data != newData){
        //     return 1;
        // }
        else if(head!= NULL){
            node* temp = head; ;
            while(temp !=NULL){
            if(head-> data == deletedData){
             node* second_head =  head->next;
             free(head); // make a new head so we can delete the old one 
                head= second_head;
               free(second_head);
                break;
            }
            else if(afterHead->data == deletedData){
                if (afterHead->next != NULL)
                    headBefore->next = afterHead->next;
                else headBefore->next = NULL;

            //  afterHead->next == NULL;
               free(afterHead);
            }
            
            temp = temp->next;
            }
        free(temp);    
        }
        
        //free(afterHead);
        return head;
    }
       
//     void traverseList(){
//          struct node* var;

//     // Return if list is empty 
//     // if(head == NULL)
//     // {
//     //     printf("List is empty.");
//     //     return;
//     // }
    
//             var = head;
//             int otherCounter;
//          while(var != NULL) {
//         if(head == NULL) {
//         printf("List is empty.");
//         return;
//         break;
//          }
//         printf("Data = %d\n", var->data); // Print data of current node
//         var = var->next; 
//           otherCounter++;                // Move to next node
//     }
   
// }
    void someNodes(){
    int count = 0;
    struct node* pointer = head;
    while(pointer!= NULL){
        count++;
        pointer = pointer->next;
    }
    printf("%i", count);
    printf(" ");
    printf(":");
}
void printList(){
    struct node* pointer = head;
    int some;
    while(pointer != NULL){
        some = pointer->data;
        printf(" ");
        printf("%i", some);
        pointer= pointer->next;
    }
    printf("\n");
}
void freeNodes(){
    // if(head == NULL){
    //     free(head);
    // }
    while(head!=NULL){
        //printf("%d\n", head->data);
        struct node* headcpy;
        headcpy = head;
        head = head->next;
        free(headcpy);
    }
    //free(head);
}

//now we create a linked list with n nodes

int main(int argc, char** argv){
    int someData;
    char n;
    while(scanf("%c %d", &n,&someData)!= -1){
        if(n=='i'){
            insert(someData);
            someNodes();
            printList();
        }
        else if(n=='d'){
            deletion(someData);
            someNodes();
            printList();
        }
    }
    freeNodes();
    return EXIT_SUCCESS;
}
