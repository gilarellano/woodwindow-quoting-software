#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "WoodWindow.h"
#include "WindowConstants.h"
#include "IOWindowQuotes.h"
using namespace std;

void IOWindowQuotes::ReadFile() {

    char delimeter;
    inFS.open(inputFile);

    if (!inFS.is_open()) {
        cout << "Could not open " << inputFile << endl;
        throw runtime_error("Error Opening File");
    }

    // Skips header
    getline(inFS, line);

    while(!inFS.eof()) {
    
        // Read through values
        inFS >> width >> delimeter
            >> height >> delimeter
            >> quantity >> delimeter
            >> numLites >> delimeter;

        getline(inFS, windowType, ',');
        getline(inFS, woodType, ',');
        getline(inFS, glassType, ',');
        
        inFS >> installationCost;

        // Goes onto next line
        getline(inFS, line);
        
        if (windowType == "SH" || windowType == "DH") { // Single/Double Hung, split up height for bottom and top sash

            // Top Sash, Add 3" to height to account for the legs
            double topSashHeight = (height / 2) + 3;
            double bottomSashHeight = height / 2;

            if (numLites >= 1) {
                numLites /= 2;
                WoodWindow topSash(width, topSashHeight, windowType, woodType, glassType, quantity, numLites);
                WoodWindow bottomSash(width, bottomSashHeight, windowType, woodType, glassType, quantity, numLites);

                // Will use a custom installation price instead of the constant value in WindowConstants.h
                if (installationCost != 0) {
                    installationCost /= 2;

                    topSash.SetInstallationCost(installationCost);
                    topSash.CalculateCost();

                    bottomSash.SetInstallationCost(installationCost);
                    bottomSash.CalculateCost();
                }

                WoodWindow windowPair = topSash + bottomSash;

                windowPair.SetWindowType(windowType);
                windowPair.SetMeasurements(width, height);
                windowPair.SetNumWindows(quantity);

                listOfWindows.push_back(windowPair);
                
            } else {
                WoodWindow topSash(width, topSashHeight, windowType, woodType, glassType, quantity);
                WoodWindow bottomSash(width, bottomSashHeight, windowType, woodType, glassType, quantity);

                if (installationCost != 0) {
                    installationCost /= 2;

                    topSash.SetInstallationCost(installationCost);
                    topSash.CalculateCost();

                    bottomSash.SetInstallationCost(installationCost);
                    bottomSash.CalculateCost();
                }

                WoodWindow windowPair = topSash + bottomSash;

                windowPair.SetWindowType(windowType);
                windowPair.SetMeasurements(width, height);
                windowPair.SetNumOfLites(numLites);
                windowPair.SetNumWindows(quantity);

                listOfWindows.push_back(windowPair);

            }

        } else if (windowType == "DC") { // Double Casement, split up width for left and right window pair

            windowType = "CA";
            double leftCasementWidth = width / 2;
            double rightCasementWidth = width / 2;

            if (numLites >= 1) {
                numLites /= 2;

                WoodWindow leftCasement(leftCasementWidth, height, windowType, woodType, glassType, quantity, numLites);
                WoodWindow rightCasement(rightCasementWidth, height, windowType, woodType, glassType, quantity, numLites);

                if (installationCost != 0) {
                    installationCost /= 2;

                    leftCasement.SetInstallationCost(installationCost);
                    leftCasement.CalculateCost();

                    rightCasement.SetInstallationCost(installationCost);
                    rightCasement.CalculateCost();
                }

                WoodWindow casementPair = leftCasement + rightCasement;

                casementPair.SetWindowType("DC");
                casementPair.SetMeasurements(width, height);
                casementPair.SetNumWindows(quantity);

                listOfWindows.push_back(casementPair);
            } else {
                WoodWindow leftCasement(leftCasementWidth, height, windowType, woodType, glassType, quantity);
                WoodWindow rightCasement(rightCasementWidth, height, windowType, woodType, glassType, quantity);

                if (installationCost != 0) {
                    installationCost /= 2;

                    leftCasement.SetInstallationCost(installationCost);
                    leftCasement.CalculateCost();

                    rightCasement.SetInstallationCost(installationCost);
                    rightCasement.CalculateCost();
                }

                WoodWindow casementPair = leftCasement + rightCasement;

                casementPair.SetWindowType("DC");
                casementPair.SetMeasurements(width, height);
                casementPair.SetNumOfLites(numLites);
                casementPair.SetNumWindows(quantity);

                listOfWindows.push_back(casementPair);
            }

        } else if (numLites >= 1) {

            WoodWindow currentWindow(width, height, windowType, woodType, glassType, quantity, numLites);

            if (installationCost != 0) {
                currentWindow.SetInstallationCost(installationCost);
                currentWindow.CalculateCost();
            }

            listOfWindows.push_back(currentWindow);
        
        } else {

            WoodWindow currentWindow(width, height, windowType, woodType, glassType, quantity);

            if (installationCost != 0) {
                currentWindow.SetInstallationCost(installationCost);
                currentWindow.CalculateCost();
            }

            listOfWindows.push_back(currentWindow);
        }
    }

    inFS.close();

}

