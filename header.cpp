#include<iostream>
#include<fstream>
#include "header.h"
#include<stdio.h>
#include<string.h>
#include<array>
#include <random>
using std::ofstream; //write
using std::ifstream; //read
using std::string; //read
using std::cout;
using std::endl;
using std::cin;
using std::cerr;
int totalTasks = 0;
int totalWorkers = 0;
int countStructified = 0;
string THICK_SEPERATOR = "====================";
string REGULAR_SEPERATOR = "--------------------";
string THIN_SEPERATOR = "- - - - - - - - - - - - - - - - ";
workerStructure arrayOfstructifiedWorkers[20];
taskStructure arrayOfStructifiedTasks[20];
void wipeArraysOfStructures() {
    for (int ia = 0; ia <= 20; ia++) {
        arrayOfStructifiedTasks[ia] = taskStructure();
        arrayOfstructifiedWorkers[ia] = workerStructure();
    }
}
void textSplitterTask(string text2Split) {
    int foundCommaCount = 0;
    int countPosition = 0;
    string workerDelimiter = "workers:";
    string fieldStorage[text2Split.length()];
    text2Split.find("workers:");
    string workerChunk = text2Split.substr(text2Split.find(workerDelimiter), text2Split.length());
    text2Split.erase(text2Split.find(workerDelimiter), workerDelimiter.length());
    string delimiter = ",";
    string spliterised;
    for (int i = 0; i < text2Split.length(); i++) {
        fieldStorage[i] = "";
    }
    int lexemised = 0;
    while ((foundCommaCount = text2Split.find(delimiter)) != -1) { //how. what
//    while ((foundCommaCount = text2Split.find(delimiter)) != std::string::npos) {
        spliterised = text2Split.substr(0, foundCommaCount);
        fieldStorage[countPosition] = spliterised;
        countPosition++;
        lexemised++;
        text2Split.erase(0, foundCommaCount + delimiter.length());
    }
    totalTasks++;
    int text2SplitIntegerised = std::stoi(text2Split);
    taskStructure tokenToTask;
    tokenToTask.setTaskId(std::stoul(fieldStorage[0]));
    tokenToTask.setDescription(fieldStorage[1]);
    tokenToTask.setUncertainty(std::stoi(fieldStorage[2]));
    tokenToTask.setDifficulty(std::stoi(fieldStorage[3]));
    arrayOfStructifiedTasks[countStructified].setTaskId(std::stoul(fieldStorage[0]));
    arrayOfStructifiedTasks[countStructified].setDescription(fieldStorage[1]);
    arrayOfStructifiedTasks[countStructified].setUncertainty(std::stoi(fieldStorage[2]));
    arrayOfStructifiedTasks[countStructified].setDifficulty(std::stoi(fieldStorage[3]));
    for (int meow = 0; meow < 20; meow++) {
        arrayOfStructifiedTasks[countStructified].attemptedWorkers[meow] = -1;
    }
    int blah = 0;
    for (int m = 4; m < countPosition + 1; m++) {
        if (fieldStorage[m] != "") {
            arrayOfStructifiedTasks[countStructified].attemptedWorkers[blah] = std::stoi(fieldStorage[m]);
        }
        blah++;
    }
    arrayOfStructifiedTasks[countStructified].attemptedWorkers[blah - 1] = text2SplitIntegerised;
    countStructified++;
}
void workerTextToStructureArray(string workerSplitText) {
    int foundCommaCount = 0;
    int countPosition = 0;
    string fieldStorage[workerSplitText.length()];
    string delimiter = ",";
    string spliterised;
    for (int i = 0; i < workerSplitText.length(); i++) {
        fieldStorage[i] = "";
    }
    while ((foundCommaCount = workerSplitText.find(delimiter)) != std::string::npos) {
        spliterised = workerSplitText.substr(0, foundCommaCount);
        fieldStorage[countPosition] = spliterised;
        countPosition++;
        workerSplitText.erase(0, foundCommaCount + delimiter.length());
    }
    workerStructure tokenToTask;
    tokenToTask.setWorkerId(std::stoul(fieldStorage[0]));
    tokenToTask.setName(fieldStorage[1]);
    tokenToTask.setVariability(std::stoi(fieldStorage[2]));
    tokenToTask.setAbility(std::stoi(workerSplitText));
    arrayOfstructifiedWorkers[totalWorkers].setWorkerId(std::stoul(fieldStorage[0]));
    arrayOfstructifiedWorkers[totalWorkers].setName(fieldStorage[1]);
    arrayOfstructifiedWorkers[totalWorkers].setVariability(std::stoi(fieldStorage[2]));
    arrayOfstructifiedWorkers[totalWorkers].setAbility(std::stoi(workerSplitText));
    totalWorkers++;
}
void readFromTaskFile(ofstream &outfile) {
    ifstream readWorker("Workers.txt");
    ifstream readTasks("Tasks.txt");
    std::string myText;
    std::string myText2;
    int lineCounter = 0;
    while (getline(readTasks, myText)) {
        lineCounter++;
        textSplitterTask(myText);
    }
    if(readTasks.is_open()){
    printToOutputFile("Tasks.txt read successfully", outfile, true);
    }
    readTasks.close();
    while (getline(readWorker, myText2)) {
        lineCounter++;
        workerTextToStructureArray(myText2);
    }
    if(readWorker.is_open()){
    printToOutputFile("Workers.txt read successfully", outfile, true);
    }
    readWorker.close();
    printToOutputFile(REGULAR_SEPERATOR, outfile, true);

};

