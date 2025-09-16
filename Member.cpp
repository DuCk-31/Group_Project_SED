#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <fstream>
#include "Member.h"

using namespace std;

bool checkPassword(string password) {
    bool hasDigit = false, hasUpper = false, hasLower = false, hasSpecial = false;
    bool hasMinLength = password.length() >= 10;

    for (char ch : password) {
        if (isalnum(ch)) {
            if (isalpha(ch)) {
                if (isupper(ch)) hasUpper = 1;
                else if (islower(ch)) hasLower = 1;
            } else if (isdigit(ch)) {
                hasDigit = 1;
            }
        } else {
            hasSpecial = 1;
        }
    }

    if (!hasMinLength) cout << "Password must be at least 10 characters long" << endl;
    if (!hasLower) cout << "Password must contain lowercase letters" << endl;
    if (!hasUpper) cout << "Password must contain uppercase letters" << endl;
    if (!hasDigit) cout << "Password must contain numeric characters" << endl;
    if (!hasSpecial) cout << "Password must contain special characters" << endl;

    return hasMinLength && hasLower && hasUpper && hasDigit && hasSpecial;
}

Member::Member(PersonalInfo info, PersonalDoc doc, Listing list,
        string renterName, string ownerName, string password, int status, Motorbike bike)
        :personalInfomation(info), personalDocument(doc), listBike(list),
        renterName(renterName), ownerName(ownerName), password(password), status(status),
        bike(bike){}

Motorbike Member::getBike(){
    return bike;
}

string Member::getName(){
    return personalInfomation.getInfo(1);
}

int Member::getCPs(){
    return creditPoints;
}

float Member::calculateRating(){
    int sum = 0;
    for (int i = 0; i < myRating.size(); i++){
        sum = myRating[i].getStars() + sum;
    }
    return (float)sum/myRating.size();
}

float Member::calculateMotoRating(){
    if (motorbikeRating.size() == 0) return 0.0;
    int sum = 0;
    for (Rating rating : motorbikeRating){
        sum = rating.getStars() + sum;
    }
    return (float)sum/motorbikeRating.size();
}

bool Member::verifiedPassword(string password){
    return password == this->password;
}

bool Member::checkCondition(Date start, Date end, float renterRating, int CPs, int location){
        if (listBike.checkStatus() == 0) return 0;
        if (!listBike.checkRequirement(renterRating)) return 0;
        if (CPs < listBike.calculateTotal(end - start)) return 0;
        if (!listBike.checkLocation(location)) return 0;
        if (!listBike.checkAvailable(start, end)) return 0;
        return 1;
    }

bool Member::checkLicense(Date end){
        return personalDocument.checkLicense(end);
    }

bool Member::checkOverlap(Date start, Date end){   
    for (UnavailablePeriod period : unavailablePeriod){
        if (period.isOverlap(start, end)) return 1;
    }
    return 0;
}

bool Member::isReturn(){
        return ownerName == "N/A";
    }

bool Member::checkReturn(){
    return renterName == "N/A";
}

bool Member::validateOptions(string renterName){
    return renterRequest.count(renterName) != 0;
}

bool Member::checkListStatus(){
    return listBike.checkStatus();
}

bool Member::checkRequest(){
    return renterRequest.size() != 0;
}

