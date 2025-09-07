#include "Member.h"
#include <fstream>

using namespace std;

bool isValid(vector<string> validOptions, string choice)
{
    for (int i = 0; i < validOptions.size(); i++)
    {
        if (validOptions[i] == choice)
            return 1;
    }
    return 0;
}

void memberRegister(map<string, Member> &members)
{
    string usernameTemp;
    Member temp;
    cout << "Enter your username: ";
    getline(cin, usernameTemp);
    while (members.count(usernameTemp) == 1)
    {
        cout << "The username has been taken" << endl;
        cout << "Please enter another username: ";
        getline(cin, usernameTemp);
    }
    temp.insertMember(usernameTemp);
    members.insert({temp.getName(), temp});
}

int main()
{
    string choice;
    map<string, Member> members;
    fstream myfile("MemberData.dat", ios::in);
    if (!myfile)
    {
        cerr << "Failed to open/create file" << endl;
        return 1;
    }

    while (true)
    {
        Member temp;
        if (!(myfile >> temp))
            break;
        members.insert({temp.getName(), temp});
    }
    myfile.close();

    cout << "EEET2482/EEET2653/COSC2082/COSC2721(Delete whichever is not needed) GROUP PROJECT" << endl
         << "Semester 2 2025" << endl
         << "E-MOTORBIKE RENTAL APPLICATION" << endl
         << "Instructor: Dr Ling Huo Chong, Dr Ushik Shrestha, Dr Tri Huynh" << endl
         << "Group: Group No.11" << endl
         << "XXXXXXX, Tran Dang Khoi" << endl
         << "4137976, Nguyen Huynh Duc" << endl
         << "XXXXXXX, Tran Gia Khanh" << endl
         << "XXXXXXX, Bui Hoang Thai Hung" << endl;

    cout << "Use the app as   1. Guest   2. Member   3. Admin" << endl;
    cout << "1. Guest" << endl;
    cout << "2. Member" << endl;
    cout << "3. Admin" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    while (true)
    {
        if (choice == "1" || choice == "2" || choice == "3")
            break;
        cout << "Please select valid option" << endl;
        cout << "Please select again: ";
        cin >> choice;
    }

    cin.ignore();

    if (choice == "1")
    {
        string checkRegister;
        for (pair<string, Member> member : members)
        {
            member.second.show2Guest();
        }
        cout << "Do you want to register:" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cout << "Your choice: ";
        cin >> checkRegister;

        while (true)
        {
            if (checkRegister == "1" || checkRegister == "2")
                break;
            cout << "Invalid option, please select again: ";
            cin >> checkRegister;
        }

        cin.ignore();

        if (checkRegister == "1")
        {
            memberRegister(members);
        }
        else
        {
            return 1;
        }
    }

    else if (choice == "2")
    {
        string functionChoice;
        int wrongTimes = 0;
        string usernameTemp, passwordTemp;
        Member temp;
        cout << "Enter your username: ";
        getline(cin, usernameTemp);
        while (members.count(usernameTemp) == 0)
        {
            wrongTimes++;
            cout << "Wrong username, please enter again: ";
            getline(cin, usernameTemp);

            if (wrongTimes == 5)
            {
                cout << "You enter wrong username for so many times" << endl;
                return 1;
            }
        }
        wrongTimes = 0;
        cout << "Enter your password: ";
        getline(cin, passwordTemp);
        while (members[usernameTemp].verifiedPassword(passwordTemp) == 0)
        {
            wrongTimes++;
            cout << "Wrong password, please enter password again: ";
            getline(cin, passwordTemp);
            if (wrongTimes == 5)
            {
                cout << "You enter wrong password for so many times" << endl;
                return 1;
            }
        }

        
        while (true)
        {   cout << endl
            << "Account overview: " << usernameTemp << endl;
        cout << "---------------------------------------" << endl
                << endl;

        cout << "Current Credit Points: " << members[usernameTemp].getCPs() << endl;
        cout << "Renter rating: " << members[usernameTemp].calculateRating();
        cout << "   Motobike rating: " << members[usernameTemp].calculateMotoRating();
        cout << endl
                << endl;

        cout << "Your active rental booking" << endl;
        cout << "---------------------------------------" << endl;
        members[usernameTemp].showActive();
        cout << endl
                << endl;

        cout << "Your active rental request" << endl;
        cout << "---------------------------------------" << endl;
        members[usernameTemp].showRequest();

        cout << endl
                << "This is your menu: " << endl;
        cout << "1. Log out" << endl;
        cout << "2. Update profile" << endl;
        cout << "3. Change password" << endl;
        cout << "4. Top up Credit Point" << endl;
        cout << "5. Booking history" << endl;
        cout << "6. List your motorbike" << endl;
        cout << "7. Unlist your motorbike" << endl;
        cout << "8. Search and send request for motorbike rental" << endl;
        cout << "9. Accept the request" << endl;
        cout << "10. Reject the request" << endl;
        cout << "11. Return a motorbike" << endl;
        cout << "12. Confirm motorbike return from renter" << endl;
        cout << "13. Verify your account" << endl;

            cout << "Enter your choice: ";
            cin >> functionChoice;
            cin.ignore();
            if (functionChoice == "1")
            {
                break;
            }
            else if (functionChoice == "2")
            {
                members[usernameTemp].editProfile();
            }
            else if (functionChoice == "3")
            {
                members[usernameTemp].changePassword();
            }
            else if (functionChoice == "4")
            {
                members[usernameTemp].topupCPs();
            }
            else if (functionChoice == "5")
            {
                members[usernameTemp].showHistory();
            }
            else if (functionChoice == "6")
            {
                if (members[usernameTemp].getBike().checkExist() == 0)
                {
                    cout << "You have not registered any bikes" << endl;
                    cout << "So you cannot list a bike" << endl;
                }
                else
                {
                    members[usernameTemp].listmyBike();
                }
            }
            else if (functionChoice == "7")
            {
                cout << "Unlist motorbike successful.";
                cout << endl;
                members[usernameTemp].unlistmyBike();
            }
            else if (functionChoice == "8")
            {
                Date start, end;
                string locationStr;
                vector<string> validOptions;
                cout << "Enter date range" << endl;
                cout << "Enter start date: ";
                start.insertDate();
                cout << "Enter end date: ";
                end.insertDate();
                while (start > end)
                {
                    cout << "End date must be after or equal to start date" << endl;
                    cout << "Please enter end date again: ";
                    end.insertDate();
                }
                cout << "Enter location: " << endl;
                cout << "1. HCM" << endl;
                cout << "2. Ha Noi" << endl;   

                while (true)
                {
                    cout << "Your choice: ";
                    cin >> locationStr;
                    if (locationStr == "1" || locationStr == "2")
                        break;
                    cout << "Invalid option, please select again." << endl;
                }
                int location = stoi(locationStr);
                cin.ignore();
                for (pair<string, Member> member : members)
                {
                    if (member.second.checkCondition(start, end, members[usernameTemp].calculateRating(), members[usernameTemp].getCPs(), location) == 1 && member.second.checkOverlap(start, end) == 0 && member.first != usernameTemp)
                    {
                        if (!members[usernameTemp].checkLicense(end))
                        {
                            if (member.second.getBike().checkSize())
                            {
                                continue;
                            }
                            cout << "Owner: " << member.first << endl;
                            cout << member.second.getBike().showMotorbike();
                            member.second.showMotoRating();
                            cout << "-----------------------" << endl;
                            validOptions.push_back(member.first);
                        }
                        else
                        {
                            cout << "Owner: " << member.first << endl;
                            cout << member.second.getBike().showMotorbike();
                            member.second.showMotoRating();
                            cout << "-----------------------" << endl;
                            validOptions.push_back(member.first);
                        }
                    }
                }

                if (validOptions.empty())
                {
                    cout << "Cannot find motorbike which is fit with your condition!!!" << endl;
                }
                else
                {
                    string choice;
                    cout << "Enter the username of member you want to send request: ";
                    getline(cin, choice);
                    while (!isValid(validOptions, choice))
                    {
                        cout << "Invalid option, please select again: ";
                        getline(cin, choice);
                    }
                    members[usernameTemp].sendRequest(members, choice, start, end, members[usernameTemp].calculateRating());
                    validOptions.clear();
                }
            }
            else if (functionChoice == "9")
            {
                string choice;
                cout << "Your active rental request" << endl;
                cout << "---------------------------------------" << endl;
                members[usernameTemp].showRequest();
                cout << "Enter the name of renter you want to accept: ";
                getline(cin, choice);
                while (members[usernameTemp].validateOptions(choice) == 0)
                {
                    cout << "Invalid option, please enter again: ";
                    getline(cin, choice);
                }
                members[usernameTemp].acceptRequest(members, choice);
            }
            else if (functionChoice == "10")
            {
                string choice;
                cout << "Your active rental request" << endl;
                cout << "---------------------------------------" << endl;
                members[usernameTemp].showRequest();
                cout << "Enter the name of renter you want to reject: ";
                getline(cin, choice);
                while (members[usernameTemp].validateOptions(choice) == 0)
                {
                    cout << "Invalid option, please enter again: ";
                    getline(cin, choice);
                }
                members[usernameTemp].rejectRequest(members, choice);
            }
            else if (functionChoice == "11")
            {
                members[usernameTemp].rateMotobike(members);
            }
            else if (functionChoice == "12")
            {
                members[usernameTemp].rateRenter(members);
            }
            else
            {
                cout << "Invalid option, please enter valid option" << endl;
            }
        }
    }
    else if (choice == "3")
    {   
        cout << endl;
        for (pair<string, Member> member : members)
        {
            member.second.show2Admin();
            cout << endl;
        }               
    }

    myfile.open("MemberData.dat", ios::out | ios::trunc);
    for (pair<string, Member> member : members)
    {
        myfile << member.second;
    }
    myfile.close();
}