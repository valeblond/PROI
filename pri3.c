#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

char trash[50];

int dyn_sala_id=0;
typedef struct
{
    int id;
    char number[6];
    int persons;
    char tech_inf[256];
} sala;
sala *sala_;

int dyn_wyklad_id=0;
typedef struct
{
    int id;
    char title[51];
    char start_time[6];
    char end_time[6];
    char date[11];
    int id_saly;
} wyklad;
wyklad *wyklad_;

char *encode_text(char *text, int i)
{
    char temp[9];
    char *encoded_data = malloc(sizeof(char) * (i+1));
    encoded_data[i] = '\0';
    int j;
    for(j=0; j<i; j++)
    {
        strncpy(temp,text+j*8,8);
        encoded_data[j] = strtol(temp, 0, 2);
    }
    return encoded_data;
}

void work_with_files()
{
    int way,i,persons,id_saly;
    char haslo_plik[81],start_time_plik[41],id_saly_plik[41],end_time_plik[41], date_plik[81],persons_plik[33],plik_name[16], haslo[11], number[6], tech_inf[256],title[51],start_time[6],end_time[6],date[11];
    haslo_plik[81] = '\0';
    start_time_plik[41] = '\0';
    end_time_plik[41] = '\0';
    id_saly_plik[41] = '\0';
    date_plik[81] = '\0';
    persons_plik[33]= '\0';
    char space[] = "00100000";
    char *rozsz, *enc_data, *person_elem;
     char *space_check = malloc(sizeof(char) * 9);
    FILE *plik;
    printf("Wpisz nazwe oraz rozszerzenie pliku(max 15sym.)");
    fgets(trash,50,stdin);
    fgets(plik_name, 16, stdin);
    if ( plik_name[strlen(plik_name)- 1] == '\n') plik_name[strlen(plik_name) - 1]='\0';
    rozsz = strstr(plik_name,".enc");

    printf("Co trzeba zrobic:\n 1.Odczytaj\n 2.Zapisz\n 0.Wroc do menu\n");
    scanf("%d",&way);
                    switch(way)
                    {
                        case 1:
                                if(rozsz != NULL)
                                {
                                    printf("Wpisz haslo: ");
                                    fgets(trash,50,stdin);
                                    fgets(haslo, 11, stdin);
                                    if ( haslo[strlen(haslo)- 1] == '\n') haslo[strlen(haslo) - 1]='\0';
                                    plik = fopen(plik_name, "rb+");
                                    if(!plik)
                                    {
                                        printf("Nie ma takiego pliku\n");
                                        work_with_files();
                                        break;
                                    }else
                                        {
                                            fread(haslo_plik, sizeof(char), 80, plik);
                                            printf("%s",haslo);
                                            enc_data = encode_text(haslo_plik, 10);
                                            if(!strcmp(haslo, enc_data))
                                                {
                                                    printf("\nPlik jest otworzony\n");
                                                    free(enc_data);
                                                }
                                                else
                                                    {
                                                        printf("Zle haslo!\n");
                                                        free(enc_data);
                                                        work_with_files();
                                                        break;
                                                    }
                                        }

                                }else
                                {
                                    plik = fopen(plik_name, "r");
                                    if(!plik)
                                    {
                                        printf("Nie ma takiego pliku\n");
                                        work_with_files();
                                    }else{printf("Plik jest otworzony\n");}
                                }
                                printf("Plik zawiera informacje:\n 1.O salach\n 2.O wykladach\n");
                                scanf("%d",&way);
                                switch(way)
                                {
                                    case 1:
                                        if(rozsz != NULL)
                                        {
                                            space_check[0] = '\0';
                                            fread(space_check, sizeof(char), 8, plik);
                                            if(!strcmp(space_check, space))
                                            {
                                                 space_check[0] = '\0';
                                                fread(space_check, sizeof(char), 8, plik);
                                                while( !feof(plik) ){

                                                for(i=0; strcmp(space, space_check)!= 0; i++)
                                                {
                                                    enc_data = encode_text(space_check, 1);
                                                    number[i] = *enc_data;
                                                    free(enc_data);
                                                    space_check[0] = '\0';
                                                    fread(space_check, sizeof(char), 8, plik);

                                                }

                                                space_check[0] = '\0';
                                                fread(persons_plik, sizeof(char), 32, plik);
                                                enc_data = encode_text(persons_plik, 4);
                                                persons = atoi(enc_data);
                                                free(enc_data);

                                                space_check[0] = '\0';
                                                fread(space_check, sizeof(char), 8, plik);
                                                 space_check[0] = '\0';
                                                fread(space_check, sizeof(char), 8, plik);

                                                for(i=0; strcmp(space, space_check)!= 0; i++)
                                                {
                                                    enc_data = encode_text(space_check, 1);
                                                    tech_inf[i] = *enc_data;
                                                    free(enc_data);
                                                    space_check[0] = '\0';
                                                    tech_inf[i+1] = '\0';
                                                    printf("\n%c",  tech_inf[i]);
                                                    fread(space_check, sizeof(char), 8, plik);

                                                }
                                                space_check[0] = '\0';
                                                sala_ = (sala*)realloc(sala_,(dyn_sala_id+1)*sizeof(sala));
                                                sala_[dyn_sala_id].id = (dyn_sala_id+1);
                                                strncpy(sala_[dyn_sala_id].number, number, 6);
                                                sala_[dyn_sala_id].persons = persons;
                                                strncpy(sala_[dyn_sala_id].tech_inf, tech_inf, 256);
                                                printf("\nSala zostala dodana!\n\n");
                                                dyn_sala_id++;
                                                space_check[0] = '\0';
                                                fread(space_check, sizeof(char), 8, plik);
                                                }
                                                fclose(plik);
                                                work_with_files();

                                            }
                                            break;
                                        }
                                        while (fscanf (plik, "%s%d%s", number, &(persons), tech_inf) != EOF)
                                        {
                                            printf("%s %d %s\n", number, persons, tech_inf);
                                            sala_ = (sala*)realloc(sala_,(dyn_sala_id+1)*sizeof(sala));
                                            sala_[dyn_sala_id].id = (dyn_sala_id+1);
                                            strncpy(sala_[dyn_sala_id].number, number, 6);
                                            sala_[dyn_sala_id].persons = persons;
                                            strncpy(sala_[dyn_sala_id].tech_inf, tech_inf, 256);
                                            printf("\nSala zostala dodana!\n\n");
                                            dyn_sala_id++;
                                            i++;
                                        }
                                        fclose(plik);
                                         work_with_files();
                                        break;
                                    case 2:
                                    if(rozsz != NULL)
                                        {
                                            space_check[0] = '\0';
                                            fread(space_check, sizeof(char), 8, plik);
                                            if(!strcmp(space_check, space))
                                            {
                                                 space_check[0] = '\0';
                                                fread(space_check, sizeof(char), 8, plik);
                                                while( !feof(plik) ){

                                                for(i=0; strcmp(space, space_check)!= 0; i++)
                                                {
                                                    enc_data = encode_text(space_check, 1);
                                                    title[i] = *enc_data;
                                                    free(enc_data);
                                                    space_check[0] = '\0';
                                                    fread(space_check, sizeof(char), 8, plik);

                                                }

                                                space_check[0] = '\0';
                                                fread(start_time_plik, sizeof(char), 40, plik);
                                                enc_data = encode_text(start_time_plik, 5);
                                                strcpy(start_time, enc_data);
                                                free(enc_data);

                                                space_check[0] = '\0';
                                                fread(space_check, sizeof(char), 8, plik);

                                                space_check[0] = '\0';
                                                fread(end_time_plik, sizeof(char), 40, plik);
                                                enc_data = encode_text(end_time_plik, 5);
                                                strcpy(end_time, enc_data);
                                                free(enc_data);

                                                space_check[0] = '\0';
                                                fread(space_check, sizeof(char), 8, plik);

                                                space_check[0] = '\0';
                                                fread(date_plik, sizeof(char), 80, plik);
                                                enc_data = encode_text(date_plik, 10);
                                                strcpy(date, enc_data);
                                                free(enc_data);

                                                space_check[0] = '\0';
                                                fread(space_check, sizeof(char), 8, plik);

                                                space_check[0] = '\0';
                                                fread(id_saly_plik, sizeof(char), 40, plik);
                                                enc_data = encode_text(id_saly_plik, 5);
                                                id_saly = atoi(enc_data);
                                                free(enc_data);

                                                space_check[0] = '\0';
                                                fread(space_check, sizeof(char), 8, plik);



                                                space_check[0] = '\0';

                                                wyklad_ = (wyklad*)realloc(wyklad_,(dyn_wyklad_id+1)*sizeof(wyklad));
                                                wyklad_[dyn_wyklad_id].id = (dyn_wyklad_id+1);
                                                strncpy(wyklad_[dyn_wyklad_id].title, title, 51);
                                                strncpy(wyklad_[dyn_wyklad_id].end_time, end_time, 6);
                                                strncpy(wyklad_[dyn_wyklad_id].start_time, start_time, 6);
                                                strncpy(wyklad_[dyn_wyklad_id].date, date, 11);
                                                wyklad_[dyn_wyklad_id].id_saly = id_saly;
                                                dyn_wyklad_id++;
                                                printf("\nWyklad zostal dodany do bazy!\n\n");
                                                space_check[0] = '\0';
                                                fread(space_check, sizeof(char), 8, plik);
                                                }
                                                fclose(plik);
                                                work_with_files();

                                            }
                                            break;
                                        }
                                        while (fscanf (plik, "%s%s%s%s%d", title, start_time, end_time, date, &(id_saly)) != EOF)
                                        {
                                            printf("%s %s %s %s %d\n", title, start_time, end_time, date, id_saly);
                                            wyklad_ = (wyklad*)realloc(wyklad_,(dyn_wyklad_id+1)*sizeof(wyklad));
                                            wyklad_[dyn_wyklad_id].id = (dyn_wyklad_id+1);
                                            strncpy(wyklad_[dyn_wyklad_id].title, title, 51);
                                            strncpy(wyklad_[dyn_wyklad_id].end_time, end_time, 6);
                                            strncpy(wyklad_[dyn_wyklad_id].start_time, start_time, 6);
                                            strncpy(wyklad_[dyn_wyklad_id].date, date, 11);
                                            wyklad_[dyn_wyklad_id].id_saly = id_saly;
                                            dyn_wyklad_id++;
                                            printf("\nWyklad zostal dodany do bazy!\n\n");
                                            i++;
                                        }
                                        fclose(plik);
                                        work_with_files();
                                        break;
                                    default:
                                        printf("Blad danych sprobuj ponownie\n");
                                        work_with_files();
                                        break;
                                }

                            break;
                        case 2:
                                if(rozsz != NULL)
                                {
                                    printf("Wpisz haslo: ");
                                    fgets(haslo, 11, stdin);
                                    plik = fopen(plik_name, "ab+");
                                    if(!plik)
                                    {
                                        printf("Nie ma takiego pliku\n");
                                        work_with_files();
                                    }else{printf("Plik jest otworzony\n");}
                                }else
                                {
                                    plik = fopen(plik_name, "a");
                                    if(!plik)
                                    {
                                        printf("Nie ma takiego pliku\n");
                                        work_with_files();
                                    }else{printf("Plik jest otworzony\n");}
                                }
                                printf("Jaka informacje chcesz skopiowac?:\n 1.O salach\n 2.O wykladach\n");
                                scanf("%d",&way);
                                switch(way)
                                {
                                case 1:
                                    for(i=0; i<dyn_sala_id; i++)
                                    {
                                        if(sala_[i].id != 0)
                                        {
                                            fprintf(plik, "%s %d %s\n", sala_[i].number, sala_[i].persons, sala_[i].tech_inf);
                                        }
                                    }
                                    printf("Dane zapisane do pliku!\n");
                                    fclose(plik);
                                    work_with_files();
                                    break;
                                case 2:
                                    for(i=0; i<dyn_wyklad_id; i++)
                                    {
                                        if(wyklad_[i].id != 0)
                                        {
                                            fprintf(plik, "%s %s %s %s %d\n", wyklad_[i].title, wyklad_[i].start_time, wyklad_[i].end_time, wyklad_[i].date, wyklad_[i].id_saly);
                                        }
                                    }
                                    printf("Dane zapisane do pliku!\n");
                                    fclose(plik);
                                    work_with_files();
                                    break;
                                default:
                                    printf("Blad danych sprobuj ponownie\n");
                                    work_with_files();
                                    break;
                                }
                            break;
                        case 0:
                            main();
                            break;
                        default:
                            printf("Blad danych sprobuj ponownie\n");
                            work_with_files();
                            break;
                    }
}

