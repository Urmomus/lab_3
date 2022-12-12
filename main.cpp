/************************************************************
 *                                                          *
 *                  Программная инженерия                   *
 *                                                          *
 ************************************************************
 *  Project type: ConsoleApplication                        *
 *  Project name: lab_3                                     *
 *  Language: cpp MSVS 2022                                 *
 *  Programmers: М3О-111Б-22                                *
 *               Яковченко Николай Романович;               *
 *               Деккер Сергей Альбертович;                 *
 *  Modigied by:                                            *
 *  Created: 09.12.2022                                     *
 *  Comment: ThirdProgramm (Одномерные массивы)             *
 ************************************************************/

#include <iostream>     //стандартные потоки ввода/вывода
#include <fstream>      //файловые потоки ввода/вывода
using namespace std;


int main()
{
    const char *FNAME = "../test/less.txt"; // имя файла с исходными данными

    // инициализация длин массивов
    int LenA = 9;
    int LenB = 12;
    int LenK = 8;
    int LenNew = 23;

    // инициализация массивов
    int AVec[LenA];
    int BVec[LenB];
    int KVec[LenK];
    int NewVec[LenNew];

    int MinPos = -1;         // индекс минимального элемента
    int MaxPos = -1;         // инжекс максимального элемента
    int Min = 2000000000;    // значение максимального элемента
    int Max = -2000000000;   // значение минисального элемента
    int Absolute;            // сумма абсолютных значений всех элементов, начиная с N
    int N;                   // Величина N
    int NumberOfElement = 0; // реальное число элементов в массиве

    // объявление файловой переменной и открытие файла для чтения
    ifstream fin(FNAME);

    if (!fin)
    {
        cout << "Файл " << FNAME << " не найден" << endl;
        return 1; // выход по ошибке
    }

    fin >> N; // чтение числа элементов массива из файла

    // проверки состояния файла
    if ((fin.eof()) && (fin.fail())) // файл пуст
    {
        cout << "Файл " << FNAME << " пустой" << endl;
        fin.close();    // закрыть файл
        return 2;       // выход по ошибке
    }

    if (fin.fail()) // в файле не число
    {
        cout << "Сбой при чтении файла " << FNAME << endl;
        cout << "В файле не число" << endl;
        fin.close(); // закрыть файл
        return 3;    // выход по ошибке
    }

    if (N >= LenNew || N < 0)
    {
        cout << "Недопустимое значение N: " << N << endl;
        fin.close(); // закрыть файл
        return 4;    // выход по ошибке
    }

    // эхо-печать N
    cout << "Эхо печать N = " << N << endl;

    if ((fin.eof()) && (!(fin.fail()))) // присутствует только N
    {
        cout << "В файле " << FNAME << " присутствует только N." << endl
             << "Другие данные отстутсвуют" << endl;
        fin.close(); // закрыть файл
        return 5; // выход по ошибке
    }

    while (!fin.eof()) // пока файл не кончился
    {
        if (NumberOfElement == LenA + LenB + LenK) // в файле присутствуют лишние элементы
        {
            cout << "Элементов в файле больше, чем заявлено" << endl;
            fin.close(); // закрыть файл
            return 6;    // выход по ошибке

        }

        // вектор не кончился, читаем дальше
        if (NumberOfElement < LenA)
            fin >> AVec[NumberOfElement];

        else if (NumberOfElement < LenA + LenB)
            fin >> BVec[NumberOfElement - LenA];

        else if (NumberOfElement < LenA + LenB + LenK)
            fin >> KVec[NumberOfElement - LenA - LenB];


        NumberOfElement++; // текущее число прочитанных элементов
    }

    if (NumberOfElement < LenA + LenB + LenK) // число элементов массива меньше, чем заявлено N
    {
        cout << "Элементов в файле меньше, чем заявлено" << endl;
        fin.close(); // закрытие файла
        return 7;    // выход по ошибке
    }

    // чтение из файла завершено успешно
    fin.close(); // закрытие файла

    // начало основной программы

    // построение массива NewVec
    for (int i = 0; i < LenA; i++)
        NewVec[i] = AVec[i];

    for (int i = 1; i < LenB; i += 2)
        NewVec[LenA + i / 2] = BVec[i];

    for (int i = LenK - 1; i > -1; i--)
        NewVec[LenNew - i - 1] = KVec[i];

    // вычисление суммы абсолютных значений NewVec начиная с N
    for (int i = N; i < LenNew; i++)
        Absolute += abs(NewVec[i]);

    for (int i = 0; i < LenNew; i++)
    {
        if (NewVec[i] > Max)
        {
            Max = NewVec[i];
            MaxPos = i;
        }
        if (NewVec[i] < Min)
        {
            Min = NewVec[i];
            MinPos = i;
        }
    }

    // вывод массива NewVec
    cout << "[";
    for (int i = 0; i < LenNew; i++)
        cout << NewVec[i] << ", ";
    cout << "\b\b]" << endl;

    cout << "Сумма абсолютных значений, начиная с N: " << Absolute << endl;

    cout << "Максимальное значение: " << Max << endl << "Индекс максимального значения: " << MaxPos << endl;
    cout << "Минимальное значение: " << Min << endl << "Индекс минимального значения: " << MinPos << endl;

    return 0;
}
