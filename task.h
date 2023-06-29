//
// Created by Colli on 6/27/2023.
//

#ifndef STRUCTSREVIEWASSIGNMENT_TASK_H
#define STRUCTSREVIEWASSIGNMENT_TASK_H
#include <iostream>
using namespace std;

enum class Category{
    operations_0 ,
    maintainance_1 ,
    inventory_2 ,
    communications_3 ,
    others_4
};


struct Task {
    int day = 0;
    char taskName[101];
    int duration = 0;
    char name[101];
    Category category;
};

void menu();
//void openFile(ifstream &inFile);
void openFile(char fileName[], ifstream &inFile);
void openFile(char fileName[], ofstream &outFile);
void outputFile(Task tasks[], int count, ofstream& outFile);
void loadData(ifstream &inFile, Task tasks[], int &count);
void printData(Task tasks[], int count);
char readInput();
bool isLessThan(char name1[], char name2[]);
void addTask(Task tasks[], int& count);
void searchByTaskName(Task tasks[], int count);
void removeTask(Task tasks[], int &size);
void exeCmd(char option, Task tasks[], int &size);
#endif //STRUCTSREVIEWASSIGNMENT_TASK_H
