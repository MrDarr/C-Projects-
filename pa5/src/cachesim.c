#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct cache{
    unsigned long int tag; 
    int valid; 
    int val; 
}cache;



int counter = 0;
int mem_reads_increment = 0;
int mem_writes_increment = 0; 
int cache_hit = 0;
int cache_miss = 0;

int pcounter = 0;
int pmem_reads_increment = 0;
int pmem_writes_increment = 0;
int pcache_hit = 0;
int pcache_miss = 0;
int left_most = 0;


int help_check_1(int some_val){
    
  if (some_val == 0|| some_val%2 != 0){
      return 0;
  }
    
    for(int i = 0; i < 1; i++){
        some_val = some_val/2;
    }
    return 1;
}



int helper_for_log_eval(int some_val){
    int final = 0;
    
    if (some_val== 0||some_val %2 !=0){
        return 0;
    }
    if( some_val == 2){
        return 1;
    }
   
    while (some_val != 1){
        
        some_val = some_val/2;
        final++;
    }
  return final;
}



      


void prefetchLoad(int cache_lines, unsigned long int setIndex, unsigned long int tag_index, struct cache** new_cache){
    for(int i = 0; i < cache_lines; i++){
        if(new_cache[setIndex][i].tag == tag_index){
                break;
            }
        else{
            if(new_cache[setIndex][i].valid != 0){
             new_cache[setIndex][i].tag = tag_index;
            new_cache[setIndex][i].valid = 0;
            pcounter++;
            new_cache[setIndex][i].val = pcounter;
            pmem_reads_increment++;
            break;
        }
            if(i +1 != cache_lines){
                continue;
            }
            if(i + 1 == cache_lines){
           
                for(int j = 0; j < cache_lines; j++){
                    if(new_cache[setIndex][j].val > new_cache[setIndex][left_most].val){
                        continue;
                    }
                   if(new_cache[setIndex][j].val <= new_cache[setIndex][left_most].val){
                        left_most = j;
                  
                    }   
                }    
                new_cache[setIndex][left_most].valid = 0;
                new_cache[setIndex][left_most].tag = tag_index;
                pcounter++;
                pmem_reads_increment++;    
                 new_cache[setIndex][left_most].val = pcounter;
                continue;

            }
        }  
    }
    return;
}

int checker(int first_check, int second_check){
     if(first_check == 0 && second_check == 0){
            if(second_check == 0){
             printf("Error! Both of the Cache Size and Block Sizes aren't powers of 2!\n");
            return EXIT_FAILURE;
            }

        }
        else if(first_check == 0){
            printf("Error! Only the Cache Size is not a power of 2!\n");
            return EXIT_FAILURE;
        }
        else if(second_check == 0){
            printf("Error! Only the Block Size is not a power of 2!\n");
            return EXIT_FAILURE;
        }
        return -1;
}

// void incrementer(int cache, int memReads){
//     cache++;
//     memReads++;
// }



