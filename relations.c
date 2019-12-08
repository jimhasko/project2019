
#include "relations.h"
#define bool_num 50000000
/*void init_tables(List_of_Tables lista_pinakon){
    lista_pinakon.num_of_tables=0;
    lista_pinakon.tables=(Single_Table*)malloc(10*sizeof(Single_Table));



}
*/



 Single_Table*  simple_mesure(Single_Table* table,uint64_t num,int type,int column){
    int i,j,new_rows=0;

   int* new_ids;
   new_ids=malloc(sizeof(int)*table->stats->row);


    switch(type){

        case 3:
            for(i=0;i<table->stats->row;i++){
               j= table->id_table[i];
                if(table->Full_Table[column].Column[j]>num){
                    new_rows++;
                    new_ids[i]=i;
                }

            }
            free(table->id_table);
            table->id_table=new_ids;
            return table;
        case 4:
            for(i=0;i<table->stats->row;i++){
                j= table->id_table[i];
                if(table->Full_Table[column].Column[j]<num){
                    new_rows++;
                    new_ids[i]=i;
                }

            }
            free(table->id_table);
            table->id_table=new_ids;
            return table;
        case 2:
            for(i=0;i<table->stats->row;i++){
                j= table->id_table[i];
                if(table->Full_Table[column].Column[j]==num){
                    new_rows++;
                    new_ids[i]=i;
                }

            }
            free(table->id_table);
            table->id_table=new_ids;
            return table;

        default:
            printf("wront character");
            return NULL;
    }




}



int power(int basi,int pano){

    int i,temp;
    temp=1;
    for (i=0;i<pano;i++){
        temp=temp*basi;

    }
    return temp;


}
/*
void quicksort(priority* number,int first,int last){
    uint64_t i, j, pivot;
    priority temp;

    if(first<last){
        pivot=first;
        i=first;
        j=last;

        while(i<j){
            while(number[i].type<=number[pivot].type&&i<last)
                i++;
            while(number[j].type>number[pivot].type)
                j--;
            if(i<j){
                temp=number[i];
                number[i]=number[j];
                number[j]=temp;
            }
        }

        temp=number[pivot];
        number[pivot]=number[j];
        number[j]=temp;
        quicksort(number,first,j-1);
        quicksort(number,j+1,last);

    }
}


*/
Single_Table fill(char* filename,int name){     //diabazi binary k gemizi ti mnimi
    Single_Table Table_Node;
    FILE *fp = fopen(filename,"r");
if(!fp){
    printf("wrong imput fille %s \n",filename);

}
    int* distinct;

    //int y;
    fread(&Table_Node.tube_num,sizeof(uint64_t),1,fp);
    fread(&Table_Node.column_num,sizeof(uint64_t),1,fp);

    Table_Node.Full_Table=(Row_table*)malloc(sizeof(Row_table)*Table_Node.column_num);
    Table_Node.stats=(statistics*)malloc(sizeof(statistics)*Table_Node.column_num);
    Table_Node.id_table=malloc(sizeof(int)*Table_Node.tube_num);
Table_Node.table_name=name;
    int j,bool_test,i,k=0;
    j=0;
    //uint64_t i,max;
    //int kl=0;



    for(i=0;i<Table_Node.column_num;i++){


        Table_Node.Full_Table[i].Column=(uint64_t*)malloc(sizeof(uint64_t)*Table_Node.tube_num);
        //   int *temp;
        // temp=(int*)malloc(sizeof(int)*Table_Node.tube_num);
        // Table_Node.Full_Table[i]=temp;
        //   Table_Node.Full_Table[i] = (int *) malloc(sizeof(int) * Table_Node.tube_num);



    }

    //uint64_t *temp;
   // temp=(uint64_t*)malloc(sizeof(uint64_t)*Table_Node.tube_num);

    for(i=0;i<Table_Node.tube_num*Table_Node.column_num;i++){

        if(i / Table_Node.tube_num>j) {
         /*   // Table_Node.Full_Table[j]=temp;
            //  temp=(uint64_t*)malloc(sizeof(uint64_t)*Table_Node.tube_num);
            //  k=0;
            //  j++;
            //  hj=temp[k];
           // printf("\n x  %ld  x",i);
            Table_Node.stats[j].full=Table_Node.tube_num;

            if(Table_Node.stats[j].upper-Table_Node.stats[j].lower>bool_num){
                max=bool_num;
            }else{
                max=Table_Node.stats[j].upper-Table_Node.stats[j].lower+1;
            }
            distinct=(int*)calloc(max,sizeof(int));
            Table_Node.stats->distinct=0;
            for(bool_test=0;bool_test<Table_Node.tube_num;bool_test++){
                if(distinct[(Table_Node.Full_Table[j].Column[bool_test]-Table_Node.stats->lower)%max]==0){
                    distinct[(Table_Node.Full_Table[j].Column[bool_test]-Table_Node.stats->lower)%max]=1;
                    Table_Node.stats->distinct++;
                }

            }
*/

            k=0;
            j++;

        }
    if(j==0){

        Table_Node.id_table[i]=i;
    }
         //   printf("\n %ld  <",i);

        fread(& Table_Node.Full_Table[j].Column[k],sizeof(uint64_t),1,fp);
        // fread(&temp[k],sizeof(uint64_t),1,fp);

        //  printf("x  %ld  x\n",temp[k]);
        //  fread(&Table_Node.Full_Table[j],sizeof(uint64_t),1,fp);
//printf(" \n %d i",i);
            if(k==0){

                Table_Node.stats[j].lower=Table_Node.Full_Table[j].Column[k];
                Table_Node.stats[j].upper=Table_Node.Full_Table[j].Column[k];

            }else{

                if(Table_Node.Full_Table[j].Column[k]<Table_Node.stats[j].lower)
                    Table_Node.stats[j].lower=Table_Node.Full_Table[j].Column[k];

                if(Table_Node.Full_Table[j].Column[k]>Table_Node.stats[j].upper)
                    Table_Node.stats[j].upper=Table_Node.Full_Table[j].Column[k];


            }


        k++;
    }


    fclose(fp);
    return Table_Node;
}



