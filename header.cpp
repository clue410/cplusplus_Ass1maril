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
string THICK_SEPARATOR = "===================="; //print separator for output file
string REGULAR_SEPARATOR = "--------------------";//print separator for output file
string THIN_SEPARATOR = "- - - - - - - - - - - - - - - - ";//print separator for output file
workerStructure arrayOfstructifiedWorkers[20];
taskStructure arrayOfStructifiedTasks[20];
void wipeArraysOfStructures() { //sets all array entries to blank structure constructors
    for (int ia = 0; ia <= 20; ia++) {
        arrayOfStructifiedTasks[ia] = taskStructure();
        arrayOfstructifiedWorkers[ia] = workerStructure();
    }
}
void taskTextToStructureArray(string text2Split) { //function to split task line into tokens
    //text2split is one line from the Tasks.txt file, ie one task
    int foundCommaCount = 0; //amount of found commas
    int countPosition = 0; //index of current comma
    string workerDelimiter = "workers:"; //worker delimiter
    string fieldStorage[text2Split.length()]; //field storage is an array to store fields split by ",". Numbers of fields cant be more than the total string length.
//    text2Split.find("workers:");
    string workerChunk = text2Split.substr(text2Split.find(workerDelimiter), text2Split.length()); //finds the start of the worker delimiter, till the end of the string. workerChunk contains all task workers
    text2Split.erase(text2Split.find(workerDelimiter), workerDelimiter.length()); //erases the worker delimiter ("workers: ") from the workerChunk, leaving only the workers and commas
    string delimiter = ","; //comma delimiter
    string spliterised;
    for (int i = 0; i < text2Split.length(); i++) {
        fieldStorage[i] = ""; //initialise all of fieldStorage with blank values
    }
    int lexemised = 0; //keeps count of how many tokens have been made from string
    while ((foundCommaCount = text2Split.find(delimiter)) != -1) { //same as std::string::npos, -1 is the largest possible representable value for this type.
        spliterised = text2Split.substr(0, foundCommaCount); //create token from beginning of string till first found delimiter(",")
        fieldStorage[countPosition] = spliterised; //found token is put into fieldStorage at the index of comma position. Comma position is the count of how many commas have been found
        countPosition++;
        lexemised++;
        text2Split.erase(0, foundCommaCount + delimiter.length()); //erase the tokenised chunk of the task string
    }
    totalTasks++; //once all commas have been found, totalTasks is incremented by 1
    int lastWorkerFromString = std::stoi(text2Split);
    taskStructure tokenToTask; //new taskStructure
    tokenToTask.setTaskId(std::stoul(fieldStorage[0])); //assign values from fieldStorage to new taskStructure, fieldStorage[0] will always be id
    tokenToTask.setDescription(fieldStorage[1]); // fieldStorage[1] will always be description
    tokenToTask.setUncertainty(std::stoi(fieldStorage[2])); // fieldStorage[2] will always be uncertainty
    tokenToTask.setDifficulty(std::stoi(fieldStorage[3])); // fieldStorage[3] will always be difficulty
    arrayOfStructifiedTasks[countStructified].setTaskId(std::stoul(fieldStorage[0])); //populate blank taskStructure in array of taskStructures with correct values
    arrayOfStructifiedTasks[countStructified].setDescription(fieldStorage[1]);
    arrayOfStructifiedTasks[countStructified].setUncertainty(std::stoi(fieldStorage[2]));
    arrayOfStructifiedTasks[countStructified].setDifficulty(std::stoi(fieldStorage[3]));
    for (int workerPosition = 0; workerPosition < 20; workerPosition++) {
        //set all values in the attemptedWorkers array of the new taskStrucutre to -1, to differentiate between real workers id and invalid worker ids.
        arrayOfStructifiedTasks[countStructified].attemptedWorkers[workerPosition] = -1;
    }
    int foundWorkerAmount = 0;
    for (int m = 4; m < countPosition + 1; m++) { // m starts from 4 because any value after fieldStorage[3] has to be a worker
        if (fieldStorage[m] != "") { //if current value of fieldStorage isn't blank
            arrayOfStructifiedTasks[countStructified].attemptedWorkers[foundWorkerAmount] = std::stoi(fieldStorage[m]); //add the value to taskStructures attemptedWorkers array
        }
        foundWorkerAmount++; //increment the amount of workers that have been found
    }
    arrayOfStructifiedTasks[countStructified].attemptedWorkers[foundWorkerAmount -1] = lastWorkerFromString; //lastWorkerFromString is the last token left over after all the other tokens have been erased(it does not have a comma after it and therefore cannot be tokenised by found delimiter),
    countStructified++; //increment amount of lines from Tasks.txt have tokenised into new taskStructures.
}
void workerTextToStructureArray(string workerSplitText) { //function to split worker line into tokens
    int foundCommaCount = 0; //amount of found commas
    int countPosition = 0;  //index of current comma
    string fieldStorage[workerSplitText.length()];
    string delimiter = ","; //comma delimiter
    string spliterised;
    for (int i = 0; i < workerSplitText.length(); i++) {
        fieldStorage[i] = ""; //initialise all of fieldStorage with blank values
    }
    while ((foundCommaCount = workerSplitText.find(delimiter)) != -1) { //while the found comma isn't the end of the line
//    while ((foundCommaCount = workerSplitText.find(delimiter)) != std::string::npos) {
        spliterised = workerSplitText.substr(0, foundCommaCount); //split workerstring into a substring from the beginning of the string to the index of the delimiter
        fieldStorage[countPosition] = spliterised; //add found substring to fieldStorage
        countPosition++; //incremet amount of found tokens
        workerSplitText.erase(0, foundCommaCount + delimiter.length()); //erase found substring
    }
    workerStructure tokenToTask; //new Worker structure
    tokenToTask.setWorkerId(std::stoul(fieldStorage[0])); //assign values from fieldStorage to new workerStructure, fieldStorage[0] will always be id
    tokenToTask.setName(fieldStorage[1]); //assign values from fieldStorage to new workerStructure, fieldStorage[0] will always be the workers name
    tokenToTask.setVariability(std::stoi(fieldStorage[2])); //assign values from fieldStorage to new workerStructure, fieldStorage[0] will always be variability
    tokenToTask.setAbility(std::stoi(workerSplitText)); //assign values from fieldStorage to new workerStructure, fieldStorage[0] will always be ability
    arrayOfstructifiedWorkers[totalWorkers].setWorkerId(std::stoul(fieldStorage[0])); //populate blank workerStructure in array of workerStructure with correct values
    arrayOfstructifiedWorkers[totalWorkers].setName(fieldStorage[1]);
    arrayOfstructifiedWorkers[totalWorkers].setVariability(std::stoi(fieldStorage[2]));
    arrayOfstructifiedWorkers[totalWorkers].setAbility(std::stoi(workerSplitText));
    totalWorkers++; //increment amount of found workers
}
void readFromTaskFile(ofstream &outfile) { //read from "Workers.txt" and "Tasks.txt"
    ifstream readWorker("Workers.txt");
    ifstream readTasks("Tasks.txt");
    std::string myText;
    std::string myText2;
    int lineCounter = 0;
    while (getline(readTasks, myText)) {
        lineCounter++;
        taskTextToStructureArray(myText); //send current line to task tokeniser function
    }
    if(readTasks.is_open()){ //if "Tasks.txt" is open, output status to "Outfile.txt"
    printToOutputFile("Tasks.txt read successfully", outfile, true);
    }
    readTasks.close(); //close task reader
    while (getline(readWorker, myText2)) {
        lineCounter++;
        workerTextToStructureArray(myText2); //send current line to worker tokeniser function
    }
    if(readWorker.is_open()){ //if "Tasks.txt" is open, output status to "Outfile.txt"
    printToOutputFile("Workers.txt read successfully", outfile, true);
    }
    readWorker.close(); //close worker reader
    printToOutputFile(REGULAR_SEPARATOR, outfile, true);

};

