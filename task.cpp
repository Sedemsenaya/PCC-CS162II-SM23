//
// Created by Colli on 6/30/2023.
//

#include "task.h"
#include <cstring>
#include <iostream>
#include <ostream>
#include <fstream>

using namespace std;

void menu(){
    cout <<"Pick an option from below\n\n";
    cout << "(a)Add a new task\n";
    cout << "(b)List tasks by name\n";
    cout << "(c)Remove tasks by index\n";
    cout << "(d)Search tasks by task name\n";
    cout << "(q)Quit\n";
}

//open file to read from
void openFile(char fileName[], ifstream &inFile){
    inFile.open(fileName);
    if(! inFile.is_open())
    {
        cout << "could not open file\n";
        exit(0);
    }
}
//open file to write to
void openFile(char fileName[], ofstream &outFile){
    outFile.open(fileName);
    if(! outFile.is_open())
    {
        cout << "could not open file\n";
        exit(0);
    }
}


//print file contents
void printTasks(Tasks & thetasks){
    if(thetasks.tasksCount == 0)
    {
        cout << "There are no tasks\n";
    }
    for (int i = 0; i < thetasks.tasksCount; i++) {
        int cat = static_cast<int>(thetasks.tasks[i].type);
        string category= "";
        switch (cat) {
            case 0:
                category = "Operations";
                break;
            case 1:
                category = "Maintenance";
                break;
            case 2:
                category = "Inventory";
                break;
            case 3:
                category = "Communications";
                break;
            case 4:
                category = "Others";
                break;
        }
        cout << i + 1 << ". " << thetasks.tasks[i].day << ";" << thetasks.tasks[i].taskName << ";" << thetasks.tasks[i].duration << ";" << thetasks.tasks[i].personName << ";" << category<< endl;
    }
    cout << "\n";
}

int validDay(){
    int value = 0;
    char numberStr[51];
    do {
        std::cin.getline(numberStr, 51);
        value = atoi(numberStr); // Hello
        if(value <= 0) {
            cout<<"Invalid day! Must be between 1 and 30 inclusive!\n";
            cout <<"Enter the day of the task (whole numbers between 1 and 30): ";
        }
    }while(value <= 0 || value > 30);
    return value;
}

int validDuration(){
    int value = 0;
    char numberStr[51];
    do {
        std::cin.getline(numberStr, 51);
        value = atoi(numberStr); // Hello
        if(value <= 0) {
            cout<<"Invalid hour! Must be between 1 and 10 inclusive!\n";
            cout <<"Enter the number of hours (whole numbers between 1 and 10): ";
        }
    }while(value <= 0 || value > 10);
    return value;
}


//load item
void loadTask(Task & task)
{
    int strSize = 30;
    char numberStr[strSize];
    cout <<"Enter the day of the task (whole numbers between 1 and 30): ";
    task.day = validDay();

    cout <<"Enter the task name (50 characters or less): ";
    cin.getline(task.taskName, strSize);

    cout <<"Enter the person's name (50 characters or less): ";
    cin.getline(task.personName, strSize);

    cout <<"Enter the number of hours (whole numbers between 1 and 10): ";
    task.duration = validDuration();


    cout <<"Enter the task type 0-Operations, 1-Maintenance, 2-Inventory, 3-communications, and 4-Others): ";
    int type;
    cin >> type;
    task.type = static_cast<Type>(type);
    while(!cin || cin.get() == '.' || type < 0 || type > 5) {
        cin.clear();
        cin.ignore(3, '\n');
        cout << "Invalid operation! Must be between 0 and 4 inclusive!\n";
        cout << "Enter the task type 0-Operations, 1-Maintenance, 2-Inventory, 3-communications, and 4-Others): ";
        cin >> type;
        task.type = static_cast<Type>(type);
    }
}

// load from file
bool loadTasks(Tasks & tasks, char fileName[])
{

    ifstream inFile(fileName);
    char numStr[30];
    Task tempTask;
    bool result = false, stillRoom = true;

    if(inFile.is_open())
    {
        do {
            if(tasks.tasksCount >= 30)
            {
                cout << "Array is full.\n";
                stillRoom = false;
            }
            else
            {
                inFile.getline(numStr, 51, ';');
                tempTask.day = atoi(numStr);
                inFile.getline(tempTask.taskName, 51, ';');
                inFile.getline(numStr, 51 , ';');
                tempTask.duration = atoi(numStr);
                inFile.getline(tempTask.personName, 51, ';');
                inFile.getline(numStr, 51);
                tempTask.type = static_cast<Type>(atoi(numStr));
                addTask(tasks, tempTask);
            }
            inFile.peek();
        } while(!inFile.eof() && stillRoom);
        result = true;
    }
    inFile.close();
    return result;
}

