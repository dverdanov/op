//для отключения warning в clion
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma ide diagnostic ignored "cert-err34-c"
#pragma ide diagnostic ignored "misc-no-recursion"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <Windows.h>

using namespace std;

//перечисление пунктов меню
enum Options {
    DATA_INPUT_FROM_KEYBOARD = 1,
    DATA_FROM_TEXT_FILE,
    DATA_FROM_BINARY_FILE,
    OUTPUT_DATA_TO_CONSOLE,
    OUTPUT_DATA_TO_FILE,
    GET_DATA_BY_REQUEST,
    CONVERT_DATA_TO_TEXT_FILE,
    CONVERT_DATA_TO_BINARY_FILE,
    CONVERT_TEXT_FILE_TO_BINARY_FILE,
    ADD_ENTRY,
    CHANGE_ENTRY,
    DELETE_ENTRY,
    SORTING,
    EXIT
};

struct Student {
    char lastName[64] = "";
    int course{};
    char group[32] = "";
    int grades[7]{};
};

//прототипы основных функций
void dataInputFromKeyboard(Student* studentList);
void dataFromTextFile(Student* studentList);
void dataFromBinaryFile(Student* studentList);
void outputData(Student* studentList, bool isFile);
void getDataByRequest(Student* studentList);
void convertDataToTextFile(Student* studentList);
void convertDataToBinaryFile(Student* studentList);
int convertTextFileToBinaryFile();
void addEntry(Student* studentList);
int changeEntry(Student* studentList);
int deleteEntry(Student* studentList);
int sort(Student* studentList);

//прототипы дополнительных функций
void printMenuList();
void printTextFileNames();
void printBinaryFileNames();
int inputNum(const char inputLine[], int floor = -2147483648, int ceil = 2147483647);
char* substr(const char str[], int start, int end);
int linesCount(int & len, int& maxWidth);
char* inputStr(const char inputLine[], int size, bool isOnlyCharacters = false);
char* inputFileName(const char inputLine[], bool isBinary);
ofstream getOfstream(bool isBinary);
ifstream getIfstream(bool isBinary);
void structFromLine(char line[], Student& temp);
char* printw(const char str[1024], int width);
char* printwInt(int num, int width);
void inputFromKeyboard(Student* studentList, int index);
int maxNum(int num1, int num2);
int intlen(int num);

//глобальные переменные
const int listLen = 1024;
const int lenGrades = 7;
int border = 0;

//основная функция (меню)
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::setlocale(LC_ALL, "Russian");

    Student studentList[listLen]{};

    bool isExit = false;
    int menuNumber;
    while (!isExit) {
        system("cls");
        printMenuList();
        menuNumber = inputNum("\nВыберите пункт меню: ", 1, 14);
        switch (menuNumber) {
            case DATA_INPUT_FROM_KEYBOARD:
                dataInputFromKeyboard(studentList);
                break;
            case DATA_FROM_TEXT_FILE:
                dataFromTextFile(studentList);
                break;
            case DATA_FROM_BINARY_FILE:
                dataFromBinaryFile(studentList);
                break;
            case OUTPUT_DATA_TO_CONSOLE:
                outputData(studentList, false);
                break;
            case OUTPUT_DATA_TO_FILE:
                outputData(studentList, true);
                break;
            case GET_DATA_BY_REQUEST:
                getDataByRequest(studentList);
                break;
            case CONVERT_DATA_TO_TEXT_FILE:
                convertDataToTextFile(studentList);
                break;
            case CONVERT_DATA_TO_BINARY_FILE:
                convertDataToBinaryFile(studentList);
            case CONVERT_TEXT_FILE_TO_BINARY_FILE:
                convertTextFileToBinaryFile();
                break;
            case ADD_ENTRY:
                addEntry(studentList);
                break;
            case CHANGE_ENTRY:
                changeEntry(studentList);
                break;
            case DELETE_ENTRY:
                deleteEntry(studentList);
                break;
            case SORTING:
                sort(studentList);
                break;
            case EXIT:
                isExit = true;
                break;
            default:
                break;
        }
    }
    return 0;
}

//основные функции
void dataInputFromKeyboard(Student* studentList) {
    border = 0;
    system("cls");
    int isExit = 1;
    while (isExit == 1) {
        system("cls");
        inputFromKeyboard(studentList, border);
        border += 1;
        system("cls");
        isExit = inputNum("Добавить еще одного студента? (1 - да, 2 - нет):", 1, 2);
    }
}

