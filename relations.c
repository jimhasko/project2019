
#include "relations.h"
#define bool_num 50000000


#include "Result_List.h"
/*void init_tables(List_of_Tables lista_pinakon){
    lista_pinakon.num_of_tables=0;
    lista_pinakon.tables=(Single_Table*)malloc(10*sizeof(Single_Table));



}
*/

int curr = 0;
pthread_cond_t condd = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_total = PTHREAD_COND_INITIALIZER;

uint64_t Sto64(const char *s) { // string to number

    uint64_t i;
    char c;

    int scanned = sscanf(s, "%" SCNu64 "%c", &i, &c);
    if (scanned) return i;

    return 0;
}

void short_priority(priority* prior,int prior_num){
    int i,j;
    int test1,test2;
    priority temp;
    for(j=0;j<prior_num;j++){
        for(i=0;i<prior_num-1;i++){
            test1=prior[i].type;
            test2=prior[i+1].type;
            if(prior[i].type>prior[i+1].type){
                temp=prior[i];
                prior[i]=prior[i+1];
                prior[i+1]=temp;
            }

        }
    }


}


List_of_Tables* get_data_from_file( List_of_Tables* master_table, int argc, char* argv[]) {

    if (argc != 3 ) {
        printf("\n\nError with arguments! input-> ./myexe Init_file Work_file!\n");
        exit(1);
    }
    else {

        FILE * fptri = NULL;
        int lines = 0;
        char * line =  (char*) malloc( sizeof(char) * max_line_length);

        fptri = fopen(argv[1], "r");
        if(fptri == NULL) {
            printf("\n\nNo such init_file in the working directory!\n");
            exit(1);
        }

        while(!feof(fptri)) {
            if(fgetc(fptri) == '\n') {
                lines++;
            }
        }

        fseek(fptri, 0, SEEK_SET);

        if (lines <= 0 ) {

            printf("\n\nInit_file was empty, check file again!\n");
            exit(1);
        }

        // master_table = (List_of_Tables*) malloc (sizeof(List_of_Tables));
        master_table->num_of_tables = lines;
        master_table->work_file = false;
        lines = 0;
        master_table->tables=(Single_Table*)malloc(sizeof(Single_Table)*master_table->num_of_tables);
        while (EOF != fscanf(fptri, "%[^\n]\n", line)) {

            master_table->tables[lines]=fill(line, lines);
            //printf("%s %d\n",line, lines);
            lines++;
        }
        free(line);
        fclose(fptri);
    }


    return master_table;
}

int do_the_work(List_of_Tables* master_table, int argc, char* argv[]) {

    master_table = get_data_from_file( master_table, argc, argv);

    FILE * fptrw = NULL;
    int lines = 0;
    int batches = 0;
    char cur_char;
    char * line =  (char*) malloc( sizeof(char) * max_line_length);

    fptrw = fopen(argv[2], "r");

    if (fptrw == NULL) {
        printf("No such work_file in the working directory!");
        return false;
    }

    while(!feof(fptrw)) {
        cur_char = fgetc(fptrw);
        if(cur_char== '\n') {
            lines++;
        }

        if(cur_char== 'F') {
            batches++;
        }
    }

    fseek(fptrw, 0, SEEK_SET);

    if (lines <= 0 ) {

        printf("Work_file was empty, check file again!");
        return false;
    }

    just_transfer * test;
    middle* bad_word;
  //  lines=0;
   // batches =0;


    int wut,i,j;

    jobqueue_big* jobquery;

    jobquery=(jobqueue_big*)malloc(sizeof(jobqueue_big));
    jobquery->jobs=(job_big*)malloc(sizeof(job_big)*lines);
    jobquery->size=0;
    jobquery->used=0;
    jobquery->thread_num=0;
    pthread_t* thread_matrix_big;
    thread_matrix_big=(pthread_t*)malloc(sizeof(pthread_t)*big_threads);
    pthread_mutex_init(&mutexbig, NULL);
    pthread_mutex_init(&mutexsumbig, NULL);
    pthread_cond_init(&condd, NULL);




    lines=0;
    batches =0;

    while (EOF != fscanf(fptrw, "%[^\n]\n", line)) {

        if(strcmp(line, "F") != 0) {
if(do_big_thread==0) {
    test = analise(line, master_table);

     bad_word = run_filters(master_table, test);

     athrisma(bad_word, test, master_table,print_in_line);
     //exit(1);
}else {
    jobquery->jobs[lines].line = (char *) malloc(sizeof(char) * strlen(line)+1);
    strcpy(jobquery->jobs[lines].line, line);
    jobquery->jobs[lines].master_table = master_table;

    jobquery->size++;

}

            lines++;

        }
        else {
            batches++;
            //if (batches == 2)
                //break;
        }
    }

    if(do_big_thread==1) {
        for (i = 0; i < big_threads; i++) {

            wut = pthread_create(&thread_matrix_big[i], NULL, big_thread, (void *) jobquery);
        }


        for (i = 0; i < big_threads; i++)
            pthread_join(thread_matrix_big[i], NULL);
if(print_in_line==1) {
    for (i = 0; i < lines; i++) {
        for (j = 0; j < jobquery->jobs[i].res->result_numb; j++) {
            if (jobquery->jobs[i].res->empty == 0) {
                printf("%"PRIu64 " ", jobquery->jobs[i].res->result[j]);
            } else {
                printf("NULL ");
            }
        }
        printf("\n");
    }


    for (i = 0; i < lines; i++) {
        if (i == 43) {
            int brolk = 0;
        }
        if (jobquery->jobs[i].res->empty == 0) {
            free(jobquery->jobs[i].res->result);
        }
        free(jobquery->jobs[i].res);
         free( jobquery->jobs[i].line);
    }
}
        free(thread_matrix_big);
        free(jobquery->jobs);
        free(jobquery);
    }
    free(line);
    free_big(master_table);
    return true;
}


int min_priority(priority* prior,int priority_number){
    int i,min;
    min=priority_number-1;
    for(i=priority_number-1;i>-1;i--) {
        if (prior[i].type == 5) {
            if (prior[min].size > prior[i].size) {
                min = i;
            }

        }
    }
    return min;





}

