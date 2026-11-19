#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

vector<string> tasks;
vector<string> deadlines;
vector<string> doneTasks;
vector<string> doneDeadlines;

bool validDate(string date){
    if(date.length() != 10){
        return false;
    }

    for(int i = 0; i < date.length(); i++){
        if(i == 2 || i == 5){
            if(date[i] != '-'){
                return false;
            }
        }
        else{
            if(!isdigit(date[i])){
                return false;
            }
        }
    }
    return true;
}

void saveTasks(){
    json data;

    data["in_progress"] = json::array();
    data["completed"] = json::array();

    for(int i = 0; i < tasks.size(); i++){
        data["in_progress"].push_back({
            {"task", tasks[i]},
            {"deadline", deadlines[i]}
        });
    }

    for(int i = 0; i < doneTasks.size(); i++){
        data["completed"].push_back({
            {"task", doneTasks[i]},
            {"deadline", doneDeadlines[i]}
        });
    }

    ofstream file("tasks.json");

    file << data.dump(4);

    file.close();
}

void loadTasks(){
    ifstream file("tasks.json");

    if(!file.is_open()){
        return;
    }

    json data;

    file >> data;

    tasks.clear();
    deadlines.clear();
    doneTasks.clear();
    doneDeadlines.clear();

    for(auto item : data["in_progress"]){
        tasks.push_back(item["task"]);
        deadlines.push_back(item["deadline"]);
    }

    for(auto item : data["completed"]){
        doneTasks.push_back(item["task"]);
        doneDeadlines.push_back(item["deadline"]);
    }

    file.close();
}

void addTask(){
    cin.ignore();

    string task;
    string deadline;
    bool go = false;

    cout << "\nEnter The Task: ";
    getline(cin, task);
    tasks.push_back(task);

    do{
        cout << "Enter The Deadline (dd-mm-yyyy): ";
        getline(cin, deadline);

        if(validDate(deadline)){
            go = true;
        }

    }while(go != true);

    deadlines.push_back(deadline);
    cout << "Task Added Successfully!\n";

    saveTasks();
}

void editTask(string task){
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string newTask;

    cout << "\nEnter The New Task: ";
    getline(cin, newTask);

    for(int i = 0; i < tasks.size(); i++){
        if(task == tasks[i]){
            tasks[i] = newTask;
            cout << "Task Changed Successfully!\n";
        }
    }
    saveTasks();
}

void editDeadline(string task){
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string newDeadline;
    bool go = false;

    do{
        cout << "\nEnter The New Deadline (dd-mm-yyyy): ";
        getline(cin, newDeadline);

        if(validDate(newDeadline)){
            go = true;
        }

    }while(go != true);

    for(int i = 0; i < tasks.size(); i++){
        if(task == tasks[i]){
            deadlines[i] = newDeadline;
            cout << "Deadline Changed Successfully!\n";
        }
    }
    saveTasks();
}

void updateTask(){
    cin.ignore();

    string task;
    int userInput;

    cout << "\nEnter The Task: ";
    getline(cin, task);
    bool found = false;

    for(int i = 0; i < tasks.size(); i++){
        if(task == tasks[i]){
            found = true;
            break;
        }
    }

    if(!found){
        cout << "Task Not Found!\n";
        return;
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
            saveTasks();
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
            saveTasks();
            return;
        }
    }
    cout << "Task Not Found!\n";
}

void listTasks(){
    cout << endl << "List of All Tasks" << endl << string(43, '-') << endl;
    cout << "No. " << left << setw(30) << "Tasks In Progress" << "Deadline\n";
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
    cout << "No. " << left << setw(30) << "Tasks In Progress" << "Deadline\n";
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
    loadTasks();

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