void printToOutputFile(string insertToFile, ofstream &file, bool newLine) {
    if (newLine == true) {
        file << insertToFile << endl;
    } else {
        file << insertToFile;
    }
}

long getWorkerByWorkerId(long idIn) {
    long position = -1;
    for (int q = 0; q <= totalWorkers; q++) {
        if (arrayOfstructifiedWorkers[q].workerId == idIn) {
            position = arrayOfstructifiedWorkers[q].getWorkerId();
            return position;
        }else{
        }
    }
    return position;
}

void checkFileAndOutput(ofstream &outfile) {
    if (totalTasks != 0 && totalWorkers != 0) {
        string stringifiedTasks = std::to_string(totalTasks);
        string stringifiedWorkers = std::to_string(totalWorkers);
        printToOutputFile("Total Tasks populated | count : " + stringifiedTasks, outfile, true);
        printToOutputFile("Total Workers populated | count : " + stringifiedWorkers, outfile, true);
        printToOutputFile(THICK_SEPERATOR, outfile, true);
    } else {
        printToOutputFile("Tasks and Workers population failed", outfile, true);
        printToOutputFile(THICK_SEPERATOR, outfile, true);
        //throw exception if within week 4 scopce sdovkjldj
    }
    printToOutputFile(REGULAR_SEPERATOR, outfile, true);
    printToOutputFile("BEGIN OUTSOURCING PROCESS", outfile, true);
    printToOutputFile(REGULAR_SEPERATOR, outfile, true);
};


int calculateMean(int ability, int difficulty) {
    int out = (ability-difficulty);
    return out;
};

int calculateTaskStandardDeviation(int uncertainty, int variability) {
    int out =  (uncertainty + variability);
    return out;
};
int calculateAveragePerformance(int mean, int standardDeviation,int  maxAttempts){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(mean, standardDeviation);
    int scores = 0;
    for (int attempts = 0; attempts <= maxAttempts; attempts++) {
        scores = scores + distribution(generator);
    }
    int averageScore = scores / maxAttempts;
    return averageScore;

};
void printTaskStats(int currentTaskNumber, ofstream &outfile){
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

};
void printWorkerStats(int currentTaskNumber,long foundWorkerId, int a, ofstream &outfile, int averageScore){
    printToOutputFile("Trial : Worker -> " +std::to_string(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[a]) + " (" +arrayOfstructifiedWorkers[foundWorkerId].getName() + ")", outfile, true);
    printToOutputFile(arrayOfstructifiedWorkers[foundWorkerId].getName() + "'s (" +std::to_string(arrayOfstructifiedWorkers[foundWorkerId].workerId) +") average performance is " + std::to_string(averageScore), outfile, true);
};