void printToOutputFile(string insertToFile, ofstream &file, bool newLine) { //function to print text to output file "Outfile.txt"
    if (newLine == true) {
        file << insertToFile << endl;
    } else {
        file << insertToFile;
    }
}

long getWorkerByWorkerId(long idIn) { //function to get find a worker by a passed id
    long position = -1;
    for (int q = 0; q <= totalWorkers; q++) {
        if (arrayOfstructifiedWorkers[q].workerId == idIn) {
            position = arrayOfstructifiedWorkers[q].getWorkerId();
            return position; //return found worker position inside worker array
        }else{
        }
    }
    return position;
}

void checkFileAndOutput(ofstream &outfile) { //function to print program status before starting main functions
    if (totalTasks != 0 && totalWorkers != 0) { //if total workers and total tasks is not 0
        string stringifiedTasks = std::to_string(totalTasks);
        string stringifiedWorkers = std::to_string(totalWorkers);
        printToOutputFile("Total Tasks populated   |count : " + stringifiedTasks, outfile, true);
        printToOutputFile("Total Workers populated |count : " + stringifiedWorkers, outfile, true);
        printToOutputFile(THICK_SEPARATOR, outfile, true);
    } else {
        printToOutputFile("Tasks and Workers population failed", outfile, true);
        printToOutputFile(THICK_SEPARATOR, outfile, true);
    }
    printToOutputFile(REGULAR_SEPARATOR, outfile, true);
    printToOutputFile("BEGIN OUTSOURCING PROCESS", outfile, true);
    printToOutputFile(REGULAR_SEPARATOR, outfile, true);
};