void dataFromTextFile(Student* studentList) {
    system("cls");
    printTextFileNames();
    ifstream fin = getIfstream(false);
    border = 0;
    int i = 0;
    char *line = new char[128]{};
    while (fin.getline(line, 128)) {
        structFromLine(line, studentList[i]);
        border++;
        i++;
    }
    system("cls");
    fin.close();
    cout << "База данных успешно импортирована из текстового файла" << endl;
    system("pause");
}

void dataFromBinaryFile(Student* studentList) {
    system("cls");
    printBinaryFileNames();
    ifstream fin = getIfstream(true);
    border = 0;
    int i = 0;
    Student buff{};
    while (fin.read((char *) &buff, sizeof(Student))) {
        studentList[i] = buff;
        border++;
        i++;
    }
    system("cls");
    fin.close();
    cout << "База данных успешно импортирована из бинарного файла" << endl;
    system("pause");
}

void outputData(Student* studentList, bool isFile) {
    if (border > 0) {
        system("cls");

        char number[] = "Номер";
        char lastName[] = "Фамилия";
        char course[] = "Курс";
        char group[] = "Группа";
        char firstSubject[] = "Математич. анализ";
        char secondSubject[] = "Аналитич.  геометрия";
        char thirdSubject[] = "Высокоур.  программ.";
        char fourthSubject[] = "Теоретич.  информатика";
        char fifthSubject[] = "Инженерная графика";
        char sixthSubject[] = "Иностранн. язык";
        char seventhSubject[] ="История    России";

        int *maxLinesCount = new int[border]{1};
        int maxLinesCountTop = 1;
        int maxWidth = 11;
        int lenNumber = 5;
        int lenLastName = 7;
        int lenCourse = 4;
        int lenGroup = 6;
        int lenFirstSG = 11;
        int lenSecondSG = 19;
        int lenThirdSG = 21;
        int lenFourthSG = 21;
        int lenFifthSG = 12;
        int lenSixthSG = 12;
        int lenSeventhSG = 14;
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenLastName, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenCourse, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenGroup, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenFirstSG, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenSecondSG, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenThirdSG, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenFourthSG, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenFifthSG, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenSixthSG, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenSeventhSG, maxWidth));
        for (int i = 0; i < border; i++) {
            lenLastName = maxNum(lenLastName, strlen(studentList[i].lastName));
            lenCourse = maxNum(lenCourse, intlen(studentList[i].course));
            lenGroup = maxNum(lenGroup, strlen(studentList[i].group));
            maxLinesCount[i] = maxNum(maxLinesCount[i], linesCount(lenLastName, maxWidth));
            maxLinesCount[i] = maxNum(maxLinesCount[i], linesCount(lenCourse, maxWidth));
            maxLinesCount[i] = maxNum(maxLinesCount[i], linesCount(lenGroup, maxWidth));
        }
        int length = 2 + lenLastName + lenCourse + lenGroup + lenFirstSG + lenSecondSG + lenThirdSG + lenFourthSG + lenFifthSG + lenSixthSG + lenSeventhSG + 49;

        int gradesLen[] = {lenFirstSG, lenSecondSG, lenThirdSG, lenFourthSG, lenFifthSG, lenSixthSG, lenSeventhSG};

        if (isFile) {
            printTextFileNames();
            ofstream fout = getOfstream(false);

            for (int i = 0; i < length; i++) {
                fout << "=";
            }
            fout << endl;

            for (int i = 0; i < maxLinesCountTop; i++) {
                fout << "|| " << substr(printw(number, lenNumber * maxLinesCountTop), i * lenNumber, (i + 1) * lenNumber);
                fout << " || " << substr(printw(lastName, lenLastName * maxLinesCountTop), i * lenLastName, (i + 1) * lenLastName);
                fout << " || " << substr(printw(course, lenCourse * maxLinesCountTop), i * lenCourse, (i + 1) * lenCourse);
                fout << " || " << substr(printw(group, lenGroup * maxLinesCountTop), i * lenGroup, (i + 1) * lenGroup);
                fout << " || " << substr(printw(firstSubject, lenFirstSG * maxLinesCountTop), i * lenFirstSG, (i + 1) * lenFirstSG);
                fout << " || " << substr(printw(secondSubject, lenSecondSG * maxLinesCountTop), i * lenSecondSG, (i + 1) * lenSecondSG);
                fout << " || " << substr(printw(thirdSubject, lenThirdSG * maxLinesCountTop), i * lenThirdSG, (i + 1) * lenThirdSG);
                fout << " || " << substr(printw(fourthSubject, lenFourthSG * maxLinesCountTop), i * lenFourthSG, (i + 1) * lenFourthSG);
                fout << " || " << substr(printw(fifthSubject, lenFifthSG * maxLinesCountTop), i * lenFifthSG, (i + 1) * lenFifthSG);
                fout << " || " << substr(printw(sixthSubject, lenSixthSG * maxLinesCountTop), i * lenSixthSG, (i + 1) * lenSixthSG);
                fout << " || " << substr(printw(seventhSubject, lenSeventhSG * maxLinesCountTop), i * lenSeventhSG, (i + 1) * lenSeventhSG) << " ||";
                fout << endl;
            }
            for (int i = 0; i < border; i++) {
                for (int k = 0; k < length; k++) {
                    fout << "=";
                }
                for (int j = 0; j < maxLinesCount[i]; j++) {

                    fout << endl;
                    fout << "|| " << substr(printwInt(i + 1, lenNumber * maxLinesCount[i]), j * lenNumber, (j + 1) * lenNumber);
                    fout << " || " << substr(printw(studentList[i].lastName, lenLastName * maxLinesCount[i]), j * lenLastName, (j + 1) * lenLastName);
                    fout << " || " << substr(printwInt(studentList[i].course, lenCourse * maxLinesCount[i]), j * lenCourse, (j + 1) * lenCourse);
                    fout << " || " << substr(printw(studentList[i].group, lenGroup * maxLinesCount[i]), j * lenGroup, (j + 1) * lenGroup);
                    for (int k = 0; k < lenGrades; k++) {
                        fout << " || " << substr(printwInt(studentList[i].grades[k], gradesLen[k] * maxLinesCount[i]), j * gradesLen[k], (j + 1) * gradesLen[k]);
                    }
                    fout << " ||";
                }
                fout << endl;
            }
            for (int i = 0; i < length; i++) {
                fout << "=";
            }
            fout << endl;
            cout << "Таблица успешно выведена в файл" <<
            system("pause");
        }
        else {
            for (int i = 0; i < length; i++) {
                cout << "=";
            }
            cout << endl;

            for (int i = 0; i < maxLinesCountTop; i++) {
                cout << "|| " << substr(printw(number, lenNumber * maxLinesCountTop), i * lenNumber, (i + 1) * lenNumber);
                cout << " || " << substr(printw(lastName, lenLastName * maxLinesCountTop), i * lenLastName, (i + 1) * lenLastName);
                cout << " || " << substr(printw(course, lenCourse * maxLinesCountTop), i * lenCourse, (i + 1) * lenCourse);
                cout << " || " << substr(printw(group, lenGroup * maxLinesCountTop), i * lenGroup, (i + 1) * lenGroup);
                cout << " || " << substr(printw(firstSubject, lenFirstSG * maxLinesCountTop), i * lenFirstSG, (i + 1) * lenFirstSG);
                cout << " || " << substr(printw(secondSubject, lenSecondSG * maxLinesCountTop), i * lenSecondSG, (i + 1) * lenSecondSG);
                cout << " || " << substr(printw(thirdSubject, lenThirdSG * maxLinesCountTop), i * lenThirdSG, (i + 1) * lenThirdSG);
                cout << " || " << substr(printw(fourthSubject, lenFourthSG * maxLinesCountTop), i * lenFourthSG, (i + 1) * lenFourthSG);
                cout << " || " << substr(printw(fifthSubject, lenFifthSG * maxLinesCountTop), i * lenFifthSG, (i + 1) * lenFifthSG);
                cout << " || " << substr(printw(sixthSubject, lenSixthSG * maxLinesCountTop), i * lenSixthSG, (i + 1) * lenSixthSG);
                cout << " || " << substr(printw(seventhSubject, lenSeventhSG * maxLinesCountTop), i * lenSeventhSG, (i + 1) * lenSeventhSG) << " ||";
                cout << endl;
            }
            for (int i = 0; i < border; i++) {
                for (int k = 0; k < length; k++) {
                    cout << "=";
                }
                for (int j = 0; j < maxLinesCount[i]; j++) {

                    cout << endl;
                    cout << "|| " << substr(printwInt(i + 1, lenNumber * maxLinesCount[i]), j * lenNumber, (j + 1) * lenNumber);
                    cout << " || " << substr(printw(studentList[i].lastName, lenLastName * maxLinesCount[i]), j * lenLastName, (j + 1) * lenLastName);
                    cout << " || " << substr(printwInt(studentList[i].course, lenCourse * maxLinesCount[i]), j * lenCourse, (j + 1) * lenCourse);
                    cout << " || " << substr(printw(studentList[i].group, lenGroup * maxLinesCount[i]), j * lenGroup, (j + 1) * lenGroup);
                    for (int k = 0; k < lenGrades; k++) {
                        cout << " || " << substr(printwInt(studentList[i].grades[k], gradesLen[k] * maxLinesCount[i]), j * gradesLen[k], (j + 1) * gradesLen[k]);
                    }
                    cout << " ||";
                }
                cout << endl;
            }
            for (int i = 0; i < length; i++) {
                cout << "=";
            }
            cout << endl;
        }
    }
    else {
        system("cls");
        cout << "Пустая таблица" << endl << endl;
    }
    cout << endl;
    if (!isFile) {
        system("pause");
    }
    system("cls");
}

