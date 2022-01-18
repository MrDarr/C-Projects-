#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

 double** transpose(double** a_matrix, int rows,int cols){// transpose function
    double **temp_matrix = (double**)malloc(sizeof(double*)*cols);// create a temp matrix to return at the end 
    for(int i= 0 ; i < cols; i++){
        temp_matrix[i] = (double*)malloc(sizeof(double*)*rows); //allocate space for rows 

    }
     for(int i = 0; i < rows; i++){
         for(int j = 0; j < cols; j++){
            temp_matrix[j][i]=a_matrix[i][j];// transposing is switching rows and cols so switch rols and cols of this first matrix 
         }
     }
     
    //  for(int i = 0; i <cols; i++) {
    //      for (int j = 0; j < rows; j++) {
    //          printf("[%d][%d]:%lf" , i, j, temp_matrix[i][j]);
    //      }
    //  }

    return temp_matrix;  

}
    





double** multiply( double** a_matrix, int arows, int acols,double** b_matrix,int brows,int bcols){
    // int crows = 0;
    // int ccols = 0;
// double ** a_matrix =(double**)malloc(sizeof(double*)*arows);
//double ** b_matrix = (double**)malloc(sizeof(double*)*brows);//allocate space for both rows and cols




double **c_matrix = (double**)malloc(sizeof(double*)*arows);// create a new matrix using arows to return at the end 
double sum = 0;// dummy var


//for(int i = 0; i < arows;i++){
    //a_matrix[i]= (double**)malloc(sizeof(double*)*acols);

//}
//for(int i = 0; i< brows;i++){
   // b_matrix[i]= (double**)malloc(sizeof(double*)*bcols);
//}



for(int i = 0; i< arows;i++){   
    c_matrix[i]= (double*)malloc(sizeof(double)*bcols);
}
if(acols == brows){
for(int i = 0; i< arows;i++){//multiplying both matrices
    for(int j = 0; j < bcols;j++){
        sum = 0; // make sum = 0 


        for(int k = 0; k < acols;k++){
           sum +=a_matrix[i][k]*b_matrix[k][j];  //make sum = to the multiplication of both matrices
        }
        c_matrix[i][j] = sum;  // make c matrix = sum
        }
    }


//    for(int i = 0; i < arows;i++) {
//        for(int j = 0; j < acols;j++){
//            a_matrix[i][j]=b_matrix[i][j];
//        }
//    }
//    for(int i = 0; i < crows; i++){
//        for(int j = 0; j < ccols;j++){
//            c_matrix[i][j]=a_matrix[i][j];
//        }
//    }
}
// for(int i = 0 ; i < arows;i++){
//     for(int j = 0 ; j < bcols;j++){
//         tempc[i][j]=c_matrix[i][j];
//     }
// }


// for(int i = 0; i < arows;i++){
//     free(c_matrix[i]);
// }
// free(c_matrix);


return c_matrix;  //we return the final matrix which is the c matrix

}








double** invert( double** original_matrix, int rows){
    // allocate space for n x n identity matrix 
    double** n_matrix = malloc(sizeof(double)*rows);

    for(int i = 0; i < rows; i++){
        n_matrix[i] =  malloc(rows*sizeof(double*));
    }


// identity matrix 

    for(int i = 0; i < rows;i++){
        for(int j = 0; j < rows;j++){
            if(i==j){
                n_matrix[i][j]=1;

            }else{
                n_matrix[i][j]=0;
            }
        }
    }

  
     
    
double f;  // variable f needed for inverse 
// begining of pseudocode 
    for( int p = 0; p < rows;p++){
        f = original_matrix[p][p]; 

        for(int j = 0; j < rows;j++){
            original_matrix[p][j]=original_matrix[p][j]/f;
            n_matrix[p][j]=n_matrix[p][j]/f;
        }   
        for(int i = p+1;i < rows;i++){
            f=original_matrix[i][p];
        
            for(int j = 0; j < rows; j++){
                original_matrix[i][j] = original_matrix[i][j]-(original_matrix[p][j]*f); // subtract methods 
                n_matrix[i][j]= n_matrix[i][j]-(n_matrix[p][j] * f);  
            }
        }
    }
    for(int p = rows-1; p>=0; p--){
        for(int i = p-1;i >= 0;i--){
            f = original_matrix[i][p];
            for(int k = 0; k < rows;k++){
                original_matrix[i][k]= original_matrix[i][k] - (f*original_matrix[p][k]);
                n_matrix[i][k]=n_matrix[i][k]-(f*n_matrix[p][k]);
            }
        }
    }


    // free the original matrix that we have used 
    for(int i = 0; i < rows;i++){
        free(original_matrix[i]);
    }
    free (original_matrix);
    return n_matrix;
    
}







