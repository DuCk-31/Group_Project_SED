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

// Member class to represent a user/member in the system
class Member{
    PersonalInfo personalInfomation;           // Member's personal information
    PersonalDoc personalDocument;              // Member's personal document (ID, license, etc.)
    Listing listBike;                          // Listing info for the member's bike
    Motorbike bike;                            // The member's motorbike
    vector <UnavailablePeriod> unavailablePeriod; // Periods when the member/bike is unavailable
    map <string, Rental> renterRequest;        // Rental requests from other users (key: renter name)
    vector <Rental> activeRental;              // Currently active rentals
    vector <Rental> history;                   // Rental history
    vector <Rating> motorbikeRating;           // Ratings for the member's motorbike
    vector <Rating> myRating;                  // Ratings for the member as a renter
    string renterName, ownerName, password;    // Names and password
    int creditPoints;                          // Member's credit points
    bool status; // 1 is busy 0 is free         // Member's status (busy/free)

    public:

    // Constructor with default values for all members
    Member(PersonalInfo info = PersonalInfo(), PersonalDoc doc = PersonalDoc(), Listing list = Listing(),
        string renterName= string(), string ownerName = string(), string password = string(), int status = -1,
        Motorbike bike = Motorbike());

    Motorbike getBike(); // Get the member's motorbike
    
    string getName(); // Get the member's name

    int getCPs(); // Get the member's credit points

    float calculateRating(); // Calculate the member's average rating

    float calculateMotoRating(); // Calculate the motorbike's average rating
    
    bool verifiedPassword(string password); // Verify password

    bool checkCondition(Date start, Date end, float renterRating, int CPs, int location); // Check rental conditions

    bool checkLicense(Date end); // Check if license is valid

    bool checkOverlap(Date start, Date end); // Check for unavailable period overlap

    bool validateOptions(string renterName); // Validate if a renter request exists

    bool isReturn(); // Check if member is returning a bike

    bool checkReturn(); // Check if member has returned the bike

    bool checkListStatus(); // Check if bike is listed

    bool checkRequest(); // Check if there are rental requests

    bool verifyMember(); // OTP verification for member

    void deductCPs(int totalPrice); // Deduct credit points

    void insertMember(string username); // Insert new member

    void changeStatus(bool status); // Change member status

    void addOwner(string ownerName); // Add owner name

    void sendRequest(map <string, Member> &members, string username, Date startDate, Date endDate, float renterRating); // Send rental request

    void acceptRequest(map <string, Member> &members, string username); // Accept rental request

    void rejectRequest(map <string, Member> &members, string username); // Reject rental request

    void rateMotobike(map <string, Member> &members); // Rate a motorbike

    void rateRenter(map <string, Member> &members); // Rate a renter

    void listmyBike(); // List the member's bike

    void unlistmyBike(); // Unlist the member's bike
    
    void showHistory(); // Show rental history

    void showActive(); // Show active rental

    void showRequest(); // Show rental requests

    void show2Guest(); // Show bike to guest

    void showMotoRating(); // Show motorbike ratings

    void editProfile(); // Edit member profile

    void changePassword(); // Change password

    void topupCPs(); // Top up credit points

    void show2Admin(); // Show all info to admin

    // Overload output operator to write Member object to output stream
    friend ostream& operator << (ostream& out, Member member);
    // Overload input operator to read Member object from input stream
    friend istream& operator >> (istream& in, Member &member);

};

#endif