bool shiftUpAndInsert(Tasks & tasks, Task & task, int index)
{
    bool result = false;
    if(tasks.tasksCount >= 51) { // No more room, return result = false.
        result = false;
    }
    else if (tasks.tasksCount == 0) {
        tasks.tasks[0] = task;      // If the list is empty, place item at index 0.
        tasks.tasksCount++;
    }
    else {
        result = true;
        for(int i = tasks.tasksCount; i >= index; i--) {
            tasks.tasks[i] = tasks.tasks[i - 1];
        }
        tasks.tasks[index] = task;  // Insert the new item.
        tasks.tasksCount++;          // count the new item.
    }
    return result;
}

bool addTask(Tasks & tasks, Task & task){
    bool result = false;
    int index = 0;
    index = getIndex(tasks, task);
    result = shiftUpAndInsert(tasks, task, index);
    cout << "\nTask  added!\n";
    return result;
}

int getIndex(const Tasks & tasks, const Task & task){
    int index = 0;
    for(index = 0; index < tasks.tasksCount; index++) {
        if(strcmp(tasks.tasks[index].personName, task.personName) >= 0) {
            // We found where the item should go at index.
            break;
        }
    }
    return index; // Where the new item should go.
}

bool searchByTaskName(Tasks & tasks){
    char srchStr[51];
    bool found = false;
    cout <<"Enter task name to find: ";
    cin.getline(srchStr, 101);
    for (int i = 0; i < tasks.tasksCount; i++) {
        if(strstr(tasks.tasks[i].taskName, srchStr) != NULL)
        {
            int cat = static_cast<int>(tasks.tasks[i].type);
            string category= "";
            switch (cat) {
                case 0:
                    category = "Operations";
                    break;
                case 1:
                    category = "Maintenance";
                    break;
                case 2:
                    category = "Inventory";
                    break;
                case 3:
                    category = "Communications";
                    break;
                case 4:
                    category = "Others";
                    break;
            }
            cout << i<< ". " <<tasks.tasks[i].day <<";"<< tasks.tasks[i].taskName <<";"<< tasks.tasks[i].duration<<";"<< tasks.tasks[i].personName <<";" << category<<endl;
            found = true;
        }
    }
    if(!found)
    {
        found  = false;
        cout << "Task not found!!"<<endl;
    }
    return found;
}

void removeTask(Tasks & tasks){
    int taskIndex = 0;
    cout << "Enter the index of task to remove: ";
    cin>>taskIndex;
    while(!cin || cin.get() == '.' || taskIndex < 1 || taskIndex > tasks.tasksCount)
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout<<"Invalid index number!\n";
        cout << "Enter the index of task to remove: ";
        cin>> taskIndex;
    }
    if(taskIndex < tasks.tasksCount)
    {
        for (int i = taskIndex; i < tasks.tasksCount; i++)
        {
            tasks.tasks[i-1] = tasks.tasks[i];
        }
    }
    cout <<"Task Removed!\n";
    tasks.tasksCount--;
}

char readInput(){
    char option;
    cin.get(option);
    cin.ignore(100,'\n');
    return option;
}


void exeCmd(char option, Tasks & tasks) {
    Task task;
    char fileName[51];
    bool success = false;
    switch (tolower(option)) {
        case 'a':
            if (tasks.tasksCount >= 51) {
                cout << "Your list is full! Task not added!!";
                return;
            }
            loadTask(task);
            success = addTask(tasks, task);
            break;
        case 'b':
            printTasks(tasks);
            break;
        case 'c':
            printTasks(tasks);
            removeTask(tasks);
            break;
        case 'd':
            searchByTaskName(tasks);
            break;
        case 'q':
            break;
        default:
            cout << "Invalid input, please try again!!" << endl;
    }
}

void outputFile(Tasks & thetasks, ofstream& outFile){
    for (int i = 0; i < thetasks.tasksCount; i++) {
        int cat = static_cast<int>(thetasks.tasks[i].type);
        string category= "";
        switch (cat) {
            case 0:
                category = "Operations";
                break;
            case 1:
                category = "Maintenance";
                break;
            case 2:
                category = "Inventory";
                break;
            case 3:
                category = "Communications";
                break;
            case 4:
                category = "Others";
                break;
        }
        outFile << i + 1 << ". " << thetasks.tasks[i].day << ";" << thetasks.tasks[i].taskName << ";" << thetasks.tasks[i].duration << ";" << thetasks.tasks[i].personName << ";" << category<< endl;
        }
        outFile.close();

}

