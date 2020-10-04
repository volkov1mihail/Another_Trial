#include<iostream>
#include<clocale>
#include<ctime>

using namespace std;


void printMenu()
{
    cout << "МЕНЮ" << endl;
    cout << "0 - Выход из программы" << endl;
    cout << "1 - Ввести несколько элемнетов с клавиатуры" << endl;
    cout << "2 - Добавить в массив n случайных чисел в промежутке от a до b(n, a, b вводится с клавиатуры)" << endl;
    cout << "3 - Вывести массив на экран" << endl;
    cout << "4 - Поиск индекса элемента" << endl;
    cout << "5 - Добавление массив к массиву" << endl;
    cout << "6 - Объединение массивов" << endl;
    cout << "7 - Вставка элемента в массив" << endl;
    cout << "8 - Удаление нескольких подряд идущих элементов массива" << endl;
    cout << "9 - Поиск подпоследовательности" << endl;
}



void conclusion(int a)
{
    if (a == 0)
    {
        cout << "Операция выполнена успешно" << endl;
    }
    else
    {
        cout << "Не удалось выполнить операцию" << endl;
    }
}



int* initArray(int capacity = 10)
{
    int* result = new int[capacity + 2]{ 0 };
    //*(result + 1) = capacity;
    result += 2;
    result[-1] = capacity;
    return result;
}



void deleteArray(int* arr)
{
    arr -= 2;
    delete[] arr;
}



void expandArray(int*& arr)    //Удвоение длинны массива в случае, если оно потребуется
{
    int* temp = initArray(2 * arr[-1]);
    for (int i = 0; i < arr[-1]; ++i)        //Переписывание значений уже существующих элементов массива
    {
        temp[i] = arr[i];
    }
    temp[-2] = arr[-2];
    temp[-1] = 2 * arr[-1];
    arr -= 2;
    delete[] arr;
    arr = temp;
}



void addElement(int*& arr, int element)
{
    if (arr[-2] + 1 < arr[-1])
    {
        arr[arr[-2]] = element;
    }
    else
    {
        expandArray(arr);
        arr[arr[-2]] = element;
    }
    ++arr[-2];
}



void add_M_Elements(int*& arr)
{
    cout << "Вводите элементы, которые хотите добавить в массив." << endl;
    cout << "Чтобы остановить операцию или добавить в массив 0, введите 0." << endl;
    int n = 1;
    while (n != 0)
    {
        cin >> n;
        addElement(arr, n);
    }
    --arr[-2];
    cout << "Чтобы ввести 0, как элемент массива, введите 1." << endl;
    cout << "Чтобы закончить операцию, введите 0." << endl;
    cin >> n;
    if (n == 1)
    {
        addElement(arr, 0);
    }
}



void addRandomElements(int*& arr, int n, int min, int max)
{
    for (int i = 0; i < n; ++i)
    {
        addElement(arr, rand() % (max - min + 1) + min);
    }
}



void printArray(int* arr)
{
    cout << "[" << arr[-2] << "/" << arr[-1] << "] {";
    for (int i = 0; i < arr[-2]; ++i)
    {
        cout << *(arr + i) << (i == arr[-2] - 1 ? "}\n" : ", ");
    }
}

//void printArray(int* arr, int count)
//{
//    cout << "[" << count << "/" << arr[-1] << "] {";
//    for (int i = 0; i < count; ++i)
//    {
//        cout << *(arr + i) << (i == count - 1 ? "}\n" : ", ");
//    }
//}



int search(int* arr, int element, int start)
{
    int a = -1;
    for (int i = start; i < arr[-2]; ++i)
    {
        if (arr[i] == element)
        {
            a = i;
            break;
        }
    }
    return a;
}



void add(int*& arr, int* addedArr)
{
    for (int i = arr[-2]; i < arr[-2] + addedArr[-2]; ++i)
    {
        addElement(arr, addedArr[i - arr[-2]]);
    }
}



int* unify(int* a, int* b)
{
    int* arr=initArray(2 * (a[-2] + b[-2]));
    for (int i = 0; i < 2 * a[-2]; i+=2)
    {
        arr[i] = a[i / 2];
    }
    for (int i = 1; i < 2 * b[-2]; i += 2)
    {
        arr[i] = b[(i - 1) / 2];
    }
    if (a[-2] >= b[-2])
    {
        arr[-2] = 2 * a[-2];
    }
    else
    {
        arr[-2] = 2 * b[-2];
    }
    return arr;
}



int extract(int*& a,  int index)
{
    if ((index < 0) or (index >= a[-2]))
    {
        return 1;
    }
    else
    {
        int c = a[index];
        for (int i = index; i < a[-2] - 1; ++i)
        {
            a[i] = a[i + 1];
        }
        a[a[-2] - 1] = 0;
        return c;
        --a[-2];
    }
}



int insert(int*& a, int index, int element)
{
    if ((index < 0) or (index > a[-2] + 1))
    {
        return 1;
    }
    else
    {
        if (a[-2] + 1 == a[-1])
        {
            expandArray(a);
        }
        for (int i = a[-2]; i >= index; --i)
        {
            a[i] = a[i - 1];
        }
        if (index != 0)
        {
            a[index - 1] = element;
        }
        else
        {
            a[index] = element;
        }
        ++a[-2];
        return 0;
    }
    //else
    //{
    //    while (index >= a[-1])
    //    {
    //        expandArray(a);
    //    }
    //    a[index] = element;
    //    ++a[-2];
    //    return 0;
    //}
}



