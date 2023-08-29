//
// Created by Marilena on 21/8/2023.
//

#ifndef ADVPROGASSINGMENT1_HEADER_H
#define ADVPROGASSINGMENT1_HEADER_H
#endif //ADVPROGASSINGMENT1_HEADER_H
using namespace std;

struct workerStructure {
    long workerId;
    string name;
    int variability;
    int ability;

    long getWorkerId() const {
        return workerId;
    }

    const string &getName() const {
        return name;
    }

    int getVariability() const {
        return variability;
    }

    int getAbility() const {
        return ability;
    }

    void setWorkerId(long workerId) {
        workerStructure::workerId = workerId;
    }

    void setName(const string &name) {
        workerStructure::name = name;
    }

    void setVariability(int variability) {
        workerStructure::variability = variability;
    }

    void setAbility(int ability) {
        workerStructure::ability = ability;
    }

    workerStructure() {

    }

    workerStructure(long workerId, const string &name, int variability, int ability) : workerId(workerId), name(name),
                                                                                       variability(variability),
                                                                                       ability(ability) {}
};

struct taskStructure {
    taskStructure() {

    }

    long taskId;
    string description;
    int uncertainty;
    int difficulty;
    int attemptedWorkers[20];

    long getTaskId() const {
        return taskId;
    }

    const string &getDescription() const {
        return description;
    }

    int getUncertainty() const {
        return uncertainty;
    }

    int getDifficulty() const {
        return difficulty;
    }

    //new getter
    const int *getAttemptedWorkers() const {
        return attemptedWorkers;
    }

//    int getAllTaskWorkers() const {
//        for (int iter = 0; iter <= 20; iter++) {
//            return attemptedWorkers[iter];
//        }
//    }

    void setTaskId(long taskId) {
        taskStructure::taskId = taskId;
    }

    void setDescription(const string &description) {
        taskStructure::description = description;
    }

    void setUncertainty(int uncertainty) {
        taskStructure::uncertainty = uncertainty;
    }

    void setDifficulty(int difficulty) {
        taskStructure::difficulty = difficulty;
    }

    //new setter for workers


    taskStructure(long taskId, const string &description, int uncertainty, int difficulty) : taskId(taskId),
                                                                                             description(description),
                                                                                             uncertainty(uncertainty),
                                                                                             difficulty(difficulty) {}
};


void readFromTaskFile(fstream outfile);

void printer();

taskStructure getTaskById();

void finalPrintOut();

void readFromWorkerFile();

void textSplitterTasks();

void textSplitterWorker();

void getNextTask();

void getNextWorker();

void calculateMean();

void calculateTaskStandardDeviation();

void worker5Attempts();

void calculateAveragePerformance();

void calculatePerformanceScore();

void outputToFile();

void printTask(int id);

void tokenToString(string fieldStorage);

void printToOutputFile(string textToPut, ofstream& file);


