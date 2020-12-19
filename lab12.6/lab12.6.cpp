#include <iostream>
#include <fstream>
#include <Windows.h>
#include <time.h>
#include <string>

using namespace std;


typedef double Info;
struct Elem
{
    Elem* link;
    Info info;
};

void Read_File(Elem*& first, Elem*& last);
void Print(Elem* L);
void Rand_Action(Elem*& first, Elem*& last);
void Enqueue(Elem*& first, Elem*& last, Info value);
Info Dequeue(Elem*& first, Elem*& last);

int main()
{
    srand((unsigned)time(NULL));

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Elem* first = NULL,
        * last = NULL;

    int action;

    do
    {
        cout << endl << endl;
        cout << "Виберіть дію: " << endl;
        cout << "1 - Побудувати чергу" << endl;
        cout << "2 - Надрукувати чергу" << endl;
        cout << "3 - Випадкова дія" << endl;       
        cout << "0 - Завершити роботу програми" << endl;
        cout << "Введіть: "; cin >> action;
        switch (action)
        {
        case 1:
            Read_File(first, last);
            break;
        case 2:
            cout << "Черга: "; Print(first);
            break;
        case 3:
            Rand_Action(first, last);
            break;
        case 0:
            exit(1);
        }
    } while (action != 0);

    return 0;
}

void Read_File(Elem*& first, Elem*& last)
{
    ifstream f("list.txt", ios::in);

    if (!f.is_open())
    {
        cout << "Помилка!Файл не відкрито." << endl;
        exit(1);
    }
    string line;
    double number;
    while (!f.eof())
    {
        getline(f, line);
        number = stod(line);
        Enqueue(first, last, number);
    }
}
void Print(Elem* L)
{
    while (L != NULL)
    {
        cout << L->info << " ";
        L = L->link;
    }
}
void Rand_Action(Elem*& first, Elem*& last)
{
    int action = rand() % 2;
    
    Info value;

    if (action == 0)
        cout << "Видалений елемент: " << Dequeue(first, last);
    else
    {
        cout << "Введіть значення нового елемента: "; cin >> value;
        Enqueue(first, last, value);
    }
}
void Enqueue(Elem*& first, Elem*& last, Info value)
{
    Elem* tmp = new Elem;
    tmp->info = value;
    tmp->link = NULL;
    if (last != NULL)
        last->link = tmp; 
    last = tmp; 
    if (first == NULL)
        first = tmp;
}
Info Dequeue(Elem*& first, Elem*& last)
{
    Elem* tmp = first->link;
    Info value = first->info;
    delete first;
    first = tmp; 
    if (first == NULL)
        last = NULL;
    return value;
}