bool Member::verifyMember() {
    srand(time(0));  // seed random generator
    string letters = "";
    string digits = "";
    // Generate 4 random letters
    for (int i = 0; i < 4; i++) {
        char c;
        if (rand() % 2 == 0)
            c = 'A' + rand() % 26;  // uppercase
        else
            c = 'a' + rand() % 26;  // lowercase
        letters += c;
    }
    // Generate 4 random digits
    for (int i = 0; i < 4; i++) {
        char d = '0' + rand() % 10;
        digits += d;
    }
    // Combine
    string OTP = letters + digits;
    string fileName = getName() + "CerfFile.dat";
    // Write OTP to file
    ofstream CerfFile(fileName);
    CerfFile << OTP;
    CerfFile.close();

    cout << endl << "You have five attempts to enter the correct file (format: usernameCerfFile.dat)" << endl;
    cout << "For example: Dang_KhoiCerfFile.dat, member1CerfFile.dat, etc." << endl;

    string fileNameCheck;
    int attempts = 5;

    while (attempts > 0) {
        cout << "Enter the file name: ";
        cin >> fileNameCheck;

        if (fileNameCheck == fileName) {
            ifstream inFile(fileNameCheck);
            string OTPCode;
            inFile >> OTPCode;
            inFile.close();

            if (OTPCode == OTP) {
                cout << "Verification successful!!!" << endl;
                remove(fileName.c_str()); // delete file
                return 1;
            } else {
                cout << "Wrong OTP inside the file!" << endl;
            }
        } else {
            cout << "Wrong file name!!!" << endl;
        }

        attempts--;
        if (attempts > 0) {
            cout << "You have " << attempts << " attempts left." << endl;
        }
    }

    cout << "Failed to verify whether you are human!!!" << endl;

    // Remove file after failure too
    remove(fileName.c_str()); // delete file
    return 0;
}

void Member::deductCPs(int totalPrice){
    this->creditPoints = this->creditPoints - totalPrice;
}

void Member::insertMember(string username){
    int checkBike;
    personalInfomation.insertInfo(username);
    personalDocument.insertDoc();
    cout << "Do you want to register a bike?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cout << "Your choice: "; cin >> checkBike; cin.ignore();
    if (checkBike == 1) bike.insertMotorbike();
    else bike = Motorbike();
    cout << "Password must be at least 10 characters long" << endl;
    cout << "Password must contain lowercase letters" << endl;
    cout << "Password must contain uppercase letters" << endl;
    cout << "Password must contain numeric characters" << endl;
    cout << "Password must contain special characters" << endl;
    cout << "Enter your password: "; getline(cin, password);
    while (!checkPassword(password)){
        cout << "Please enter stronger password!!!" << endl;
        cout << "Enter your passwrod: "; getline(cin, password);
    }
    cout << "Your register fee is 20$ and you will have 20 credit points" << endl;
    creditPoints = 20;
    myRating.push_back(Rating(3, "Default", "Default"));
    status = 0;
    renterName = "N/A";
    ownerName = "N/A";
}

void Member::changeStatus(bool status){
    this->status = status;
}

void Member::addOwner(string ownerName){
    this->ownerName = ownerName;
}

void Member::sendRequest(map <string, Member> &members, string username, Date startDate, Date endDate, float renterRating){
    if (status == 1) {
        cout << "You are sending a rental request for another member" << endl;
        return;
    }
    string renterName = personalInfomation.getInfo(1);
    members[username].renterRequest.insert({renterName, Rental(startDate, endDate, renterName, username, members[username].getBike(), 0, this->calculateRating())});
    status = 1;
    cout << "Send request to " << username << endl;
}

void Member::acceptRequest(map <string, Member> &members, string renterName){
    //accept the request
    int totalPrice;
    renterRequest[renterName].changeStatus(1); //change status of rental to 1 (accepted)
    members[renterName].activeRental.push_back(renterRequest[renterName]); //add 1 active rental to the renter
    members[renterName].history.push_back(renterRequest[renterName]); //add to the booking history of the renter
    Date start = renterRequest[renterName].getDate(1); 
    Date end = renterRequest[renterName].getDate(2);
    unavailablePeriod.push_back(UnavailablePeriod(start, end)); //Add unavailable period for the owner
    totalPrice = listBike.calculateTotal(end - start); 
    members[renterName].deductCPs(totalPrice); //deduct renter's credit points
    this->creditPoints += totalPrice; //Add owner's credit points
    cout << "You have earned " <<  totalPrice << " CPs, now you are having " << creditPoints << endl;
    members[renterName].addOwner(this->getName());
    this->renterName = renterName;
    vector <string> overlappedRenter;

    //find overlapped requests;
    for (auto &rental : renterRequest){
        if (rental.first == renterName){
            continue;
        }
        Date s1 = rental.second.getDate(1);
        Date s = renterRequest[renterName].getDate(1);
        Date e1 = rental.second.getDate(2);
        Date e = renterRequest[renterName].getDate(2);
        if (s > e1 || s1 > e) continue;

        overlappedRenter.push_back(rental.first);
    }
    //reject all overlapped requests;
    for (string username : overlappedRenter){
        this->rejectRequest(members, username);
    }
    renterRequest.erase(renterName);
}

