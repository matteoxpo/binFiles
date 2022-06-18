#include <iostream>
#include <malloc.h>
#include <locale.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define scanf scanf_s
#define fscanf fscanf_s

// структруа хранения данных о дроби и указателем на следующую дробь
struct numFraction {
public:
    int numerator;
    int denumerator;
    numFraction* next;

    numFraction(int val1 = 0, int val2 = 0, numFraction* p = nullptr) {
        numerator = val1;
        denumerator = val2;
        next = p;
    }
};

//очистить строку
void clearStr(char* str) {
    int size = strlen(str);
    for (int i = 0; i < size; i++) {
        if (i == size - 1)
            str[i] = '\n';
        else
            str[i] = 0;
    }
}

//создать бинарный файл
void plusBIN(char* str) {
    char bin[] = ".bin";
    strcat_s(str, 50, bin);
}

// перевод целочисленного типа данных к массиву символов
void intToString(char* str, int x) {
    char c = 0;
    int i = 0;
    char strTransp[50] = { 'a' };

    strTransp[0] = 0;
    printf("%s", strTransp);
    while (x / 10 != 0) {
        c = x % 10 + '0';
        strTransp[i] = c;
        i++;
        x /= 10;
    }
    c = x % 10 + '0';
    strTransp[i] = c;
    i++;
    for (int j = 0; j < i; j++) {
        str[j] = strTransp[i - j - 1];
    }
}

// подсчет количества дробей в списке
int getLen(numFraction* head) {
    int count = 0;
    numFraction* p = head;
    if (head == nullptr)
        return 0;
    while (p != nullptr) {
        count++;
        p = p->next;
    }
    return count;
}

// функция получения указателя на элемент по индексу в списке
numFraction* getElByInd(numFraction* head, int ind) {
    if (head == nullptr) return nullptr;
    numFraction* p = head;
    int i = 0;
    while (i != ind) {
        i++;
        p = p->next;
        if (p == nullptr)
            return nullptr;
    }
    return p;
}

numFraction* numFractionSort(numFraction* head, bool srt) {
    int listSize = getLen(head);
    bool flag = 0;
    for (int i = 0; i < listSize; i++) {
        for (int j = 0; j < listSize - 1; j++) {
            numFraction* first = getElByInd(head, j);
            numFraction* second = getElByInd(head, j + 1);
            if (srt == false) {
                if (((first->numerator * second->denumerator) > (second->numerator * first->denumerator))) {
                    flag = 1;
                }
            }
            else {
                if (((first->numerator * second->denumerator) < (second->numerator * first->denumerator))) {
                    flag = 1;
                }
            }
            if (flag) {
                int swapNum = first->numerator;
                first->numerator = second->numerator;
                second->numerator = swapNum;

                swapNum = first->denumerator;
                first->denumerator = second->denumerator;
                second->denumerator = swapNum;
            }
            flag = 0;
        }
    }
    return head;
}

// функция ввода новой дроби в список дробей
numFraction* push_back(numFraction* head, int val1, int val2) {
    numFraction* p = head;
    numFraction* member = new numFraction(val1, val2, nullptr);
    if (head == nullptr) {
        return member;
    }
    while (p->next != nullptr) {
        p = p->next;
    }
    p->next = member;
    return head;
}

// функция удаления последней дроби из списка
numFraction* pop_back(numFraction* head) {
    if (head == nullptr) {
        printf("\nСписок пуст!");
        return head;
    }
    numFraction* p = head;
    numFraction* prev = head;
    while (p->next != nullptr) {
        if ((p->next)->next == nullptr) prev = p;
        p = p->next;
    }
    if (p == prev) {
        free(p);
        return nullptr;
    }
    prev->next = nullptr;
    return head;
}
// функция создания бинарного файла и записи в него данных о дробях
void createFile(char* name) {
    FILE* fp;
    printf("\n%s", name);
    if (!fopen_s(&fp, name, "wb+")) {
        printf("\nЗаписываем данные о дробях, введите числитель и знаменатель через пробел:\n");
        char str[100];
        while (1) {
            gets_s(str);
            if (!str[0]) break;
            int num;
            int denum;
            int indS = 0;
            int indE = 0;
            for (int i = 0; i < strlen(str); i++) {
                if (str[i] == ' ') {
                    indE = i;
                    break;
                }
            }
            char NUM[10];
            strncpy_s(NUM, str, indE);
            num = atoi(NUM);
            indS = indE;
            NUM[0] = 0;

            for (int i = indS, k = 0; i < strlen(str); i++, k++) {
                NUM[k] = str[i];
            }
            denum = atoi(NUM);

            fwrite(&num, sizeof(int), 1, fp);
            fwrite(&denum, sizeof(int), 1, fp);

        }
        printf("\nФайл создан, данные записаны");
        fclose(fp);
    }
    else
        printf("Ошибка создания файла!");
}

