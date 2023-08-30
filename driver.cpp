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
const int MAX_ATTEMPTS = 5;

int main() {
    int currentTaskNumber = 0;
    ofstream outfile;
    outfile.open("Outfile.txt");
    wipeArraysOfStructures();
    string taskIdTarget;
    printToOutputFile("Pre-Logic status check", outfile, true);
    printToOutputFile(REGULAR_SEPERATOR, outfile, true);
    readFromTaskFile(outfile);
    checkFileAndOutput(outfile);
    while (currentTaskNumber <= totalTasks - 1) {
        string workersStringed;
        for (int l = 0; l < arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount(); l++) {
            if (l == arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount() - 1) {
                workersStringed = workersStringed + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[l]);
            } else {
                workersStringed = workersStringed + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[l]) + ",";
            }
        }
        printToOutputFile(THICK_SEPERATOR + " NEW TASK " + THICK_SEPERATOR, outfile, true);
        printToOutputFile("Processing Task id : " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()),outfile, true);
        printToOutputFile("Description        : " + arrayOfStructifiedTasks[currentTaskNumber].getDescription(),outfile, true);
        printToOutputFile("Uncertainty        : " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getUncertainty()),outfile, true);
        printToOutputFile("Difficulty         : " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getDifficulty()),outfile, true);
        printToOutputFile("Worker count       : " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount()),outfile, true);
        printToOutputFile("Workers            : " + workersStringed, outfile, true);
        printToOutputFile(THIN_SEPERATOR + " START TRIAL " + THIN_SEPERATOR, outfile, true);

        for (int a = 0; a < arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount(); a++) {
            long foundWorkerId = getWorkerByWorkerId(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[a]);
            int mean =  calculateMean(arrayOfstructifiedWorkers[foundWorkerId].getAbility(), arrayOfStructifiedTasks[currentTaskNumber].getDifficulty());
            int standardDeviation = calculateTaskStandardDeviation(arrayOfStructifiedTasks[currentTaskNumber].getUncertainty(), arrayOfstructifiedWorkers[foundWorkerId].variability);
            int averageScore = calculateAveragePerformance(mean,standardDeviation, outfile, a, currentTaskNumber, foundWorkerId, PASSING_SCORE, MAX_ATTEMPTS);

            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            default_random_engine generator(seed);
            normal_distribution<double> distribution(mean, standardDeviation);
            if (a > 0) {
                printToOutputFile("-----", outfile, true);
            }
            printToOutputFile("Trial : Worker   -> " +std::to_string(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[a]) + " (" +arrayOfstructifiedWorkers[foundWorkerId].getName() + ")", outfile, true);
            printToOutputFile(arrayOfstructifiedWorkers[foundWorkerId].getName() + "'s (" +std::to_string(arrayOfstructifiedWorkers[foundWorkerId].workerId) +") average performance is " + std::to_string(averageScore), outfile, true);
            if (averageScore <= PASSING_SCORE) {
                printToOutputFile(
                        "Worker " + std::to_string(arrayOfstructifiedWorkers[foundWorkerId].workerId) + " fails Task " +std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()), outfile, true);
                if (a == arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount() - 1) {
                    printToOutputFile(" !! Task Assignment failed !! ", outfile, true);
                }
            } else {
                printToOutputFile(
                        "Assignment of Task " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()) +" to Worker " + std::to_string(arrayOfstructifiedWorkers[foundWorkerId].workerId) +" is successful", outfile, true);
                a = arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount();
            }
        }
        printToOutputFile(THIN_SEPERATOR + " END TRIAL " + THIN_SEPERATOR, outfile, true);
        currentTaskNumber++;
    }
    printToOutputFile(THICK_SEPERATOR + "\n END PROGRAM \n" + THICK_SEPERATOR, outfile, false);}