int read_init(char *filename)
{
    // count the number of lines in the file called filename
    FILE *fp = fopen(filename,"r");
    int ch=0;
    int lines=0;

    if (fp == NULL){
        printf("error with file %s \n",filename);
    };


    lines++;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
            lines++;
    }
    fclose(fp);
    return lines;
}


List_of_Tables init_Tables(char*initfile){
    List_of_Tables master_table;
    master_table.num_of_tables=read_init(initfile);
    master_table.tables=(Single_Table*)malloc(sizeof(Single_Table)*master_table.num_of_tables);
    return master_table;

}


just_transfer* analise(char* str,List_of_Tables* master_table){              //diabazi sxesis ke kanei tis praxis
    char* sxesi;

    sxesi=malloc(sizeof(char)*strlen(str));
    sxesi[0]='\0';
    char * katigorima;
    katigorima=malloc(sizeof(char)*strlen(str));
    katigorima[0]='\0';

    char * proboli;
    proboli=malloc(sizeof(char)*strlen(str));
    proboli[0]='\0';

    int first=0;
    int second=0;
    int third=0;

    int i=0;
    char guard=' ';
    while(str[i]!='\0'){
        if(i>1)
            guard=str[i-1];
        if((str[i]=='|')&&(first==0)&&(guard!=str[i])){


            first=i;}





        if((str[i]=='|')&&(i>first)&&(second==0)&&(guard!=str[i])){
            second=i;

        }



        if((str[i]=='|')&&(i>second)&&(second>0)&&(guard!=str[i])){
            third=i;
            break;
        }
        third=i;
        i++;


    }




    strncat(sxesi,str,first);                   //spai to work se komatia diaxorismena me |
    printf("sxesi %s| len :%ld \n",sxesi,strlen(sxesi));
//char t=sxesi[0];
    strncat(katigorima,str+first+1,second-first-1);
    printf("katigorima %s \n",katigorima);

    strncat(proboli,str+second+1,third-second);
    printf("proboli %s \n",proboli);








   //List_of_Tables* temp_table;

  //  temp_table->num_of_tables=(int)strlen(sxesi)/2+1;
  //  temp_table->tables=(Single_Table*)malloc(sizeof(Single_Table)*temp_table->num_of_tables);
    priority* priority_series;
    priority_series=(priority*)malloc(sizeof(priority)*10);
    int * from;
    int from_number;
    char delim[] = " ";
    i=0;
    int j,ht1,ht2;
    char *ptr = strtok(sxesi, delim);
    from=malloc(sizeof(int)*master_table->num_of_tables);
    while(ptr != NULL)
    {
       j=atoi(ptr);
        from[i]=j;
      // printf("j-> %d ",j);
      // printf("'%s'\n", ptr);

      //  temp_table->tables[i]=master_table.tables[j];
      //  temp_table->tables[i].table_name=j;
        ptr = strtok(NULL, delim);
        i++;

    }
from_number=i;


////////////////////////////////////type:1 = self join; type:2==int; type:3=>int;type:4=<int;type:5=table_join
    char delimkat[] = "&";

    int priority_number=0;


    int swap,max_rows;
    ptr = strtok(katigorima, delimkat);
int table1,table2,column1,column2,here_table1,here_table2,counter=0;
int len,counter_guard=10;
    char *last;
   // Row_table replace;
    while(ptr != NULL)
    {   priority_number++;
        priority_series[counter].command=ptr;
        printf("ptr %s \n",ptr);
    len=strlen(ptr);
    here_table1=ptr[0]-48;
    table1=from[here_table1];
    column1=ptr[2]-48;
    if(len>6){
        here_table2=ptr[4]-48;
        table2=from[here_table2];
        column2=ptr[6]-48;}
    else{
        table2=-1;
        column2=-1;
    }



        if(ptr[3]=='='){

            if(len==5||ptr[5]!='.'){
                priority_series[counter].type=2;  //=number
                last = strrchr(ptr, '=');
                priority_series[counter].number=Sto64(last);

            }else   if(((here_table1)==(here_table2)&&(master_table->tables[table1].table_name==master_table->tables[table2].table_name))){// self join

                priority_series[counter].type=1;

            }else {


                if (master_table->tables[table1].tube_num > master_table->tables[table2].tube_num) {
                    priority_series[counter].size = master_table->tables[table2].tube_num;

                } else {
                    priority_series[counter].size = master_table->tables[table1].tube_num;

                }

              if(here_table2<here_table1){
                swap=here_table2;
                  here_table2=here_table1;
                  here_table1=swap;
                  swap=column2;
                  column2=column1;
                  column1=swap;
              }

                priority_series[counter].type = 5;
            }
        }
        if(ptr[3]=='>'){

            priority_series[counter].size=master_table->tables[table1].tube_num;
            priority_series[counter].type=3;
            last = strrchr(ptr, '>');
            priority_series[counter].number=Sto64(last+1);

        }

        if(ptr[3]=='<'){

            priority_series[counter].type=4;
            priority_series[counter].size=master_table->tables[table1].tube_num;
            last = strrchr(ptr, '<');
            priority_series[counter].number=Sto64(last+1);

        }
        priority_series[counter].col1=column1;
        priority_series[counter].col2=column2;
        priority_series[counter].master_table1=table1;
        priority_series[counter].master_table2=table2;
        priority_series[counter].here_table1=here_table1;
        priority_series[counter].here_table2=here_table1;
        counter++;
        if(counter==counter_guard){//if there are more than 10 where cases realloc


            priority_series=realloc(priority_series,counter+10);
            counter_guard=counter+10;
        }
        ptr = strtok(NULL, delimkat);

}


just_transfer* transfer;
    transfer=(just_transfer*)malloc(sizeof(just_transfer));
    transfer->priority_number=priority_number;
    transfer->priority1=priority_series;
    transfer->tables=from;
    transfer->num_of_tables=from_number;
    transfer->tables_ids=(tableid*)malloc(sizeof(tableid)*from_number);
    for(i=0;i<from_number;i++){
        transfer->tables_ids[i].id_list=malloc(sizeof(int)*master_table->tables[from[i]].tube_num);

    }
   max_rows=max(from,from_number,master_table);
    for(i=0;i<max_rows;i++){
        for(j=0;j<from_number;j++) {
            if (i < master_table->tables[from[j]].tube_num)
                transfer->tables_ids[j].id_list[i]=i;
        }
    }
    for(j=0;j<from_number;j++) {

            transfer->tables_ids[j].size=(int)master_table->tables[from[j]].tube_num;
    }



    return transfer;

}

