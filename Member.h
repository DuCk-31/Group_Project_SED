#include <iostream>
#include "PersonalInfo.h"
#include "PersonalDoc.h"
#include "Motorbike.h"
#include "Listing.h"
#include "Rental.h"
#include "UnavailablePeriod.h"
#include "Date.h"
#include "Rating.h"
#include <map>
#include <vector>
using namespace std;

#ifndef MEMBER_H
#define MEMBER_H


class Member{
    PersonalInfo personalInfomation;
    PersonalDoc personalDocument;
    Listing listBike;
    Motorbike bike;
    vector <UnavailablePeriod> unavailablePeriod;
    map <string, Rental> renterRequest;
    vector <Rental> activeRental;
    vector <Rental> history;
    vector <Rating> motorbikeRating;
    vector <Rating> myRating;
    string renterName, ownerName, password;
    int creditPoints;
    bool status; // 1 is busy 0 is free


    public:

    Member(PersonalInfo info = PersonalInfo(), PersonalDoc doc = PersonalDoc(), Listing list = Listing(),
        string renterName= string(), string ownerName = string(), string password = string(), int status = -1,
        Motorbike bike = Motorbike());

    Motorbike getBike();
    
    string getName();

    int getCPs();

    float calculateRating();

    float calculateMotoRating();
    
    bool verifiedPassword(string password);

    bool checkCondition(Date start, Date end, float renterRating, int CPs, int location);

    bool checkLicense(Date end);

    bool checkOverlap(Date start, Date end);

    bool validateOptions(string renterName);

    bool isReturn();
    
    void deductCPs(int totalPrice);

    void insertMember(string username);

    void changeStatus(bool status);

    void addOwner(string ownerName);

    void sendRequest(map <string, Member> &members, string username, Date startDate, Date endDate, float renterRating);

    void acceptRequest(map <string, Member> &members, string username);

    void rejectRequest(map <string, Member> &members, string username);

    void rateMotobike(map <string, Member> &members);

    void rateRenter(map <string, Member> &members);

    void listmyBike();

    void unlistmyBike();
    
    void showHistory();

    void showActive();

    void showRequest();

    void show2Guest();

    void showMotoRating();

    void editProfile();

    void changePassword();

    void topupCPs();

    void show2Admin();

    friend ostream& operator << (ostream& out, Member member);
    friend istream& operator >> (istream& in, Member &member);

};

#endif