void Member::rejectRequest(map <string, Member> &members, string renterName){
    renterRequest[renterName].changeStatus(0);
    members[renterName].changeStatus(0);
    members[renterName].history.push_back(renterRequest[renterName]);
    renterRequest.erase(renterName);
}

void Member::rateMotobike(map <string, Member> &members){

    if (ownerName == "N/A"){
        cout << "You are not renting any motorbike" << endl;
        return;
    }

    Rating temp;
    cout << "Rate the motobike" << endl;
    temp.rateObj(personalInfomation.getInfo(1));
    members[ownerName].motorbikeRating.push_back(temp);
    activeRental.clear();
    ownerName = "N/A";
}

void Member::rateRenter(map <string, Member> &members){

    if (renterName == "N/A") {
        cout << "Your bike is not being rented by anyone" << endl;
        return;
    }

    if (members[renterName].isReturn() == 0) {
        cout << "The renter must return the motorbike first" << endl;
        cout << "After that you can confirm" << endl;
        return;
    }

    Rating temp;
    cout << "Rate the renter" << endl;
    temp.rateObj(personalInfomation.getInfo(1));
    members[renterName].myRating.push_back(temp);
    members[renterName].changeStatus(0); //renter 100% free
    renterName = "N/A";
}

void Member::listmyBike(){
    if (listBike.checkStatus()){
        cout << "Your bike has already been listed" << endl;
        return;
    }
    listBike.listMotorbike();
}

void Member::unlistmyBike(){
    if (renterName != "N/A"){
        cout << "Your bike is being rented, you cannot unlist your bike" << endl;
        return;
    }
    listBike.unlistMotorbike();
}

void Member::showHistory(){
    if (history.size() == 0) {
        cout << "You have not sent any request" << endl;
        return;
    }
    cout  << endl << personalInfomation.getInfo(1) << "'s booking history: " << endl;
    cout << setw(25) << left << "Rental Period" << right << "|" << "Owner's name and status" << endl;
    
    for (Rental rental : history){
        rental.showHistory();
    }
    cout << endl;
}

void Member::showActive(){
    if (activeRental.size() == 0) {
        cout << "No active rental" << endl;
        return;
    }
    activeRental[0].show2Renter();
}

void Member::showRequest(){
    if (renterRequest.size() == 0) {
        cout << "No active request at the moment" << endl;
        return;
    }

    cout << setw(25) << left << "Rental Period"  << right << "|" << setw(15) << left << "Renter Rating"  << right << "|" << "Username" << endl;
    for (auto request : renterRequest){
        request.second.show2Owner();
    }
}

void Member::show2Guest(){
    if (listBike.checkStatus()){
        cout << endl;
        cout << bike.showMotorbike();
        cout << "Location: " << (listBike.checkLocation(1) == 1?"HCM":"Ha Noi") << endl;
        cout << "-------------------------------------------" << endl;
    }
}

void Member::showMotoRating(){
    if (motorbikeRating.size() == 0){
        cout << "No rating at the moment" << endl;
        return;
    }
    cout << "Motorbike rating: " << calculateMotoRating() << endl;
    cout << "All ratings: " << endl;
    for (Rating rating : motorbikeRating){
        rating.showRating();
    }
}

