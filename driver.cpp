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
const int PASSING_SCORE = 50;
const int MAX_ATTEMPTS = 5;
int main() {
    int currentTaskNumber = 0;
    ofstream outfile;
    outfile.open("Outfile.txt");
    wipeArraysOfStructures();
    string taskIdTarget;
    printToOutputFile("Pre-Logic status check \n" + REGULAR_SEPERATOR, outfile, true);
    readFromTaskFile(outfile);
    checkFileAndOutput(outfile);
    while (currentTaskNumber <= totalTasks - 1) {
        printTaskStats(currentTaskNumber,outfile);
        for (int a = 0; a < arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount(); a++) {
            long foundWorkerId = getWorkerByWorkerId(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[a]);
            int mean =  calculateMean(arrayOfstructifiedWorkers[foundWorkerId].getAbility(), arrayOfStructifiedTasks[currentTaskNumber].getDifficulty());
            int standardDeviation = calculateTaskStandardDeviation(arrayOfStructifiedTasks[currentTaskNumber].getUncertainty(), arrayOfstructifiedWorkers[foundWorkerId].variability);
            int averageScore = calculateAveragePerformance(mean,standardDeviation, MAX_ATTEMPTS);
            if (a > 0) {
                printToOutputFile("-----", outfile, true);
            }
            printWorkerStats(currentTaskNumber,foundWorkerId,a, outfile,averageScore);
            if (averageScore <= PASSING_SCORE) {
                printToOutputFile("Worker " + std::to_string(arrayOfstructifiedWorkers[foundWorkerId].workerId) + " fails Task " +std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()), outfile, true);
                if (a == arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount() - 1) {
                    printToOutputFile(" !! Task Assignment for task "  +std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()) + " has failed !! ", outfile, true);
                }
            } else {
                printToOutputFile("Assignment of Task " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()) +" to Worker " + std::to_string(arrayOfstructifiedWorkers[foundWorkerId].workerId) +" is successful", outfile, true);
                a = arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount();
            }
        }
        printToOutputFile(THIN_SEPERATOR + " END TRIAL " + THIN_SEPERATOR, outfile, true);
        currentTaskNumber++;
    }
    printToOutputFile(THICK_SEPERATOR + "\n END PROGRAM \n" + THICK_SEPERATOR, outfile, false);}