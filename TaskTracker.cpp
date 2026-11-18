#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

vector<string> tasks;
vector<string> deadlines;
vector<string> doneTasks;
vector<string> doneDeadlines;

void addTask(){
    cin.ignore();

    string task;
    string deadline;

    cout << "\nEnter The Task: ";
    getline(cin, task);
    tasks.push_back(task);

    cout << "Enter The Deadline (dd-mm-yyyy): ";
    getline(cin, deadline);
    deadlines.push_back(deadline);
    cout << "Task Added Successfully!\n";
}

void editTask(string task){
    string newTask;

    cout << "\nEnter The New Task: ";
    cin >> newTask;

    for(int i = 0; i < tasks.size(); i++){
        if(task == tasks[i]){
            tasks[i] = newTask;
            cout << "Task Changed Successfully!\n";
        }
    }
}

void editDeadline(string task){
    string newDeadline;

    cout << "\nEnter The New Deadline: ";
    cin >> newDeadline;

    for(int i = 0; i < tasks.size(); i++){
        if(task == tasks[i]){
            deadlines[i] = newDeadline;
            cout << "Deadline Changed Successfully!\n";
        }
    }
}

void updateTask(){
    cin.ignore();

    string task;
    int userInput;

    cout << "\nEnter The Task: ";
    cin >> task;

    for(int i = 0; i < tasks.size(); i++){
        if(task == tasks[i]){
            continue;
        }
        else{
            cout << "Task Not Found!\n";
            return;
        }
    }

    do
    {
        cout << "1. Edit Task Name\n";
        cout << "2. Edit Task Deadline\n";
        cout << "3. Exit\n";
        cout << "Enter a number: ";
        cin >> userInput;

        switch (userInput)
        {
        case 1:
            editTask(task);
            break;
        case 2:
            editDeadline(task);
            break;
        case 3:
            break;
        default:
            cout << "Invalid Number!" << endl;
            break;
        }

    } while (userInput != 3);
}

void deleteTask(){
    cin.ignore();

    string task;

    cout << "\nEnter The Task: ";
    getline(cin, task);

    for (int i = 0; i < tasks.size(); i++)
    {
        if (task == tasks[i])
        {
            tasks.erase(tasks.begin() + i);
            deadlines.erase(deadlines.begin() + i);
            cout << "Task Deleted Successfully!\n";
            return;
        }
    }
    cout << "Task Not Found!\n";
}

void markTask(){
    cin.ignore();

    string task;

    cout << "\nEnter The Task: ";
    getline(cin, task);

    for(int i = 0; i < tasks.size(); i++){
        if(task == tasks[i]){
            doneTasks.push_back(tasks[i]);
            doneDeadlines.push_back(deadlines[i]);
            tasks.erase(tasks.begin() + i);
            deadlines.erase(deadlines.begin() + i);
            cout << "Marked Task Successfully!\n";
        }
    }
}

void listTasks(){
    cout << endl << string(43, '-') << endl;
    cout << "No. " << left << setw(30) << "List of Tasks" << "Deadline\n";
    cout << string(43, '-') << endl;
    if(tasks.size() > 0){
        for(int i = 0; i < tasks.size(); i++){
            cout << i+1 << ".  " << left << setw(30) << tasks[i] << deadlines[i] << endl;
        }
    }
    else{
        cout << "None\n";
    }
    cout << string(43, '-') << endl;
    cout << "No. " << left << setw(30) << "Completed Tasks" << "Deadline\n";
    if(doneTasks.size() > 0){
        for(int i = 0; i < doneTasks.size(); i++){
            cout << i+1 << ".  " << left << setw(30) << doneTasks[i] << doneDeadlines[i] << endl;
        }
    }
    else{
        cout << "None\n";
    }
    cout << string(43, '-') << endl;
}

void listProgressTasks(){
    cout << endl << string(43, '-') << endl;
    cout << "No. " << left << setw(30) << "List of Tasks" << "Deadline\n";
    cout << string(43, '-') << endl;
    if(tasks.size() > 0){
        for(int i = 0; i < tasks.size(); i++){
            cout << i+1 << ".  " << left << setw(30) << tasks[i] << deadlines[i] << endl;
        }
    }
    else{
        cout << "None\n";
    }
    cout << string(43, '-') << endl;
}

void listCompletedTasks(){
    cout << endl << string(43, '-') << endl;
    cout << "No. " << left << setw(30) << "Completed Tasks" << "Deadline\n";
    if(doneTasks.size() > 0){
        for(int i = 0; i < doneTasks.size(); i++){
            cout << i+1 << ".  " << left << setw(30) << doneTasks[i] << doneDeadlines[i] << endl;
        }
    }
    else{
        cout << "None\n";
    }
    cout << string(43, '-') << endl;
}

int main(){
    int userInput;

    cout << "------------------------------\n";
    cout << "-- Welcome To Task Tracker! --\n";
    cout << "------------------------------\n\n";

    do
    {
        cout << "1. Add a Task\n";
        cout << "2. Update a Task\n";
        cout << "3. Delete a Task\n";
        cout << "4. Mark a Task as Done\n";
        cout << "5. List All Tasks\n";
        cout << "6. List Tasks in Progress\n";
        cout << "7. List Completed Tasks\n";
        cout << "8. Exit\n";
        cout << "Enter a number: ";
        cin >> userInput;

        switch (userInput)
        {
        case 1:
            addTask();
            break;
        case 2:
            updateTask();
            break;
        case 3:
            deleteTask();
            break;
        case 4:
            markTask();
            break;
        case 5:
            listTasks();
            break;
        case 6:
            listProgressTasks();
            break;
        case 7:
            listCompletedTasks();
            break;
        case 8:
            break;
        default:
            cout << "Invalid Number!" << endl;
            break;
        }
        cout << "\n";

    } while (userInput != 8);

    return 0;
}