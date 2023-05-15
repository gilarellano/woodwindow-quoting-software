#ifndef WOODWINDOW_H
#define WOODWINDOW_H

#include <string>
using namespace std;

class WoodWindow {
    public:
        WoodWindow();
        WoodWindow(double widthInches, double heightInches, string windowType, string windowWood, string windowGlass, int numWindows);
        WoodWindow(double widthInches, double heightInches, string windowType, string windowWood, string windowGlass, int numWindows, int numLites);
        WoodWindow(string windowType, string windowWood, string windowGlass, int numWindows);
        WoodWindow(string windowType, string windowWood, string windowGlass, int numWindows, int numLites);

        void SetMeasurements(double widthInches, double heightInches);
        void SetWindowType(string windowType) { this->windowType = windowType; }
        void SetWindowWood(string windowWood) { this->windowWood = windowWood; }
        void SetWindowGlass(string windowGlass) { this->windowGlass = windowGlass; }
        void SetWindowDescription(string windowDescription) { this->windowDescription = windowDescription; }
        void SetNumWindows(int numWindows) { this->numWindows = numWindows; }
        void SetNumOfLites(int numLites) { this->numLites = numLites; if(numLites != 0) { hasLites = true; } else { hasLites = false; } }

        void SetSashFrameCost(int sashFrameCost) { this->sashFrameCost = sashFrameCost; }
        void SetGlassAreaCost(int glassAreaCost) { this->glassAreaCost = glassAreaCost; }
        void SetInstallationCost(int installationCost) { this->installationCost = installationCost; }

        void SetSubtotalCostPerWindow(int subtotalCostPerWindow) { this->subtotalCostPerWindow = subtotalCostPerWindow; }
        void SetWindowTaxPerWindow(double windowTaxPerWindow) { this->windowTaxPerWindow = windowTaxPerWindow; }
        void SetTotalCostPerWindow(double totalCostPerWindow) { this->totalCostPerWindow = totalCostPerWindow; }

        void SetSubtotalCost(int subtotalCost) { this->subtotalCost = subtotalCost; }
        void SetTotalTax(double totalTax) { this->totalTax = totalTax; }
        void SetTotalCost(double totalCost) { this->totalCost = totalCost; }

        double GetWidthInches() { return widthInches; }
        double GetHeightInches() { return heightInches; }
        string GetWindowType() { return windowType; }
        string GetWindowWood() { return windowWood; }
        string GetWindowGlass() { return windowGlass; }
        string GetWindowDescription() { return windowDescription; }
        int GetNumWindows() { return numWindows; }
        int GetNumLites() { return numLites; }

        int GetSashPerimeterFt() { return sashPerimeterFt; }
        int GetSashFrameCost() { return sashFrameCost; }
        double GetGlassAreaSqFt() { return glassAreaSqFt; }
        int GetGlassAreaCost() { return glassAreaCost; }
        int GetInstallationCost() { return installationCost; }

        int GetSubtotalCostPerWindow() { return subtotalCostPerWindow; }
        double GetTaxPerWindow() { return windowTaxPerWindow; }
        double GetTotalCostPerWindow() { return totalCostPerWindow; }

        int GetSubtotalCost() { return subtotalCost; }
        double GetTotalTax() { return totalTax; }
        double GetTotalCost() { return totalCost; }

        void PrintData();
        void CalculateCost();

        WoodWindow operator+(WoodWindow rhs);

    private:
        void ConvertInchesToFeet();
        void CalculatePerimeter();
        void CalculateGlassArea();
        int RoundToNearestTen(int value);

        string windowType;
        string windowWood;
        string windowGlass;
        string windowDescription;

        int numWindows;

        bool hasLites;
        int numLites;

        double widthInches;
        double heightInches;
        double widthFeet;
        double heightFeet;

        int sashPerimeterFt;
        int sashFrameCost;
        double glassAreaSqFt;
        int glassAreaCost;
        double installationCost;

        int subtotalCostPerWindow;
        double windowTaxPerWindow; 
        double totalCostPerWindow;

        int subtotalCost;
        double totalTax;
        double totalCost;
};

#endif