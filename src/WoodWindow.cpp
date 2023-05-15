#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <math.h>
#include "WindowConstants.h"
#include "WoodWindow.h"
using namespace std;

const double WindowConstants::SF_SALES_TAX = 0.08625;

WoodWindow::WoodWindow() {
    this->widthInches = 0;
    this->heightInches = 0;
    this->windowType = "SH";
    this->windowWood = "DF";
    this->windowGlass = "DP";
    this->numLites = 0;
    this->hasLites = false;
    this->numWindows = 0;
}

WoodWindow::WoodWindow(double widthInches, double heightInches, string windowType, string windowWood, string windowGlass, int numWindows) {
    this->widthInches = widthInches;
    this->heightInches = heightInches;
    this->windowType = windowType;
    this->windowWood = windowWood;
    this->windowGlass = windowGlass;
    this->numWindows = numWindows;
    this->installationCost = 0;
    this->hasLites = false;
    this->numLites = 0;

    ConvertInchesToFeet();
    CalculateCost();
}

WoodWindow::WoodWindow(double widthInches, double heightInches, string windowType, string windowWood, string windowGlass, int numWindows, int numLites) {
    this->widthInches = widthInches;
    this->heightInches = heightInches;
    this->windowType = windowType;
    this->windowWood = windowWood;
    this->windowGlass = windowGlass;
    this->numWindows = numWindows;
    this->installationCost = 0;
    this->numLites = numLites;
    this->hasLites = true;

    ConvertInchesToFeet();
    CalculateCost();
}

WoodWindow::WoodWindow(string windowType, string windowWood, string windowGlass, int numWindows) {
    this->windowType = windowType;
    this->windowWood = windowWood;
    this->windowGlass = windowGlass;
    this->numWindows = numWindows;
    this->installationCost = 0;
    this->hasLites = false;
    this->numLites = 0;
}

WoodWindow::WoodWindow(string windowType, string windowWood, string windowGlass, int numWindows, int numLites) {
    this->windowType = windowType;
    this->windowWood = windowWood;
    this->windowGlass = windowGlass;
    this->numWindows = numWindows;
    this->installationCost = 0;
    this->numLites = numLites;
    this->hasLites = true;
}

WoodWindow WoodWindow::operator+(WoodWindow rhs) {

    WoodWindow windowPair;

    windowPair.sashPerimeterFt = this->sashPerimeterFt + rhs.sashPerimeterFt;
    windowPair.sashFrameCost = this->sashFrameCost + rhs.sashFrameCost;
    windowPair.glassAreaSqFt = this->glassAreaSqFt + rhs.glassAreaSqFt;
    windowPair.glassAreaCost = this->glassAreaCost + rhs.glassAreaCost;
    windowPair.numLites = this->numLites + rhs.numLites;
    windowPair.installationCost = this->installationCost + rhs.installationCost;

    windowPair.subtotalCostPerWindow = this->subtotalCostPerWindow + rhs.subtotalCostPerWindow;
    windowPair.windowTaxPerWindow = this->windowTaxPerWindow + rhs.windowTaxPerWindow;
    windowPair.totalCostPerWindow = this->totalCostPerWindow + rhs.totalCostPerWindow;

    windowPair.subtotalCost = this->subtotalCost + rhs.subtotalCost;
    windowPair.totalTax = this->totalTax + rhs.totalTax;
    windowPair.totalCost = this->totalCost + rhs.totalCost;

    return windowPair;
}

void WoodWindow::SetMeasurements(double widthInches, double heightInches) {
    this->widthInches = widthInches;
    this->heightInches = heightInches;

    ConvertInchesToFeet();
}

