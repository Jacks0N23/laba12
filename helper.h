//
// Created by Alexandr on 30.05.2015.
//
#pragma hdrstop
#include <windows.h>
#include <stdio.h>
#include <conio.h>
//---------------------------------------------------------------------------


#pragma argsused

struct TComp {
    char Mark[31];
    struct {
        int D,M,Y;
    } DATE;

    int Room;
    char Name[31];

};

//---------------в верхнем регистре в Win1251
char *ANSIUpperCase(char *s, char *S){
    S = strcpy(S, s);
    char *ch=S;
    while (*ch) {
        if (*ch>='a' && *ch<='z' || *ch>='а' && *ch<='я') *ch= *ch-32;
        if (*ch =='ё') *ch='Ё';
        ch++;
    }
    return S;
}

//----------первая часть: создание двоичного из текстового
void CreateBinaryFile(int argc, char* argv[]){
    if (argc<3) {
        printf("Мало параметров\nPress any key");
        getch();
        return;
    }

    FILE *ft = fopen(argv[2], "rt");
    if (ft==NULL) {
        printf("Error: не удалось открыть файл с исходными данными %s\n", argv[2]);
        printf("Press any key ");	getch();
        return;
    }

    FILE *fb = fopen(argv[1], "wb");
    if (fb==NULL) {
        fclose(ft);
        printf("Error: не удалось создать двоичный файл %s\n", argv[1]);
        printf("Press any key"); getch();
        return;
    }

    TComp Comp; // либо struct TStud Stud;
    int i,kol=0;
    char s[6];
    fscanf(ft,"%s",s); i=atoi(s);
    while (kol<i){

        fscanf(ft,"%10s",Comp.Mark);
        fscanf(ft,"%s", s); Comp.DATE.D=atoi(s);
        fscanf(ft,"%s", s); Comp.DATE.M=atoi(s);
        fscanf(ft,"%s", s); Comp.DATE.Y=atoi(s);
        fscanf(ft,"%s", s); Comp.Room=atoi(s);
        fscanf(ft,"%10s", Comp.Name);

        fwrite(&Comp, sizeof(Comp), 1, fb);
        kol++;
    }

    fclose(ft);
    fclose(fb);

    printf("Создан двоичный файл из %d записей  по %d байт\n", kol, (int) sizeof(TComp));
    printf("Press any key to continue");
    getch();
    return;
}

//-------------- вторая часть: поиск в двоичном файле ----
void FindIVAN(int argc, char* argv[]){
    if (argc<2) {
        printf("Мало параметров\nPress any key");
        getch();
        return;
    }
    FILE *fb = fopen(argv[1], "rb");
    if (fb==NULL) {

        printf("Error: не удалось открыть двоичный файл %s\n", argv[1]);
        printf("Press ENTER");
        getch();
        return;
    }

    TComp Comp;
    char SUp[31];
    int kol=0, nr=1;
    while (nr){
        nr=(int)fread(&Comp, sizeof(Comp), 1, fb);
        if (nr>0)
        if (strcmp(ANSIUpperCase(Comp.Mark, SUp),"IBM_PC-486")==0 && Comp.DATE.Y==1995 ) {
            printf("Найден компьютер:\n Марка %s\n %d.%d.%d\n Расположение комната № %d\n Ответственное лицо %s\n",
                   Comp.Mark,Comp.DATE.D,Comp.DATE.M,Comp.DATE.Y,Comp.Room,Comp.Name);
            kol++;
        }
    }
    if (kol==0)
        printf("Данные, соответствующие запросу,не найдены\n");
    else
        printf("Всего найдено: %d\n", kol);

    fclose(fb);

    printf("Press any key to continue");
    getch();
    return;
}

//-------третья часть: корректировка в двоичном файле ----
void CorrectFile(int argc, char* argv[]){
    if (argc<2) {
        printf("Мало параметров\nPress any key");
        getch();
        return;
    }
    FILE *fb = fopen(argv[1], "rb+");
    if (fb==NULL) {
        printf("Error: не удалось открыть двоичный файл %s\n", argv[1]);
        printf("Press ENTER");
        getch();
        return;
    }

    TComp Comp;
    int kol=0, nr=1, nw=1, flag;
    nr=(int) fread(&Comp, sizeof(Comp), 1, fb);
    while (nr==1 && nw==1){
        printf("Считана запись:\n");
        printf("%25s %2d %2d %2d %2d %25s\n", Comp.Mark,Comp.DATE.D,
               Comp.DATE.M,Comp.DATE.Y,Comp.Room,Comp.Name);

        flag=0;
        if (Comp.DATE.M<1) {Comp.DATE.M=1; flag=1;}
        if (Comp.DATE.M>12) {Comp.DATE.M=12; flag=1;}
        // расчет дней по месяцам

        if (Comp.DATE.M == 1 && Comp.DATE.D>31) {Comp.DATE.D=31; flag=1;}
        if (Comp.DATE.M == 2 && Comp.DATE.D>28) {Comp.DATE.D=28; flag=1;}
        if (Comp.DATE.M == 3 && Comp.DATE.D>31) {Comp.DATE.D=31; flag=1;}
        if (Comp.DATE.M == 4 && Comp.DATE.D>30) {Comp.DATE.D=30; flag=1;}
        if (Comp.DATE.M == 5 && Comp.DATE.D>31) {Comp.DATE.D=31; flag=1;}
        if (Comp.DATE.M == 6 && Comp.DATE.D>30) {Comp.DATE.D=30; flag=1;}
        if (Comp.DATE.M == 7 && Comp.DATE.D>31) {Comp.DATE.D=31; flag=1;}
        if (Comp.DATE.M == 8 && Comp.DATE.D>31) {Comp.DATE.D=31; flag=1;}
        if (Comp.DATE.M == 9 && Comp.DATE.D>30) {Comp.DATE.D=30; flag=1;}
        if (Comp.DATE.M == 10 && Comp.DATE.D>31) {Comp.DATE.D=31; flag=1;}
        if (Comp.DATE.M == 11 && Comp.DATE.D>30) {Comp.DATE.D=30; flag=1;}
        if (Comp.DATE.M == 12 && Comp.DATE.D>31) {Comp.DATE.D=31; flag=1;}


        if (Comp.Room <0) {Comp.Room=-Comp.Room; flag=1;}

        if (flag) {
            kol++;

            fseek(fb, -sizeof(Comp),SEEK_CUR);
            nw = (int)fwrite(&Comp,sizeof(Comp),1,fb);
            fseek(fb,0,SEEK_CUR);

            printf("Сделана корректировка:\n");
            printf("%25s %2d %2d %2d %2d %25s\n", Comp.Mark,Comp.DATE.D,
                   Comp.DATE.M,Comp.DATE.Y,Comp.Room,Comp.Name);
        }
        nr=(int)fread(&Comp, sizeof(Comp), 1, fb);
        printf("вот здесь косяк nr, %d",nr);
    }
    if (kol==0)
        printf("Ни одной корректировки\n");
    else
        printf("Всего корректировок: %d\n", kol);

    fclose(fb);

    printf("Press any key to continue");
    getch();
    return;
}
