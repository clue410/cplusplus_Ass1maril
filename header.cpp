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
const int PASSING_SCORE = 50; //constant int for passing score
const int MAX_ATTEMPTS = 5; //constant int for max attempts
const int WORKERS_LENGTH = 20;
const int TASKS_LENGTH = 20;
workerStructure arrayOfStructifiedWorkers[WORKERS_LENGTH];
taskStructure arrayOfStructifiedTasks[TASKS_LENGTH];

//sets all array entries to blank structure constructors
void initializeArraysWithBlankStructures() {
    for (int ia = 0; ia <= WORKERS_LENGTH; ia++) {
        arrayOfStructifiedWorkers[ia] = workerStructure();
    }
    for (int ia = 0; ia <= TASKS_LENGTH; ia++) {
        arrayOfStructifiedTasks[ia] = taskStructure();
    }
}

//function to split task line into tokens
void taskTextToStructureArray(string text2Split) {
    //text2split is one line from the Tasks.txt file, ie one task
    int foundCommaCount = 0;
    int countPosition = 0; //index of current comma
    string workerDelimiter = "workers:"; //worker delimiter
    //field storage is an array to store fields split by ",". Numbers of fields cant be more than the total string length.
    string fieldStorage[text2Split.length()];
    //finds the start of the worker delimiter, till the end of the string. workerChunk contains all task workers
    string workerChunk = text2Split.substr(text2Split.find(workerDelimiter), text2Split.length());
    //erases the worker delimiter ("workers: ") from the workerChunk, leaving only the workers and commas
    text2Split.erase(text2Split.find(workerDelimiter), workerDelimiter.length());
    string delimiter = ","; //comma delimiter
    string spliterised;
    for (int i = 0; i < text2Split.length(); i++) {
        fieldStorage[i] = ""; //initialise all of fieldStorage with blank values
    }
    int lexemised = 0; //keeps count of how many tokens have been made from string
    //same as std::string::npos, -1 is the largest possible representable value for this type.
    while ((foundCommaCount = text2Split.find(delimiter)) != -1) {
        //create token from beginning of string till first found delimiter(",")
        spliterised = text2Split.substr(0, foundCommaCount);
        //found token is put into fieldStorage at the index of comma position.
        // Comma position is the count of how many commas have been found
        fieldStorage[countPosition] = spliterised;
        countPosition++;
        lexemised++;
        //erase the tokenised chunk of the task string
        text2Split.erase(0, foundCommaCount + delimiter.length());
    }
    totalTasks++; //once all commas have been found, totalTasks is incremented by 1
    int lastWorkerFromString = std::stoi(text2Split);
    //populate blank taskStructure in array of taskStructures with correct values
    arrayOfStructifiedTasks[countStructified].setTaskId(std::stoul(fieldStorage[0]));
    arrayOfStructifiedTasks[countStructified].setDescription(fieldStorage[1]);
    arrayOfStructifiedTasks[countStructified].setUncertainty(std::stoi(fieldStorage[2]));
    arrayOfStructifiedTasks[countStructified].setDifficulty(std::stoi(fieldStorage[3]));
//    for(int workerPosition = 0; workerPosition < WORKERS_LENGTH; workerPosition++) {
//        //set all values in the attemptedWorkers array of the new taskStructure to -1, to differentiate between real workers id and invalid worker ids.
//        arrayOfStructifiedTasks[countStructified].attemptedWorkers[workerPosition] = -1;
//    }
    int foundWorkerAmount = 0;
    // m starts from 4 because any value after fieldStorage[3] has to be a worker
    for (int m = 4; m < countPosition + 1; m++) {
        if (fieldStorage[m] != "") { //if current value of fieldStorage isn't blank
            //add the value to taskStructures attemptedWorkers array
            arrayOfStructifiedTasks[countStructified].attemptedWorkers[foundWorkerAmount] = std::stoi(fieldStorage[m]);
        }
        foundWorkerAmount++; //increment the amount of workers that have been found
    }
    //lastWorkerFromString is the last token left over after all the other tokens have been erased
    // (it does not have a comma after it and therefore cannot be tokenised by found delimiter),
    arrayOfStructifiedTasks[countStructified].attemptedWorkers[foundWorkerAmount - 1] = lastWorkerFromString;
    arrayOfStructifiedTasks[countStructified].attemptedWorkers[foundWorkerAmount] = -1;
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
    while ((foundCommaCount = workerSplitText.find(delimiter)) !=
           -1) { //while the found comma isn't the end of the line
//    while ((foundCommaCount = workerSplitText.find(delimiter)) != std::string::npos) {
        spliterised = workerSplitText.substr(0,
                                             foundCommaCount); //split workerstring into a substring from the beginning of the string to the index of the delimiter
        fieldStorage[countPosition] = spliterised; //add found substring to fieldStorage
        countPosition++; //incremet amount of found tokens
        workerSplitText.erase(0, foundCommaCount + delimiter.length()); //erase found substring
    }
    workerStructure tokenToTask; //new Worker structure
    tokenToTask.setWorkerId(std::stoul(
            fieldStorage[0])); //assign values from fieldStorage to new workerStructure, fieldStorage[0] will always be id
    tokenToTask.setName(
            fieldStorage[1]); //assign values from fieldStorage to new workerStructure, fieldStorage[0] will always be the workers name
    tokenToTask.setVariability(std::stoi(
            fieldStorage[2])); //assign values from fieldStorage to new workerStructure, fieldStorage[0] will always be variability
    tokenToTask.setAbility(std::stoi(
            workerSplitText)); //assign values from fieldStorage to new workerStructure, fieldStorage[0] will always be ability
    arrayOfStructifiedWorkers[totalWorkers].setWorkerId(std::stoul(
            fieldStorage[0])); //populate blank workerStructure in array of workerStructure with correct values
    arrayOfStructifiedWorkers[totalWorkers].setName(fieldStorage[1]);
    arrayOfStructifiedWorkers[totalWorkers].setVariability(std::stoi(fieldStorage[2]));
    arrayOfStructifiedWorkers[totalWorkers].setAbility(std::stoi(workerSplitText));
    totalWorkers++; //increment amount of found workers
}