void WoodWindow::CalculateCost() {

    CalculatePerimeter();
    CalculateGlassArea();

    // Calculate the cost of the sash only
    if (strcmp("DF", windowWood.c_str()) == 0) {
        sashFrameCost = sashPerimeterFt * WindowConstants::DOUGLAS_FIR_COST_FT;
    } else if (strcmp("MA", windowWood.c_str()) == 0) {
        sashFrameCost = sashPerimeterFt * WindowConstants::MAHOGANY_COST_SQFT;
    }

    // If there is grids, add onto the cost of the sash
    if (hasLites == true && (strcmp("DF", windowWood.c_str()) == 0)) {
        sashFrameCost += (numLites * WindowConstants::DOUGLAS_FIR_GRID);
    } else if (hasLites == true && (strcmp("MA", windowWood.c_str()) == 0)) {
        sashFrameCost += (numLites * WindowConstants::MAHOGANY_GRID);
    }

    // We charge the minimum of 3-SqFt for the glass
    if (hasLites == false && glassAreaSqFt < 3) {
        glassAreaSqFt = 3.0;
    } else if (hasLites == true) {
        if ((glassAreaSqFt / numLites) < 3) {
            glassAreaSqFt = 3.0;
        } else {
            glassAreaSqFt /= numLites;
        }
    }

    // Calculate the cost of the glass
    if (strcmp("DP", windowGlass.c_str()) == 0) {
        glassAreaCost = glassAreaSqFt * WindowConstants::DP_COST_SQFT;
    } else if (strcmp("DP_LOW_E", windowGlass.c_str()) == 0) {
        glassAreaCost = glassAreaSqFt * WindowConstants::DP_LOW_E_COST_SQFT;
    } else if (strcmp("DP_TEMPERED", windowGlass.c_str()) == 0) {
        glassAreaCost = glassAreaSqFt * WindowConstants::DP_TEMPERED_COST_SQFT;
    } else if (strcmp("DP_LAMINATED", windowGlass.c_str()) == 0) {
        glassAreaCost = glassAreaSqFt * WindowConstants::DP_LAMINATED_COST_SQFT;
    } else if (strcmp("DP_TEMPERED_LOW_E", windowGlass.c_str()) == 0) {
        glassAreaCost = glassAreaSqFt * WindowConstants::DP_TEMPERED_LOW_E_COST_SQFT;
    } else if (strcmp("DP_SATIN_ETCHED", windowGlass.c_str()) == 0) {
        glassAreaCost = glassAreaSqFt * WindowConstants::DP_SATIN_ETCHED_COST_SQFT;
    } else if (strcmp("DP_OBSCURED", windowGlass.c_str()) == 0) {
        glassAreaCost = glassAreaSqFt * WindowConstants::DP_OBSCURED_COST_SQFT;
    
        
    } else if (strcmp("SP", windowGlass.c_str()) == 0) {
        if (hasLites == true) {
            glassAreaCost = 10 + (glassAreaSqFt * WindowConstants::SP_COST_SQFT); 
            // Since we dont charge for SP, add $10 per pane for the labor of cutting it
            // the total value is reflected when we multiply it by numLites
        } else {
            glassAreaCost = glassAreaSqFt * WindowConstants::SP_COST_SQFT;
        }
    } else if (strcmp("SP_LAMINATED", windowGlass.c_str()) == 0) {
        glassAreaCost = glassAreaSqFt * WindowConstants::SP_LAMINATED_COST_SQFT;
    } else if (strcmp("SP_TEMPERED", windowGlass.c_str()) == 0) {
        glassAreaCost = glassAreaSqFt * WindowConstants::SP_TEMPERED_COST_SQFT;
    } else if (strcmp("SP_WHITE_LAMINATE", windowGlass.c_str()) == 0) {
        glassAreaCost = glassAreaSqFt * WindowConstants::SP_WHITE_LAMINATE_COST_SQFT;
    } else if (strcmp("SP_OBSCURED", windowGlass.c_str()) == 0) {
        glassAreaCost = glassAreaSqFt * WindowConstants::SP_OBSCURED_COST_SQFT;
    }

    if (hasLites == true) {
        glassAreaCost *= numLites;
    }
    
    // Since installationCost is a floating point value, we cannot compare using ==
    // Due to how floating point values are stored in binary, IEEE 754, we compare as "close enough" using < or >
    if (fabs(installationCost - 0) < 0.0001) {
        // Calculates the installation fee, depending on the type of window
        if (strcmp("SH", windowType.c_str()) == 0) {
            installationCost = WindowConstants::SH_INSTALLATION_FEE;
        } else if (strcmp("DH", windowType.c_str()) == 0) {
            installationCost = WindowConstants::DH_INSTALLATION_FEE;
        } else if (strcmp("AW", windowType.c_str()) == 0) {
            installationCost = WindowConstants::AW_INSTALLATION_FEE;
        } else if (strcmp("FIXED", windowType.c_str()) == 0) {
            if (sashPerimeterFt < 11) {
                installationCost = WindowConstants::FIXED_SMALL_INSTALLATION_FEE;
            } else {
                installationCost = WindowConstants::FIXED_LARGE_INSTALLATION_FEE;
            }
        } else if (strcmp("CA", windowType.c_str()) == 0) {
            if (sashPerimeterFt < 11) {
                installationCost = WindowConstants::CA_SMALL_INSTALLATION_FEE;
            } else {
                installationCost = WindowConstants::CA_LARGE_INSTALLATION_FEE;
            }
        }
    }

    subtotalCostPerWindow = RoundToNearestTen(sashFrameCost + glassAreaCost + installationCost);
    windowTaxPerWindow = sashFrameCost * WindowConstants::SF_SALES_TAX;
    totalCostPerWindow = subtotalCostPerWindow + windowTaxPerWindow;

    subtotalCost = subtotalCostPerWindow * numWindows;
    totalTax = windowTaxPerWindow * numWindows;
    totalCost = subtotalCost + totalTax;
}