void swap_priority(priority* prior,int from,int to){
    priority temp;
    temp=prior[to];
    prior[to]=prior[from];
    prior[from]=temp;


}
void get_size(priority* prior,int priority_number,just_transfer* just, int now){
    int i,j,hr1,hr2;
    for(i=now;i<priority_number;i++){
        hr1=prior[i].here_table1;
        hr2=prior[i].here_table2;
        if(just->tables_ids[hr1].size<=just->tables_ids[hr2].size){
            prior[i].size=just->tables_ids[hr1].size;
        }else{
            prior[i].size=just->tables_ids[hr2].size;
        }

    }




}

void priority_tree(priority* prior,int priority_number,just_transfer* just,List_of_Tables* master_table){
    int i,j,min,k,now=0;

    for(j=0;j<priority_number;j++){
        if(prior[j].type==5){
            now=j;
        break;}
    }
   test_run_stats_joins(master_table,just,priority_number);

while(now<priority_number){

    min=min_priority(prior,priority_number);
    if(min!=now){
        swap_priority(prior,min,now);}
    run_stats_joins(master_table,just,now);
    now++;
    for(i=now;i<priority_number;i++){
        if((prior[now-1].here_table1==prior[i].here_table1&&prior[now-1].col1==prior[i].col1)||(prior[now-1].here_table2==prior[i].here_table2&&prior[now-1].col2==prior[i].col2)){
            swap_priority(prior,i,now);
            now++;

        }
    }
    test_run_stats_joins(master_table,just,priority_number);
}
    //get_size(prior,priority_number,just,now);

/*
    min=min_priority(prior,priority_number);

    if(min!=now){
        swap_priority(prior,min,now);}
        run_stats_joins(master_table,just,now);
    for(;j<priority_number;j++){
        for(i=now+1;i<priority_number;i++){
            if(prior[j].here_table1==prior[i].here_table1||prior[j].here_table2==prior[i].here_table1||prior[j].here_table1==prior[i].here_table2||prior[j].here_table2==prior[i].here_table2){
            now++;
                swap_priority(prior,i,now);}
        }
    }
    /*for(k=0;k<priority_number;k++){
        printf(" j:%d ,ptr: %s size:%d \n",k,prior[k].command,(int)prior[k].size);
    }*/
}


/*
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
*/


float power(float basi,float pano){

    int i;
    float temp;
    temp=1.0;
    for (i=0;i<pano;i++){
        temp=temp*basi;

    }
    return temp;


}

