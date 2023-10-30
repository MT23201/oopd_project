#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class TelecomOperator {
protected:
    string name;
    double threshold;

public:
    TelecomOperator(const string& operatorName, double densityThreshold)
        : name(operatorName), threshold(densityThreshold) {}

    bool isRequestLegitimate(const string& hashCode) {
        return hashCode == "True";
    }

    bool isSpectrumAvailable(double requestedDensity) {
        return requestedDensity > threshold;
    }

    void makeSpectrumRequest(const string& hashCode, double requestedDensity) {
        if (isRequestLegitimate(hashCode) && isSpectrumAvailable(requestedDensity)) {
            cout << "Request from " << name << " for spectrum having usage density " << requestedDensity << " is granted." << endl;
        } else {
            cout << "Request from " << name << " is denied." << endl;
        }
    }
};

class MVNO : public TelecomOperator {
public:
    MVNO(const string& mvnoName, double densityThreshold) : TelecomOperator(mvnoName, densityThreshold) {}
};

int main() {
    MVNO mvno1("MVNO1", 1.65);
    MVNO mvno2("MVNO2", 1.65);
    MVNO mvno3("MVNO3", 1.65);

    ifstream mvnoFile("MVNOSpectrum.csv");
    if (mvnoFile.is_open()) {
        int entryNumber = 0;
        string line;
        while (getline(mvnoFile, line)) {
            stringstream ss(line);
            string date, mvnoCompany, location, request;
            getline(ss, date, ',');
            getline(ss, mvnoCompany, ',');
            getline(ss, location, ',');
            getline(ss, request);

            entryNumber++;
            
            if (entryNumber > 1) {
                cout << "Date: " << date << endl;
                cout << "MVNO Company: " << mvnoCompany << endl;
                cout << "Location: " << location << endl;
                cout << "Request: " << request << " MHz" << "\n\n";
            }
        }
        mvnoFile.close();
    } else {
        cerr << "Invalid file!" << endl;
    }

    mvno1.makeSpectrumRequest("True", 1.7567);
    mvno2.makeSpectrumRequest("False", 0.890);
    mvno3.makeSpectrumRequest("True", 2.5856);
}