int is_free()
{
    char date[11],start_time[6],end_time[6];
    int i=0,s=0,free_status=0,start_time_result=0,end_time_result=0,start_time_result2=0,end_time_result2=0;
    fflush(stdin);

    printf("Wprowadz date: ");
    scanf("%s",date);
    if(strlen(date)!=10 || strstr(date,"-")==NULL)
    {
        printf(" Data sklada sie z 10 znakow oraz piaty musi byc '-'!\n");
        fflush(stdin);
        is_free();
        return 0;
    }

    fflush(stdin);

    printf("Wprowadz czas rozpoczecia: ");
    scanf("%s",start_time);
    if(strlen(start_time)!=5 || strstr(start_time,":")==NULL)
    {
        printf("Czas sklada sie z 5 znakow oraz trzeci musi byc ':'!\n");
        fflush(stdin);
        is_free();
        return 0;
    }
    fflush(stdin);

    printf("Wprowadz czas zakonczenia: ");
    scanf("%s", end_time);
    if(strlen(end_time)!=5 || strstr(end_time,":")==NULL)
    {
        printf("Czas sklada sie z 5 znakow oraz trzeci musi byc ':'!\n");
        fflush(stdin);
        is_free();
        return 0;
    }
    fflush(stdin);
    for(i=0; i<dyn_sala_id; i++)
    {
        free_status = 1;
        for(s=0; s<dyn_wyklad_id; s++)
        {
            if(wyklad_[s].id_saly == i+1)
            {
              if(strcmp(wyklad_[s].date, date)!=0 && wyklad_[s].id_saly!=0)
              {
                free_status = 1;
              }
              else
              {
                start_time_result = strcmp(wyklad_[s].start_time, start_time);
                end_time_result = strcmp(wyklad_[s].start_time, end_time);
                start_time_result2 = strcmp(wyklad_[s].end_time, start_time);
                end_time_result2 = strcmp(wyklad_[s].end_time, end_time);
                if(((start_time_result>0 && end_time_result>=0)||(start_time_result2<=0 && end_time_result2<0)) && wyklad_[s].id_saly!=0)
                {
                    free_status = 1;
                }else
                {
                    free_status = 0;
                    break;
                }
              }
            }
         }
         printf("%d",free_status);
         if(free_status == 1)
         {
            printf(" #%d %s ilosc miejsc:%d wyposazenie: %s\n", sala_[i].id, sala_[i].number, sala_[i].persons, sala_[i].tech_inf);
         }
    }
    main();
    return 0;
}