void WoodWindow::PrintData() {

    int widthSize = 19;

    cout << "\n";
    cout << "     " << widthInches << "x" << heightInches << " " << windowType << " Window Cost Breakdown" << endl;
    cout << "Sash Perimeter: " << sashPerimeterFt << "ft | Area of Glass: " << glassAreaSqFt << "ft^2";
    if (hasLites) {
        cout << " | Num of Lites: " << numLites << endl;
    } else {
        cout << endl;
    }

    cout << setfill('-') << setw(45) << "" << endl;
    cout << setfill(' ');

    cout << "     Cost Per Window" << endl;
    cout << setw(widthSize) << left << "Sash:" << "$" << sashFrameCost << endl;
    if (hasLites) {
        cout << setw(widthSize) << left << "Glass Cost" << endl;
        cout << setw(widthSize) << left << " - Per Pane:" << "$" << (glassAreaCost / numLites) << endl;
        cout << setw(widthSize) << left << " - Total:" << "$" << glassAreaCost << endl;
    } else {
        cout << setw(widthSize) << left << "Glass:" << "$" << glassAreaCost << endl;
    }
    cout << setw(widthSize) << left << "Installation:" << "$" << installationCost << endl;
    cout << setw(widthSize) << left << "Subtotal:" << "$" << subtotalCostPerWindow << endl;
    cout << setw(widthSize) << left << "Tax:" << "$" << setprecision(2) << fixed << windowTaxPerWindow << endl;
    cout << setw(widthSize) << left << "Total:" << "$" << setprecision(2) << fixed << totalCostPerWindow << endl;

    cout << setfill('-') << setw(45) << "" << endl;
    cout << setfill(' ');

    cout << "    Total Cost for " << numWindows <<  " Windows" << endl;
    cout << setw(widthSize) << "Subtotal:" << "$" << subtotalCost << endl;
    cout << setw(widthSize) << "Tax:" << "$" << totalTax << endl;
    cout << setw(widthSize) << "Total:" <<  "$" << totalCost << endl << endl;


}

void WoodWindow::CalculatePerimeter() {
    // Rounds up to nearest foot
    sashPerimeterFt = ceil(widthFeet * 2) + ceil(heightFeet * 2);
}

void WoodWindow::CalculateGlassArea() {
    // Removes the wood thickness in the measurements to get the glass measurements
    // Rounds up to nearest inch
    // Divide by 144 to convert from in^2 to ft^2
    glassAreaSqFt = ((ceil(widthInches) - 4) * (ceil(heightInches) - 3)) / 144.0;
}

void WoodWindow::ConvertInchesToFeet() {
    widthFeet = widthInches/12;
    heightFeet = heightInches/12;
}

int WoodWindow::RoundToNearestTen(int value) {

    while( (value % 10) != 0){
        value++;
    }

    return value;
}

/*int main(){

    WoodWindow userWindow(24, 52, "CA",  "DF", "SP", 2, 8);
    userWindow.PrintData();

    return 0;
}*/