int main(int argc, char**argv){
    FILE* train;// BOTH files that we read in
     FILE* data;


    int file_rows;  // row of trains
    int file_cols;  //cols of trains
     char some[8];  //character of strings for train

    int data_row; //row of data
    int data_col; //cols of data 
    char pump[9]; //character of strings for data 
    
   

    train = fopen(argv[1],"r"); //opening file

    if( train==NULL){
        printf("error");
        return 1;
    }
    

    // scaning vals

    fscanf(train, "%s", some);

    fscanf(train, "%d", &file_cols);

    file_cols++;// expand the col since extra col space is needed

    fscanf(train, "%d", &file_rows);


    // creating matrix x and y to work with 
    double **matrix_x = (double**)malloc(sizeof(double*)*file_rows);
    double **matrix_y = (double**)malloc(sizeof(double*)*file_rows);

    for(int i = 0; i < file_rows;i++){
        matrix_x[i] = (double*)malloc(sizeof(double)*file_cols);
        matrix_y[i] = (double*)malloc(sizeof(double));
    }

    // scanning in values and changing to 1 
    for(int i = 0; i < file_rows;i++){
        for(int j = 0; j < file_cols+1;j++){
            if(j ==0){
                matrix_x[i][j]= 1.0;
            }
            else if( j == file_cols){
                fscanf(train,"%lf", &matrix_y[i][0]);
            }else{
                fscanf(train, "%lf", &matrix_x[i][j]);
            }
        }
    }

// ALLOCATE SPACE AND DO OPERATIONS

// we cannot use malloc to allocate space for these since that gives a memory leak erorr instead we can copy the methods into a double ** function instead 

    double **transposer = transpose(matrix_x,file_rows,file_cols);


    double **multiplier = multiply(transposer, file_cols,file_rows,matrix_x,file_rows,file_cols);

    double **inverse = invert(multiplier,file_cols);

    double **second_multiplier = multiply(inverse,file_cols,file_cols,transposer,file_cols,file_rows);



    double **W =multiply(second_multiplier,file_cols,file_rows,matrix_y,file_rows,1);


    //FREE ALL HERE 
    for(int i = 0; i < file_rows;i++){
        free(matrix_x[i]);
    }
    free(matrix_x);




    for(int i = 0; i < file_cols;i++){
        free(transposer[i]);
    }
    free(transposer);





    for(int i = 0; i < file_cols;i++){
        free(inverse[i]);
    }
    free(inverse);



    for(int i = 0; i < file_rows; i++){
        free(matrix_y[i]);
    }
    free(matrix_y);



    for(int i = 0; i < file_cols;i++){
        free(second_multiplier[i]);
    }
    free(second_multiplier);




// CLOSE HERE 
    fclose(train);

   //START HERE
    // FILE* data;
    
    data = fopen(argv[2], "r");


    // error case 
    if(data==NULL){
        printf("error");
        return 1;
    }
    // scan in vals
    fscanf(data, " %s",pump);
    fscanf(data, "%d", &data_col);
    data_col++; //expand the col
    fscanf(data, " %d", &data_row);

    double **matrices = (double**)malloc(sizeof(double*)*data_row);

    for(int i = 0; i < data_row;i++){
        matrices[i]= (double*)malloc(sizeof(double)*data_col);
    }

    for(int i = 0; i < data_row;i++){
        for(int j = 0; j<data_col;j++){
            if(j ==0){
                matrices[i][j]=1.0;
            }else{
                fscanf(data, "%lf", &matrices[i][j]);
            }
        }
    }


       
double **final=multiply(matrices,data_row,data_col,W,file_cols,1);  // operation needed 
if(final==NULL) return 1;
for(int i = 0; i < data_row;i++){
    for(int j = 0; j < 1; j++){
        printf("%.0f",final[i][j]);// print method
    }
    printf("\n");
}



 // FREE ALL and end
for(int i = 0; i < data_row;i++){
    free(matrices[i]);
}
free(matrices);


for(int i = 0; i < data_row;i++){
    free(final[i]);
}
free(final);

for(int i = 0; i < file_cols;i++){
    free(W[i]);
}
free(W);



fclose(data);

return 0;  // return 0 since everything was sucessful 



}