int wyklad_search()
{
    fflush(stdin);
    int way,i=0,j=0,c=0;

    wyklad wyklad_sorted_[dyn_wyklad_id];


    printf("Wybierz parametr sortowania\n 1.Nazwa wykladu\n 2.Godzina rozpoczecia\n 3.Godzina zakonczenia\n 4.Data\n 0.Wroc do menu\n");
    scanf("%d", &way);
    fflush(stdin);
    switch(way)
    {
        case 1:
            for(i=0; i<dyn_wyklad_id; i++)
        {
            wyklad_sorted_[i]= wyklad_[i];
        }
        for(i=0; i<dyn_wyklad_id-1; i++)
            {
                for(j=0; j<(dyn_wyklad_id-1)-i; j++)
                {
                    if(strcmp(wyklad_sorted_[j].title, wyklad_sorted_[j+1].title)<0)
                    {
                        int tmp = (wyklad_sorted_[j].id - 1);
                        wyklad_sorted_[j] = wyklad_sorted_[j+1];
                        wyklad_sorted_[j+1] = wyklad_[tmp];
                    }
                }
            }
        for(c=0; c<dyn_wyklad_id; c++)
            {
                if(wyklad_sorted_[c].id!=0)
                {
                    printf("\n#%d %s\n Godziny:%.5s - %.5s\n Data: %s\n Sala:%d\n", wyklad_sorted_[c].id, wyklad_sorted_[c].title, wyklad_sorted_[c].start_time, wyklad_sorted_[c].end_time, wyklad_sorted_[c].date, wyklad_sorted_[c].id_saly);
                }
            }
        wyklad_search();
            break;

        case 2:
            for(i=0; i<dyn_wyklad_id; i++)
        {
            wyklad_sorted_[i]= wyklad_[i];
        }

        for(i=0; i<dyn_wyklad_id-1; i++)
            {
                for(j=0; j<(dyn_wyklad_id-1)-i; j++)
                {
                    if(strcmp(wyklad_sorted_[j].start_time, wyklad_sorted_[j+1].start_time)<0)
                    {
                        int tmp = (wyklad_sorted_[j].id - 1);
                        wyklad_sorted_[j] = wyklad_sorted_[j+1];
                        wyklad_sorted_[j+1] = wyklad_[tmp];
                    }
                }
            }
        for(c=0; c<dyn_wyklad_id; c++)
            {
            if(wyklad_sorted_[c].id!=0)
                {
                    printf("\n#%d %s\n Godziny:%.5s - %.5s\n Data: %s\n Sala:%d\n", wyklad_sorted_[c].id, wyklad_sorted_[c].title, wyklad_sorted_[c].start_time, wyklad_sorted_[c].end_time, wyklad_sorted_[c].date, wyklad_sorted_[c].id_saly);
                }
            }
        wyklad_search();
            break;

        case 3:
            for(i=0; i<dyn_wyklad_id; i++)
        {
            wyklad_sorted_[i]= wyklad_[i];
        }
        for(i=0; i<dyn_wyklad_id-1; i++)
            {
                for(j=0; j<(dyn_wyklad_id-1)-i; j++)
                {
                    if(strcmp(wyklad_sorted_[j].end_time, wyklad_sorted_[j+1].end_time)<0)
                    {
                        int tmp = (wyklad_sorted_[j].id - 1);
                        wyklad_sorted_[j] = wyklad_sorted_[j+1];
                        wyklad_sorted_[j+1] = wyklad_[tmp];
                    }
                }
            }
        for(c=0; c<dyn_wyklad_id; c++)
            {
                if(wyklad_sorted_[c].id!=0)
                {
                    printf("\n#%d %s\n Godziny:%.5s - %.5s\n Data: %s\n Sala:%d\n", wyklad_sorted_[c].id, wyklad_sorted_[c].title, wyklad_sorted_[c].start_time, wyklad_sorted_[c].end_time, wyklad_sorted_[c].date, wyklad_sorted_[c].id_saly);
                }
            }
        wyklad_search();
            break;

        case 4:
            for(i=0; i<dyn_wyklad_id; i++)
        {
            wyklad_sorted_[i]= wyklad_[i];
        }
        for(i=0; i<dyn_wyklad_id-1; i++)
            {
                for(j=0; j<(dyn_wyklad_id-1)-i; j++)
                {
                    if(strcmp(wyklad_sorted_[j].date, wyklad_sorted_[j+1].date)<0)
                    {
                        int tmp = (wyklad_sorted_[j].id - 1);
                        wyklad_sorted_[j] = wyklad_sorted_[j+1];
                        wyklad_sorted_[j+1] = wyklad_[tmp];
                    }
                }
            }
        for(c=0; c<dyn_wyklad_id; c++)
            {
                if(wyklad_sorted_[c].id!=0)
                {
                    printf("\n#%d %s\n Godziny:%.5s - %.5s\n Data: %s\n Sala:%d\n", wyklad_sorted_[c].id, wyklad_sorted_[c].title, wyklad_sorted_[c].start_time, wyklad_sorted_[c].end_time, wyklad_sorted_[c].date, wyklad_sorted_[c].id_saly);
                }
            }
        wyklad_search();
            break;
        case 0:
            main();
            break;
        default:
            printf("Blad danych sprobuj ponownie\n");
            wyklad_search();
            break;

    }
    return 0;

}