void getDataByRequest(Student* studentList) {
    system("cls");
    if (border) {
        system("cls");
        float average = 0, maxAverage = 0;
        int index = 0;
        for (int i = 0; i < border; i++) {
            for (int grade : studentList[i].grades) {
                average += grade;
            }
            average /= 7;
            if (average > maxAverage) {
                index = i;
                maxAverage = average;
            }
        }

        char number[] = "Номер";
        char lastName[] = "Фамилия";
        char course[] = "Курс";
        char group[] = "Группа";
        char firstSubject[] = "Математич. анализ";
        char secondSubject[] = "Аналитич.  геометрия";
        char thirdSubject[] = "Высокоур.  программ.";
        char fourthSubject[] = "Теоретич.  информатика";
        char fifthSubject[] = "Инженерная графика";
        char sixthSubject[] = "Иностранн. язык";
        char seventhSubject[] ="История    России";

        int maxLinesCount = 1;
        int maxLinesCountTop = 1;
        int maxWidth = 11;
        int lenNumber = 5;
        int lenLastName = 7;
        int lenCourse = 4;
        int lenGroup = 6;
        int lenFirstSG = 11;
        int lenSecondSG = 15;
        int lenThirdSG = 16;
        int lenFourthSG = 17;
        int lenFifthSG = 12;
        int lenSixthSG = 12;
        int lenSeventhSG = 14;
        lenLastName = maxNum(lenLastName, strlen(studentList[index].lastName));
        lenCourse = maxNum(lenCourse, intlen(studentList[index].course));
        lenGroup = maxNum(lenGroup, strlen(studentList[index].group));
        lenFirstSG = maxNum(lenFirstSG, intlen(studentList[index].grades[0]));
        lenSecondSG = maxNum(lenSecondSG, intlen(studentList[index].grades[1]));
        lenThirdSG = maxNum(lenThirdSG, intlen(studentList[index].grades[2]));
        lenFourthSG = maxNum(lenFourthSG, intlen(studentList[index].grades[3]));
        lenFifthSG = maxNum(lenFifthSG, intlen(studentList[index].grades[4]));
        lenSixthSG = maxNum(lenSixthSG, intlen(studentList[index].grades[5]));
        lenSeventhSG = maxNum(lenSeventhSG, intlen(studentList[index].grades[6]));

        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenLastName, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenCourse, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenGroup, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenFirstSG, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenSecondSG, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenThirdSG, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenFourthSG, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenFifthSG, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenSixthSG, maxWidth));
        maxLinesCountTop = maxNum(maxLinesCountTop, linesCount(lenSeventhSG, maxWidth));

        lenLastName = maxNum(lenLastName, strlen(studentList[index].lastName));
        lenCourse = maxNum(lenCourse, intlen(studentList[index].course));
        lenGroup = maxNum(lenGroup, strlen(studentList[index].group));
        maxLinesCount = maxNum(maxLinesCount, linesCount(lenLastName, maxWidth));
        maxLinesCount = maxNum(maxLinesCount, linesCount(lenCourse, maxWidth));
        maxLinesCount = maxNum(maxLinesCount, linesCount(lenGroup, maxWidth));

        int length =
                lenLastName + lenCourse + lenGroup + lenFirstSG + lenSecondSG + lenThirdSG + lenFourthSG + lenFifthSG +
                lenSixthSG + lenSeventhSG + 51;

        int gradesLen[] = {lenFirstSG, lenSecondSG, lenThirdSG, lenFourthSG, lenFifthSG, lenSixthSG, lenSeventhSG};

        for (int i = 0; i < length; i++) {
            cout << "=";
        }
        cout << endl;

        for (int i = 0; i < maxLinesCountTop; i++) {
            cout << "|| " << substr(printw(number, lenNumber * maxLinesCountTop), i * lenNumber, (i + 1) * lenNumber);
            cout << " || " << substr(printw(lastName, lenLastName * maxLinesCountTop), i * lenLastName, (i + 1) * lenLastName);
            cout << " || " << substr(printw(course, lenCourse * maxLinesCountTop), i * lenCourse, (i + 1) * lenCourse);
            cout << " || " << substr(printw(group, lenGroup * maxLinesCountTop), i * lenGroup, (i + 1) * lenGroup);
            cout << " || " << substr(printw(firstSubject, lenFirstSG * maxLinesCountTop), i * lenFirstSG, (i + 1) * lenFirstSG);
            cout << " || " << substr(printw(secondSubject, lenSecondSG * maxLinesCountTop), i * lenSecondSG, (i + 1) * lenSecondSG);
            cout << " || " << substr(printw(thirdSubject, lenThirdSG * maxLinesCountTop), i * lenThirdSG, (i + 1) * lenThirdSG);
            cout << " || " << substr(printw(fourthSubject, lenFourthSG * maxLinesCountTop), i * lenFourthSG, (i + 1) * lenFourthSG);
            cout << " || " << substr(printw(fifthSubject, lenFifthSG * maxLinesCountTop), i * lenFifthSG, (i + 1) * lenFifthSG);
            cout << " || " << substr(printw(sixthSubject, lenSixthSG * maxLinesCountTop), i * lenSixthSG, (i + 1) * lenSixthSG);
            cout << " || " << substr(printw(seventhSubject, lenSeventhSG * maxLinesCountTop), i * lenSeventhSG, (i + 1) * lenSeventhSG) << " ||";
            cout << endl;
        }
        for (int k = 0; k < length; k++) {
            cout << "=";
        }
        for (int j = 0; j < maxLinesCount; j++) {
            cout << endl;
            cout << "|| " << substr(printwInt(index + 1, lenNumber * maxLinesCount), j * lenNumber, (j + 1) * lenNumber);
            cout << " || " << substr(printw(studentList[index].lastName, lenLastName * maxLinesCount), j * lenLastName, (j + 1) * lenLastName);
            cout << " || " << substr(printwInt(studentList[index].course, lenCourse * maxLinesCount), j * lenCourse, (j + 1) * lenCourse);
            cout << " || " << substr(printw(studentList[index].group, lenGroup * maxLinesCount), j * lenGroup, (j + 1) * lenGroup);
            for (int k = 0; k < lenGrades; k++) {
                cout << " || "
                     << substr(printwInt(studentList[index].grades[k], gradesLen[k] * maxLinesCount), j * gradesLen[k],
                               (j + 1) * gradesLen[k]);
            }
            cout << " ||";
            cout << endl;
        }
        for (int k = 0; k < length; k++) {
            cout << "=";
        }
        cout << endl << endl;
        system("pause");
    }
    else {
        cout << "Пустая таблица" << endl;
        system("pause");
    }
}