int max(int* from,int from_num,List_of_Tables* master_table){
    int i,max;
    max=(int)master_table->tables[from[0]].tube_num;
    for(i=0;i<from_num;i++){
        if(max<master_table->tables[from[i]].tube_num){
            max=(int)master_table->tables[from[i]].tube_num;
        }

    }

    return max;
}


middle* run_filters(List_of_Tables* master_table,just_transfer* transfer) {


    int comparison, i, j,temp;

    int counter = 0;



    int size,table1,table2,column1,column2,ht1,ht2,priority_number;

    //size=temp_table.tables[priority_series[0].command[0]-48].tube_num;
    middle* middle_matrix;
    int* replacer_matrix;
    //int* line_matrix;
  //  middle_matrix=(middle*)calloc(temp_table.num_of_tables,sizeof(middle));//kratai to size tis ka8e kolonas
 //   for(i=0;i<temp_table.num_of_tables;i++){
  //      middle_matrix[i].size=temp_table.tables[i].tube_num;

  //  }

    priority_number=transfer->priority_number;


    for (i = 0; i < priority_number; i++) {         //gia ola ta queries
                counter=0;

        uint64_t * col1;
        uint64_t *  col2;
        int * new;
        int id,idcounter=0;
        new=malloc(sizeof(int)*transfer->tables_ids[ht1].size);


    table1=transfer->priority1[i].master_table1;
    column1=transfer->priority1[i].col1;
    ht1=transfer->priority1[i].here_table1;
        col1=master_table->tables[table1].Full_Table[column1].Column;
    if(transfer->priority1[i].type==5||transfer->priority1[i].type==1){// if it needs 2 matrixes

        table2=transfer->priority1[i].master_table2;
        column2=transfer->priority1[i].col2;
        ht2=transfer->priority1[i].here_table2;
        col2=master_table->tables[table2].Full_Table[column2].Column;
    }




        if (transfer->priority1[i].type == 1) {             //self join 111111111111111111111111111111111111111111111111111111111111111






            for(j=0;j<transfer->tables_ids[ht1].size;j++){
                id=transfer->tables_ids[ht1].id_list[j];
                if(col1[id]==col2[id]){
                new[idcounter]=id;
                idcounter++;
                }


            }



        }




        else if (transfer->priority1[i].type == 2) {        //column=number     2222222222222222222222222222222222222222222222222222222222

            for(j=0;j<transfer->tables_ids[ht1].size;j++){
                id=transfer->tables_ids[ht1].id_list[j];
                if(col1[id]==transfer->priority1[i].number){
                    new[idcounter]=id;
                    idcounter++;
                }


            }

        }
        else if (transfer->priority1[i].type == 3) {        //column>number   3333333333333333333333333333333333333333333333333333333333333333333333333

            for(j=0;j<transfer->tables_ids[ht1].size;j++){
                id=transfer->tables_ids[ht1].id_list[j];
                if(col1[id]>transfer->priority1[i].number){
                    new[idcounter]=id;
                    idcounter++;
                }


            }


        }else
        if (transfer->priority1[i].type == 4) {                          //column<number     444444444444444444444444444444444444444444444444444444444444444444444444

            for(j=0;j<transfer->tables_ids[ht1].size;j++){
                id=transfer->tables_ids[ht1].id_list[j];
                if(col1[id]<transfer->priority1[i].number){
                    new[idcounter]=id;
                    idcounter++;
                }


            }

        }

        transfer->tables_ids[ht1].size=idcounter;
        free(transfer->tables_ids[ht1].id_list);
        transfer->tables_ids[ht1].id_list=new;

    }


}





