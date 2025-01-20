/* NAME: 1.SITI NUR FARIHIN BINTI HABIB ISMAIL A24CS0191
         2.NUR FATIN NABILA BINTI ZAINUDIN A24CS0163
    DATE OF COMPLETION : 19 JANUARY 2025*/
    
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

#define MAX_CENTERS 100

// TASK 1 : DEFINE A STUCTURED DATA TYPE
struct ReliefCenter {  
    string code;
    string name;
    string state;
    int evacuees[12],resources[12];
    double expenditures[12];
    int totalEvacuees = 0, totalResources = 0;
    double totalExpenditures = 0,avgResourcesPerEvacuee = 0.0,expPerEvacuee = 0.0;
};

// FUNCTION PROTOTYPE
bool validateInputFiles(const string filenames[], int fileCount);
void readData(ReliefCenter centers[], int& centerCount, const string filenames[]);
void mapCenterDetails(ReliefCenter centers[], int centerCount);
void calcAnnualTotals(ReliefCenter centers[], int centerCount);
void generateReport(const ReliefCenter centers[], int centerCount);

//TASK 2 : READ AND VALIDATE INPUT FILES

int main() {
    string filenames[] = {"centers.txt", "evacuees.txt", "resources.txt", "expenditures.txt"};
    ReliefCenter centers[MAX_CENTERS];
    int centerCount = 0;

// CHECK IF THE FILES EXIST
    if (!validateInputFiles(filenames,4)) {
        cerr << "Error ! Missing or inconsistent input files." << endl; 
        return 1;
    }

    readData(centers, centerCount, filenames);
    mapCenterDetails(centers, centerCount);
    calcAnnualTotals(centers, centerCount);
    generateReport(centers, centerCount);
    
    system("pause");
    return 0;
}

// FUNCTION TO VALIDATE INPUT FILES
bool validateInputFiles(const string filenames[], int fileCount) {
    ifstream file;
    int lineCounts[fileCount] = {0};

    for (int i = 0; i < fileCount; i++) {
        file.open(filenames[i]);
        if (!file) {
            cout << "Error: File not found !" << filenames[i] << endl;
            return false;
        }

        string line;
        while (getline(file, line)) {
            lineCounts[i]++;
        }
        file.close();
    }
    
    //VERIFY FILES HAVE SAME NUMBER OF LINES
    for (int i = 1; i < fileCount; i++) {
        if (lineCounts[i] != lineCounts[0]) {
            cout << "Error ! Inconsistent number of lines in input files." << endl;
            return false;
        }
    }

    return true;
}

// FUNCTION TO READ DATA FROM FILES
void readData(ReliefCenter centers[], int& centerCount, const string filenames[]) {
    ifstream file;
    string line;

    // READ CENTER CODE
    file.open(filenames[0]);
    while (file >> centers[centerCount].code) {
        centerCount++;
    }
    file.close();

    // READ EVACUEES DATA
    file.open(filenames[1]);
    for (int i = 0; i < centerCount; i++) {
        for (int j = 0; j < 12; j++) {
            file >> centers[i].evacuees[j];
        }
    }
    file.close();

    // READ RESOURCES DATA
    file.open(filenames[2]);
    for (int i = 0; i < centerCount; i++) {
        for (int j = 0; j < 12; j++) {
            file >> centers[i].resources[j];
        }
    }
    file.close();

    //READ EXPENDITURES DATA
    file.open(filenames[3]);
    for (int i = 0; i < centerCount; i++) {
        for (int j = 0; j < 12; j++) {
            file >> centers[i].expenditures[j];
        }
    }
    file.close();
}

//TASK 3 : DETERMINE RELIEF CENTER DETAILS
void mapCenterDetails(ReliefCenter centers[], int centerCount) {
    const string prefixes[] = {"TGR", "JHR", "KLT", "TRG", "SGR", "KDU", "KCH"};
    const string names[] = {"Tanjung Relief Center", "Johor Relief Center", "Kelantan Relief Center",
                            "Terengganu Relief Center", "Sungai Relief Center", "Kudat Relief Center", "Kuching Relief Center"};
    const string states[] = {"Selangor", "Johor", "Kelantan", "Terengganu", "Perak", "Sabah", "Sarawak"};

    for (int i = 0; i < centerCount; i++) {
        string prefix = "";
        if (centers[i].code.length() >= 3) {
          prefix += centers[i].code[0];
          prefix += centers[i].code[1];
          prefix += centers[i].code[2];
      } else {
        prefix = centers[i].code; // HANDLE CASES WHERE THE CODE IS SHORTER THAN 3 CHARACTERS 
}

        for (int j = 0; j < 7; j++) {
            if (prefix == prefixes[j]) {
                centers[i].name = names[j];
                centers[i].state = states[j];
                break;
            }
        }
    }
}

