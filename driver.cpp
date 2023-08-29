//
// Created by Marilena on 21/8/2023.
//
#include "header.cpp"
#include<iostream>
#include <random>
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
const int PASSING_SCORE = 50;

int main() {
    int currentTaskNumber = 0;
    ofstream outfile;
    outfile.open("Outfile.txt");
    wipeArrayOfTasks();
    string taskIdTarget;
    taskStructure structifiedTasks[totalTasks];
    workerStructure structifiedWorkers[totalWorkers];
    printToOutputFile("Pre-Logic status check", outfile, true);
    printToOutputFile(REGULAR_SEPERATOR, outfile, true);
    readFromTaskFile(outfile);
    printToOutputFile(REGULAR_SEPERATOR, outfile, true);
    cout << "Total Tasks --> " << totalTasks << endl;
    cout << "Total Workers --> " << totalWorkers << endl;
    if (totalTasks != 0 && totalWorkers != 0) {
        string stringifiedTasks = std::to_string(totalTasks);
        string stringifiedWorkers = std::to_string(totalWorkers);
        printToOutputFile("Total Tasks populated | count : " + stringifiedTasks, outfile, true);
        printToOutputFile("Total Workers populated | count : " + stringifiedWorkers, outfile, true);
        printToOutputFile(THICK_SEPERATOR, outfile, true);
    } else {
        printToOutputFile("Tasks and Workers population failed", outfile, true);
        printToOutputFile(THICK_SEPERATOR, outfile, true);
        return -1;
    }
    printToOutputFile(REGULAR_SEPERATOR, outfile, true);
    printToOutputFile("BEGIN OUTSOURCING PROCESS", outfile, true);
    printToOutputFile(REGULAR_SEPERATOR, outfile, true);
    while (currentTaskNumber <= totalTasks - 1) {
        string meow;
        for(int l = 0; l<arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount(); l++){
            if(l == arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount() - 1){
                meow =meow+std::to_string(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[l]);
            }else{
            meow =meow+std::to_string(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[l])+",";
            }
        }
        printToOutputFile("Processing Task id : "+ std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()), outfile, true);
        printToOutputFile("Description        : "+ arrayOfStructifiedTasks[currentTaskNumber].getDescription(), outfile, true);
        printToOutputFile("Uncertainty        : "+  std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getUncertainty()), outfile, true);
        printToOutputFile("Difficulty         : "+  std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getDifficulty()), outfile, true);
        printToOutputFile("Worker count       : "+  std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount()), outfile, true);
        printToOutputFile("Workers            : "+  meow, outfile, true);
        printToOutputFile(THIN_SEPERATOR, outfile, true);
        printToOutputFile("START TRIAL", outfile, true);
        printToOutputFile(THIN_SEPERATOR, outfile, true);
        for(int a = 0; a<arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount(); a++){
           long foundWorkerId = getWorkerByWorkerId(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[a]);
           int mean = (arrayOfstructifiedWorkers[foundWorkerId].getAbility()) - (arrayOfStructifiedTasks[currentTaskNumber].getDifficulty());
           int standardDeviation = (arrayOfStructifiedTasks[currentTaskNumber].getUncertainty()) + (arrayOfstructifiedWorkers[foundWorkerId].variability);

            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            default_random_engine generator(seed);
            normal_distribution<double> distribution(mean, standardDeviation);
            int scores = 0;
            for (int attempts = 0; attempts <= 5; attempts++) {
                scores =  scores + distribution(generator);
           }
            int averageScore = scores / 5;
            cout << "Average performance is :" << scores << "/5 =" << averageScore <<endl;
            cout << "mean : " << mean <<endl;
            cout << "standard deviation : " << standardDeviation <<endl;
            cout << "foundWorkerId : "+ std::to_string(foundWorkerId) <<endl;
            cout << "foundWorkerId name : "+ arrayOfstructifiedWorkers[foundWorkerId].getName() <<endl;
            printToOutputFile("Trial : Worker   -> "+ std::to_string(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[a]) + " ("+  arrayOfstructifiedWorkers[foundWorkerId].getName() +")", outfile, true);
            printToOutputFile(arrayOfstructifiedWorkers[foundWorkerId].getName() + "'s ("+ std::to_string(arrayOfstructifiedWorkers[foundWorkerId].workerId) +") average performance is " + std::to_string(averageScore), outfile, true);
            if(averageScore <= 50){
                printToOutputFile("Worker "+ std::to_string(arrayOfstructifiedWorkers[foundWorkerId].workerId) +" fails Task " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()), outfile, true);
                if(a == arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount()-1){
                    printToOutputFile("Task Assignment failed", outfile, true);
                }
            }else{
                printToOutputFile( "Assignment of Task " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()) + " to Worker " + std::to_string(arrayOfstructifiedWorkers[foundWorkerId].workerId) + " is successful", outfile, true);
                a = arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount();
            }

//        calculateMean();
//        calculateTaskStandardDeviation();
        }
        printToOutputFile(THIN_SEPERATOR, outfile, true);
        printToOutputFile("END TRIAL", outfile, true);
        printToOutputFile(THIN_SEPERATOR, outfile, true);

        currentTaskNumber++;
    }
    printToOutputFile(THICK_SEPERATOR, outfile, true);
    printToOutputFile("END PROGRAM", outfile, true);
    printToOutputFile(THICK_SEPERATOR, outfile, true);
}


//readFromWorkerFile();
//getNextTask();
//getNextWorker();
//calculateMean();
//calculateTaskStandardDeviation();
//worker5Attempts();
//calculateAveragePerformance();
//outputToFile();

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