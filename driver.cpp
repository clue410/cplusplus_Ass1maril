//
// Created by Marilena on 21/8/2023.
//
#include "header.cpp"
#include<iostream>
#include<fstream>

using std::ofstream; //write
using std::ifstream; //read
using std::array;
using std::cout;
using std::endl;
using std::cin;
using std::cerr;

struct taskStructure;
struct workerStructure;

int main() {
    int currentTaskNumber = 1;
    wipeArrayOfTasks();
    string taskIdTarget;
    taskStructure structifiedTasks[totalTasks];
    workerStructure structifiedWorkers[totalWorkers];
    readFromTaskFile();
    cout << "Total Tasks --> " << totalTasks << endl;
    cout << "Total Workers --> " << totalWorkers << endl;
    printOut(structifiedTasks);
    getTaskById(2, structifiedTasks);

//readFromWorkerFile();
//getNextTask();
//getNextWorker();
//calculateMean();
//calculateTaskStandardDeviation();
//worker5Attempts();
//calculateAveragePerformance();
//outputToFile();
}

//int main() {
//    taskStructure structure(22,"meow",111,222);
////    structure.setTaskId(22);
////    structure.setDescription("meow");
////    structure.setDifficulty(111);
////    structure.setUncertainty(222);
//    cout << structure.taskId << endl;
//    cout << structure.description << endl;
//    cout << structure.uncertainty << endl;
//    cout << structure.difficulty << endl;
//
//
//}