int deleteGroup(int*& a, int startIndex, int n)
{
    if ((startIndex < 0) or (startIndex + n >= a[-2]))
    {
        return 1;
    }
    else
    {
        for (int i = startIndex; i < a[-2] -n; ++i)
        {
            a[i] = a[i + n];
        }
        a[-2] -= n;
        return 0;
    }
}



int subSequence(int* a, int* b)
{
    int k = 0;
    int* c = initArray(b[-2]);
    for (int i = 0; i < a[-2] - b[-2]; ++i)
    {
        c[0] = search(a, b[0], i);
        for (int j = 1; j < b[-2]; ++j)
        {
            c[j] = search(a, b[j], i);
            if (c[j] != c[j - 1] + 1)
            {
                k = -1;
                break;
            }
            else
            {
                k = 2;
            }
        }
        if (k == 2)
        {
            k = c[0];
            break;
        }
    }
    return k;
}



void processChoice(int*& arr1, int*& arr2, int choice)
{
    int n = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    switch (choice)
    {
    case 1:
        cout << "Введите 1, чтобы добавить элементы в массив a" << endl;
        cout << "Введите 2, чтобы добавить элементы в массив b" << endl;
        cin >> c;
        if (c == 1)
        {
            add_M_Elements(arr1);
        }
        else
        {
            add_M_Elements(arr2);
        }
        break;
    case 2:
        cout << "Введите 1, чтобы добавить элементы в массив a" << endl;
        cout << "Введите 2, чтобы добавить элементы в массив b" << endl;
        cin >> c;
        cout << "Введите n" << endl;
        cin >> n;
        cout << "Введите a" << endl;
        cin >> a;
        cout << "Введите b" << endl;
        cin >> b;
        if (c == 1)
        {
            addRandomElements(arr1, n, a, b);
        }
        else
        {
            addRandomElements(arr2, n, a, b);
        }
        break;
    case 3:
        cout << "Введите 1, чтобы вывести массив a" << endl;
        cout << "Введите 2, чтобы вывести массив b" << endl;
        cin >> c;
        if (c == 1)
        {
            printArray(arr1);
        }
        else
        {
            printArray(arr2);
        }
        break;
    case 4:
        cout << "Введите 1, чтобы найти номер элемента массива a" << endl;
        cout << "Введите 2, чтобы найти номер элемента массива b" << endl;
        cin >> c;
        cout << "Введите элемент, который хотите найти" << endl;
        cin >> a;
        cout << "Введите индекс, с котрого начать поиск" << endl;
        cin >> n;
        if (c == 1)
        {
            b = search(arr1, a, n);
        }
        else
        {
            b = search(arr2, a, n);
        }
        cout << b << endl;
        break;
    case 5:
        cout << "Введите 1, чтобы добавить массив b в массив a" << endl;
        cout << "Введите 2, чтобы добавить массив a в массив b" << endl;
        cin >> c;
        if (c == 1)
        {
            add(arr1, arr2);
        }
        else
        {
            add(arr2, arr1);
        }
        break;
    case 6:
        cout << "Введите 1, чтобы элементы массива a стояли на нечетных номерах" << endl;
        cout << "Введите 2, чтобы элементы массива b стояли на нечетных номерах" << endl;
        cin >> c;
        if (c == 1)
        {
            int* a = unify(arr1, arr2);
            printArray(a);
            deleteArray(a);
        }
        else
        {
            int* a = unify(arr2, arr1);
            printArray(a);
            deleteArray(a);
        }
        break;
    case 7:
        cout << "Введите 1, чтобы вставить элемент в массив a" << endl;
        cout << "Введите 2, чтобы вставить элемент в массив b" << endl;
        cin >> c;
        cout << "Введите индекс, который нужно присвоить новому элементу" << endl;
        cin >> n;
        cout << "Введите элемент, который хотите вставить" << endl;
        cin >> a;
        if (c == 1)
        {
            b = insert(arr1, n, a);
        }
        else
        {
            b = insert(arr2, n, a);
        }
        conclusion(b);
        break;
    case 8:
        cout << "Введите 1, чтобы удалить последовательность из массива a" << endl;
        cout << "Введите 2, чтобы удалить последовательность из массива b" << endl;
        cin >> c;
        cout << "Введите индекс, с которого начинается последовательность" << endl;
        cin >> a;
        cout << "Введите количество элементов последовательности" << endl;
        cin >> n;
        if (c == 1)
        {
            b = deleteGroup(arr1, a, n);
        }
        else
        {
            b = deleteGroup(arr2, a, n);
        }
        conclusion(b);
        break;
    case 9:
        cout << "Введите 1, чтобы найти последовательность b в массиве a" << endl;
        cout << "Введите 2, чтобы найти последовательность a в массиве b" << endl;
        cin >> c;
        if (c == 1)
        {
            b = subSequence(arr1, arr2);
        }
        else
        {
            b = subSequence(arr2, arr1);
        }
        cout << b << endl;
        break;
    }
}



int main(int argc, char* argv[])
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    int* a = initArray(10);
    int* b = initArray(10);
    int choice = 0;
    do
    {
        system("cls");
        printMenu();
        cin >> choice;
        processChoice(a, b, choice);
        system("pause");
    } while (choice != 0);
    deleteArray(a);
    deleteArray(b);
    return EXIT_SUCCESS;
}