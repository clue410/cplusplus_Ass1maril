#ifndef ADVPROGASSINGMENT1_HEADER_H
#define ADVPROGASSINGMENT1_HEADER_H
#endif //ADVPROGASSINGMENT1_HEADER_H
using namespace std;

struct workerStructure { //worker Structure
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

    workerStructure() { //blank constructor

    }

    workerStructure(long workerId, const string &name, int variability, int ability) :
            workerId(workerId),
            name(name), //full constructor
            variability(variability),
            ability(ability) {}
};

struct taskStructure { //task Structure
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

    const int *getAttemptedWorkers() const {
        return attemptedWorkers;
    }

    int getWorkerCount() const { //get amount of workers
        int ndx = 0;
        while(attemptedWorkers[ndx] != -1){
            ndx++;
        }
        return ndx;
    }

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

    taskStructure(long taskId, const string &description, int uncertainty, int difficulty) :
            taskId(taskId), //full constructor
            description(description),
            uncertainty(uncertainty),
            difficulty(difficulty) {}
};

/*function declaration*/

void printToOutputFile(string textToPut, ofstream &file, bool newLine);

long getWorkerByWorkerId(long id);

void checkDataValidity(ofstream &outfile);

int calculateAveragePerformance(int mean, int standardDeviation, int MAX_ATTEMPTS);

int calculateMean(int ability, int difficulty);

int calculateTaskStandardDeviation(int uncertainty, int variability);

void printTaskStats(int currentTaskNumber, ofstream &outfile);

void printWorkerStats(int currentTaskNumber, long foundWorkerId, int a, ofstream &outfile, int averageScore);

void taskAssingment(ofstream &outfile);