int calculateMean(int ability, int difficulty) { //function to calculate mean for standard deviation
    int out = (ability-difficulty);
    return out;
};

int calculateTaskStandardDeviation(int uncertainty, int variability) { //function to calculate standard deviation
    int out =  (uncertainty + variability);
    return out;
};
int calculateAveragePerformance(int mean, int standardDeviation,int  maxAttempts){ //function to calculate workers average performance on task
    unsigned seed = chrono::system_clock::now().time_since_epoch().count(); //new random seed for random engine
    default_random_engine generator(seed); //new random engine using create seed
    normal_distribution<double> distribution(mean, standardDeviation); //normal distribution using calculated mean and standard deviation
    int scores = 0;
    for (int attempts = 0; attempts <= maxAttempts; attempts++) { //while worker has made less than 5 total attempts
        scores = scores + distribution(generator); //add score from normal distribution to total scores
    }
    int averageScore = scores / maxAttempts; //average score of all 5 attempts at task
    return averageScore;

};
void printTaskStats(int currentTaskNumber, ofstream &outfile){ //function to print task details
    string workersStringed;
    for (int l = 0; l < arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount(); l++) {
        if (l == arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount() - 1) { //if last worker, do not put comma after worker id after printing
            workersStringed = workersStringed + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[l]);
        } else {
            workersStringed = workersStringed + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[l]) + ","; //list workers between commas for outfile print
        }
    }
    printToOutputFile(THICK_SEPARATOR + " NEW TASK " + THICK_SEPARATOR, outfile, true);
    printToOutputFile("Processing Task id : " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()),outfile, true); //print task id
    printToOutputFile("Description        : " + arrayOfStructifiedTasks[currentTaskNumber].getDescription(),outfile, true); //print task description
    printToOutputFile("Uncertainty        : " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getUncertainty()),outfile, true); //print task uncertainty
    printToOutputFile("Difficulty         : " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getDifficulty()),outfile, true); //print task difficulty
    printToOutputFile("Worker count       : " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount()),outfile, true); //print tasks total worker amount
    printToOutputFile("Workers            : " + workersStringed, outfile, true); //print all tasks workers
    printToOutputFile(THIN_SEPARATOR + " START TRIAL " + THIN_SEPARATOR, outfile, true);

};
void printWorkerStats(int currentTaskNumber,long foundWorkerId, int a, ofstream &outfile, int averageScore){ //function to print worker stats during assignment trial
    printToOutputFile("Trial : Worker -> " +std::to_string(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[a]) + " (" +arrayOfstructifiedWorkers[foundWorkerId].getName() + ")", outfile, true); //print worker name and id
    printToOutputFile(arrayOfstructifiedWorkers[foundWorkerId].getName() + "'s (" +std::to_string(arrayOfstructifiedWorkers[foundWorkerId].workerId) +") average performance is " + std::to_string(averageScore), outfile, true); //print workers calculated average performance
};

