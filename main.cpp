#include <iostream>
#include <conio.h>
#include "helper.h"

using namespace std;


int main(int argc, char* argv[])
{
    char ch;
    SetConsoleOutputCP(1251);
    do{

        printf("\n N - создать новый тип.файл;\n F - сразу поиск;\n C - коррекция;\n E - конец.\nВаш выбор? ");
        ch=getchar();   fflush(stdin);
        ch=toupper(ch);
        switch (ch) {
//----------первая часть: создание двоичного из текстового
            case 'N': CreateBinaryFile(argc, argv); break;
//-------------- вторая часть: поиск в двоичном файле ----
            case 'F': FindIVAN(argc, argv); break;
//-------третья часть: корректировка в двоичном файле ----
            case 'C': CorrectFile(argc, argv); break;
//-----------выход----------------------------------------
            case 'E': return 0;
//--------------------------------------------------------
            default:
                printf("Нет такой команды\nPress any key");
                getch();
        }

    } while (ch!='E');

    return 0;
}
//-----------------------------------------------------------