// функция создания файла с именем name с случайными данными
void createFileWithRandomData(char* name) {
    FILE* fp;
    if (!fopen_s(&fp, name, "wb+")) {
        srand(time(NULL));
        int count = (rand() % 10);
        for (int i = 0; i < count; i++) {
            int num, denum;
            num = rand();

            denum = rand();

            if (denum == 0) continue;

            fwrite(&num, sizeof(int), 1, fp);
            fwrite(&denum, sizeof(int), 1, fp);
        }
        printf("\nФайл создан, данные записаны");
        fclose(fp);
    }
    else
        printf("Ошибка создания файла!");
}


// функция генерации count числа файлов с случайными данными
void createFilesWithData(int count) {
    FILE* fp;
    char name[8] = "RGZdata";

    for (int i = 0; i < count; i++) {
        srand(time(NULL));

        char newName[50] = { ' ' };
        newName[0] = 0;
        strcat_s(newName, 8, name);

        char numberOfTest[50] = { ' ' };
        numberOfTest[0] = 0;
        intToString(numberOfTest, i);
        strcat_s(newName, 15, numberOfTest);
        plusBIN(newName);
        if (!fopen_s(&fp, newName, "wb+")) {
            printf("\nЗаписываем случайные данные о дробях в файл %s\n", newName);
            for (int j = 0; j < rand() % 100; j++) {
                int num, denum;
                num = rand();
                denum = rand();
                if (denum != 0) {
                    fwrite(&num, sizeof(int), 1, fp);
                    fwrite(&denum, sizeof(int), 1, fp);
                }
                else
                    printf("\nБыл сгенерирован нулевой знаменатель!Дробь пропущена.");
            }
            printf("\nФайл создан, данные записаны");
            fclose(fp);
        }
        else
            printf("Ошибка создания файла!");


    }

    printf("\nФайлы созданы в количестве - %d штук\n", count);
}

// функция загрузки данных из файла
numFraction* getDataFromFile(char* name) {
    FILE* fp;
    fopen_s(&fp, name, "rb+");
    numFraction* numList = nullptr;
    int num, denum;
    while (fread(&num, sizeof(int), 1, fp)) {
        fread(&denum, sizeof(int), 1, fp);
        if (denum == 0) {
            printf("\nОшибка - деление на ноль. Дробь пропущенна, остальные данные записываются.");
            continue;
        }
        numList = push_back(numList, num, denum);
    }
    fclose(fp);
    return numList;
}

// функция загрузки данных из неизвестного количества файлов
numFraction* getDataFromUnknownFile(char* name, ...) {
    FILE* fp;
    va_list p;
    numFraction* numList = nullptr;
    va_start(p, name);


    while (1) {
        if (name == nullptr) {
            va_end(p);
            return numList;
        }
        int x = fopen_s(&fp, name, "rb+");
        int num, denum;
        while (fread(&num, sizeof(int), 1, fp)) {
            fread(&denum, sizeof(int), 1, fp);
            if (denum == 0) {
                printf("\nОшибка - деление на ноль. Дробь пропущенна, остальные данные записываются.");
                continue;
            }
            numList = push_back(numList, num, denum);
        }
        fclose(fp);
        name = va_arg(p, char*);
    }
}

// функция вывода информации о имеющихся дробях в списке дробей
void printfFraction(numFraction* head) {
    printf("\n");

    numFraction* p = head;
    if (head == nullptr) {
        printf("Дробей нет!");
        return;
    }
    printf("\nИнформация о дробях:\n");
    while (p != nullptr) {
        printf("\n%d/%d", p->numerator, p->denumerator);
        p = p->next;
    }
}