int sala_search()
{
    int way,i=0,j=0,c=0,tmp=0;
    sala sala_sorted_[dyn_sala_id];

    printf("Wybierz parametr sortowania\n 1.Ilosc miejsc sali\n 0.Wroc do menu\n");
    scanf("%d", &way);
    fflush(stdin);
    switch(way)
    {
    case 1:
        for(i=0; i<dyn_sala_id; i++)
        {
            sala_sorted_[i]= sala_[i];
        }

        for(i=0; i<(dyn_sala_id-1); i++)
            {
                for(j=0; j<(dyn_sala_id-1)-i; j++)
                {
                    if(sala_sorted_[j].persons>sala_sorted_[j+1].persons)
                    {
                        tmp = (sala_sorted_[j].id - 1);
                        sala_sorted_[j] = sala_sorted_[j+1];
                        sala_sorted_[j+1] = sala_[tmp];
                    }
                }
            }
            for(c=0; c<dyn_sala_id; c++)
            {
                if(sala_sorted_[c].id!=0)
                {
                    printf("#%d %s ilosc miejsc:%d wyposazenie: %s\n", sala_sorted_[c].id, sala_sorted_[c].number, sala_sorted_[c].persons, sala_sorted_[c].tech_inf);
                }
            }
        sala_search();
        break;
    case 0:
        main();
        break;
    default:
        printf("Blad danych sprobuj ponownie\n");
        sala_search();
        break;

    }
    return 0;
}

