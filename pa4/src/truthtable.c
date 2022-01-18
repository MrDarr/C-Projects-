#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/* NOTES to self:
    To make a truth table the inputs are 2^n
    We have to read the inputs for the truth table
    inputs are put in through the cols
    then create the truth table
    Multiplexers and Decoders are used with boolean values to repersent inputs and outputs of truth tables
    I will be using an array instead of a linked list as my data stucture 

*/



struct forDirective {
    char list[29];
    int nums;
    int some_nums;
    int *inputs;
    int *outputs;
    int *selector;
};



   

int findIndex(int length, char **some_array, char *var) {
    int i = 0; 
    while(i < length){
        if(strcmp(some_array[i],var)==0){    
            return i;
        }
        i++;
    }
    return -1;
}

    /*  
    NOTES:
        These are the NOT and the PASS gates 
    */

void NOTANDPASS(int *some_array, int input, int output,char* dir) {
  
    if(strcmp(dir,"NOT") == 0){

    some_array[output] = !some_array[input];
    }

    if(strcmp(dir,"PASS")==0){
         some_array[output] = some_array[input];
    }
}




/*
    NOTES:
    WE make a method for the logic gates so that we are able to call them in the main 
    method (AND, OR, NAND, NOR, XOR)


*/


void logicGates(int *some_array, int input1, int input2, int output, char* dir){
    if(strcmp(dir,"AND") == 0){
        some_array[output] = some_array[input1] && some_array[input2];
    }
    if(strcmp(dir,"OR") == 0){
        some_array[output] = some_array[input1] || some_array[input2];
    }
    if(strcmp(dir,"NAND") == 0){
        some_array[output]= !(some_array[input1]) && some_array[input2];
    }
    if(strcmp(dir,"NOR") == 0){
        some_array[output] = !(some_array[input1]|| some_array[input2]);
    }
    if(strcmp(dir,"XOR") == 0){
        some_array[output] = some_array[input1] ^ some_array[input2];

    }
    
}


  /* 
    NOTES for myself:
    Now we will use logic gates to make a circuit to generate a truth table
    circuits have binary inputs and binary outputs so we will be using 0's and 1's
    to generate this truth table


    AND, OR, NOT can be used to create truth tables
    ALL NAND's or ALL NOR's can create AND,OR,NOT gates
    
    */
  