////////////////////////
/*
List_of_Tables run_joins(List_of_Tables* temp_table,middle* mid_table,int priority_number,int max_priority,priority* priority_series){
    uint64_t i,j,k,master_table1,n,column1,master_table2,column2,temp1,temp2;

    tableid*test_matrix;
    test_matrix=(tableid*)malloc(parag(temp_table->num_of_tables)*sizeof(tableid));
    statistics* stats_table;
    int max_columns=0;
    int * arr;
    arr=malloc(temp_table->num_of_tables*sizeof(int));
    for(j=0;j<temp_table->num_of_tables;j++)
        arr[i]=i;










    for(j=0;j<temp_table->num_of_tables;j++) {


        test_matrix[j].f_size=0;
//        test_matrix[j].is_it_on=calloc(temp_table->num_of_tables,sizeof(int));
        test_matrix[j].piority_list=calloc(temp_table->num_of_tables,sizeof(int));

    }






for(j=0;j<max_priority-priority_number;j++){

    master_table1= priority_series[j+priority_number].command[0]-48;
    column1= priority_series[j+priority_number].command[2]-48;
    master_table2= priority_series[j+priority_number].command[4]-48;
    column2= priority_series[j+priority_number].command[6]-48;

    for(i=0;i<max_priority-priority_number;i++){

        



    }




}






}
*/








