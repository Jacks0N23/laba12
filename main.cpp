#include <iostream>
#include <conio.h>
#include "helper.h"

using namespace std;


int main(int argc, char* argv[])
{
    char ch;
    SetConsoleOutputCP(1251);
    do{

        printf("\n N - ������� ����� ���.����;\n F - ����� �����;\n C - ���������;\n E - �����.\n��� �����? ");
        ch=getchar();   fflush(stdin);
        ch=toupper(ch);
        switch (ch) {
//----------������ �����: �������� ��������� �� ����������
            case 'N': CreateBinaryFile(argc, argv); break;
//-------------- ������ �����: ����� � �������� ����� ----
            case 'F': FindIVAN(argc, argv); break;
//-------������ �����: ������������� � �������� ����� ----
            case 'C': CorrectFile(argc, argv); break;
//-----------�����----------------------------------------
            case 'E': return 0;
//--------------------------------------------------------
            default:
                printf("��� ����� �������\nPress any key");
                getch();
        }

    } while (ch!='E');

    return 0;
}
//-----------------------------------------------------------