//дополнительные функции
void printMenuList() {
    cout << "\tСписок комманд:" << endl;
    cout << "1. Ввод информации с клавиатуры" << endl;
    cout << "2. Ввод информации из текстового файла" << endl;
    cout << "3. Ввод информации из бинарного файла" << endl;
    cout << "4. Вывод данных на экран" << endl;
    cout << "5. Вывод данных в файл" << endl;
    cout << "6. Распечатка информации данных по запросу" << endl;
    cout << "7. Перевод базы данных в текстовый файл" << endl;
    cout << "8. Перевод базы данных в бинарный файл" << endl;
    cout << "9. Перевод содержимого текстового файла в бинарный файл;" << endl;
    cout << "10. Добавление записи" << endl;
    cout << "11. Изменение записи" << endl;
    cout << "12. Удаление записи" << endl;
    cout << "13. Сортировка" << endl;
    cout << "14. Выход" << endl;
}

void printTextFileNames() {
    cout << "\nТекстовые файлы:" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << "data" << i << ".txt" << endl;
    }
    for (int i = 1; i <= 3; i++) {
        cout << "output" << i << ".txt" << endl;
    }
    cout << endl;
    cout << "Для выхода в меню введите exit" << endl;
    cout << endl;
}

void printBinaryFileNames() {
    cout << "\nБинарные файлы:" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << "data" << i << ".bin" << endl;
    }
    cout << endl;
    cout << "Для выхода в меню введите exit" << endl;
    cout << endl;
}