void Menu()
{
    int i, k, num, denum;
    int inpt;
    int count;
    const char* ss[] = { " 0 - Создание бинарного файла и запись данных в него", \
    " 1 - Сгенерировать файлы с последующим автозаполнением", \
    " 2 - Чтение дробей из определенного бинарного файла",\
    " 3 - Чтение дробей из файлов(функция с переменным количеством параметров)", " 4 - Вывод списка дробей", \
    " 5 - Добавление дроби в список", " 6 - Удаление последней дроби из списка", \
    " 7 - Отсортировать список" , \
    " 8 - Вывод дроби по индексу в списке", \
    " 9 - Вывод длинны списка дробей", " 10 - Выход", "---------------------------------ВЫБЕРИТЕ ОПЦИЮ-----------------------------" };
    k = sizeof(ss) / sizeof(ss[0]);

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); //Позволяет вводить в консоль русские символы

    numFraction* head = nullptr;
    numFraction* el = nullptr;
    int checkInpt = -1;
    int ind;
    char name[50] = { ' ' };
    bool sort;
    char name1[] = { "RGZdata0.bin" };
    char name2[] = { "RGZdata1.bin" };

    // указатели на функции
    void(*operat)(char* name); // createFile
    void(*operatP)(numFraction * head); // printfFraction
    numFraction* (*operatGet)(char* name); // getDataFromFile getDataFromUnknownFile 
    numFraction* (*operatGetEl)(numFraction * head, int ind); // getElByInd
    numFraction* (*operatPush)(numFraction * head, int val1, int val2); // push_back
    numFraction* (*operatSort)(numFraction * head, bool srt); // numFractionSort
    numFraction* (*operatPop)(numFraction * head); // pop_back 
    int (*operatLen)(numFraction * head); // getLen


    while (1)
    {
        puts("\n---------------------------РАБОТА С БИНАРНЫМИ ФАЙЛАМИ-----------------------");
        for (i = 0; i < k; i++) puts(ss[i]);
        scanf_s("%d", &inpt);
        getchar();
        switch (inpt)
        {
        case 0:
            printf("При вводе имени файла для создания не нужно указывать бинарный формат файла!");
            printf("\nВведите имя файла для создания и записи данных: ");
            name[0] = 0;
            gets_s(name);
            plusBIN(name);
            operat = createFile;
            operat(name);
            break;
        case 1:
            printf("Введите количество генерируемых файлов: ");
            checkInpt = scanf("%d", &count);
            while (checkInpt == 0) {
                printf("\nОшибка ввода числа! Попробуйте снова: ");
                checkInpt = scanf("%d", &count);
            }

            createFilesWithData(count);
            break;
        case 2:
            printf("При вводе имени файла для создания не нужно указывать бинарный формат файла!");
            printf("\nВведите имя файла для чтения: ");
            name[0] = 0;
            gets_s(name);
            plusBIN(name);
            operatGet = getDataFromFile;
            head = operatGet(name);
            break;
        case 3:
            printf("Чтение из файлов осуществляется функцией многих переменных, для изменения кол-ва файлов для считывания");
            printf("\nизмените в коде программы вызов функции: добавьте новые имена файлов после ',' или сотрите более ненужные.");
            printf("\nАприори программа считывает данные из двух файлов - \"RGZdata0\", \"RGZdata1\"; указанных в вызове функции.");
            head = getDataFromUnknownFile(name1, name2, nullptr);
            break;
        case 4:
            printf("Список дробей:\n");
            operatP = printfFraction;
            operatP(head);
            break;
        case 5:
            operatPush = push_back;
            printf("Введите числитель: ");
            checkInpt = scanf("%d", &num);
            while (checkInpt == 0) {
                printf("\nОшибка ввода числителя! Попробуйте снова: ");
                checkInpt = scanf("%d", &num);
            }
            printf("Введите знаменатель: ");
            checkInpt = scanf("%d", &denum);
            while (checkInpt == 0) {
                printf("\nОшибка ввода знаменятеля! Попробуйте снова: ");
                checkInpt = scanf("%d", &denum);
            }
            operatPush(head, num, denum);
            break;
        case 6:
            operatPop = pop_back;
            head = operatPop(head);
            break;
        case 7:
            operatSort = numFractionSort;
            printf("0 - Сортировка по возрастанию\n1 - Сортировка по убыванию\n");
            scanf("%d", &sort);
            head = operatSort(head, sort);
            break;
        case 8:
            printf("Учитывайте, что индексация идет с нуля!\nВведите индекс: ");
            checkInpt = scanf("%d", &ind);
            while (checkInpt == 0) {
                printf("\nОшибка ввода, попробуйте снова: ");
                checkInpt = scanf("%d", &ind);
            }

            operatGetEl = getElByInd;
            el = operatGetEl(head, ind);
            if (el != nullptr)
                printf("Дробь по индексу %d \n %d/%d", ind, el->numerator, el->denumerator);
            else
                printf("Дроби по такому индексу нет!");
            break;
        case 9:
            operatLen = getLen;
            printf("Длина списка = %d", operatLen(head));
            break;
        case 10:
            printf("До свидания!");
            free(el);
            free(head);
            return;
        default:
            printf("Неизвестная команда!");
        }
    }

}




int main()
{
    setlocale(LC_ALL, "Rus");
    void(*menuptr)();
    menuptr = Menu;
    menuptr();

}