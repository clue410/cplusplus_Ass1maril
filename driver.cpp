#include "header.cpp"
#include<iostream>
#include<random>

using std::ofstream; //write
using std::ifstream; //read
using std::array;
using std::cout;
using std::endl;
using std::cin;
using std::cerr;

struct taskStructure;
struct workerStructure;

int main() {
    ofstream outfile;
    outfile.open("Outfile.txt");
    initializeArraysWithBlankStructures();
    printToOutputFile("Pre-Logic status check" + REGULAR_SEPARATOR, outfile, true);
    printToOutputFile(REGULAR_SEPARATOR, outfile, true);
    readWorkerAndTaskFiles(outfile);
    checkDataValidity(outfile);
    tasksAssingment(outfile);
    printToOutputFile(THICK_SEPARATOR, outfile, true);
    printToOutputFile("END PROGRAM", outfile, true);
    printToOutputFile(THICK_SEPARATOR, outfile, true);
}