void inputFromKeyboard(Student* studentList, int index) {
    strcpy(studentList[index].lastName, inputStr("Введите фамилию: ", 64, true));
    system("cls");
    studentList[index].course = inputNum("Введите курс (1-6): ", 1, 6);
    system("cls");
    strcpy(studentList[index].group, inputStr("Введите группу: ", 32));
    system("cls");
    char outputString[1024] = "Введите оценки по ";
    char outputStringCopy[1024] = "Введите оценки по ";
    char subjects[][64] = {"мат. анализу", "анал. геометрии", "высокоур. прогр.", "теор. информатике", "инж. графике", "иностр. языку", "истории России"};
    for (int j = 0; j < 7; j++) {
        strcat(outputString, subjects[j]);
        studentList[index].grades[j] = inputNum(outputString, 2, 5);
        strcpy(outputString, outputStringCopy);
        system("cls");
    }
}

int inputNum(const char inputLine[], int floor, int ceil) {
    cout << inputLine << endl;
    char num[1024] = "";
    cin.getline(num, 1024);
    if (strlen(num) == 0) {
        cout << "Строка не может быть пустой" << endl;
        return inputNum(inputLine, floor, ceil);
    }
    else {
        for (int i = 0; num[i]; i++) {
            if (num[i] < 48 || num[i] > 57) {
                cout << "В числе должны быть только цифры" << endl;
                return inputNum(inputLine, floor, ceil);
            }
        }
        int input = atoi(num);
        if (input < floor || input > ceil) {
            cout << "Число должно быть в диапазоне от " << floor << " до " << ceil << endl;
            return inputNum(inputLine, floor, ceil);
        }
        return input;
    }
}

