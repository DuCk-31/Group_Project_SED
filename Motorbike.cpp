#include <iostream>
#include <regex>
#include <iomanip>
#include "Motorbike.h"
using namespace std;

bool check_plateFormat(string licensePlate)
{
    regex platePattern(R"(^\d{2}(?:MD|AC|CA|[A-Z]{1,2}\d?)?\d{3,4}\.\d{2}$)");
    return regex_match(licensePlate, platePattern);
}

Motorbike::Motorbike(string brand, string model, string color,
                     string licensePlate, string engineSize, int yearMade)
    : brand(brand), model(model), color(color), licensePlate(licensePlate),
      engineSize(engineSize), yearMade(yearMade) {}

void Motorbike::insertMotorbike()
{
    regex engineSizeFormat("^[1-9]\\d{0,3}[cC]{2}$");
    cout << "Enter bike's brand: ";
    getline(cin, brand);
    cout << "Enter bike's model: ";
    getline(cin, model);
    cout << "Enter bike's color: ";
    getline(cin, color);

    cout << "Enter bike's license plate (e.g., 64CA016.00, 65K3946.37): ";
    cin >> licensePlate;
    while (!check_plateFormat(licensePlate))
    {
        cout << "Wrong license plate format!!!" << endl;
        cout << "Please enter again (format like 64CA016.00, 65K3946.37): ";
        cin >> licensePlate;
    }

    cout << "Enter bike's engine (e.g, 125cc, 50cc, ...): ";
    cin >> engineSize;
    while (!regex_match(engineSize, engineSizeFormat))
    {
        cout << "Please follow the format such as 150cc, 50cc, etc";
        cout << "Enter the engine size again: ";
        cin >> engineSize;
    }

    cout << "Enter year made: ";
    cin >> yearMade;
    cin.ignore();
}

bool Motorbike::checkSize()
{
    return stoi(engineSize.substr(0, engineSize.length() - 2)) > 50;
}

bool Motorbike::checkExist()
{
    if (licensePlate != "N/A")
        return 1;
    return 0;
}

string Motorbike::showMotorbike()
{
    return brand + " " + model + "  Engine size: " + engineSize + "\n";
}

void Motorbike::editMotorbike(){
    string choiceStr;
    cout << "What do you want to update: " << endl;
    cout << "1. Brand" << endl;
    cout << "2. Model" << endl;
    cout << "3. Color" << endl;
    cout << "4. Engine size" << endl;
    cout << "5. Year made" << endl;
    cout << "6. License plate" << endl;

    cout << "Enter your choice: "; 
    cin >> choiceStr;
    while (choiceStr < "1" || choiceStr > "6"){
        cout << "Invalid option, please select again: "; 
        cin >> choiceStr;
    }
    cin.ignore();

    int choice = stoi(choiceStr);

    if (choice == 1) {
        cout << "Enter new brand for the bike: ";
        getline(cin, brand);
        while (brand.empty()){
            cout << "Brand cannot be empty. Enter again: ";
            getline(cin, brand);
        }
    } 
    else if (choice == 2) {
        cout << "Enter new model for the bike: ";
        getline(cin, model);
        while (model.empty()){
            cout << "Model cannot be empty. Enter again: ";
            getline(cin, model);
        }
    } 
    else if (choice == 3) {
        cout << "Enter new color for the bike: ";
        getline(cin, color);
        while (color.empty()){
            cout << "Color cannot be empty. Enter again: ";
            getline(cin, color);
        }
    } 
    else if (choice == 4) {
        regex engineSizeFormat("^[1-9]\\d{0,3}[cC]{2}$");
        cout << "Enter bike's engine (e.g, 125cc, 50cc, ...): "; cin >> engineSize;
        while(!regex_match(engineSize, engineSizeFormat)){
            cout << "Please follow the format such as 150cc, 50cc, etc";
            cout << "Enter the engine size again: "; cin >> engineSize;
        }
    } 
    else if (choice == 5) {
        cout << "Enter new year made: ";
        cin >> yearMade;
    } 
    else if (choice == 6) {
        cout << "Enter new license plate (format: XXCA or AC, letter+X) XXX.XX for example 51K3659.54): ";
        getline(cin, licensePlate);
        while (!check_plateFormat(licensePlate)){
            cout << "Wrong license plate format!" << endl;
            cout << "Please enter again (format like 64CA016.00, 65K3946.37): ";
            getline(cin, licensePlate);
        }
    }
}

void Motorbike::show2Renter(Date startDate, Date endDate, string ownerName, bool status)
{
    cout << left << setw(23) << "Rental period" << " |";
    cout << setw((brand.length() > 5 ? brand.length() + 2 : 7)) << "Brand" << "|";
    cout << setw((model.length() > 5 ? model.length() + 2 : 7)) << "Model" << "|";
    cout << setw((color.length() > 5 ? color.length() + 2 : 7)) << "Color" << "|";
    cout << setw((engineSize.length() > 4 ? engineSize.length() + 2 : 6)) << "Size" << "|";
    cout << setw((licensePlate.length() > 9 ? licensePlate.length() + 2 : 11)) << "Plate No." << "|";
    cout << setw((ownerName.length() > 5 ? ownerName.length() + 2 : 7)) << "Owner" << "|";
    cout << setw(9) << "Status" << endl;
    startDate.showDate();
    cout << " - ";
    endDate.showDate();
    cout << setw(2) << setfill(' ') << " |";
    cout << left << setw((brand.length() > 5 ? brand.length() + 2 : 7)) << brand << "|";
    cout << setw((model.length() > 5 ? model.length() + 2 : 7)) << model << "|";
    cout << setw((color.length() > 5 ? color.length() + 2 : 7)) << color << "|";
    cout << setw((engineSize.length() > 4 ? engineSize.length() + 2 : 6)) << engineSize << "|";
    cout << setw((licensePlate.length() > 9 ? licensePlate.length() + 2 : 11)) << licensePlate << "|";
    cout << setw((ownerName.length() > 5 ? ownerName.length() + 2 : 7)) << ownerName << "|";
    cout << (status == 1 ? "Accepted" : "Rejected") << endl;
}

ostream &operator<<(ostream &out, Motorbike bike)
{
    out << bike.brand << endl;
    out << bike.model << endl;
    out << bike.color << endl;
    out << bike.licensePlate << " " << bike.engineSize << " " << bike.yearMade << endl;
    return out;
}

istream &operator>>(istream &in, Motorbike &bike)
{
    getline(in >> ws, bike.brand);
    getline(in >> ws, bike.model);
    getline(in >> ws, bike.color);
    in >> bike.licensePlate >> bike.engineSize >> bike.yearMade;
    return in;
}