//read from "Workers.txt" and "Tasks.txt"
void readWorkerAndTaskFiles(ofstream &outfile) {
    std::string myText;
    std::string myText2;
    ifstream readWorker("Workers.txt");
    ifstream readTasks("Tasks.txt");
    int lineCounter = 0;
    if (readTasks.is_open()) { //if "Tasks.txt" is open, output status to "Outfile.txt"
        while (getline(readTasks, myText)) {
            lineCounter++;
            taskTextToStructureArray(myText); //send current line to task tokeniser function
        }
        printToOutputFile("Tasks.txt read successfully", outfile, true);
    }
    readTasks.close(); //close task reader
    if (readWorker.is_open()) { //if "Tasks.txt" is open, output status to "Outfile.txt"
        while (getline(readWorker, myText2)) {
            lineCounter++;
            workerTextToStructureArray(myText2); //send current line to worker tokeniser function
        }
        printToOutputFile("Workers.txt read successfully", outfile, true);
    }
    readWorker.close(); //close worker reader
    printToOutputFile(REGULAR_SEPARATOR, outfile, true);
};

void printToOutputFile(string insertToFile, ofstream &file,
                       bool newLine) { //function to print text to output file "Outfile.txt"
    if (newLine == true) {
        file << insertToFile << endl;
    } else {
        file << insertToFile;
    }
}

long getWorkerByWorkerId(long idIn) { //function to get find a worker by a passed id
    long position = -1;
    for (int q = 0; q <= totalWorkers; q++) {
        if (arrayOfStructifiedWorkers[q].workerId == idIn) {
            position = arrayOfStructifiedWorkers[q].getWorkerId();
            return position; //return found worker position inside worker array
        } else {
        }
    }
    return position;
}

void checkDataValidity(ofstream &outfile) { //function to print program status before starting main functions
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
    int out = (ability - difficulty);
    return out;
};

int calculateTaskStandardDeviation(int uncertainty, int variability) { //function to calculate standard deviation
    int out = (uncertainty + variability);
    return out;
};

int calculateAveragePerformance(int mean, int standardDeviation,
                                int maxAttempts) { //function to calculate workers average performance on task
    unsigned seed = chrono::system_clock::now().time_since_epoch().count(); //new random seed for random engine
    default_random_engine generator(seed); //new random engine using create seed
    normal_distribution<double> distribution(mean,
                                             standardDeviation); //normal distribution using calculated mean and standard deviation
    int scores = 0;
    for (int attempts = 0; attempts <= maxAttempts; attempts++) { //while worker has made less than 5 total attempts
        scores = scores + distribution(generator); //add score from normal distribution to total scores
    }
    int averageScore = scores / maxAttempts; //average score of all 5 attempts at task
    return averageScore;

};