char* substr(const char str[], int start, int end) {
    char* resStr = new char[128]{};
    int resIndex = 0;
    for (int i = start; i < end; i++) {
        resStr[resIndex] = str[i];
        resIndex++;
    }
    return resStr;
}

int linesCount(int& len, int& maxWidth) {
    int linesCount = 1;
    if (len > maxWidth) {
        linesCount = ceil((double) len / maxWidth);
        len = maxWidth;
    }
    return linesCount;
}

char* inputStr(const char inputLine[], int size,  bool isOnlyCharacters) {
    cout << inputLine << endl;
    char *str = new char[1024]{};
    cin.getline(str, 1024);
    if (strlen(str) == 0) {
        cout << "Строка не может быть пустой" << endl;
        return inputStr(inputLine, size, isOnlyCharacters);
    }
    else {
        for (int i = 0; str[i]; i++) {
            if (!(str[i] >= 65 && str[i] <= 90) && !(str[i] >= 97 && str[i] <= 122) && !(str[i] >= -64 && str[i] <= -1) && str[i] != 45) {
                if (isOnlyCharacters && str[i] >= 48 && str[i] <= 57) {
                    cout << "В строке должны быть только символы русского и английского алфавита и тире" << endl;
                    return inputStr(inputLine, size, isOnlyCharacters);
                }
                else if (!(str[i] >= 48 && str[i] <= 57)) {
                    cout << "В строке должны быть только цифры, символы русского и английского алфавита и тире" << endl;
                    return inputStr(inputLine, size, isOnlyCharacters);
                }
            }
        }
        str[size - 1] = '\0';
        return str;
    }
}

char* inputFileName(const char inputLine[], bool isBinary) {
    cout << inputLine << endl;
    char *str = new char[1024]{};
    cin.getline(str, 1024);
    int len = strlen(str);
    if (len == 0) {
        cout << endl << "Имя файла не может быть пустым" << endl << endl;
        return inputFileName(inputLine, isBinary);
    }
    else {
        for (int i = 0; str[i]; i++) {
            if (!isBinary) {
                if ((str[i] < 48 || str[i] > 57) && !(str[i] >= 65 && str[i] <= 90) && !(str[i] >= 97 && str[i] <= 122) && !(str[i] >= -64 && str[i] <= -1) && str[i] != '-' && str[i] != '.' && str[i] != '_') {
                    cout << endl << "Имя файла должно содержать только буквы, цифры, тире, нижнее подчеркивание и точку" << endl << endl;
                    return inputFileName(inputLine, isBinary);
                }
            }
        }
        if (strcmp(str, "exit") == 0) {
            return str;
        }
        if (isBinary) {
            if (!(str[len - 4] == '.' && str[len - 3] == 'b' && str[len - 2] == 'i' && str[len - 1] == 'n')) {
                cout << endl << "Файл должен иметь расширение .bin" << endl << endl;
                return inputFileName(inputLine, isBinary);
            }
        }
        else {
            if (!(str[len - 4] == '.' && str[len - 3] == 't' && str[len - 2] == 'x' && str[len - 1] == 't')) {
                cout << endl << "Файл должен иметь расширение .txt" << endl << endl;
                return inputFileName(inputLine, isBinary);
            }
        }
        return str;
    }
}