void IOWindowQuotes::WriteQuote() {

    outFS.open(outputFile);

    if (!outFS.is_open()) {
        cout << "Could not create " << outputFile << endl;
        throw runtime_error("Error Creating File");
    }

    // Header
    outFS << "Description,Qty,Unit,Total" << endl;

    int subtotalCost = 0;
    double totalTax = 0;
    double totalCost = 0;


    for (int i = 0; i < listOfWindows.size(); i++) {
        //listOfWindows.at(i).PrintData();

        outFS << listOfWindows.at(i).GetWidthInches() << "x" << listOfWindows.at(i).GetHeightInches() << " " << ConvertDescription(listOfWindows.at(i).GetWindowType()) << " Window";
        if (listOfWindows.at(i).GetNumLites() >= 1) {
            outFS << " " << listOfWindows.at(i).GetNumLites() << " Lites,";
        } else {
            outFS << ",";
        }

        outFS << listOfWindows.at(i).GetNumWindows() << ", $" << listOfWindows.at(i).GetSubtotalCostPerWindow() << ", $" << listOfWindows.at(i).GetSubtotalCost() << endl;

        subtotalCost += listOfWindows.at(i).GetSubtotalCost();
        totalTax += listOfWindows.at(i).GetTotalTax();
        totalCost += listOfWindows.at(i).GetTotalCost();
    }

    WriteDescription(listOfWindows.at(0).GetWindowWood(), listOfWindows.at(0).GetWindowGlass(), outFS);

    outFS << ",,Subtotal:, $" << subtotalCost << endl;
    outFS << ",,Total Tax:, $" << totalTax << endl;
    outFS << ",,Total Cost:, $" << totalCost << endl;

    outFS.close();

}