//TASK 4 : PERFORM DATA ANALYSIS
// FUNCTION TO CALCULATE ANNUAL TOTALS
void calcAnnualTotals(ReliefCenter centers[], int centerCount) {
    for (int i = 0; i < centerCount; i++) {
        centers[i].totalEvacuees = 0;
        centers[i].totalResources = 0;
        centers[i].totalExpenditures = 0.0;

        for (int j = 0; j < 12; j++) {
            centers[i].totalEvacuees += centers[i].evacuees[j];
            centers[i].totalResources += centers[i].resources[j];
            centers[i].totalExpenditures += centers[i].expenditures[j];
        }
        
        //CALCULATE AVERAGES RESOURCES PER EVACUEE
        centers[i].avgResourcesPerEvacuee = (double)centers[i].totalResources / centers[i].totalEvacuees;
        //CALCULATE TOTAL EXPENDITURE PER EVACUEE
        centers[i].expPerEvacuee = centers[i].totalExpenditures / centers[i].totalEvacuees;
    }
}

//TASK 5 : GENERATE A FLOOD RELIEF REPORT
// FUNCTION TO GENERATE REPORT
void generateReport(const ReliefCenter centers[], int centerCount) {

    //DISPLAY DATA IN FORMATTED TABLE FOR EACH CENTER
    cout << left << setw(12) << "CENTER CODE" << setw(25) << "CENTER NAME" << setw(15) << "STATE"
         << setw(15) << "ANNUAL EVAC" << setw(15) << "ANNUAL RES" << setw(20) << "ANNUAL EXP (RM)"
         << setw(15) << "AVG RES/EVAC" << setw(15) << "EXP/EVAC (RM)" << endl;
    cout << string(130, '-') << endl;

    double totalExpenditures = 0.0;
    string maxEvacCenter, minExpCenter;
    int maxEvac = 0;
    double minExp = 1e9;

    int monthlyEvac[12] = {0};
    for (int i = 0; i < centerCount; i++) {
        cout << left << setw(12) << centers[i].code << setw(25) << centers[i].name << setw(18) << centers[i].state
             << setw(14) << centers[i].totalEvacuees << setw(16) << centers[i].totalResources
             << setw(20) << fixed << setprecision(2) << centers[i].totalExpenditures
             << setw(15) << centers[i].avgResourcesPerEvacuee
             << setw(15) << centers[i].expPerEvacuee << endl;

        totalExpenditures += centers[i].totalExpenditures;

        if (centers[i].totalEvacuees > maxEvac) {
            maxEvac = centers[i].totalEvacuees;
            maxEvacCenter = centers[i].name + " (" + centers[i].state + ")";
        }

        if (centers[i].totalExpenditures < minExp) {
            minExp = centers[i].totalExpenditures;
            minExpCenter = centers[i].name + " (" + centers[i].state + ")";
        }

        for (int j = 0; j < 12; j++) {
            monthlyEvac[j] += centers[i].evacuees[j];
        }
    }

    int highestMonth = 0, lowestMonth = 0;
    for (int i = 1; i < 12; i++) {
        if (monthlyEvac[i] > monthlyEvac[highestMonth]) highestMonth = i;
        if (monthlyEvac[i] < monthlyEvac[lowestMonth]) lowestMonth = i;
    }

    cout << string(130, '-') << endl;

    //DISPLAY SUMMARY STATISTICS
    cout << "\nSUMMARY:" << endl;
    cout << "Total Expenditures: RM" << fixed << setprecision(2) << totalExpenditures << endl;
    cout << "Center with Highest Evacuees: " << maxEvacCenter << endl;
    cout << "Center with Lowest Expenditures: " << minExpCenter << endl;
    cout << "Month with Highest Evacuees: Month " << (highestMonth + 1) << " (" << monthlyEvac[highestMonth] << " evacuees)" << endl;
    cout << "Month with Lowest Evacuees: Month " << (lowestMonth + 1) << " (" << monthlyEvac[lowestMonth] << " evacuees)" << endl;
}