void Member::editProfile(){
    int choice;
    cout << "What do you want to update" << endl;
    cout << "1. Full name" << endl;
    cout << "2. Email" << endl;
    cout << "3. Phone number" << endl;
    cout << "4. ID type and ID number" << endl;
    cout << "5. License number and its properties" << endl;
    cout << "6. Add motorbike" << endl;
    cout << "7. Edit the motorbike" << endl;
    cout << "8. Delete your motorbike" << endl;
    cout << "9. Delete your license" << endl;

    cout << "Enter your choice: "; cin >> choice; 

    while (true){
        if (choice > 0 && choice < 11) break;
        cout << "Invalid option, please select again: "; cin >> choice; 
    }

    cin.ignore();
    
    if (choice == 1 || choice == 2 || choice == 3){
        personalInfomation.editInfo(choice);
    }
    else if (choice == 4 || choice == 5){
        personalDocument.editDoc(choice);
    }
    else if (choice == 6){
        if (bike.checkExist()){
            cout << "You have registered a bike, cannot add new bike" << endl;
        }
        else {
            bike.insertMotorbike();
        }
    }
    else if (choice == 7){
        if (this->renterName != "N/A" || this->listBike.checkStatus() == 1) {
            cout << "Your bike are being rented or listed, cannot be modified" << endl;
        }
        else {
            bike.editMotorbike();
        }
    }
    else if (choice == 8){
        if (this->renterName != "N/A" || this->listBike.checkStatus() == 1) {
            cout << "Your bike are being rented or listed, cannot be deleted" << endl;
        }
        else {
            bike = Motorbike();
        }
    }
    else if (choice == 9) {
        if (!activeRental.empty()){    
            if (activeRental[0].getBike().checkSize() == 1){
                cout << "You are renting a bike with engin size larger than 50cc, your license cannot be deleted" << endl;
            }
            else {
                personalDocument.deleteLicense();
            }
        }
        else {
            personalDocument.deleteLicense();
        }
    }
}

void Member::changePassword(){
    string oldPassword;
    int wrongPassword;
    cout << "Enter old password: "; getline(cin, oldPassword);
    while (oldPassword != password){
        if (wrongPassword > 5) {
            cout << "You enter wrong password for so many times" << endl;
            return;
        }
        wrongPassword++;
        cout << "Wrong password, please enter again: "; getline(cin, oldPassword);
    }

    cout << "Enter your new password: ";
    cout << "Password must be at least 10 characters long" << endl;
    cout << "Password must contain lowercase letters" << endl;
    cout << "Password must contain uppercase letters" << endl;
    cout << "Password must contain numeric characters" << endl;
    cout << "Password must contain special characters" << endl;
    cout << "Enter your password: "; getline(cin, password);
    while (!checkPassword(password)){
        cout << "Please enter stronger password!!!" << endl;
        cout << "Enter your passwrod: "; getline(cin, password);
    }
}

void Member::topupCPs(){
    int CPs, wrongPassword = 0; string currentPassword; 
    cout << "Enter password to top up credit points: "; getline(cin, currentPassword);
    while (currentPassword != password){
        if (wrongPassword > 5) {
            cout << "You enter wrong password for so many times" << endl;
            return;
        }
        wrongPassword++;
        cout << "Wrong password, please enter again: "; getline(cin, currentPassword); 
    }
    cout << "How many do you want to top up (1$ = 1 CP): "; cin >> CPs;
    while (CPs < 0) {
        cout << "Credit Points cannot be negative!!!" << endl;
        cout << "Please enter again: "; cin >> CPs;
    }

    creditPoints += CPs;

    cout << "Top up successfuly, now you are having " << creditPoints << " Credit Point(s)" << endl;
}