int mod_wyklad()
{
    int id,way,id_saly;
    char start_time[6],end_time[6],date[11],title[6];
    fflush(stdin);
    printf("Wprowadz id wykladu: ");
    scanf("%d", &id);
    id = id-1;
    if(wyklad_[id].id==0)
        {
            printf("Nie ma takiego wykladu\n");
            mod_sali();
            return 0;
        }
    fflush(stdin);
    printf("Co chcesz modyfikowac?\n 1.Nazwa wykladu\n 2.Zmienic sale\n 3.Czas rozpoczeca/zakonczenia\n 4.Data prowadzenia\n 0.Wroc do menu\n");
    scanf("%d", &way);
    fflush(stdin);
    switch(way)
    {
        case 1:
            printf("Wprowadz nowa nazwe wykladu #%d\n", id+1);
            fgets(trash,50,stdin);
            fgets(title,51,stdin);
            if(strlen(title)>50)
            {
                printf("Nazwa musi byc nie wiecej, niz 50 znakow!\n");
                fflush(stdin);
                mod_wyklad();
            }
            fflush(stdin);
            strncpy(wyklad_[id].title, title, 50);
            printf("\nNazwa zostala zmieniona!\n\n");

            mod_wyklad();
            break;
        case 2:
            printf("Wprowadz id nowej sali\n");
            scanf("%d", &id_saly);
            wyklad_[id].id_saly = id_saly;
            fflush(stdin);
            printf("\nSala zostala zmieniona!\n\n");

            mod_wyklad();
            break;
        case 3:
            printf("Najperw wprowadz nowe czasy rozpoczecia(np. 00:00)\n");
            scanf("%s",start_time);
            if(strlen(start_time)!=5 || strstr(start_time,":")==NULL)
            {
                printf("Czas sklada sie z 5 znakow oraz trzeci musi byc ':'!\n");
                fflush(stdin);
                mod_wyklad();
            }
            fflush(stdin);
            strncpy(wyklad_[id].start_time, start_time, 5);
            printf("Potem zakonczenia (np. 00:00)\n");
            scanf("%s",end_time);
            if(strlen(end_time)!=5 || strstr(end_time,":")==NULL)
            {
                printf("Czas sklada sie z 5 znakow oraz trzeci musi byc ':'!\n");
                fflush(stdin);
                mod_wyklad();
            }
            fflush(stdin);
            strncpy(wyklad_[id].end_time, end_time, 5);
            printf("\nCzas zostal zmieniony!\n\n");

            mod_wyklad();
            break;
        case 4:
            printf("Wprowadz nowa date wykladu #%d(np. 2000-12-31)\n", id+1);
            scanf("%s",date);
            if(strlen(date)!=10 || strstr(date,"-")==NULL)
            {
                printf(" Data sklada sie z 10 znakow oraz piaty musi byc '-'!\n");
                fflush(stdin);
                mod_wyklad();
            }
            fflush(stdin);
            strncpy(wyklad_[id].date, date, 10);
            printf("\nData zostala zmieniona!\n\n");

            mod_wyklad();
            break;
        case 0:
            main();
            break;
        default:
            printf("Blad danych sprobuj ponownie\n");
            mod_wyklad();
            break;

    }
    return 0;
}

