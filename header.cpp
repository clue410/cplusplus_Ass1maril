#include<iostream>
#include<fstream>
#include "header.h"
#include<stdio.h>
#include<string.h>
#include<array>

using std::ofstream; //write
using std::ifstream; //read
using std::string; //read
using std::cout;
using std::endl;
using std::cin;
using std::cerr;


int totalTasks = 0;
int totalWorkers = 0;
int structifiedCount = 0;
const string THICK_SEPERATOR = "====================";
const string REGULAR_SEPERATOR = "--------------------";
const string THIN_SEPERATOR = "- - - - - - - - - - - - - - - - ";
workerStructure structifiedWorkers[20];
taskStructure arrayOfStructifiedTasks[20];

void wipeArrayOfTasks() {
    for (int ia = 0; ia <= 20; ia++) {
        arrayOfStructifiedTasks[ia] = taskStructure();
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
    while ((foundCommaCount = text2Split.find(delimiter)) != std::string::npos) {
        spliterised = text2Split.substr(0, foundCommaCount);
        fieldStorage[countPosition] = spliterised;
//        cout << "count -> " << countPosition << " | stored field -> " << fieldStorage[countPosition] << endl;
        countPosition++;
        lexemised++;
        text2Split.erase(0, foundCommaCount + delimiter.length());
    }
    totalTasks++;
    int text2SplitIntegerised = std::stoi(text2Split);

//    taskStructure tokenToTask(std::stoul(fieldStorage[0]), fieldStorage[1], std::stoi(fieldStorage[2]),
//                              std::stoi(fieldStorage[3]));
//    taskStructure tokenToTask;
//    tokenToTask.taskId = std::stoul(fieldStorage[0]);
//    tokenToTask.description = fieldStorage[1];
//    tokenToTask.uncertainty = std::stoi(fieldStorage[2]);
//    tokenToTask.difficulty = std::stoi(fieldStorage[3]);

    taskStructure tokenToTask;
    tokenToTask.setTaskId(std::stoul(fieldStorage[0]));
    tokenToTask.setDescription(fieldStorage[1]);
    tokenToTask.setUncertainty(std::stoi(fieldStorage[2]));
    tokenToTask.setDifficulty(std::stoi(fieldStorage[3]));

    arrayOfStructifiedTasks[structifiedCount].setTaskId(std::stoul(fieldStorage[0]));
    arrayOfStructifiedTasks[structifiedCount].setDescription(fieldStorage[1]);
    arrayOfStructifiedTasks[structifiedCount].setUncertainty(std::stoi(fieldStorage[2]));
    arrayOfStructifiedTasks[structifiedCount].setDifficulty(std::stoi(fieldStorage[3]));
//    arrayOfStructifiedTasks[structifiedCount].setTaskId(tokenToTask.taskId);
//    arrayOfStructifiedTasks[structifiedCount].setDescription(tokenToTask.description);
//    arrayOfStructifiedTasks[structifiedCount].setUncertainty(tokenToTask.uncertainty);
//    arrayOfStructifiedTasks[structifiedCount].setDifficulty(tokenToTask.difficulty);
    cout << "`````````````````" << endl;
    cout << "Task id ~~~> " << tokenToTask.getTaskId() << endl;
    cout << "Task description ~~~> " << tokenToTask.getDescription() << endl;
    cout << "Task uncertainty ~~~> " << tokenToTask.getUncertainty() << endl;
    cout << "Task difficulty ~~~> " << tokenToTask.getDifficulty() << endl;
    cout << "X-X-X-X-X-X-X-X-X-X-X-X-X" << endl;
    cout << "Array of Structified Tasks - Task id ~~~> " << arrayOfStructifiedTasks[structifiedCount].getTaskId()
         << endl;
    cout << "Array of Structified Tasks - Task description ~~~> "
         << arrayOfStructifiedTasks[structifiedCount].getDescription() << endl;
    cout << "Array of Structified Tasks - Task uncertainty ~~~> "
         << arrayOfStructifiedTasks[structifiedCount].getUncertainty() << endl;
    cout << "Array of Structified Tasks - Task difficulty ~~~> "
         << arrayOfStructifiedTasks[structifiedCount].getDifficulty() << endl;
    cout << "X-X-X-X-X-X-X-X-X-X-X-X-X" << endl;
    int workerAmount = 0;
    int len = *(&arrayOfStructifiedTasks[structifiedCount].attemptedWorkers + 1) -
              arrayOfStructifiedTasks[structifiedCount].attemptedWorkers;
    for (int meow = 0; meow < 20; meow++) {
        arrayOfStructifiedTasks[structifiedCount].attemptedWorkers[meow] = -1;
    }
//    int workerAmount = -1;
    int blah = 0;
    for (int m = 4; m < countPosition + 1; m++) {
//        cout << "count position --> "<< countPosition <<endl;
//        cout << "field storage at current postitoin --> " << fieldStorage[m] << endl;
        if (fieldStorage[m] != "") {
            cout << "field storage at current postitoin conversion --> " << std::stoi(fieldStorage[m]) << endl;
            cout << blah << endl;
            arrayOfStructifiedTasks[structifiedCount].attemptedWorkers[blah] = std::stoi(fieldStorage[m]);
        }
//        int addToARRAY = std::stoi(fieldStorage[m]);
        int addToARRAY = 1;
//        arrayOfStructifiedTasks[structifiedCount].attemptedWorkers[blah] = addToARRAY;
//        arrayOfStructifiedTasks[structifiedCount].attemptedWorkers[blah] = std::stoi(fieldStorage[m]);
//        cout << "field storage negative -1 ? - - - > "<< fieldStorage[m] <<endl;
//        //changed from worker amount to blah
//        if (fieldStorage[m] != "" && std::stoi(fieldStorage[m]) != -1 || fieldStorage[m] != "" && fieldStorage[m] != "-1" || fieldStorage[m] != "" && std::stoi(fieldStorage[m]) > 0) {
//            int workerIdFromFieldStorage = std::stoi(fieldStorage[m]);
//            arrayOfStructifiedTasks[structifiedCount].attemptedWorkers[blah] = workerIdFromFieldStorage;
////            arrayOfStructifiedTasks[structifiedCount].attemptedWorkers[blah] = std::stoi(fieldStorage[m]);
//            cout << "VARIANTS debug output inside tokeniser of workers "<< fieldStorage[m] <<endl;
//            cout << "VARIANTS debug output inside tokeniser of workers "<< tokenToTask.attemptedWorkers[blah]<<endl;
//            cout << "VARIANTS debug output inside tokeniser of workers "<< tokenToTask.attemptedWorkers[countPosition]<<endl;
//            cout << "VARIANTS debug output inside tokeniser of workers "<< tokenToTask.attemptedWorkers[workerAmount]<<endl;
////            tokenToTask.attemptedWorkers[workerAmount] = std::stoi(fieldStorage[m]);
//            cout << "Task Worker ~~~> " << tokenToTask.attemptedWorkers[workerAmount] << endl;
        blah++;
//            workerAmount++;
//        }else{
//            cout << " **** -1 recieved ****" << endl;
//        }
//        if(arrayOfStructifiedTasks[structifiedCount].attemptedWorkers[blah] == -1 ) {
//            arrayOfStructifiedTasks[structifiedCount].attemptedWorkers[blah];
//            //remvoe append
//            cout << "found -1" <<endl;
//
//        }
    }
    cout << "text 2 split final worker lexem --> " << text2Split << endl;
    cout << blah - 1 << endl;

    arrayOfStructifiedTasks[structifiedCount].attemptedWorkers[blah - 1] = text2SplitIntegerised;


//    arrayOfStructifiedTasks[structifiedCount].attemptedWorkers[blah+1] = std::stoi(text2Split);
//    tokenToTask.attemptedWorkers[workerAmount + 1] = std::stoi(text2Split);
//    cout << "Task Worker ~~~> " << tokenToTask.attemptedWorkers[blah + 1] << endl;
//    cout << "fueld storage 0 " << fieldStorage[0] << endl;
//TODO problem area v
//    taskStructure structifiedTasks[totalTasks];
//    structifiedTasks[0] = taskStructure();
//    structifiedTasks[std::stoi(fieldStorage[0])] = tokenToTask;
//    taskStructure arrayOfStructifiedTasks[totalTasks];
//    taskStructure structifiedTasks[totalTasks];
//    arrayOfStructifiedTasks[structifiedCount] = tokenToTask;
    structifiedCount++;
}

void workerStructify(string workerSplitText) {
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
    totalWorkers++;
    workerStructure tokenWorker(std::stoul(fieldStorage[0]), fieldStorage[1], std::stoi(fieldStorage[2]),
                                std::stoi(workerSplitText));
//    workerStructure tokenWorker();
//    tokenWorker.workerId = std::stoul(fieldStorage[0]);
//    tokenWorker.name = fieldStorage[1];
//    tokenWorker.variability = std::stoi(fieldStorage[2]);
//    tokenWorker.ability = std::stoi(workerSplitText);
    cout << "- - - - - - - -" << endl;
    cout << "Worker ID ---> " << tokenWorker.getWorkerId() << endl;
    cout << "Worker Name ---> " << tokenWorker.getName() << endl;
    cout << "Worker Variability ---> " << tokenWorker.getVariability() << endl;
    cout << "Worker Ability ---> " << tokenWorker.getAbility() << endl;
    cout << "- - - - - - - -" << endl;

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
    readTasks.close();
    printToOutputFile("Tasks.txt read successfully \n", outfile);

    while (getline(readWorker, myText2)) {
        lineCounter++;
        workerStructify(myText2);
    }
    readWorker.close();
    printToOutputFile("Workers.txt read successfully \n", outfile);

};

//void printer(string printFlag) {
//
//};

taskStructure getTaskById(long targetId, taskStructure structifiedTasks[]) {

    for (int position = 0; position < totalTasks; position++) {
        if (arrayOfStructifiedTasks[position].getTaskId() == targetId) {
            cout << structifiedTasks[position].taskId << endl;
            cout << structifiedTasks[position].getTaskId() << endl;
            cout << position << " " << "found" << endl;

        } else {
            cout << "X-X-X-X-X-X-X-X-X-X-X-X-X" << endl;
            //right fetch good output woohoo V
            //doesn't save all workers to array
            cout << "NOT FOUND --> (" << targetId << ") " << "Array of Structified Tasks - Task id ~~~> "
                 << arrayOfStructifiedTasks[position].getTaskId() << endl;
            cout << "NOT FOUND --> (" << targetId << ") " << "Array of Structified Tasks - Task description ~~~> "
                 << arrayOfStructifiedTasks[position].getDescription() << endl;
            cout << "NOT FOUND --> (" << targetId << ") " << "Array of Structified Tasks - Task uncertainty ~~~> "
                 << arrayOfStructifiedTasks[position].getUncertainty() << endl;
            cout << "NOT FOUND --> (" << targetId << ") " << "Array of Structified Tasks - Task difficulty ~~~> "
                 << arrayOfStructifiedTasks[position].getDifficulty() << endl;
//            cout << "NOT FOUND --> (" << targetId << ") " << "Array of Structified Tasks - Task Workers ~~~> "
//                 << arrayOfStructifiedTasks[position].attemptedWorkers[0] << endl;
//            cout << "NOT FOUND --> (" << targetId << ") " << "Array of Structified Tasks - Task Workers ~~~> "
//                 << arrayOfStructifiedTasks[position].attemptedWorkers[1] << endl;//id 3,,id 6
//            cout << "NOT FOUND --> (" << targetId << ") " << "Array of Structified Tasks - Task Workers ~~~> "
//                 << arrayOfStructifiedTasks[position].attemptedWorkers[2] << endl;//id 7.id  10
//            cout << "NOT FOUND --> (" << targetId << ") " << "Array of Structified Tasks - Task Workers ~~~> "
//                 << arrayOfStructifiedTasks[position].attemptedWorkers[3] << endl;
//            cout << "NOT FOUND --> (" << targetId << ") " << "Array of Structified Tasks - Task Workers ~~~> "
//                 << arrayOfStructifiedTasks[position].attemptedWorkers[4] << endl;
            for (int iter = 0; iter < 20; iter++) {
                cout << "inside iter --> Array of Structified Tasks - Task Workers from new getter ~~~> "
                     << arrayOfStructifiedTasks[position].attemptedWorkers[iter] << endl;
                if (arrayOfStructifiedTasks[position].attemptedWorkers[iter] == -1) {
                }

            }
            cout << "X-X-X-X-X-X-X-X-X-X-X-X-X" << endl;
        }
    }
    return structifiedTasks[0];
}
//
//void printOut(taskStructure tasks[]) {
//    cout << "PRINT OUT FUNCTION"<< endl;
//    int len = *(&tasks + 1) - tasks;
//    cout << "size -->    " << len << endl;
//    for (int i = 0; i <= 10; i++) {
//        printTask(tasks[i]);
//    }
//    cout << "PRINT OUT FUNCTION"<< endl;
//}

void printTask(int id) {
    cout << "START Print from printTask()" << endl;
    cout << arrayOfStructifiedTasks[id].getTaskId() << endl;
    cout << arrayOfStructifiedTasks[id].getDescription() << endl;
    cout << arrayOfStructifiedTasks[id].getUncertainty() << endl;
    cout << arrayOfStructifiedTasks[id].getDifficulty() << endl;
    for (int iter = 0; iter < 20; iter++) {
        if (arrayOfStructifiedTasks[id].attemptedWorkers[iter] == -1) {
        } else {
            cout << arrayOfStructifiedTasks[id].attemptedWorkers[iter] << endl;
        }

    }
    cout << "END Print from printTask()" << endl;
}

void printToOutputFile(string insertToFile, ofstream& file){
    file << insertToFile;
}