void Member::show2Admin(){
    cout << "=== Member Information ===" << endl;
    cout << "Member rating: " << calculateRating() << endl;
    cout << "Credit points: " << creditPoints << endl;
    cout << "Status: " << (status == 1 ? "Busy" : "Free") << endl;
    cout << "Password: " << password << endl << endl;
    personalInfomation.printInfo(); cout << endl;
    personalDocument.printDoc(); cout << endl;
    bike.printInfo(); cout << endl;
    listBike.printInfo(); cout << endl;
    cout << "Unavailable periods: " << endl;
    if (unavailablePeriod.size() == 0) cout << "N/A" << endl;
    for (UnavailablePeriod period : unavailablePeriod){
            period.printPeriod();
        }
    cout << "----------------------------------" << endl;
    cout << endl << "Renter requests: " << endl;
    if (renterRequest.size() == 0) cout << "N/A" << endl;
    for (auto rental : renterRequest){
        rental.second.printInfo(0);
        cout << endl;
        }
    cout << "----------------------------------" << endl;
    cout << endl << "Active rentals: " << endl;
    if (activeRental.size() == 0) cout << "N/A" << endl;
    for (Rental rental : activeRental){
        rental.printInfo(1);
    }
    cout << "----------------------------------" << endl;
    cout << endl << "Booking history: " << endl;
    if (history.size() == 0) cout << "N/A" << endl;
    for (Rental rental : history){
        rental.printInfo(1);
    }
    cout << endl << "=========================" << endl;
}

ostream& operator << (ostream& out, Member member){
    out << member.password << endl;
    out << member.personalInfomation << member.personalDocument << member.listBike;
    out << member.bike;
    out << member.ownerName << endl << member.renterName << endl;
    out << member.unavailablePeriod.size() << endl;

    for (int i = 0; i < member.unavailablePeriod.size();  i++){
        out << member.unavailablePeriod[i];
    }

    out << member.renterRequest.size() << endl;
    for (auto rental : member.renterRequest){
        out << rental.first << endl;
        out << rental.second;
    }

    out << member.activeRental.size() << endl;
    for (int i = 0; i < member.activeRental.size(); i++){
        out << member.activeRental[i];
    }

    out << member.history.size() << endl;
    for (int i = 0; i < member.history.size(); i++){
        out << member.history[i];
    }

    out << member.motorbikeRating.size() << endl;
    for (int i = 0; i < member.motorbikeRating.size(); i++){
        out << member.motorbikeRating[i];
    }

    out << member.myRating.size() << endl;
    for (int i = 0; i < member.myRating.size(); i++){
        out << member.myRating[i];
    }
    out << member.creditPoints << " " << member.status << endl;
    return out;
}

istream& operator >> (istream& in, Member &member){
    int size;
    getline(in >> ws, member.password);
    in >> member.personalInfomation >> member.personalDocument;
    in >> member.listBike >> member.bike;
    getline(in >> ws, member.ownerName);
    getline(in >> ws, member.renterName);


    in >> size;
    member.unavailablePeriod.clear();
    for (int i = 0; i < size; i++){
        UnavailablePeriod temp;
        in >> temp;
        member.unavailablePeriod.push_back(temp);
    }

    in >> size;
    member.renterRequest.clear();
    for (int i = 0; i < size; i++){
        Rental value;
        string key;
        in >> key >> value;
        member.renterRequest.insert({key, value});
    }

    in >> size;
    member.activeRental.clear();
    for (int i = 0; i < size; i++){
        Rental temp;
        in >> temp;
        member.activeRental.push_back(temp);
    }

    in >> size;
    member.history.clear();
    for (int i = 0; i < size; i++){
        Rental temp;
        in >> temp;
        member.history.push_back(temp);
    }

    in >> size;
    member.motorbikeRating.clear();
    for (int i = 0; i < size; i++){
        Rating temp;
        in >> temp;
        member.motorbikeRating.push_back(temp);
    }

    in >> size;
    member.myRating.clear();
    for (int i = 0; i < size; i++){
        Rating temp;
        in >> temp;
        member.myRating.push_back(temp);
    }

    in >> member.creditPoints >> member.status;
    return in;
}