//
// Created by Colli on 6/27/2023.
//

#include "task.h"
#include <iostream>
#include <cstring>
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

char readInput(){
    char option;
    cin.get(option);
    cin.ignore(100,'\n');
    return option;
}



bool isLessThan(char name1[], char name2[]){
    if(strcmp(name1, name2) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}



void loadData(ifstream &inFile, Task tasks[], int &count){
    Task tempTasks;
    int i = 0;
    inFile.ignore(101,'\n');
    inFile>>tempTasks.day;
    while(!inFile.eof()){
        inFile.ignore(100,';');
        inFile.getline(tempTasks.taskName, 101, ';');
        inFile>>tempTasks.duration;
        inFile.ignore(100,';');
        inFile.getline(tempTasks.name, 101, ';');
        int categoryInput;
        inFile>> categoryInput;
        tempTasks.category = static_cast<Category>(categoryInput);
        inFile.ignore(101,'\n');
        count++;
        if(count == 101)
        {
            cout << "Array full!" << endl;
            return;
        }
        if(!count)
        {
            tasks[count] = tempTasks;
        }
        else
        {
            for(i = 0; i < count; i++)
            {
                if(!(isLessThan(tasks[i].name, tempTasks.name)))
                {
                    break;
                }
            }
            //in a loop copy one fruit object to the next space
            //This is the process of shifting to make room.
            for(int j = count; j > i; j--)
            {
                tasks[j] = tasks[j-1];
            }
            //insert into the right position AFTER shifting all the fruits
            tasks[i] = tempTasks;
        }
        //increment size - one more fruit inserted.
        inFile>>tempTasks.day;

    }
}


void printData(Task tasks[], int count){
    for (int i = 1; i <= count; i++) {
        int cat = static_cast<int>(tasks[i].category);
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
        cout << i<< ". " <<tasks[i].day <<";"<< tasks[i].taskName <<";"<< tasks[i].duration<<";"<< tasks[i].name <<";" << category<<endl;
    }
}

void addTask(Task tasks[], int& count){
    cout <<"Enter the day of the task (whole numbers between 1 and 30): ";
    cin>>tasks[count].day;
    while(!cin || cin.get() == '.' || tasks[count].day < 1 || tasks[count].day > 30)
    {
        cin.clear();
        cin.ignore(3, '\n');
        cout<<"Invalid day! Must be between 1 and 30 inclusive!\n";
        cout <<"Enter the day of the task (whole numbers between 1 and 30): ";
        cin>> tasks[count].day;
    }


    cout <<"Enter the task name (50 characters or less): ";
    cin.getline(tasks[count].taskName, 101);
    cout <<"Enter the person's name (50 characters or less): ";
    cin.getline(tasks[count].name, 101);
    cout <<"Enter the number of hours (whole numbers between 1 and 10): ";
    cin>>tasks[count].duration;
    while(!cin || cin.get() == '.' || tasks[count].duration < 1 || tasks[count].duration > 10)
    {
        cin.clear();
        cin.ignore(3, '\n');
        cout<<"Invalid hour! Must be between 1 and 10 inclusive!\n";
        cout <<"Enter the number of hours (whole numbers between 1 and 10): ";
        cin>> tasks[count].duration;
    }

    cout <<"Enter the task type 0-Operations, 1-Maintenance, 2-Inventory, 3-communications, and 4-Others): ";
    int categoryNum;
    cin>>categoryNum;
    tasks[count].category = static_cast<Category>(categoryNum);
    while(!cin || cin.get() == '.' || tasks[count].duration < 1 || tasks[count].duration > 10)
    {
        cin.clear();
        cin.ignore(3, '\n');
        cout<<"Invalid hour! Must be between 1 and 10 inclusive!\n";
        cout <<"Enter the task type 0-Operations, 1-Maintenance, 2-Inventory, 3-communications, and 4-Others): ";
        cin>>categoryNum;
        tasks[count].category = static_cast<Category>(categoryNum);
    }
    cout<< "Task added!\n";
}

void searchByTaskName(Task tasks[], int count){
    char srchStr[101];
    bool found = false;
    cout <<"Enter task name to find: ";
    cin.getline(srchStr, 101);
    for (int i = 0; i < count; i++) {
        if(strstr(tasks[i].taskName, srchStr) != NULL)
        {
            int cat = static_cast<int>(tasks[i].category);
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
            cout << i<< ". " <<tasks[i].day <<";"<< tasks[i].taskName <<";"<< tasks[i].duration<<";"<< tasks[i].name <<";" << category<<endl;
            found = true;
        }
    }
    if(!found)
    {
        cout << "Task not found!!"<<endl;
    }
}

void removeTask(Task tasks[], int &size){
    int taskIndex = 0;
    cout << "Enter the index of task to remove: ";
    cin>>taskIndex;
    while(!cin || cin.get() == '.' || taskIndex < 1 || taskIndex > size)
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout<<"Invalid index number!\n";
        cout << "Enter the index of task to remove: ";
        cin>> taskIndex;
    }
    if(taskIndex < size)
    {
        for (int i = taskIndex; i < size; i++)
        {
            tasks[i-1] = tasks[i];
        }
    }
    cout <<"Task Removed!\n";
    size--;
}

void exeCmd(char option, Task tasks[], int &size){
    Task tempTasks;
    switch (tolower(option)) {
        case 'a':
            if(size == 101)
            {
                cout << "Your list is full! Task not added!!";
                return;
            }
            addTask(tasks, size);
            break;
        case 'b':
            printData(tasks, size);
            break;
        case 'c':
            printData(tasks, size);
            removeTask(tasks, size);
            break;
        case 'd':
            searchByTaskName(tasks, size);
            break;
        case 'q':
            break;
        default:
            cout << "Invalid input, please try again!!" << endl;
    }

}

void outputFile(Task tasks[], int count, ofstream& outFile){
    for (int i = 1; i <= count; i++) {
        int cat = static_cast<int>(tasks[i].category);
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
        outFile << i<< ". " <<tasks[i].day <<";"<< tasks[i].taskName <<";"<< tasks[i].duration<<";"<< tasks[i].name <<";" << category<<endl;
    }
    outFile.close();
}

//This opens the output file
void openFile(char fileName[], ifstream &inFile)
{
    inFile.open(fileName);
    if(!inFile)
    {
        cout << "Output file did not open!! Program exiting!!!" << endl;
        exit(0);
    }
}
//This opens the output file
void openFile(char fileName[], ofstream &outFile)
{
    outFile.open(fileName);
    if(!outFile)
    {
        cout << "Output file did not open!! Program exiting!!!" << endl;
        exit(0);
    }
}