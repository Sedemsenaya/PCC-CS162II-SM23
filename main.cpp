#include <iostream>
#include <fstream>
#include "main.h"

using namespace std;
int main() {
    ifstream inFile;
    ofstream outFile;
    Task tasks[101];
    int size = 0;
    char option;
    char filename[101] = "tasks.txt";
    openFile(filename , inFile);
    loadData(inFile, tasks, size);
    cout << "Welcome!\n";
    cout << "This program will help you manage your tasks for this Space Station.\n";
    do{
        menu();
        option = readInput();
        exeCmd(option, tasks, size );
    }
    while (tolower(option) != 'q');
    char filename1[101] = "tasks1.txt";
    openFile(filename1, outFile);
    outputFile(tasks, size, outFile);
//
//    printData(tasks, size);
//    addTask(tasks, size);
//    printData(tasks, size);
//    searchByTaskName(tasks, size);
//    removeTask(tasks, size);
//    printData(tasks, size);
//    openFile(inFile);
    loadData(inFile, tasks, size);
//    outputFile(tasks, size, );

    return 0;
}