ofstream getOfstream(bool isBinary) {
    ofstream fout{};
    char fileName[128] = "";
    strcpy(fileName, inputFileName("Введите имя файла:", isBinary));
    if (strcmp(fileName, "exit") == 0) {
        return fout;
    }
    fout.open(fileName, ios::out);
    while (!fout.is_open()) {
        cout << endl << "Файл с таким именем не обнаружен" << endl << endl;
        strcpy(fileName, inputFileName("Введите имя файла:", isBinary));
        if (strcmp(fileName, "exit") == 0) {
            return fout;
        }
        fout.open(fileName, ios::out);
    }
    return fout;
}

ifstream getIfstream(bool isBinary) {
    ifstream fin{};
    char fileName[128] = "";
    strcpy(fileName, inputFileName("Введите имя файла:", isBinary));
    if (strcmp(fileName, "exit") == 0) {
        return fin;
    }
    fin.open(fileName, ios::in);
    while (!fin.is_open()) {
        cout << endl << "Файл с таким именем не обнаружен" << endl << endl;
        strcpy(fileName, inputFileName("Введите имя файла:", isBinary));
        if (strcmp(fileName, "exit") == 0) {
            return fin;
        }
        fin.open(fileName, ios::in);
    }
    return fin;
}

void structFromLine(char* line, Student& temp) {
    char *ptr = strtok(line, " ");
    strcpy(temp.lastName, ptr);
    ptr = strtok(nullptr, " ");
    temp.course = atoi(ptr);
    ptr = strtok(nullptr, " ");
    strcpy(temp.group, ptr);
    ptr = strtok(nullptr, " ");
    for (int & grade : temp.grades) {
        grade = atoi(ptr);
        ptr = strtok(nullptr, " ");
    }
    delete ptr;
}

char* printw(const char str[1024], int width) {
    char *buff = new char[1024];
    strcpy(buff, str);
    for (int i = 0; i < width - strlen(str); i++) {
        strcat(buff, " ");
    }
    return buff;
}

char* printwInt(int num, int width) {
    char str[1024] = "";
    itoa(num, str, 10);
    return printw(str, width);
}

int maxNum(int num1, int num2) {
    if (num1 > num2) {
        return num1;
    }
    else {
        return num2;
    }
}

int intlen (int num) {
    char strnum[1024] = "";
    itoa(num, strnum, 10);
    return strlen(strnum);
}

void convertDataToTextFile(Student* studentList) {
    system("cls");
    printTextFileNames();
    ofstream fout = getOfstream(false);
    for (int i = 0; i < border; i++) {
        fout << studentList[i].lastName;
        fout << " ";
        fout << studentList[i].course;
        fout << " ";
        fout << studentList[i].group;
        fout << " ";
        for (int j = 0; j < lenGrades; j++) {
            fout << studentList[i].grades[j];
            if (j != lenGrades) {
                fout << " ";
            }
        }
        fout << endl;
    }
    cout << "База данных успешно записана в текстовый файл" << endl;
    system("pause");
}

void convertDataToBinaryFile(Student* studentList) {
    system("cls");
    printBinaryFileNames();
    ofstream fout = getOfstream(true);
    for (int i = 0; i < border; i++) {
        fout.write((char*) &studentList[i], sizeof(Student));
    }
    fout.close();
    cout << "База данных успешно записана в бинарный файл" << endl;
    system("pause");
}

int convertTextFileToBinaryFile() {
    system("cls");
    printTextFileNames();
    ifstream fin = getIfstream(false);
    if (!fin.is_open()) {
        return -1;
    }
    system("cls");
    printBinaryFileNames();
    ofstream fout = getOfstream(true);
    char buff[128] = "";
    Student temp{};
    while (fin.getline(buff, 128)) {
        structFromLine(buff, temp);
        fout.write((char*) &temp, sizeof(Student));
    }
    system("cls");
    fin.close();
    fout.close();
    cout << "Перевод из текстового файла в бинарный прошел успешно" << endl;
    system("pause");
    return 0;
}

void addEntry(Student* studentList) {
    system("cls");
    inputFromKeyboard(studentList, border);
    border += 1;
}

int changeEntry(Student* studentList) {
    if (!border) {
        cout << "Пустая таблица, изменение записи не удалось" << endl;
        system("pause");
    }
    system("cls");
    int index = inputNum("Введите номер строки которую нужно изменить:", 1, border) - 1;
    inputFromKeyboard(studentList, index);
}

