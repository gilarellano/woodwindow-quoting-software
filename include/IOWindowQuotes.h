#ifndef IOWINDOWQUOTES_H
#define IOWINDOWQUOTES_H

#include <fstream>
#include <string>
#include <vector>
#include "WoodWindow.h"
using namespace std;

class IOWindowQuotes {

    public:
        IOWindowQuotes() { this->inputFile = "WindowSpecs.csv"; this->outputFile = "WindowQuote.csv"; }
        IOWindowQuotes(string inputFile, string outputFile) { this->inputFile = inputFile; this->outputFile = outputFile; }

        void ReadFile();
        void WriteQuote();
        void WriteDetailedQuote(string outputFile);

    private:
        void WriteDescription(string woodType, string glassType, ofstream& outFS);
        bool ConvertToBool(string booleanString);
        string ConvertDescription(string description);

        vector<WoodWindow> listOfWindows;
        ifstream inFS;
        ofstream outFS;

        string inputFile;
        string outputFile;

        string line;
        int width;
        int height;
        int quantity;
        int numLites;
        int installationCost;
        string windowType;
        string woodType;
        string glassType;

};

#endif