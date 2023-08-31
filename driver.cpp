#include "header.cpp"
#include<iostream>
#include <random>
using std::ofstream; //write
using std::ifstream; //read
using std::array;
using std::cout;
using std::endl;
using std::cin;
using std::cerr;
struct taskStructure;
struct workerStructure;
const int PASSING_SCORE = 50; //constant int for passing score
const int MAX_ATTEMPTS = 5; //constant int for max attempts
int main() {
    int currentTaskNumber = 0;
    ofstream outfile;
    outfile.open("Outfile.txt");
    wipeArraysOfStructures();
    string taskIdTarget;
    printToOutputFile("Pre-Logic status check \n" + REGULAR_SEPARATOR, outfile, true);
    readFromTaskFile(outfile);
    checkFileAndOutput(outfile);
    while (currentTaskNumber <= totalTasks - 1) {
        printTaskStats(currentTaskNumber,outfile);
        for (int a = 0; a < arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount(); a++) {
            long foundWorkerId = getWorkerByWorkerId(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[a]);
            int mean =  calculateMean(arrayOfstructifiedWorkers[foundWorkerId].getAbility(), arrayOfStructifiedTasks[currentTaskNumber].getDifficulty()); //find mean
            int standardDeviation = calculateTaskStandardDeviation(arrayOfStructifiedTasks[currentTaskNumber].getUncertainty(), arrayOfstructifiedWorkers[foundWorkerId].variability); //find Standard Deviation
            int averageScore = calculateAveragePerformance(mean,standardDeviation, MAX_ATTEMPTS); //calculate Average Score over 5 attempts
            if (a > 0) { //if not first worker, print divider
                printToOutputFile("-----", outfile, true);
            }
            printWorkerStats(currentTaskNumber,foundWorkerId,a, outfile,averageScore);
            if (averageScore <= PASSING_SCORE) { //if worker's average score is less than passing score
                printToOutputFile("Worker " + std::to_string(arrayOfstructifiedWorkers[foundWorkerId].workerId) + " fails Task " +std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()), outfile, true);
                if (a == arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount() - 1) { //if all workers have attempted and none have succeeded
                    printToOutputFile(" !! Task Assignment for task "  +std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()) + " has failed !! ", outfile, true);
                }
            } else { //if worker gets passing score
                printToOutputFile("Assignment of Task " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()) +" to Worker " + std::to_string(arrayOfstructifiedWorkers[foundWorkerId].workerId) +" is successful", outfile, true);
                a = arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount(); //set a to amount of workers in task, breaks for loop
            }
        }
        printToOutputFile(THIN_SEPARATOR + " END TRIAL " + THIN_SEPARATOR, outfile, true);
        currentTaskNumber++;
    }
    printToOutputFile(THICK_SEPARATOR + "\n END PROGRAM \n" + THICK_SEPARATOR, outfile, false);}