Single_Table fill(char* filename,int name){     //diabazi binary k gemizi ti mnimi
    Single_Table Table_Node;
    FILE *fp = fopen(filename,"r");
    uint64_t result;
    if(!fp){

        printf("wrong input file %s \n",filename);
    }

    int* distinct;
   // int result;

    result = fread(&Table_Node.tube_num,sizeof(uint64_t),1,fp);
    result = fread(&Table_Node.column_num,sizeof(uint64_t),1,fp);

    Table_Node.Full_Table=(Row_table*)malloc(sizeof(Row_table)*Table_Node.column_num);
    Table_Node.stats=(statistics*)malloc(sizeof(statistics)*Table_Node.column_num);
   // Table_Node.id_table=malloc(sizeof(int)*Table_Node.tube_num);
    Table_Node.table_name=name;
    int j,bool_test,i,k=0;
    j=0;
    uint64_t max;
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

    for(i=0;i<Table_Node.tube_num*Table_Node.column_num+1;i++){

        if((i / Table_Node.tube_num>j)||j==Table_Node.tube_num-1) {
            // Table_Node.Full_Table[j]=temp;
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
            Table_Node.stats[j].distinct=0;
            for(bool_test=0;bool_test<Table_Node.tube_num;bool_test++){
                if(distinct[(Table_Node.Full_Table[j].Column[bool_test]-Table_Node.stats[j].lower)%max]==0){
                    distinct[(Table_Node.Full_Table[j].Column[bool_test]-Table_Node.stats[j].lower)%max]=1;
                    Table_Node.stats[j].distinct++;
                }

            }
            free(distinct);

            k=0;
            j++;

        }
    if(j==Table_Node.column_num){
    break;
        //Table_Node.id_table[i]=i;
    }
         //   printf("\n %ld  <",i);
        // uint64_t result;

        result = fread(& Table_Node.Full_Table[j].Column[k],sizeof(uint64_t),1,fp);
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



int read_init(char *filename) {
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


List_of_Tables init_Tables(char*initfile) {

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
    //printf("sxesi %s| len :%ld \n",sxesi,strlen(sxesi));
//char t=sxesi[0];
    strncat(katigorima,str+first+1,second-first-1);
    //printf("katigorima %s \n",katigorima);

    strncat(proboli,str+second+1,third-second);
    //printf("proboli %s \n",proboli);








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
    //printf("%d\n",master_table->num_of_tables);
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


    int swap,max_rows,l;
    ptr = strtok(katigorima, delimkat);
    int table1,table2,column1,column2,here_table1,here_table2,counter=0;
    int len,counter_guard=10;
    char *last;
    // Row_table replace;
    while(ptr != NULL)
    {   priority_number++;
        priority_series[counter].command=ptr;
        //printf("ptr %s \n",ptr);
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
            here_table2=-1;
        }



        if(ptr[3]=='='){

            if(len==5||ptr[5]!='.'){
                priority_series[counter].type=2;  //=number
                last = strrchr(ptr, '=');
                priority_series[counter].number=Sto64(last+1);


            }else   if(((here_table1)==(here_table2)&&(master_table->tables[table1].table_name==master_table->tables[table2].table_name)&&(column1==column2))){// self join

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
                    swap=table2;
                    table2=table1;
                    table1=swap;
                }

                priority_series[counter].type = 5;


                for(l=0;l<counter;l++){
                    if( priority_series[l].type ==5){
                        if(priority_series[l].here_table1==here_table1&&priority_series[l].here_table2==here_table2&&priority_series[l].col1==column1&&priority_series[l].col2==column2){
                            priority_series[counter].type=1;
                        }
                    }


                }


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
        priority_series[counter].here_table2=here_table2;
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
        transfer->tables_ids[i].id_list=(int**)malloc(sizeof(int*)*1);
        transfer->tables_ids[i].stats=(statistics*)malloc(sizeof(statistics)*(master_table->tables[from[i]].column_num));

    }
    for(i=0;i<from_number;i++)
    transfer->tables_ids[i].id_list[0]=malloc(sizeof(int*)*master_table->tables[from[i]].tube_num);

   max_rows=max(from,from_number,master_table);
    for(i=0;i<max_rows;i++){
        for(j=0;j<from_number;j++) {
            if (i < master_table->tables[from[j]].tube_num)
                transfer->tables_ids[j].id_list[0][i]=i;
        }
    }


///////
    for(i=0;i<from_number;i++){
        for(j=0;j<master_table->tables[from[i]].column_num;j++){
            transfer->tables_ids[i].stats[j]=master_table->tables[from[i]].stats[j];
        }

    }

    /////////

    for(j=0;j<from_number;j++) {

        transfer->tables_ids[j].size=(int)master_table->tables[from[j]].tube_num;
    }
/////////////////
    char* temp;
    temp=(char*)malloc(sizeof(char)*strlen(proboli)+1);
    strcpy(temp,proboli);
    char delimprov[] = " ";
    ptr = strtok(temp, delimprov);
    i=0;
    int size=0;


    while(ptr != NULL)
    {

        ptr = strtok(NULL, delim);
        size++;

    }
    ptr = strtok(proboli, delimprov);
    summa * suma=(summa*)malloc(sizeof(summa)*size);
    while(ptr != NULL)
    {

        suma[i].here_table=ptr[0]-48;
        suma[i].master_table=(int)from[ptr[0]-48];
        suma[i].col=ptr[2]-48;


        ptr = strtok(NULL, delim);
        i++;

    }
    transfer->suma_size=size;
    transfer->suma=suma;
    free(temp);
    free(proboli);
    free(katigorima);
    free(sxesi);
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

    ht1 = 0;
    ht2 = 0;

    int ** list1;
    results * res1;
    results * res2;
    res1=NULL;
    priority_number=transfer->priority_number;
    short_priority(transfer->priority1,priority_number);
    uint64_t * col1;
    uint64_t *  col2;
    int * new;

    int id,idcounter;
    middle* midle;
    midle=(middle*)malloc(sizeof(middle));
    midle->inserted=NULL;
    midle->inserted=malloc(sizeof(int)*master_table->num_of_tables);
   // midle->inserted=pass;
    midle->num_inserted=0;
    midle->start=NULL;
    midle->columns=0;
    midle->size=-1;
 //   middle.start  //kane initialize ti lista



    run_stats_filters(master_table,transfer,priority_number);


    for (i = 0; i < priority_number; i++) {         //gia ola ta queries
                counter=0;
    if(transfer->priority1[i].type == 5 && midle->num_inserted==0)
        priority_tree(transfer->priority1, transfer->priority_number, transfer,master_table);
        //printf(" priority %d : %s \n",i, transfer->priority1[i].command);
        idcounter=0;


        table1=transfer->priority1[i].master_table1;
        column1=transfer->priority1[i].col1;
        ht1=transfer->priority1[i].here_table1;
        col1=master_table->tables[table1].Full_Table[column1].Column;
        ht2=ht1;
        col2=col1;
        table2=table1;
        column2=column1;
        if(transfer->priority1[i].type==5||transfer->priority1[i].type==1){// if it needs 2 matrixes

            table2=transfer->priority1[i].master_table2;
            column2=transfer->priority1[i].col2;
            ht2=transfer->priority1[i].here_table2;
            col2=master_table->tables[table2].Full_Table[column2].Column;
        }


   /* if(transfer->priority1[i].type!=5){
       // printf("made A  new %d",transfer->tables_ids[ht1].size);
       new=malloc(sizeof(int)*transfer->tables_ids[ht1].size);
        if(new == NULL) {
            perror("malloc");
        exit(1);
        }}*/

        if (transfer->priority1[i].type == 1) {             //self join 111111111111111111111111111111111111111111111111111111111111111

        //   0|0.1=0.1



        }

        else if (transfer->priority1[i].type == 2) {        //column=number     2222222222222222222222222222222222222222222222222222222222

            for(j=0;j<transfer->tables_ids[ht1].size;j++){
                id=transfer->tables_ids[ht1].id_list[0][j];
                if(col1[id]==transfer->priority1[i].number){
                    transfer->tables_ids[ht1].id_list[0][idcounter]=id;
                   // new[idcounter]=id;
                    idcounter++;
                }


            }

        }
        else if (transfer->priority1[i].type == 3) {        //column>number   3333333333333333333333333333333333333333333333333333333333333333333333333

            for(j=0;j<transfer->tables_ids[ht1].size;j++){
                id=transfer->tables_ids[ht1].id_list[0][j];
                if(col1[id]>transfer->priority1[i].number){
                    transfer->tables_ids[ht1].id_list[0][idcounter]=id;
                    // new[idcounter]=id;
                    idcounter++;
                }


            }


        }else
        if (transfer->priority1[i].type == 4) {                          //column<number     444444444444444444444444444444444444444444444444444444444444444444444444

            for(j=0;j<transfer->tables_ids[ht1].size;j++){
                id=transfer->tables_ids[ht1].id_list[0][j];
                if(col1[id]<transfer->priority1[i].number){
                    transfer->tables_ids[ht1].id_list[0][idcounter]=id;
                    // new[idcounter]=id;
                    idcounter++;
                }


            }

        }else{                                              //tablejoin!!!!!!!!!!!!!!5555555555555555555///////////////
   //f printf("has 5\n");

            int isin1,isin2,mid_size,needed1,needed=0;

            if(midle->num_inserted==0) {  //////first runnnnn

               //    prior ity_tree(transfer->priority1, transfer->priority_number, transfer);
              //  int ** list2;
                   // list1=get_id_list(&transfer->tables_ids[ht1]);
                  //  list2=get_id_list(&transfer->tables_ids[ht2]);


                res1=big_short(col1,transfer->tables_ids[ht1].id_list,1,transfer->tables_ids[ht1].size,needed);
//exit(1);
                res2=big_short(col2,transfer->tables_ids[ht2].id_list,1,transfer->tables_ids[ht2].size,needed);

                 midle->table =join_matrices(res1,res2,0,middle__size,(&midle->size));        ////////< join

                midle->num_inserted=2;
                midle->inserted[0]=ht1;
                midle->inserted[1]=ht2;
                midle->columns=2;
               // free_list(list1,transfer->tables_ids[ht1].size);
               // free_list(list2,transfer->tables_ids[ht2].size);


            }
            else{       //////secomnd run//////////////////




                isin1=0;
                isin2=0;

                for(j=0;j<midle->num_inserted;j++){
                  if(ht1==midle->inserted[j]){
                    isin1=1;
                    needed=j;
                  }
                  //  needed1=i;
                 if(ht2==midle->inserted[j]){
                    isin2=1;
                    needed=j;
                 }
                }
                if(isin1+isin2==2){
                    midle_scan(midle,(&transfer->priority1[i]),master_table);


                } else {

                     if (isin1 == 1) {
                         if(transfer->priority1[i-1].col1==column1&&transfer->priority1[i-1].here_table1==ht1) {
                             res1=get_old_results(col1,midle->table,midle->num_inserted,midle->size,needed);
                         }else{
                             //free_results(res1);
                             res1=big_short(col1,midle->table,midle->num_inserted,midle->size,needed);
                         }
                        // list1= get_id_list(&transfer->tables_ids[ht2]);
                      //  list1= transfer->tables_ids[ht2];
                         res2=big_short(col2,transfer->tables_ids[ht2].id_list,1,transfer->tables_ids[ht2].size,0);

                         midle->inserted[midle->num_inserted]=ht2;
                        // free_list(list1,transfer->tables_ids[ht2].size);
                     } else {
                         if(transfer->priority1[i-1].col2==column2&&transfer->priority1[i-1].here_table2==ht2) {
                             res1=get_old_results(col2,midle->table,midle->num_inserted,midle->size,needed);
                         }else{
                            // free_results(res1);
                             res1=big_short(col2,midle->table,midle->num_inserted,midle->size,needed);
                         }

                       // list1= get_id_list(&transfer->tables_ids[ht1]);

                         res2=big_short(col1,transfer->tables_ids[ht1].id_list,1,transfer->tables_ids[ht1].size,0);
                         midle->inserted[midle->num_inserted]=ht1;
                         //free_list(list1,transfer->tables_ids[ht1].size);

                     }
                        free_midle_table(midle);
                     midle->table =join_matrices(res1,res2,needed,middle__size,(&midle->size));            ////////< join


                     midle->num_inserted++;
                     midle->columns++;

                 }



            }

        }
        if(transfer->priority1[i].type !=5&&transfer->priority1[i].type !=1){
        transfer->tables_ids[ht1].size=idcounter;
        transfer->priority1[i].size=idcounter;
        midle->size=idcounter;
       // fr ee(transfer->tables_ids[ht1].id_list);
       // transfer->tables_ids[ht1].id_list=new;

        //new=NULL;
        }


        if(midle->size==0){
            //printf("0 common values \n");
               break;
        }



    }
   // if(res1!=NULL)
     //   free_results(res1);



    return midle;

}



void midle_scan(middle* midle,priority* prior,List_of_Tables* master_table){
    int i,j,k,size;
    int* test;
    size=midle->size;
    uint64_t * column1=master_table->tables[prior->master_table1].Full_Table[prior->col1].Column;
    uint64_t * column2=master_table->tables[prior->master_table2].Full_Table[prior->col2].Column;
    int  nht1=prior->here_table1;
    int  nht2=prior->here_table2;
    int col1=prior->col1;
    int col2=prior->col2;
    int id1;
    int id2;
    int ht1,ht2;

    int** temp=(int**)malloc(sizeof(int*)*(midle->num_inserted));
    if(temp==NULL){
        printf(" out of memory ");
        exit(1);
    }
    /*for(i=0;i<(midle->num_inserted);i++)
        printf(": %d",midle->inserted[i]);
    printf("\n");*/
    for(i=0;i<(midle->num_inserted);i++) {               ///table[rows][columns]
        temp[i] = malloc(sizeof(int) * size);
        if(midle->inserted[i]==nht1){
            ht1=i;}
        if(midle->inserted[i]==nht2){
            ht2=i;}
    }
    int added=0;

///////////
    for(j=0;j<size;j++){
        id1=midle->table[ht1][j];
        id2=midle->table[ht2][j];
        if(column1[id1]==column2[id2]){
            for(i=0;i<midle->num_inserted;i++){
               temp[i][added]= midle->table[i][j];}
            added++;
            if(added==size){

                for(k=0;k<(midle->num_inserted);k++){
                    test=(int*)realloc(midle->table[k],2*size*sizeof(int));
                    if(test==NULL){
                        printf("MIDLE MATRIX REALLOC=NULL on selfjoin \n");
                        exit(1);
                    }
                    temp[k]=test;
                }
            }
        }
    }

    free_midle_table(midle);
    midle->table=temp;
    midle->size=added;
    //printf("added: %d\n",added);

}

result* athrisma(middle* midle,just_transfer* transfer,List_of_Tables* master_table,int print){
    int i,j,k,MT,CL,HT,ins_id,table_id;
    uint64_t * column;
    uint64_t * sums;
    ins_id=0;
   // printf("ADDING!!\n");
    FILE * fptrs = NULL;
    result* res;
    if(print==1){

        res=(result*)malloc(sizeof(result));
        res->result_numb=transfer->suma_size;
        res->empty=0;

    }


    if (master_table->work_file == false) {

        fptrs = fopen (work_slave,"w");
        if (fptrs == NULL) {
            printf("\n\nCant write to save file!\n");
            return NULL;
        }
        else {
            master_table->work_file = true;
        }
    }
    else {

        fptrs = fopen(work_slave, "a");

        if (fptrs == NULL) {
            printf("\n\nCant write to save file!\n");
            return NULL;
        }
    }

    if(midle->size>0) {


        sums = (uint64_t *) calloc(transfer->suma_size, sizeof(uint64_t));
        for (i = 0; i < transfer->suma_size; i++) {
            MT = transfer->suma[i].master_table;
            HT = transfer->suma[i].here_table;
            CL = transfer->suma[i].col;
            column = master_table->tables[MT].Full_Table[CL].Column;

            for (j = 0; j < midle->num_inserted; j++) {
                if (HT == midle->inserted[j]){
                    ins_id = j;

                    break;}
            }

            for (j = 0; j < midle->size; j++) {
                table_id = midle->table[ins_id][j];
                if(table_id<master_table->tables[MT].tube_num){
                sums[i] += column[table_id];}
                else{
                    //for(i=0;i<midle->num_inserted;i++)
                        //printf(": %d \n",midle->table[i][j]);
                    exit(1);
                }

            }
        if(print==0){
            printf("%"PRIu64 " ",  sums[i]);}






            fprintf (fptrs, "%"PRIu64 " ",  sums[i]);


        }
        //free(sums);
        if(print==1){
            res->result=sums;
        }
    }else{
        for(j=0;j<transfer->suma_size;j++) {
           if(print==0)
            printf("NULL ");
           if(print==1)
               res->empty=1;
            fprintf(fptrs, "NULL ");
        }
    }
    if(print==0)
    printf("\n");
    fprintf(fptrs, "\n");

    fclose(fptrs);
    free_transfer(transfer);
    free_midle(midle);
if(print==1){
    return res;
}
}



int** get_id_list(tableid * idlist){
    int j,size2=idlist->size;
   /* int ** list2;
    list2=(int**)malloc(sizeof(int*));

    // for(j=0;j<1;j++) {
    list2[0] = malloc(sizeof(int)*size2);
    //  }

    for(j=0;j<idlist->size;j++){
        list2[0][j]=idlist->id_list[j];
    }
    if(list2!=NULL){
        return list2;}
    else {
        printf("  god why ? \n");
        exit(1);
    }*/
   return idlist->id_list;
}

void free_list(int** list,int size){
    int i;
    /* for(i=1;i<size;i++)
     {
         free(list[i]);
     }*/
    free(list[0]);
    free(list);

}

void free_midle_table(middle* midle){
    int i,col;
    col=midle->columns;

    for(i=0;i<col;i++){
        free(midle->table[i]);
    }
    if(midle->num_inserted>0)
        free(midle->table);
}

void free_midle(middle* midle){
    int i,j;
    free_midle_table(midle);
    free(midle->inserted);
    free(midle);


}



void free_transfer(just_transfer* transfer){
    int i,j,from_number;
    from_number=transfer->num_of_tables;
    int k=transfer->tables_ids[0].id_list[0][1];
    for(i=0;i<transfer->num_of_tables;i++) {
        free(transfer->tables_ids[i].id_list[0]);

    }


    for(i=0;i<transfer->num_of_tables;i++) {

        free(transfer->tables_ids[i].stats);

    }

    for(i=0;i<transfer->num_of_tables;i++)
    free(transfer->tables_ids[i].id_list);

   free( transfer->tables);
    free(transfer->priority1);
    free(transfer->suma);


    free(transfer->tables_ids);
    free(transfer);

}

void free_big(List_of_Tables* master){
    int i,j,col;
    for(i=0;i<master->num_of_tables;i++){
       col= (int)master->tables[i].column_num;
        free(master->tables[i].stats);
//        free(master->tables[i].id_table);
        for(j=0;j<col;j++){
           free(master->tables[i].Full_Table[j].Column);

        }




    }

    for(i=0;i<master->num_of_tables;i++)
        free(master->tables[i].Full_Table);
   // free(master->tables->Full_Table);
    free(master->tables);

free(master);
}








void run_stats_filters(List_of_Tables* master_table,just_transfer* transfer,int priority_number) {


    int comparison, i, j,inside_counter,temp, inside_counter_guard = 500;
   // statistics * dedomena;
    int counter = 0;
    uint64_t min,max;
    int counter_guard = 10;
  //  dedomena=(statistics*)malloc(sizeof(statistics)*master_table->num_of_tables); //statistika gia tous pinakes

    int table1,column1,ht1,ht2,table2,column2;

double test,power1,power2;










    uint64_t lower,upper,stat_size,distinct,n,distinct_old_h1,distinct_old_h2,distinct_diff,full_old,full,full_diff,upper_old,lower_old;
    for (i = 0; i < priority_number; i++) {         //gia ola ta queries
        counter=0;




        table1=transfer->priority1[i].master_table1;
        column1=transfer->priority1[i].col1;
        ht1=transfer->priority1[i].here_table1;

        ht2=-1;

        table2=-1;
        column2=-1;
        if(transfer->priority1[i].type==5||transfer->priority1[i].type==1){// if it needs 2 matrixes

            table2=transfer->priority1[i].master_table2;
            column2=transfer->priority1[i].col2;
            ht2=transfer->priority1[i].here_table2;

        }




        if ((transfer->priority1[i].type == 5)&&ht1==ht2) {             //column==column(same matrix) 111111111111111111111111111111111111111111111111111111111111111


//upper lower

            max=max_num(transfer->tables_ids[ht1].stats[column1].lower,transfer->tables_ids[ht1].stats[column2].lower);
            min=min_num(transfer->tables_ids[ht1].stats[column1].upper,transfer->tables_ids[ht1].stats[column2].upper);
            transfer->tables_ids[ht1].stats[column1].lower=max;
            transfer->tables_ids[ht1].stats[column2].lower=max;

            transfer->tables_ids[ht1].stats[column1].upper=min;
            transfer->tables_ids[ht1].stats[column2].upper=min;

            //full

            n=min-max+1;
            full_old=transfer->tables_ids[ht1].stats[column1].full;
            full=full_old/n;
            transfer->tables_ids[ht1].stats[column1].full=full;
            transfer->tables_ids[ht1].stats[column2].full= full;
            //distinct

            distinct=transfer->tables_ids[ht1].stats[column1].distinct;
            if(distinct>0){
                power1=1-((double)full/full_old);
                power2=(double)full_old/distinct;
                test=(double)distinct*(1-pow(power1,power2));
                 distinct=test;}
            else{
                distinct=0;
            }

            transfer->tables_ids[ht1].stats[column1].distinct=distinct;
            transfer->tables_ids[ht1].stats[column2].distinct=distinct;


            for(j=0;j<master_table->tables[table1].column_num;j++){///other columns on table 1
                if(j!=column1&&j!=column2){
                    full_diff=transfer->tables_ids[ht1].stats[j].full;
                    distinct=transfer->tables_ids[ht1].stats[j].distinct;
                    if(distinct>0&&full_old>0){
                        power1=1-((double)full/full_old);
                        power2=(double)full_diff/distinct;
                        test=(1-pow(power1,power2));
                    transfer->tables_ids[ht1].stats[j].distinct=distinct*test;
                    transfer->tables_ids[ht1].stats[j].full=full;}
                    else{
                        transfer->tables_ids[ht1].stats[j].distinct=0;
                        transfer->tables_ids[ht1].stats[j].full=0;
                    }
                }


            }


            transfer->priority1[i].size=full;
        }






        else if (transfer->priority1[i].type == 2) {        //column=number     2222222222222222222222222222222222222222222222222222222222
            upper=transfer->tables_ids[ht1].stats[column1].upper;
            lower=transfer->tables_ids[ht1].stats[column1].lower;

            distinct=transfer->tables_ids[ht1].stats[i].distinct;
            full_old= transfer->tables_ids[ht1].stats[column1].full;
            if((transfer->priority1[i].number<upper&&transfer->priority1[i].number>lower)&&distinct>0){

                transfer->tables_ids[ht1].stats[column1].distinct=1;
                transfer->tables_ids[ht1].stats[column1].full=transfer->tables_ids[ht1].stats[column1].full/distinct;


            }else{
                transfer->tables_ids[ht1].stats[column1].distinct=0;
                transfer->tables_ids[ht1].stats[column1].full=0;

            }
            transfer->tables_ids[ht1].stats[column1].upper=transfer->priority1[i].number;
            transfer->tables_ids[ht1].stats[column1].lower=transfer->priority1[i].number;






            full= transfer->tables_ids[ht1].stats[column1].full;

            for(j=0;j<master_table->tables[table1].column_num;j++){///other columns on table 1
                if(j!=column1){
                    full_diff=transfer->tables_ids[ht1].stats[j].full;
                    distinct=transfer->tables_ids[ht1].stats[j].distinct;

                    if(distinct>0&&full_old>0){
                        power1=1-((double)full/full_old);
                        power2=(double)full_diff/distinct;
                        test=(1-pow(power1,power2));
                        transfer->tables_ids[ht1].stats[j].distinct=distinct*test;
                         transfer->tables_ids[ht1].stats[j].full=full;}


                }else{
                    transfer->tables_ids[ht1].stats[j].distinct=0;
                    transfer->tables_ids[ht1].stats[j].full=0;
                }


            }



            transfer->priority1[i].size=full;

        }
        else if (transfer->priority1[i].type == 3) {        //column>number   3333333333333333333333333333333333333333333333333333333333333333333333333

            upper_old=transfer->tables_ids[ht1].stats[column1].upper;
            lower_old=transfer->tables_ids[ht1].stats[column1].lower;
            transfer->tables_ids[ht1].stats[column1].lower=transfer->priority1[i].number;
            upper=transfer->tables_ids[ht1].stats[column1].upper;
            lower=transfer->tables_ids[ht1].stats[column1].lower;



            distinct=transfer->tables_ids[ht1].stats[column1].distinct;
            full_old=transfer->tables_ids[ht1].stats[column1].full;
            if(upper_old-lower_old==0){
                // transfer->tables_ids[ht1].stats[column1].distinct=distinct;
                // transfer->tables_ids[ht1].stats[column1].full=1;
            }else{
                test=((upper-lower)*(double)distinct/(upper_old-lower_old));
                transfer->tables_ids[ht1].stats[column1].distinct=test;

                test=((upper-lower)*(double)full_old/(upper_old-lower_old));
                transfer->tables_ids[ht1].stats[column1].full=test;
               }
            full=transfer->tables_ids[ht1].stats[column1].full;


            for(j=0;j<master_table->tables[table1].column_num;j++){///other columns on table 1
                if(j!=column1){
                    full_diff=transfer->tables_ids[ht1].stats[j].full;
                    distinct=transfer->tables_ids[ht1].stats[j].distinct;
                    if(distinct>0&&full_old>0){

                        power1=((full_old-full)/(double)full_old);
                        power2=full_diff/(double)distinct;
                        test=(1-pow(power1,power2));
                        transfer->tables_ids[ht1].stats[j].distinct=distinct*test;
                        transfer->tables_ids[ht1].stats[j].full=full;}
                    else {transfer->tables_ids[ht1].stats[j].distinct=0;
                        transfer->tables_ids[ht1].stats[j].full=0;
                    }

                }


            }



            transfer->priority1[i].size=full;


        }else
        if (transfer->priority1[i].type == 4) {                          //column<number     444444444444444444444444444444444444444444444444444444444444444444444444







            upper_old=transfer->tables_ids[ht1].stats[column1].upper;
            lower_old=transfer->tables_ids[ht1].stats[column1].lower;
            transfer->tables_ids[ht1].stats[column1].upper=transfer->priority1[i].number;
            upper=transfer->tables_ids[ht1].stats[column1].upper;
            lower=transfer->tables_ids[ht1].stats[column1].lower;


            distinct=transfer->tables_ids[ht1].stats[column1].distinct;
            full_old=transfer->tables_ids[ht1].stats[column1].full;
            if(upper_old-lower_old>0){
                test=((upper-lower)/(upper_old-lower_old))*(double)distinct;
                transfer->tables_ids[ht1].stats[column1].distinct=test;
                test=((upper-lower)/(upper_old-lower_old))*(double)full_old;
                transfer->tables_ids[ht1].stats[column1].full=test;}
            full=transfer->tables_ids[ht1].stats[column1].full;


            for(j=0;j<master_table->tables[table1].column_num;j++){///other columns on table 1
                if(j!=column1){
                    full_diff=transfer->tables_ids[ht1].stats[j].full;
                    distinct=transfer->tables_ids[ht1].stats[j].distinct;
                    if(distinct>0&&full_old>0){
                        power1=1-((double)full/full_old);
                        power2=(double)full_diff/distinct;
                        test=(1-pow(power1,power2));
                        transfer->tables_ids[ht1].stats[j].distinct=distinct*test;
                        transfer->tables_ids[ht1].stats[j].full=full;
                    }
                    else {
                        transfer->tables_ids[ht1].stats[j].distinct=0;
                        transfer->tables_ids[ht1].stats[j].full=0;
                    }

                }


            }





transfer->priority1[i].size=full;



        }else{                                                                          //555555555555555555555555555555555




/*

            //upper lower

            max=max_num(transfer->tables_ids[ht1].stats[column1].lower,transfer->tables_ids[ht2].stats[column2].lower);
            min=min_num(transfer->tables_ids[ht2].stats[column1].upper,transfer->tables_ids[ht2].stats[column2].upper);
            transfer->tables_ids[ht1].stats[column1].lower=max;
            transfer->tables_ids[ht2].stats[column2].lower=max;

            transfer->tables_ids[ht1].stats[column1].upper=min;
            transfer->tables_ids[ht2].stats[column2].upper=min;

            //full

            n=min-max+1;
            //full_old=transfer->tables_ids[ht1].stats[column1].full;
            full=(transfer->tables_ids[ht1].stats[column1].full*transfer->tables_ids[ht2].stats[column2].full)/n;
            transfer->tables_ids[ht1].stats[column1].full=full;
            transfer->tables_ids[ht2].stats[column2].full= full;
            //distinct
            distinct_old_h1=transfer->tables_ids[ht1].stats[column1].distinct;
            distinct_old_h2=transfer->tables_ids[ht2].stats[column2].distinct;
            distinct=(transfer->tables_ids[ht1].stats[column1].distinct*transfer->tables_ids[ht2].stats[column2].distinct)/n;
            //distinct=distinct*(1-power(1-(full/full_old),full_old/distinct));
            transfer->tables_ids[ht1].stats[column1].distinct=distinct;
            transfer->tables_ids[ht2].stats[column2].distinct=distinct;


            for(j=0;j<master_table->tables[ht1].column_num;j++){///other columns on table 1
                if(i!=column1){
                    full_diff=transfer->tables_ids[ht1].stats[i].full;
                    distinct_diff=transfer->tables_ids[ht1].stats[i].distinct;
                    if(distinct_old_h1>0&&distinct_diff>0){
                        transfer->tables_ids[ht1].stats[i].distinct=distinct_diff*(1-power(1-(distinct/distinct_old_h1),full_diff/distinct_diff));
                        transfer->tables_ids[ht1].stats[i].full=full;
                    }
                    else{transfer->tables_ids[ht1].stats[i].distinct=0;
                        transfer->tables_ids[ht1].stats[i].full=0;}

                }


            }

            for(j=0;j<master_table->tables[ht2].column_num;j++){///other columns on table 2
                if(i!=column2){
                    full_diff=transfer->tables_ids[ht2].stats[i].full;
                    distinct_diff=transfer->tables_ids[ht2].stats[i].distinct;
                    if(distinct_old_h1>0&&distinct_diff>0){
                        transfer->tables_ids[ht2].stats[i].distinct=distinct_diff*(1-power(1-(distinct/distinct_old_h2),full_diff/distinct_diff));
                        transfer->tables_ids[ht2].stats[i].full=full;}
                    else{transfer->tables_ids[ht1].stats[i].distinct=0;
                        transfer->tables_ids[ht1].stats[i].full=0;}
                }


            }






*/
        }
    }



}



uint64_t max_num(uint64_t a,uint64_t b){
    if(a>b){
        return a;
    }else {
        return b;
    }


}

uint64_t min_num(uint64_t a,uint64_t b){
    if(a<b){
        return a;
    }else {
        return b;
    }


}


void run_stats_joins(List_of_Tables* master_table,just_transfer* transfer,int prior) {
    int table1,table2,column1,column2,ht1,ht2,i,j,n;
    uint64_t lower,upper,stat_size,distinct,distinct_old_h1,distinct_old_h2,distinct_diff,full_old,full,full_diff,upper_old,lower_old,min,max;
    table1=transfer->priority1[prior].master_table1;
    column1=transfer->priority1[prior].col1;
    ht1=transfer->priority1[prior].here_table1;




    table2=transfer->priority1[prior].master_table2;
    column2=transfer->priority1[prior].col2;
    ht2=transfer->priority1[prior].here_table2;



//upper lower

    max=max_num(transfer->tables_ids[ht1].stats[column1].lower,transfer->tables_ids[ht2].stats[column2].lower);
    min=min_num(transfer->tables_ids[ht1].stats[column1].upper,transfer->tables_ids[ht2].stats[column2].upper);
    transfer->tables_ids[ht1].stats[column1].lower=max;
    transfer->tables_ids[ht2].stats[column2].lower=max;

    transfer->tables_ids[ht1].stats[column1].upper=min;
    transfer->tables_ids[ht2].stats[column2].upper=min;

//full

    n=min-max+1;
//full_old=transfer->tables_ids[ht1].stats[column1].full;
    full=(transfer->tables_ids[ht1].stats[column1].full*transfer->tables_ids[ht2].stats[column2].full)/n;
    transfer->tables_ids[ht1].stats[column1].full=full;
    transfer->tables_ids[ht2].stats[column2].full= full;
//distinct
    distinct_old_h1=transfer->tables_ids[ht1].stats[column1].distinct;
    distinct_old_h2=transfer->tables_ids[ht2].stats[column2].distinct;
    distinct=(transfer->tables_ids[ht1].stats[column1].distinct*transfer->tables_ids[ht2].stats[column2].distinct)/n;
//distinct=distinct*(1-power(1-(full/full_old),full_old/distinct));
    transfer->tables_ids[ht1].stats[column1].distinct=distinct;
    transfer->tables_ids[ht2].stats[column2].distinct=distinct;


    for(i=0;i<master_table->tables[table1].column_num;i++){///other columns on table 1
        if(i!=column1){
            full_diff=transfer->tables_ids[ht1].stats[i].full;
            distinct_diff=transfer->tables_ids[ht1].stats[i].distinct;
            if(distinct_old_h1>0&&distinct_diff>0){
                transfer->tables_ids[ht1].stats[i].distinct=distinct_diff*(1-pow(1-((double)distinct/distinct_old_h1),(double)full_diff/distinct_diff));
                transfer->tables_ids[ht1].stats[i].full=full;
            }
            else{transfer->tables_ids[ht1].stats[i].distinct=0;
                transfer->tables_ids[ht1].stats[i].full=0;}

        }


    }

    for(i=0;i<master_table->tables[table2].column_num;i++){///other columns on table 2
        if(i!=column2){
            full_diff=transfer->tables_ids[ht2].stats[i].full;
            distinct_diff=transfer->tables_ids[ht2].stats[i].distinct;
            if(distinct_old_h2>0&&distinct_diff>0){
                transfer->tables_ids[ht2].stats[i].distinct=distinct_diff*(1-pow(1-((double)distinct/distinct_old_h2),(double)full_diff/distinct_diff));
                transfer->tables_ids[ht2].stats[i].full=full;}
            else{
                transfer->tables_ids[ht2].stats[i].distinct=0;
                transfer->tables_ids[ht2].stats[i].full=0;}
        }


    }



}



////////////

void test_run_stats_joins(List_of_Tables* master_table,just_transfer* transfer,int priority_number) {
    int table1, table2, column1, column2, ht1, ht2, i, j;
    uint64_t  full,  min, max,n;


    for (i = 0; i < priority_number; i++) {

        if (transfer->priority1[i].type == 5) {
            table1 = transfer->priority1[i].master_table1;
            column1 = transfer->priority1[i].col1;
            ht1 = transfer->priority1[i].here_table1;



            table2 = transfer->priority1[i].master_table2;
            column2 = transfer->priority1[i].col2;
            ht2 = transfer->priority1[i].here_table2;






//upper lower

            max = max_num(transfer->tables_ids[ht1].stats[column1].lower, transfer->tables_ids[ht2].stats[column2].lower);

            min = min_num(transfer->tables_ids[ht1].stats[column1].upper, transfer->tables_ids[ht2].stats[column2].upper);

          //  transfer->tables_ids[ht1].stats[column1].lower = max;
          //  transfer->tables_ids[ht2].stats[column2].lower = max;

           // transfer->tables_ids[ht1].stats[column1].upper = min;
          //  transfer->tables_ids[ht2].stats[column2].upper = min;

//full

            n = min - max + 1;
//full_old=transfer->tables_ids[ht1].stats[column1].full;
            full = (transfer->tables_ids[ht1].stats[column1].full * transfer->tables_ids[ht2].stats[column2].full) / n;
            transfer->priority1[i].size= full;
        }

    }
}









void* big_thread(void* kk){
    int i;
    just_transfer * test;
    middle* bad_word;

    pthread_mutex_lock(&mutexbig);
    int self = curr++;
    pthread_t tid = pthread_self();

    jobqueue_big* Queue;
    Queue=(jobqueue_big*)kk;
    // printf("got \"%02x\"\n", (unsigned)tid);
    // numn++;
    Queue->thread_num++;

    if(Queue->thread_num==big_threads) {
        //  printf("%d awaken \n", Queue->thread_num);
        pthread_cond_broadcast(&condd);
        pthread_mutex_unlock(&mutexbig);

    }

    while(Queue->thread_num<big_threads) {
        // printf("got \"%d\"\n", self);

        pthread_cond_wait(&condd, &mutexbig);
    }
    pthread_mutex_unlock(&mutexbig);


    // printf("got more \"%d\"\n", self);

    //if(Queue->thread==Queue->thread_num)
    //  pthread_cond_signal(&cond);

    while(1) {
        pthread_mutex_lock (&mutexsumbig);
        i = Queue->used;
        Queue->used++;
        pthread_mutex_unlock (&mutexsumbig);
        if (i< Queue->size) {

            test = analise(Queue->jobs[i].line, Queue->jobs[i].master_table);

            bad_word = run_filters(Queue->jobs[i].master_table, test);

            Queue->jobs[i].res= athrisma(bad_word, test, Queue->jobs[i].master_table,print_in_line);

        } else {
            break;
        }
    }

    pthread_cond_signal(&condd);
    pthread_mutex_unlock(&mutexbig);
    pthread_exit(NULL);
}


//failed job schedjuler
/*

void* thread_all(void* kk){
    main_struct* Queues;
    Queues=(main_struct*)kk;
    int i,j,k,l;
    i=0;
    int what_is;
    just_transfer * test;
    middle* bad_word;
    job_join* jobjoin=NULL;
    job_sort* jobsort=NULL;
    what_is=0;
    Queues->tid= pthread_self();

    Queues->start_together++;
    pthread_mutex_lock(&mutexbigtotal);
    if(Queues->start_together==total_threads) {
        //  printf("%d awaken \n", Queue->thread_num);
        pthread_cond_broadcast(&cond_total);
        pthread_mutex_unlock(&mutexbigtotal);

    }

    while(Queues->start_together<total_threads) {
        // printf("got \"%d\"\n", self);

        pthread_cond_wait(&cond_total, &mutexbigtotal);
    }
    pthread_mutex_unlock(&mutexbigtotal);



    while(1){
        what_is=0;
        pthread_mutex_lock(&mutexlocki);//////////////
        if(Queues->big_jobs<2){

            Queues->big_jobs++;
            what_is=1;
            i=Queues->used;
            Queues->used++;
        }
        if(Queues->sort_jobs>-1&&(what_is==0)){
            Queues->sort_jobs--;
            jobsort=Queues->sort_queue->first;
            Queues->sort_queue->first=Queues->sort_queue->first->next;
            what_is=2;
        }
        if(Queues->join_jobs>-1&&(what_is==0)){
            Queues->join_jobs--;
            jobjoin=Queues->join_queue->first;
            Queues->join_queue->first=Queues->join_queue->first->next;
            what_is=3;
        }

        pthread_mutex_unlock(&mutexlocki);/////////////////

        if(what_is==1){
            printf(" got %d, %s\n",i,Queues->big_queue[i].line);
            test = analise(Queues->big_queue[i].line, Queues->big_queue[i].master_table);

            bad_word = run_filters(Queues->big_queue[i].master_table, test,Queues);

            athrisma(bad_word, test, Queues->big_queue[i].master_table);

            Queues->big_jobs--;
            if(i==Queues->totaljobs){
                Queues->done=1;
            }

        }

        if(what_is==2){

            radix_Sort2(jobsort->table,jobsort->time,jobsort->use_this,jobsort->from,jobsort->to);
            //Queues->sort_jobs--;

            if(jobsort->is_last==1){
                pthread_cond_signal(&Queues->cond1);

            }
            free(jobsort);
            jobsort=NULL;
        }


        if(what_is==3){


            //   Queues->join_jobs--;
            free(jobjoin);
            jobjoin=NULL;

        }

        if(Queues->done==1){
            break;
        }
    }
}


void* add_big_job(main_struct* main,List_of_Tables* master_table,char* line,int size){


    main->big_queue[ main->big_jobs].line=(char*)malloc(sizeof(char)*size+1);
    strcpy(main->big_queue[ main->big_jobs].line, line);

    main->big_queue[ main->big_jobs].master_table=master_table;
    //   main->big_queue[ main->big_jobs]=*temp;
    main->big_jobs++;


}


void* free_big_job(main_struct* main){
    int i;
    for(i=0;i<main->totaljobs;i++){
        free(main->big_queue[i].line);

    }
    free(main->big_queue);




}


job_sort* add_sort_job(main_struct* main,job_sort* temp){
    // job_sort* temp;



    if( main->sort_queue->first==NULL){
        main->sort_queue->last = temp;
        main->sort_queue->first = temp;
    }else{

        main->sort_queue->last->next=temp;
        main->sort_queue->last=temp;}
    main->sort_jobs++;
    main->sort_queue->used++;
    return temp;
}
*/