int mod_sali()
{
    int id,way,new_persons;
    char new_number[5],new_tech_inf[255];
    fflush(stdin);
    fgets(trash,50,stdin);
    printf("Wprowadz id sali: ");
    scanf("%d", &id);
    id = id-1;
    if(sala_[id].id==0)
        {
            printf("Nie ma takiej sali\n");
            mod_sali();
            return 0;
        }
    fflush(stdin);
    printf("Co chcesz modyfikowac?\n 1.Nazwa sali\n 2.Ilosc miejsc\n 3.Info o wyposazeniu\n 0.Wroc do menu\n");
    scanf("%d", &way);
    fflush(stdin);
    switch(way)
    {
        case 1:
            printf("Wprowadz nowa nazwe sali #%d\n", id+1);
            scanf("%s",new_number);
            if(strlen(new_number)>5)
            {
                printf("Numer musi byc nie wiecej, niz 5 znakow!\n");
                fflush(stdin);
                mod_sali();
            }
            fflush(stdin);
            strncpy(sala_[id].number, new_number, 5);
            printf("\nNazwa zostala zmieniona!\n\n");

            mod_sali();
            break;
        case 2:
            printf("Wprowadz nowa ilosc miejsc sali(max. 1000 osob) #%d\n", id+1);
            scanf("%d", &new_persons);
            if(new_persons==0 || new_persons>1000)
            {
                printf("Nie wolno wprowadzic litery! \n");
                fflush(stdin);
                mod_sali();
            }
            sala_[id].persons = new_persons;
            fflush(stdin);
            printf("\nIlosc miejsc zostala zmieniona!\n\n");

            mod_sali();
            break;
        case 3:
            printf("Wprowadz nowe wyposazenie sali #%d\n", id+1);
            fflush(stdin);
            fgets(trash,50,stdin);
            fgets(new_tech_inf,255,stdin);
            if(strlen(new_tech_inf)>255)
            {
                printf("Info musi byc nie wiecej, niz 255 znakow!\n");
                fflush(stdin);
                mod_sali();
            }
            fflush(stdin);
            strncpy(sala_[id].tech_inf, new_tech_inf, 255);
            printf("\nWyposarzenie zostalo zmienione!\n\n");

            mod_sali();
            break;
        case 0:
            main();
            break;
        default:
            printf("Blad danych sprobuj ponownie\n");
            mod_sali();
            break;

    }
    return 0;
}

