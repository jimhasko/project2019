#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "relations.h"
#include <inttypes.h>

List_of_Tables get_data_from_file( List_of_Tables master_table, int argc, char* argv[]);

int main(int argc, char** argv) {

    clock_t start = clock(); //Start timer
int j;

    char* name="r0";
    char* name2="r1";
    char* name3="r2";
    char* name4="r3";
    char* name5="r4";
    char*str="3 0 1|0.2=1.0&0.1=2.0&0.2>3499|1.2 0.1";
    List_of_Tables master_table;

    //master_table = get_data_from_file( master_table, argc, argv);
    master_table.num_of_tables=5;
    master_table.tables=(Single_Table*)malloc(sizeof(Single_Table)*master_table.num_of_tables);
    master_table.tables[0]=fill(name,0);
    master_table.tables[1]=fill(name2,1);
    master_table.tables[2]=fill(name3,2);
    master_table.tables[3]=fill(name4,3);
    master_table.tables[4]=fill(name5,4);

    just_transfer * test;
    middle* bad_word;
    test = analise(str,&master_table);

    bad_word=run_filters(&master_table,test);

    athrisma(bad_word,test,&master_table);
    clock_t stop = clock(); //End timer
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;


    printf("Time elapsed: %.5f\n", elapsed);

   // list_destruction(&join_resutl);

    return 0;
}

List_of_Tables get_data_from_file( List_of_Tables master_table, int argc, char* argv[]) {

    if (argc != 3 ) {
        printf("Error with arguments! input-> Init_file Work_file!");
    }
    else {

        FILE * fptri = NULL;
        int lines = 0;
        char * line =  (char*) malloc( sizeof(char) * max_line_length);

        fptri = fopen(argv[1], "r");
        if(fptri == NULL) {
            printf("No such init_file in the working directory!");
        }

        while(!feof(fptri)) {
            if(fgetc(fptri) == '\n') {
                lines++;
            }
        }

        fseek(fptri, 0, SEEK_SET);

        if (lines <= 0 ) {

            printf("Init_file was empty, check file again!");
        }

       // master_table = (List_of_Tables*) malloc (sizeof(List_of_Tables));
        master_table.num_of_tables = lines;
        lines = 0;
        master_table.tables=(Single_Table*)malloc(sizeof(Single_Table)*master_table.num_of_tables);
        while (EOF != fscanf(fptri, "%[^\n]\n", line)) {

            master_table.tables[lines]=fill(line, lines);
            //printf("%s %d\n",line, lines);
            lines++;
        }
        free(line);
    }


    return master_table;
}