int main(int argc, char** argv){


   
    if(argc != 6){
            printf("Error! Not Enough Arguments Or Too Many Arguments are included in this program!\n");
            return EXIT_FAILURE;
    }
   
  
    int some_val;
    int cache_lines;
    int cache_sets;

    char* assoc = argv[2];
    int size_of_cache = atoi(argv[1]);
    int block_offset = atoi(argv[4]);

    int first_check = help_check_1(size_of_cache);
    int second_check = help_check_1(block_offset);
 
    if(first_check == 0 || second_check == 0){
        checker(first_check, second_check);
    } 
    
 
    unsigned long int address;
    char read_or_write;

        FILE* trace_file;
        trace_file = fopen(argv[5], "r");
       
       
        //checks  for associativity

         if(assoc[5] == ':'){
            sscanf(assoc, "assoc:%d", &some_val);
            cache_sets = size_of_cache/(block_offset * some_val);
            cache_lines = some_val;
        }
        else{ 
            cache_lines = size_of_cache/block_offset;
            cache_sets = 1;
        }
        if(assoc[0] == 'd'){
            cache_sets = size_of_cache/block_offset;
            cache_lines = 1;
        }
        
        
        int s = helper_for_log_eval(cache_sets);
      
        int b = helper_for_log_eval(block_offset);
        
      //creates new caches
        struct cache** new_Cache = (cache**)malloc(cache_sets*sizeof(cache*));
        struct cache** prefetch_Cache = (cache**)malloc(cache_sets*sizeof(cache*));
        int i =0;
       
    
        while( i < cache_sets ){
           new_Cache[i] = (cache*)malloc((cache_lines)*sizeof(cache));
            prefetch_Cache[i] = (cache*)malloc((cache_lines)*sizeof(cache)); 
            i++;
        }

     

            
        for(int i = 0; i < cache_sets; i++){
            for(int j = 0; j < cache_lines; j++){
                new_Cache[i][j].valid = -1;
                prefetch_Cache[i][j].valid = -1;
            }
        }

       
        while(fscanf(trace_file, "%*x: %c %lx", &read_or_write, &address) == 2){
         unsigned long int index_num_one = ((1 << s) - 1);
         unsigned long int second_address = address + block_offset;
            unsigned long int tag_index = address >> (b + s);

            unsigned long int set_index = (address >> b) &index_num_one;
           
           
         
            unsigned long int second_tag_index = second_address >> (b+s);
             unsigned long int second_set_index = (second_address >> b) & index_num_one;
            //checking for regular cache read or prefetch cache read
            if(read_or_write == 'R'){
                //reading the non prefetch cache
                for(int i = 0; i < cache_lines; i++){ 
                    if(new_Cache[set_index][i].valid == 0){ 
                        if(new_Cache[set_index][i].tag == tag_index){ 
                         
                            cache_hit++;
                            break;
                        }  
                        if(i == (cache_lines - 1)){ 
                          

                             mem_reads_increment++;
                             cache_miss++;

                            int left_most = 0;
                            for(int j = 0; j < cache_lines; j++){
                                if(new_Cache[set_index][j].val <= new_Cache[set_index][left_most].val){
                                    left_most = j;
                                }   
                            }                
                            counter++;
                            new_Cache[set_index][left_most].val = counter;
                            new_Cache[set_index][left_most].valid = 0;
                            new_Cache[set_index][left_most].tag = tag_index; 

                            break;
                        }           
                    }
                    else{
                        if(new_Cache[set_index][i].valid != 0){ 
                        counter++;
                        new_Cache[set_index][i].val = counter;

                        mem_reads_increment++;
                        cache_miss++;

                      
                        new_Cache[set_index][i].tag = tag_index;
                        new_Cache[set_index][i].valid = 0;

                        break;
                        }   
                    }       
                }
                //reading the prefetch cache
                for(int i = 0; i < cache_lines; i++){
                     if(prefetch_Cache[set_index][i].valid != 0){
                        pcounter++;
                        prefetch_Cache[set_index][i].val = pcounter;

                        pmem_reads_increment++;
                        pcache_miss++;

                        prefetch_Cache[set_index][i].tag = tag_index;
                        prefetch_Cache[set_index][i].valid = 0;
                        prefetchLoad(cache_lines, second_set_index, second_tag_index, prefetch_Cache);
                        break;
                        }

                    else {
                        if(prefetch_Cache[set_index][i].valid == 0){
                        if(prefetch_Cache[set_index][i].tag == tag_index){
                            pcache_hit++;
                            break;
                        }  
                        if(i == (cache_lines - 1)){
                            pmem_reads_increment++;
                            pcache_miss++;

                            int left_most = 0;
                            for(int j = 0; j < cache_lines; j++){
                                if(prefetch_Cache[set_index][j].val <= prefetch_Cache[set_index][left_most].val){
                                    left_most = j;
                                }   
                            }                
                            pcounter++;
                            prefetch_Cache[set_index][left_most].val = pcounter;
                            prefetch_Cache[set_index][left_most].valid = 0;
                            prefetch_Cache[set_index][left_most].tag = tag_index;
                            prefetchLoad(cache_lines, second_set_index, second_tag_index, prefetch_Cache);
                            break;
                        }           
                    
                    }
                 
                    }       
                }
            }
            // checking for cache write or prefetch cache write
            else if(read_or_write == 'W'){
                //cache write function
                for(int i = 0; i < cache_lines; i++){
                      if(new_Cache[set_index][i].valid != 0){
                        counter++;
                        new_Cache[set_index][i].val = counter;

                        new_Cache[set_index][i].valid = 0;
                        new_Cache[set_index][i].tag = tag_index;

                        mem_reads_increment++;
                        mem_writes_increment++;
                         cache_miss++;
                        break;
                        } 
                    else{
                        if(new_Cache[set_index][i].valid == 0){
                        if(new_Cache[set_index][i].tag == tag_index){
                          
                            cache_hit++;
                              mem_writes_increment++;
                            break;
                        }      
                        if(i == (cache_lines - 1)){
                           
                            cache_miss++;
                             mem_reads_increment++;
                            mem_writes_increment++;
                            int left_most = 0;
                            for(int j = 0; j < cache_lines; j++){
                                if(new_Cache[set_index][j].val <= new_Cache[set_index][left_most].val){
                                    left_most = j;
                                }   
                            }
                            new_Cache[set_index][left_most].valid = 0;
                            new_Cache[set_index][left_most].tag = tag_index;
                            counter++;
                            new_Cache[set_index][left_most].val = counter;

                            break;
                        }   
                    }
                     
                    }     
                }



                //writing function for prefetch
                for(int i = 0; i < cache_lines; i++){
                    if(prefetch_Cache[set_index][i].valid == 0){
                        if(prefetch_Cache[set_index][i].tag == tag_index){
                            pmem_writes_increment++;
                            pcache_hit++;

                            break;
                        }      
                        if(i == (cache_lines - 1)){
                            pmem_reads_increment++;
                            pmem_writes_increment++;
                            pcache_miss++;

                            int left_most = 0;
                            for(int j = 0; j < cache_lines; j++){
                                if(prefetch_Cache[set_index][j].val <= prefetch_Cache[set_index][left_most].val){
                                    left_most = j;
                                }   
                            }
                            pcounter++;
                            prefetch_Cache[set_index][left_most].val = pcounter;
                            prefetch_Cache[set_index][left_most].valid = 0;
                            prefetch_Cache[set_index][left_most].tag = tag_index;

                            prefetchLoad(cache_lines, second_set_index, second_tag_index, prefetch_Cache);

                            break;
                        }   
                    
                    }
                    else{ 
                        if(prefetch_Cache[set_index][i].valid != 0){
                        pcounter++;
                        prefetch_Cache[set_index][i].val = pcounter;

                        pmem_reads_increment++;
                        pmem_writes_increment++;
                        pcache_miss++;

                        prefetch_Cache[set_index][i].valid = 0;
                        prefetch_Cache[set_index][i].tag = tag_index;

                        prefetchLoad(cache_lines, second_set_index, second_tag_index, prefetch_Cache);

                        break;
                        }   
                    }     
                }
            }
        }
        fclose(trace_file);
        


     // **** FREE METHODS ****

    for(int i = 0; i < cache_sets; i++){
        free(new_Cache[i]);
    }
    free(new_Cache);


    for(int i = 0; i < cache_sets; i++){
        free(prefetch_Cache[i]);
    }
    free(prefetch_Cache);


    //prints  cache 
        printf("Prefetch 0\n");
        printf("Memory reads: %d\n", mem_reads_increment);
        printf("Memory writes: %d\n", mem_writes_increment);
        printf("Cache hits: %d\n", cache_hit);
        printf("Cache misses: %d\n", cache_miss);

        //prints Prefetch Cache 
        printf("Prefetch 1\n");
        printf("Memory reads: %d\n", pmem_reads_increment);
        printf("Memory writes: %d\n", pmem_writes_increment);
        printf("Cache hits: %d\n", pcache_hit);
        printf("Cache misses: %d\n", pcache_miss);

        // if you reach here the program is a success
        
    return EXIT_SUCCESS;
}