void IOWindowQuotes::WriteDetailedQuote(string outputFile) {

    int subtotalCost;
    double totalTax;
    double totalCost;

    outFS.open(outputFile);

    if (!outFS.is_open()) {
        cout << "Could not create " << outputFile << endl;
        throw runtime_error("Error Creating File");
    }

    outFS << "Description,Qty,Area of Glass, Glass Cost, Sash Perimeter, Wood Cost,Installation Cost,Sash + Installation, Unit Tax, Total Tax, Total Cost - Tax" << endl;

    for (int i = 0; i < listOfWindows.size(); i++) {
        
        outFS << static_cast<int>(listOfWindows.at(i).GetWidthInches()) << "x" << static_cast<int>(listOfWindows.at(i).GetHeightInches()) << " " << ConvertDescription(listOfWindows.at(i).GetWindowType()) << " Window";

        if (listOfWindows.at(i).GetNumLites() > 0) {
            outFS << " " << listOfWindows.at(i).GetNumLites() << " Lites,";
        } else {
            outFS << ",";
        }

        outFS << listOfWindows.at(i).GetNumWindows() << ',' << setprecision(2) << fixed << listOfWindows.at(i).GetGlassAreaSqFt() << " SqFt, $" << listOfWindows.at(i).GetGlassAreaCost() << ',' << listOfWindows.at(i).GetSashPerimeterFt() << "ft, $" << listOfWindows.at(i).GetSashFrameCost() << ", $";
        outFS << listOfWindows.at(i).GetInstallationCost() << ", $" << listOfWindows.at(i).GetSubtotalCostPerWindow() << ", $" << listOfWindows.at(i).GetTaxPerWindow() << ", $" << listOfWindows.at(i).GetTotalTax() << ", $" << listOfWindows.at(i).GetSubtotalCost() << endl;

        if (listOfWindows.at(i).GetNumLites() > 0) {
            outFS << ", - Per Lite:," << setprecision(2) << fixed << (listOfWindows.at(i).GetGlassAreaSqFt() / listOfWindows.at(i).GetNumLites()) << "SqFt, $";
            outFS << setprecision(2) << fixed << (listOfWindows.at(i).GetGlassAreaCost() / listOfWindows.at(i).GetNumLites()) << ',';
            outFS << " - Per Lite:, $";

            if (listOfWindows.at(i).GetWindowWood() == "DF") {
                outFS << WindowConstants::DOUGLAS_FIR_GRID << endl;
            } else if (listOfWindows.at(i).GetWindowWood() == "MA") {
                outFS << WindowConstants::MAHOGANY_GRID << endl;
            } else {
                outFS << "Not have that pricing for wood grid" << endl;
            }
        }

        subtotalCost += listOfWindows.at(i).GetSubtotalCost();
        totalTax += listOfWindows.at(i).GetTotalTax();
        totalCost += listOfWindows.at(i).GetTotalCost();

        listOfWindows.at(i).PrintData();
    }

    outFS << " , , , , , , , , Total:, $" << totalTax << ", $" << subtotalCost << endl;
    outFS << " , , , , , , , , Total:, $" << totalCost << endl; 

    outFS.close();

}

void IOWindowQuotes::WriteDescription(string woodType, string glassType, ofstream& outFS) {

    outFS << "Wood: " << ConvertDescription(woodType) << "\n";
    outFS << "Glass: " << ConvertDescription(glassType) << "\n";
    outFS << "Installation Included" << endl;
    outFS << "Disposal and removal of old windows" << endl;
    outFS << "\"Coat of Primer, Interior and Exterior\"" << endl;

}

string IOWindowQuotes::ConvertDescription(string description) {

    if (description == "SH") {
        return "Single Hung";
    } else if (description == "DH") {
        return "Double Hung";
    } else if (description == "CA") {
        return "Casement";
    } else if (description == "DC") {
        return "Double Casement";
    } else if (description == "FIXED") {
        return "Fixed";
    } else if (description == "AW") {
        return "Awning";
    }

    if (description == "DF") {
        return "Douglas Fir";
    } else if (description == "MA") {
        return "Mahogany";
    }

    if (description == "DP") {
        return "Dual Pane";
    } else if (description == "DP_LOW_E") {
        return "Dual Pane w/ Low-E";
    } else if (description == "DP_TEMPERED") {
        return "Dual Pane w/ Tempered";
    } else if (description == "DP_LAMINATED") {
        return "Dual Pane w/ Laminated";
    } else if (description == "DP_TEMPERED_LOW_E") {
        return "Dual Pane, Tempered and Low-E";
    } else if (description == "DP_SATIN_ETCHED") {
        return "Dual Pane w/ Satin Etched";
    } 

    if (description == "SP") {
        return "Single Pane";
    } else if (description == "SP_LAMINATED") {
        return "Single Pane w/ Laminated";
    } else if (description == "SP_WHITE_LAMINATE") {
        return "Single Pane w/ White Laminate";
    } else if (description == "SP_OBSCURED") {
        return "Single Pane w/ Obscured";
    }

    return description;

}

bool IOWindowQuotes::ConvertToBool(string booleanString) {
    istringstream is(booleanString);
    bool b;

    is >> boolalpha >> b;

    return b;
}

int main() {

    IOWindowQuotes userQuote("WindowSpecs.csv", "Window Quote.csv");
    userQuote.ReadFile();
    userQuote.WriteQuote();
    userQuote.WriteDetailedQuote("Window Quote Breakdown.csv");

    return 0;

}