int deleteEntry(Student* studentList) {
    system("cls");
    if (border) {
        int index = inputNum("Введите номер записи которую нужно удалить:", 1, border) - 1;
        for (int i = index; i < border - 1; i++) {
            studentList[i] = studentList[i + 1];
        }
        border--;
        cout << "Запись под номером " << index << " удалена успешно" << endl;
    }
    else {
        cout << "Пустая таблица, удаление записи не удалось" << endl;
        system("pause");
    }
}

int sort(Student* studentList) {
    system("cls");
    if (!border) {
        cout << "Таблица пустая, сортировка не выполнена" << endl;
        system("pause");
        return 1;
    }
    cout << "Сортировка по:" << endl;
    cout << "1. Сортировка по фамилии" << endl;
    cout << "2. Сортировка по номеру курса" << endl;
    cout << "3. Сортировка по группе" << endl;
    cout << "4. Сортировка по оценкам по математическому анализу" << endl;
    cout << "5. Сортировка по оценкам по аналитической геометрии" << endl;
    cout << "6. Сортировка по оценкам по высокоуровневому программированию" << endl;
    cout << "7. Сортировка по оценкам по теоретической информатике" << endl;
    cout << "8. Сортировка по оценкам по инженерной графике" << endl;
    cout << "9. Сортировка по оценкам по иностранному языку" << endl;
    cout << "10. Сортировка по оценкам по истории России" << endl;
    int sortNumber = inputNum("\nВыберите сортировку: ", 1, 10);
    int isReversed{};
    int first{}, second{};
    system("cls");
    if (sortNumber == 1) {
        cout << "1. Сортировка по возрастанию" << endl;
        cout << "2. Сортировка по убыванию" << endl;
        isReversed = inputNum("Выберите метод сортировки:", 1, 2);
        for (int i = 0; i < border - 1; i++) {
            for (int j = i + 1; j < border; j++) {
                if (isReversed == 2) {
                    first = j;
                    second = i;
                } else {
                    first = i;
                    second = j;
                }
                if (strcmp(studentList[first].lastName, studentList[second].lastName) > 0) {
                    border++;
                    studentList[border] = studentList[first];
                    studentList[first] = studentList[second];
                    studentList[second] = studentList[border];
                    border--;
                }
            }
        }
        system("cls");
    }
    else if (sortNumber == 2) {
        cout << "1. Сортировка по возрастанию" << endl;
        cout << "2. Сортировка по убыванию" << endl;
        isReversed = inputNum("Выберите метод сортировки:", 1, 2);
        for (int i = 0; i < border - 1; i++) {
            for (int j = i + 1; j < border; j++) {
                if (isReversed == 2) {
                    first = j;
                    second = i;
                } else {
                    first = i;
                    second = j;
                }
                if (studentList[first].course > studentList[second].course) {
                    border++;
                    studentList[border] = studentList[first];
                    studentList[first] = studentList[second];
                    studentList[second] = studentList[border];
                    border--;
                }
            }
        }
        system("cls");
    }
    else if (sortNumber == 3) {
        cout << "1. Сортировка по возрастанию" << endl;
        cout << "2. Сортировка по убыванию" << endl;
        isReversed = inputNum("Выберите метод сортировки:", 1, 2);
        for (int i = 0; i < border - 1; i++) {
            for (int j = i + 1; j < border; j++) {
                if (isReversed == 2) {
                    first = j;
                    second = i;
                } else {
                    first = i;
                    second = j;
                }
                if (strcmp(studentList[first].group, studentList[second].group) > 0) {
                    border++;
                    studentList[border] = studentList[first];
                    studentList[first] = studentList[second];
                    studentList[second] = studentList[border];
                    border--;
                }
            }
        }
        system("cls");
    }
    else if (sortNumber >= 4 && sortNumber <= 10) {
        cout << "1. Сортировка по возрастанию" << endl;
        cout << "2. Сортировка по убыванию" << endl;
        isReversed = inputNum("Выберите метод сортировки:", 1, 2);
        for (int i = 0; i < border - 1; i++) {
            for (int j = i + 1; j < border; j++) {
                if (isReversed == 2) {
                    first = j;
                    second = i;
                } else {
                    first = i;
                    second = j;
                }
                if (studentList[first].grades[sortNumber - 4] > studentList[second].grades[sortNumber - 4]) {
                    border++;
                    studentList[border] = studentList[first];
                    studentList[first] = studentList[second];
                    studentList[second] = studentList[border];
                    border--;
                }
            }
        }
        cout << "Сортировка выполнена успешно" << endl;
        system("pause");
        return 0;
    }
}

#pragma clang diagnostic pop