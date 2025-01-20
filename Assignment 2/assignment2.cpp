/* NAME: 1.SITI NUR FARIHIN BINTI HABIB ISMAIL A24CS0191
         2.NUR FATIN NABILA BINTI ZAINUDIN A24CS0163
    DATE OF COMPLETION : 7 JANUARY 2025*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Task 1: Declare Parallel Arrays
const int SIZE=50;
string driverNames[SIZE];
string vehicleTypes[SIZE];
string regionsCovered[SIZE];
int tripsCompleted[SIZE];
float farePerTrip[SIZE];
float totalEarnings[SIZE];

//Task 2:Implement the readInput Function
void readInput(string driverNames[], string vehicleTypes[], string regionsCovered[],int tripsCompleted[], float farePerTrip[], int& totalDrivers) {
     ifstream inputFile("input.txt"); //open the file name "input.txt"

    if (!inputFile) {
       cout << "Error ! Input file not found." << endl;
        exit(1);
    }
   totalDrivers = 0;
    while (getline(inputFile, regionsCovered[totalDrivers], ',') && totalDrivers < SIZE) {
        getline(inputFile, driverNames[totalDrivers], ',');
        getline(inputFile, vehicleTypes[totalDrivers], ',');
        inputFile >> tripsCompleted[totalDrivers];
        inputFile.ignore(1);
        inputFile >> farePerTrip[totalDrivers];
        inputFile.ignore(1);
        totalDrivers++;
    }

    inputFile.close(); //close the file
}

//Task 3: Implement the calculateEarnings Function
void calculateEarnings(int tripsCompleted[], float farePerTrip[],
                       float totalEarnings[], int totalDrivers) {
    for (int i = 0; i < totalDrivers; i++) {
        totalEarnings[i] = tripsCompleted[i] * farePerTrip[i];
    }
}

//Task 4: Implement the displayRecords Function
void displayRecords(const string driverNames[], const string vehicleTypes[],
                    const string regionsCovered[], const int tripsCompleted[],
                    const float farePerTrip[], const float totalEarnings[], int totalDrivers) {
    cout << left << setw(15) << "Driver Name"
         << setw(15) << "Vehicle Type"
         << setw(10) << "Region"
         << setw(18) << "Trips Completed"
         << setw(20) << "Fare Per Trip (MYR)"
         << "Total Earnings (MYR)" << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < totalDrivers; i++) {
        cout << left << setw(15) << driverNames[i]
             << setw(15) << vehicleTypes[i]
             << setw(10) << regionsCovered[i]
             << setw(18) << tripsCompleted[i]
             << setw(20) << fixed << setprecision(2) << farePerTrip[i]
             << fixed << setprecision(2) << totalEarnings[i] << endl;
    }
}

//Task 5:Implement the displayAnalysis Function
void displayAnalysis(const string driverNames[], const string vehicleTypes[],
                     const string regionsCovered[], const int tripsCompleted[],
                     const float farePerTrip[], const float totalEarnings[], int totalDrivers) {
    int maxTrips = 0, maxEarnings = 0;
    int totalTrips[4] = {0};
    float totalEarningsByType[4] = {0};
    string vehicleTypeName[] = {"Compact", "Sedan", "SUV", "Luxury"};

    int regionalTrips[4] = {0}; // Index order: North, Central, South, East
    string regionLabels[] = {"North", "Central", "South", "East"};

    for (int i = 0; i < totalDrivers; i++) {
        // find driver with the most trips completed and highest earnings
        if (tripsCompleted[i] > tripsCompleted[maxTrips]) 
        maxTrips = i;
        if (totalEarnings[i] > totalEarnings[maxEarnings]) 
        maxEarnings = i;

        // calculate totaltrips completed and total earings for each vehicle type
        if (vehicleTypes[i] == "Compact") {
            totalTrips[0] += tripsCompleted[i];
            totalEarningsByType[0] += totalEarnings[i];
        } 
        else if (vehicleTypes[i] == "Sedan") {
            totalTrips[1] += tripsCompleted[i];
            totalEarningsByType[1] += totalEarnings[i];
        } 
        else if (vehicleTypes[i] == "SUV") {
            totalTrips[2] += tripsCompleted[i];
            totalEarningsByType[2] += totalEarnings[i];
        } 
        else if (vehicleTypes[i] == "Luxury") {
            totalTrips[3] += tripsCompleted[i];
            totalEarningsByType[3] += totalEarnings[i];
        }

        // Accumulate trips by region
        if (regionsCovered[i] == "North") {
            regionalTrips[0] += tripsCompleted[i];
        } 
        else if (regionsCovered[i] == "Central") {
            regionalTrips[1] += tripsCompleted[i];
        } 
        else if (regionsCovered[i] == "South") {
            regionalTrips[2] += tripsCompleted[i];
        } 
        else if (regionsCovered[i] == "East") {
            regionalTrips[3] += tripsCompleted[i];
        }
    }

    cout << "\nTop Performer (Most Trips): " << driverNames[maxTrips]
         << " (" << tripsCompleted[maxTrips] << " trips)\n";
    cout << "Top Earner: " << driverNames[maxEarnings]
         << " (MYR " << fixed << setprecision(2) << totalEarnings[maxEarnings] << ")\n";

    cout << "\nVehicle Type Performance:\n";
    cout << left << setw(15) << "Vehicle Type"
         << setw(15) << "Total Trips"
         << "Total Earnings (MYR)" << endl;
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i < 4; i++) {
        cout << left << setw(15) << vehicleTypeName[i]
             << setw(15) << totalTrips[i]
             << fixed << setprecision(2) << totalEarningsByType[i] << endl;
    }

    // Regional Trips Histogram
    cout << "\nRegional Trips Histogram:\n";
    for (int i = 0; i < 4; i++) {
        cout << left << setw(10) << regionLabels[i] << ": ";
        int stars = regionalTrips[i] / 5; // Scale trips to stars
        for (int j = 0; j < stars; j++) cout << '*';
        cout << " (" << regionalTrips[i] << ")" << endl;
    }
}

//Task 6 :Implement the main Function
int main() {
   
    int totalDrivers = 0;
    
    //read input data
    readInput(driverNames, vehicleTypes, regionsCovered, tripsCompleted, farePerTrip, totalDrivers);

    //calculate total earnings
    calculateEarnings(tripsCompleted, farePerTrip, totalEarnings, totalDrivers);

    //display individual driver information
    displayRecords(driverNames, vehicleTypes, regionsCovered, tripsCompleted, farePerTrip, totalEarnings, totalDrivers);

    //display trip analysis
    displayAnalysis(driverNames, vehicleTypes, regionsCovered, tripsCompleted, farePerTrip, totalEarnings, totalDrivers);

    system("pause");
    return 0;
}