int parag(int input){
    int i,res=1;
    for(i=1;i<=input;i++)
        res=res*i;
    return res;
}

void permute(int *array,int i,int length,int** test) {
    int temp,k,l;
    k=0;
    if (length == i){
        while(k<parag(length)) {
            if(test[k][0]!=-1){
                k++;
            }else{
                for (l = 0; l < length; l++){
                    //  printf("%d ", array[l]);
                    test[k][l]=array[l];}
                // printf("\n");
                k=24;
            }}
        return ;
    }
    int j = i;
    for (j = i; j < length; j++) {

        temp=array[i];
        array[i]=array[j];
        array[j]=temp;
        permute(array,i+1,length,test);

        temp=array[i];
        array[i]=array[j];
        array[j]=temp;
    }

}


List_of_Tables* cost(int table1,int table2,int column1,int column2 ,List_of_Tables* temp_table){
    uint64_t temp1,temp2,n,i;
    if(temp_table->tables[table1].stats[column1].lower<temp_table->tables[table2].stats[column2].lower){
        temp_table->tables[table1].stats[column1].lower=temp_table->tables[table2].stats[column2].lower;

    }else{

        temp_table->tables[table2].stats[column2].lower=temp_table->tables[table1].stats[column1].lower;
    }

    if(temp_table->tables[table1].stats[column1].upper<temp_table->tables[table2].stats[column2].upper){
        temp_table->tables[table1].stats[column1].upper=temp_table->tables[table2].stats[column2].upper;

    }else{

        temp_table->tables[table2].stats[column2].upper=temp_table->tables[table1].stats[column1].upper;
    }

    if((n=temp_table->tables[table2].stats[column2].upper-temp_table->tables[table1].stats[column1].lower+1)>bool_num){
        n=bool_num;
    }

    temp_table->tables[table1].stats[column1].full=temp_table->tables[table1].stats[column1].full*temp_table->tables[table2].stats[column2].full/n;
    temp_table->tables[table2].stats[column2].full= temp_table->tables[table1].stats[column1].full;

    temp1= temp_table->tables[table1].stats[column1].distinct;
    temp2= temp_table->tables[table2].stats[column2].distinct;
    temp_table->tables[table1].stats[column1].distinct=temp_table->tables[table1].stats[column1].distinct*temp_table->tables[table2].stats[column2].distinct/n;
    temp_table->tables[table2].stats[column2].distinct= temp_table->tables[table1].stats[column1].distinct;
    temp1= temp_table->tables[table1].stats[column1].distinct/temp1;
    temp2= temp_table->tables[table1].stats[column1].distinct/temp2;
    for(i=0;i<temp_table->tables[table1].column_num;i++){                                   //other columns//////////////////////////////////////////////
        if(i!=column1) {
            temp_table->tables[table1].stats[i].full=temp_table->tables[table1].stats[column1].full;
            temp_table->tables[table1].stats[i].distinct=(1-power(1-temp1,temp_table->tables[table1].stats[i].full/temp_table->tables[table1].stats[i].distinct));
        }

    }



    for(i=0;i<temp_table->tables[table2].column_num;i++){                                   //other columns//////////////////////////////////////////////
        if(i!=column2) {
            temp_table->tables[table2].stats[i].full=temp_table->tables[table2].stats[column2].full;
            temp_table->tables[table2].stats[i].distinct=(1-power(1-temp2,temp_table->tables[table2].stats[i].full/temp_table->tables[table2].stats[i].distinct));
        }

    }



return temp_table;



}