int unset_wyklad()
{
    int id;
    printf("Wprowadz id wykladu: ");
    scanf("%d", &id);
    wyklad_[(id-1)].id = 0;
    fflush(stdin);
    printf("\nWyklad usunienty!\n\n");
    main();
    return 0;
}

int unset_saly()
{
    int id;
    printf("Wprowadz id sali: ");
    scanf("%d", &id);
    sala_[(id-1)].id = 0;
    fflush(stdin);
    printf("\nSala usunienta!\n\n");
    main();
    return 0;
}

int show_wyklady()
{
    int i=0,j=1;
    while(i<dyn_wyklad_id)
        {
            if(wyklad_[i].id!=0)
            {
                printf("\n%d. #%d %s\n Godziny:%s - %s\n Data: %s\n Sala:%d\n", j, wyklad_[i].id, wyklad_[i].title, wyklad_[i].start_time, wyklad_[i].end_time, wyklad_[i].date, wyklad_[i].id_saly);
                i+=1;
                j+=1;
            }else{i+=1;}
        }
        main();
        return 0;
}

int show_saly()
{
    int i=0,j=1;
    while(i<dyn_sala_id)
        {
            if(sala_[i].id!=0)
            {
                printf("%d. #%d %s ilosc miejsc:%d wyposazenie: %s\n", j, sala_[i].id, sala_[i].number, sala_[i].persons, sala_[i].tech_inf);
                i+=1;
                j+=1;
            }else{i+=1;}
        }
        main();
        return 0;
}

int add_wyklad()
{
    int id_saly,id_count=1;
    fgets(trash,50,stdin);
    char title[51], start_time[6], end_time[6], date[11];
    fflush(stdin);

    wyklad_ = (wyklad*)realloc(wyklad_,(dyn_wyklad_id+1)*sizeof(wyklad));

    printf("\nWpisz nazwe wykladu(max. 50 znakow): ");
    fgets(title,51,stdin);
    if(strlen(title)>50)
    {
        printf("Nazwa musi byc nie wiecej, niz 50 znakow!\n");
        fflush(stdin);
        add_wyklad();
        return 0;
    }
    fflush(stdin);
    printf("\nWpisz godzine rozpoczecia wykladu (np. 00:00): ");
    scanf("%s",start_time);
    if(strlen(start_time)!=5 || strstr(start_time,":")==NULL)
    {
        printf("Czas sklada sie z 5 znakow oraz trzeci musi byc ':'!\n");
        fflush(stdin);
        add_wyklad();
        return 0;
    }
    fflush(stdin);

    printf("\nWpisz godzine zakonczenia wykladu (np. 00:00): ");
    scanf("%s",end_time);
    if(strlen(end_time)!=5 || strstr(end_time,":")==NULL)
    {
        printf("Czas sklada sie z 5 znakow oraz trzeci musi byc ':'!\n");
        fflush(stdin);
        add_wyklad();
        return 0;
    }
    fflush(stdin);

    printf("\nWpisz kiedy odbedzie sie wyklad (np. 2000-12-31): ");
    scanf("%s",date);
    if(strlen(date)!=10 || strstr(date,"-")==NULL)
    {
        printf(" Data sklada sie z 10 znakow oraz piaty musi byc '-'!\n");
        fflush(stdin);
        add_wyklad();
        return 0;
    }
    fflush(stdin);

    printf("\nWpisz id sali, w ktorej odbedzie sie wyklad: ");
    scanf("%d", &id_saly);
    fflush(stdin);

    wyklad_[dyn_wyklad_id].id = (dyn_wyklad_id+1);
    strncpy(wyklad_[dyn_wyklad_id].title, title, 51);
    strncpy(wyklad_[dyn_wyklad_id].end_time, end_time, 6);
    strncpy(wyklad_[dyn_wyklad_id].start_time, start_time, 6);
    strncpy(wyklad_[dyn_wyklad_id].date, date, 11);
    wyklad_[dyn_wyklad_id].id_saly = id_saly;
    dyn_wyklad_id++;
    printf("\nWyklad zostal dodany do bazy!\n\n");
    main();
    return 0;
}

