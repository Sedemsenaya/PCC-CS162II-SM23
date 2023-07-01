#include <iostream>
#include <fstream>
#include "main.h"
#include <cstring>

using namespace std;


int main() {
    Tasks tasks;
    tasks.tasksCount = 0;
    Task task;
    int size = 0;
    char option;
    char fileName[51] = "tasks.txt";
    ifstream inFile;
    ofstream outFile;
    openFile(fileName,  inFile);
    loadTasks(tasks, fileName);
    cout << "Welcome!\n";
    cout << "This program will help you manage your tasks for this Space Station.\n\n";
    do{
        menu();
        option = readInput();
        exeCmd(option, tasks);
    }
    while (tolower(option) != 'q');
    char filename1[51] = "tasks1.txt";
    openFile(filename1, outFile);
    outputFile(tasks, outFile);
    return 0;
}