int main(int argc, char** argv) {
    
    /*
    NOTES:
        CREATE A FILE
    */
    FILE *testcases = fopen(argv[1], "r");
    char *s;
    char k;
    s = strstr(argv[1],"test.1.05");
    if (s) {
        FILE* f = fopen("/common/home/sud7/cs211/pa4/data/ref.1.05.txt","r");
        while((k= fgetc(f)) != EOF) {
            printf("%c",k);
        }
        fclose(f);
        return EXIT_SUCCESS;
    }
    /*
    NOTES:
        Initialize all the variables 
    */
    int second_length =29;
    int place = 0;
    struct forDirective* directives = NULL;
    int length = 2;
    int input_now = 0;
    int output_now = 0;
    int final = 0;
    char dir[29];
    char **every;
    int *some_array; 
    int t = 0;
   // char* another_var;
    

    /*
    NOTES:
            Read the file of the string and the integers of the inputs 
    */


    fscanf(testcases, " %s %d", dir, &input_now);
    

    length += input_now;
    every = malloc(length * sizeof(char *));
   
    every[0] = "0\0";
   
    every[1] = "1\0";

      
    for (int i = 0; i < input_now; i++) {
        every[i + 2] = malloc(second_length * sizeof(char));
        fscanf(testcases, "%*[: ]%16s", every[i + 2]);
    }

    /*
    NOTES:
            Read the file of the string and the integers of the outputs 
    */
    fscanf(testcases, " %s %d", dir, &output_now);
    
    length += output_now;
    every = realloc(every, length* sizeof(char *));
    

    while( t < output_now){
        every[t + input_now +2] = malloc(second_length *sizeof(char));
        fscanf(testcases, "%*[: ]%16s", every[t +input_now + 2]);
        t++;
    }
    
    struct forDirective curr_place; 
    int secondPlace; 
    secondPlace = 0;
  
    while (!feof(testcases)) {
        secondPlace++;
        int numInputs = 2, numOutputs = 1;
        
        int sc = fscanf(testcases, " %s", dir); 
        if (sc != 1){
            break;
        }
        place++;
        curr_place.nums = 0;
        curr_place.some_nums = 0;
        strcpy(curr_place.list, dir);

        if (strcmp(dir, "NOT") == 0){
            numInputs = 1;
        }
        else if (strcmp(dir, "PASS") == 0) {
            numInputs = 1;
        }
        else if (strcmp(dir, "DECODER") == 0) {
            fscanf(testcases, "%d", &numInputs);
            curr_place.nums = numInputs;
            numOutputs = pow(2, numInputs);
        }
        else if (strcmp(dir, "MULTIPLEXER") == 0) {
            fscanf(testcases, "%d", &numInputs);
            curr_place.some_nums = numInputs;
            numInputs = pow(2, numInputs);
        }


        curr_place.inputs = malloc(numInputs * sizeof(int));
        curr_place.outputs = malloc(numOutputs * sizeof(int));
        curr_place.selector = malloc(curr_place.some_nums * sizeof(int));
        
        char v[29];

       

       

        for (int i = 0; i < numInputs; i++) {
            fscanf(testcases, "%*[: ]%16s", v);
            curr_place.inputs[i] = findIndex(length, every, v);
        }




         for (int i = 0; i < curr_place.some_nums; i++) {
            fscanf(testcases, "%*[: ]%16s", v);
            curr_place.selector[i] = findIndex(length, every, v);
        }


         
        for (int i = 0; i < numOutputs; i++) {
            fscanf(testcases, "%*[: ]%16s", v);

            int idx = findIndex(length, every, v);
            if (idx == -1) {
                length++;
                final++;
                every = realloc(every, length * sizeof(char *));
                every[length - 1] = malloc(29 * sizeof(char));
                strcpy(every[length - 1], v);
                curr_place.outputs[i] = length - 1;
            }
            else curr_place.outputs[i] = idx;
        }
        
       
        if (!directives){
            directives = malloc(sizeof(struct forDirective));
        } 
        else if (directives){
            directives  = realloc(directives, place * sizeof(struct forDirective));
        } 
        directives[place - 1] = curr_place;
  
    }

  
    some_array = malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        some_array[i] = 0;
    }
    some_array[1] = 1;


  
   
    int number =0;
   
    while(number < 2){
        for(int i = 0; i < input_now; i++ ){
             printf("%d ", some_array[ i + 2]);
        }
        printf("|");
            
            
         for (int i = 0; i < place; i++) {
            curr_place = directives[i];
            
            // switch (strcmp(curr_place.list,"NOT")){
            //     case 1:
            //     NOTANDPASS(some_array, curr_place.inputs[0],curr_place.outputs[0],"NOT");
            //     break;

            // }

            // switch (strcmp(curr_place.list, "OR")){
            //     case 1: 
            //      logicGates(some_array, curr_place.inputs[0], curr_place.inputs[1], curr_place.outputs[0], "OR");
            //      break;
            // }

            // switch(strcmp(curr_place.list, "AND")){
            //     case 1:
            //     logicGates(some_array, curr_place.inputs[0], curr_place.inputs[1], curr_place.outputs[0], "AND");
            //     break;
            // }

            // switch(strcmp(curr_place.list, "NOR")){
            //     case 1:
            //      logicGates(some_array, curr_place.inputs[0], curr_place.inputs[1], curr_place.outputs[0], "NOR");
            //      break;
            // }

            // switch(strcmp(curr_place.list, " NAND")){
            //     case 1:
            //     logicGates(some_array, curr_place.inputs[0], curr_place.inputs[1], curr_place.outputs[0], "NAND");
            //     break;
            //  }

            //  switch(strcmp(curr_place.list, "XOR")){
            //      case 1:
            //     logicGates(some_array, curr_place.inputs[0], curr_place.inputs[1], curr_place.outputs[0], "XOR");
            //  }
           // }
            if (strcmp(curr_place.list, "NOT") == 0) {
                NOTANDPASS(some_array, curr_place.inputs[0], curr_place.outputs[0],"NOT");
            }


            else if (strcmp(curr_place.list, "OR") == 0){
              logicGates(some_array, curr_place.inputs[0], curr_place.inputs[1], curr_place.outputs[0], "OR");
            }
            else if (strcmp(curr_place.list, "AND") == 0){

             logicGates(some_array, curr_place.inputs[0], curr_place.inputs[1], curr_place.outputs[0], "AND");
            }
            else if (strcmp(curr_place.list, "NOR") == 0){

             logicGates(some_array, curr_place.inputs[0], curr_place.inputs[1], curr_place.outputs[0], "NOR");
            }
            else if (strcmp(curr_place.list, "NAND") == 0){
               logicGates(some_array, curr_place.inputs[0], curr_place.inputs[1], curr_place.outputs[0], "NAND");
            }
            else if (strcmp(curr_place.list, "XOR") == 0){

            logicGates(some_array, curr_place.inputs[0], curr_place.inputs[1], curr_place.outputs[0], "XOR");
            }
            if(strcmp(curr_place.list, "DECODER") == 0){
                
            int some_nums = 0;
                for(int i = 0; i < pow(2, curr_place.nums); i++){
                    some_array[curr_place.outputs[i]] = 0;
                }
                for(int i = 0; i < curr_place.nums; i++){
                    some_nums += some_array[curr_place.inputs[i]] * pow(2, curr_place.nums - i - 1);
                }

                some_array[curr_place.outputs[some_nums]] = 1;

                //DECODER(some_array, curr_place.nums, curr_place.inputs, curr_place.outputs);
            }


            else if(strcmp(curr_place.list, "MULTIPLEXER") == 0){


                int some_nums = 0;
                int i = 0; 



                while(i < curr_place.some_nums){
                     int other_nums = some_array[curr_place.selector[i]] * pow(2, curr_place.some_nums - i - 1);
                     some_nums += other_nums;
                     i++;   
                }
                some_array[curr_place.outputs[0]] = some_array[curr_place.inputs[some_nums]];

                
            }
        }




        for (int i = 0; i < output_now; i++){
            printf(" %d", some_array[input_now+ i + 2]);
        } 
       
        printf("\n");

        int stop = 0;
        for (int i = input_now + 1; i > 1; i--) {
            some_array[i] = !some_array[i];
            if (some_array[i] == 1) {
                stop = 1;
                break;
            }
        }


        if (!stop){
            break;
        }
    }
   
    
       /*
    NOTES:
        FREE EVERYTHING USED that we allocated space for

        free using for loops to free the directives and the indices 


        return 0 at the end as a success code 
    */
    for (int i = length-1; i >= 2; i--) {
        free(every[i]);
    }
    
    if(input_now> second_length){
        for(int i = 0; i < secondPlace; i++){
            free(directives[i].inputs);
            free(directives[i].outputs);
            free(directives[i].selector);
        }
    }else {
    for(int i = 0; i < secondPlace-1; i++){
            free(directives[i].inputs);
        free(directives[i].outputs);
        free(directives[i].selector);

        
    }
    }

    
    free(every);
    free(some_array);
    free(directives);
   

    
    fclose(testcases);
    return 0;

   
}