int add_sala()
{
    int persons;
    char number[6], tech_inf[256];
    fflush(stdin);
    fgets(trash,50,stdin);

    sala_ = (sala*)realloc(sala_,(dyn_sala_id+1)*sizeof(sala));
    printf("Wpisz numer sali(max. 5 znakow): ");
    fgets(number,6,stdin);
    if(strlen(number)>5)
    {
        printf("Numer musi byc nie wiecej, niz 5 znakow!\n");
        fflush(stdin);
        add_sala();
        return 0;
    }
    fflush(stdin);

    printf("Wpisz ilosc osob, ktora wmiesci sie w sale(max. 1000 osob): ");
    scanf("%d", &persons);
    if(persons==0 || persons>1000)
    {
        printf("Nie wolno wprowadzic litery oraz max. ilosc osob to 1000\n");
        fflush(stdin);
        add_sala();
        return 0;
    }
    fflush(stdin);

    printf("Wpisz info o wyposazeniu sali(max. 255 znakow): ");
    fgets(trash,50,stdin);
    fgets(tech_inf,256,stdin);
    if(strlen(tech_inf)>255)
    {
        printf("Info musi byc nie wiecej, niz 255 znakow!\n");
        fflush(stdin);
        add_sala();
        return 0;
    }
    fflush(stdin);

    sala_[dyn_sala_id].id = (dyn_sala_id+1);
    strncpy(sala_[dyn_sala_id].number, number, 6);
    sala_[dyn_sala_id].persons = persons;
    strncpy(sala_[dyn_sala_id].tech_inf, tech_inf, 256);
    printf("\nSala zostala dodana!\n\n");
    dyn_sala_id++;
    main();
    return 0;
}

int main()
{
   int way = -1;
    fflush(stdin);
    printf("Co chcesz zrobic?\n 1.Katalog sal/wykladow\n 2.Dodac sale/wyklad\n 3.Usunac sale/wyklad\n 4.Modyfikowac sale/wyklad\n 5.Wyszukac sale/wyklad\n 6.Sprawdzic czy sala jest wolna\n 7.Pliki\n 0.Wyjsc\n");
    scanf("%d",&way);
    if(way<=7&&way>=0)
        {
            switch(way)
            {
                case 1:
                    printf("Katalog sal lub wykladow?\n 1.Sal\n 2.Wykladow\n");
                    scanf("%d",&way);
                    switch(way)
                    {
                        case 1:
                            show_saly();
                            break;
                        case 2:
                            show_wyklady();
                            break;
                        default:
                            printf("Blad danych sprobuj ponownie\n");
                            way = getchar();
                            main();
                            break;
                    }
                    break;
                case 2:
                    printf("Co chcesz dodac?\n 1.Sala\n 2.Wyklad\n");
                    scanf("%i",&way);
                    switch(way)
                    {
                        case 1:
                            add_sala();
                            break;
                        case 2:
                            add_wyklad();
                            break;
                        default:
                            printf("Blad danych sprobuj ponownie\n");
                            way = getchar();
                            main();
                            break;
                    }
                    break;
                case 3:
                    printf("Co chcesz usunac?\n 1.Sala\n 2.Wyklad\n");
                    scanf("%i",&way);
                    switch(way)
                    {
                        case 1:
                            unset_saly();
                            break;
                        case 2:
                            unset_wyklad();
                            break;
                        default:
                            printf("Blad danych sprobuj ponownie\n");
                            way = getchar();
                            main();
                            break;
                    }
                    break;
                case 4:
                    printf("Co chcesz modyficowac?\n 1.Sala\n 2.Wyklad\n");
                    scanf("%i",&way);
                    switch(way)
                    {
                        case 1:
                            mod_sali();
                            break;
                        case 2:
                            mod_wyklad();
                            break;
                        default:
                            printf("Blad danych sprobuj ponownie\n");
                            way = getchar();
                            main();
                            break;
                    }
                    break;
                case 5:
                    printf("Co chcesz wyszukac?\n 1.Sala\n 2.Wyklad\n");
                    scanf("%i",&way);
                    switch(way)
                    {
                        case 1:
                            sala_search();
                            break;
                        case 2:
                            wyklad_search();
                            break;
                        default:
                            printf("Blad danych sprobuj ponownie\n");
                            way = getchar();
                            main();
                            break;
                    }
                    break;
                case 6:
                    is_free();
                    break;
                case 7:
                    work_with_files();
                    break;
                case 0:
                    printf("Wylaczyc program?\n 1.Tak\n 2.Nie\n");
                    scanf("%i",&way);
                    switch(way)
                    {
                        case 1:
                            return 0;
                        case 2:
                            main();
                            break;
                        default:
                            printf("Blad danych sprobuj ponownie\n");
                            way = getchar();
                            main();
                            break;
                    }
                    break;
            }
        }else
        {
            printf("Blad danych sprobuj ponownie\n");
            way = getchar();
            main();
        }
    return 0;
}