void printTaskStats(int currentTaskNumber, ofstream &outfile) { //function to print task details
    string workersStringed;
    string joiner = "";
    for (int l = 0; l < arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount(); l++) {
        workersStringed = workersStringed + joiner
                          + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[l]);
        joiner = ",";
    }

    printToOutputFile(THICK_SEPARATOR + " NEW TASK " + THICK_SEPARATOR, outfile, true);
    printToOutputFile("Processing Task id : " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()),
                      outfile, true); //print task id
    printToOutputFile("Description        : " + arrayOfStructifiedTasks[currentTaskNumber].getDescription(), outfile,
                      true); //print task description
    printToOutputFile(
            "Uncertainty\t: " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getUncertainty()),
            outfile, true); //print task uncertainty
    printToOutputFile(
            "Difficulty\t: " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getDifficulty()),
            outfile, true); //print task difficulty
    printToOutputFile(
            "Worker count\t: " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount()),
            outfile, true); //print tasks total worker amount
    printToOutputFile("Workers            : " + workersStringed, outfile, true); //print all tasks workers
    printToOutputFile(THIN_SEPARATOR + " START TRIAL " + THIN_SEPARATOR, outfile, true);

};

void printWorkerStats(int currentTaskNumber, long foundWorkerId, int a, ofstream &outfile,
                      int averageScore) { //function to print worker stats during assignment trial
    printToOutputFile(
            "Trial : Worker -> " + std::to_string(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[a]) +
            " (" + arrayOfStructifiedWorkers[foundWorkerId].getName() + ")", outfile, true); //print worker name and id
    printToOutputFile(arrayOfStructifiedWorkers[foundWorkerId].getName() + "'s (" +
                      std::to_string(arrayOfStructifiedWorkers[foundWorkerId].workerId) + ") average performance is " +
                      std::to_string(averageScore), outfile, true); //print workers calculated average performance
};

void tasksAssingment(ofstream &outfile) {
    int currentTaskNumber = 0;
    while (currentTaskNumber <= totalTasks - 1) {
        printTaskStats(currentTaskNumber, outfile);
        for (int a = 0; a < arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount(); a++) {
            long foundWorkerId = getWorkerByWorkerId(arrayOfStructifiedTasks[currentTaskNumber].attemptedWorkers[a]);
            int mean = calculateMean(arrayOfStructifiedWorkers[foundWorkerId].getAbility(),
                                     arrayOfStructifiedTasks[currentTaskNumber].getDifficulty()); //find mean
            int standardDeviation = calculateTaskStandardDeviation(
                    arrayOfStructifiedTasks[currentTaskNumber].getUncertainty(),
                    arrayOfStructifiedWorkers[foundWorkerId].variability); //find Standard Deviation
            int averageScore = calculateAveragePerformance(mean, standardDeviation,
                                                           MAX_ATTEMPTS); //calculate Average Score over 5 attempts
            if (a > 0) { //if not first worker, print divider
                printToOutputFile("-----", outfile, true);
            }
            printWorkerStats(currentTaskNumber, foundWorkerId, a, outfile, averageScore);
            if (averageScore <= PASSING_SCORE) { //if worker's average score is less than passing score
                printToOutputFile(
                        "Worker " + to_string(arrayOfStructifiedWorkers[foundWorkerId].workerId) + " fails Task " +
                        to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()), outfile, true);
                if (a == arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount() -
                         1) { //if all workers have attempted and none have succeeded
                    printToOutputFile(" !! Task Assignment for task " +
                                      to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()) +
                                      " has failed !! ", outfile, true);
                }
            } else { //if worker gets passing score
                printToOutputFile(
                        "Assignment of Task " + to_string(arrayOfStructifiedTasks[currentTaskNumber].getTaskId()) +
                        " to Worker " + to_string(arrayOfStructifiedWorkers[foundWorkerId].workerId) +
                        " is successful", outfile, true);
                a = arrayOfStructifiedTasks[currentTaskNumber].getWorkerCount(); //set a to amount of workers in task, breaks for loop
            }
        }
        printToOutputFile(THIN_SEPARATOR + " END TRIAL " + THIN_SEPARATOR, outfile, true);
        currentTaskNumber++;
    }
}