//
// Created by Colli on 6/30/2023.
//

#ifndef STRUCTREVIEWASSIGNMENT1_TASK_H
#define STRUCTREVIEWASSIGNMENT1_TASK_H
#include <cstring>
#include <iostream>

using namespace std;

//enum type
enum Type {
    Operations,
    Maintenance,
    Inventory,
    Communications,
    Others
};

//struct with 51 chars
struct Task{
    char taskName[30];
    char personName[30];
    int day;
    int duration;
    Type type;
};

//array of tasks to contain 51 tasks using Task
struct Tasks{
    Task tasks[51];
    int tasksCount = 0;
};

//prototype
void menu();
void openFile(char fileName[], ifstream &inFile);
void openFile(char fileName[], ofstream &outFile);
void outputFile(Tasks & tasks, ofstream& outFile);
void printTasks(Tasks & thetasks);
char readInput();
int validDay();
int validDuration();
void loadTask(Task & task);
bool loadTasks(Tasks & task, char fileName[]);
bool addTask(Tasks & tasks, Task & task);
bool shiftUpAndInsert(Tasks & tasks, Task & task, int index);
int getIndex(const Tasks & tasks, const Task & task);
bool searchByTaskName(Tasks &  tasks);
void removeTask(Tasks & tasks);
void exeCmd(char option, Tasks & tasks);
#endif //STRUCTREVIEWASSIGNMENT1_TASK_H