void short_jois(priority* priority_series,int max_priority,int priority_number,int** prem,List_of_Tables * temp_table){
    int max_columns=0;
    uint64_t i,j,table1,table2,column1,column2,k,temp_minimum;
    int minimum=-1;
    int*priority_line;
    int* priotity_line_temp;
    priotity_line_temp=(int*)malloc(temp_table->num_of_tables*sizeof(int));
    priority_line=(int*)malloc(temp_table->num_of_tables*sizeof(int));
    neibour_node** neibour;

neibour=(neibour_node**)malloc(sizeof(neibour_node*)*temp_table->num_of_tables);
   for(j=0;j<temp_table->num_of_tables;j++)
    neibour[j]=calloc(temp_table->num_of_tables,sizeof(neibour_node));








    for(j=priority_number;j<max_priority;j++){       //pinakas geitniasis
        table1= priority_series[j].command[0]-48;
        column1= priority_series[j].command[2]-48;
        table2= priority_series[j].command[4]-48;
        column2= priority_series[j].command[6]-48;

        neibour[table1][table2].bol=1;
        neibour[table2][table1].bol=1;
        neibour[table1][table2].priority_line=j;     //pinakas geitniasis
        neibour[table2][table1].priority_line=j;
    }




    for(j=0;j<temp_table->num_of_tables;j++)
        if(max_columns<temp_table->tables[j].column_num)
            max_columns=temp_table->tables[j].column_num;

    statistics ** stats_table;
    stats_table=(statistics**)malloc(temp_table->num_of_tables*sizeof(statistics*));

    for(j=0;j<temp_table->num_of_tables;j++)
        stats_table[j]=(statistics*)malloc(sizeof(statistics)*max_columns);

   // stats_table=(statistics*)malloc(max_columns*temp_table->num_of_tables*sizeof(statistics));      //kratai ta arxika statistika///
    for(j=0;j<temp_table->num_of_tables;j++) {
        for (i = 0; i < temp_table->tables[j].column_num; i++) {
            stats_table[j][i] = temp_table->tables[j].stats[i];
        }
    }
    for(k=0;k<parag(temp_table->num_of_tables);k++){
temp_minimum=0;
        for(i=0;i<temp_table->num_of_tables-1;i++){

            if(neibour[prem[k][i]][prem[k][i+1]].bol==0)
                break;

            table1 = priority_series[neibour[prem[k][i]][prem[k][i+1]].priority_line].command[0] - 48;
            column1 = priority_series[neibour[prem[k][i]][prem[k][i+1]].priority_line].command[2] - 48;
            table2 = priority_series[neibour[prem[k][i]][prem[k][i+1]].priority_line].command[4] - 48;
            column2 = priority_series[neibour[prem[k][i]][prem[k][i+1]].priority_line].command[6] - 48;

            temp_table=cost(table1,table2,column1,column2,temp_table);
            temp_minimum=temp_minimum+temp_table->tables[table1].stats[column1].full;
            priotity_line_temp[i]=neibour[prem[k][i]][prem[k][i+1]].priority_line;
        }


        if(minimum==-1){
            minimum=temp_minimum;
            for(i=0;i<temp_table->num_of_tables;i++)
            priority_line[i]=priotity_line_temp[i];
        }else{
            if(minimum>temp_minimum){
                minimum=temp_minimum;
                for(i=0;i<temp_table->num_of_tables;i++)
                    priority_line[i]=priotity_line_temp[i];
            }

        }

        for(i=0;i<temp_table->num_of_tables;i++){






        }


        }
    }



