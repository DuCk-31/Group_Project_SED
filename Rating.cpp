#include <iostream> // For input/output operations
#include "Rating.h" // Include the header for Rating class

using namespace std; // Use the standard namespace

// Function to check if a rating string is valid (must be a number between 1 and 5, can have one dot)
bool isValidRating(string rating) {
    bool dotSeen = false; // Track if a dot has been seen
    if (rating.empty()) return false; // Empty string is invalid

    for (size_t i = 0; i < rating.size(); i++) {
        if (rating[i] == '.') {
            if (dotSeen) return false; // more than one dot is invalid
            dotSeen = true;
        } else if (!isdigit(rating[i])) {
            return false; // not a digit or dot is invalid
        }
    }

    if (stof(rating) > 5.0 || stof(rating) < 1.0) return false; // Must be between 1 and 5
    return true; // Valid rating
}

// Constructor for Rating class, initializes stars, raterName, and comment
Rating::Rating(float stars, string name, string comment)
:stars(stars), raterName(name), comment(comment) {};

// Method to rate an object, prompts user for stars and comment
void Rating::rateObj(string username){
        string starStr;
        cout << "Star(s) (1-5): "; cin >> starStr;
        while (!isValidRating(starStr)){
            cout << "Enter the star(s) from 1 to 5" << endl;
            cout << "Enter again: "; cin >> starStr;
        }

        stars = stof(starStr); // Convert string to float

        cin.ignore(); // Ignore leftover newline
        cout << "Enter your comment: "; getline(cin, comment);
        while (comment.empty()){
            cout << "Enter your comment again: "; getline(cin, comment);
        }
        raterName = username; // Set the rater's name
    }

// Method to display the rating information
void Rating::showRating(){
        cout << "Rater: " << raterName << "  star(s): " << stars << endl;
        cout << "Comment: " << comment << endl;
    }

// Method to get the number of stars
float Rating::getStars(){
    return stars;
}

// Overload output operator to write Rating to output stream
ostream& operator << (ostream& out, Rating rating){
    out << rating.raterName << endl;
    out << rating.comment << endl;
    out << rating.stars << endl;
    return out;
}

// Overload input operator to read Rating from input stream
istream& operator >> (istream& in, Rating &rating){
    getline(in >> ws, rating.raterName); // Read rater name
    getline(in >> ws, rating.comment);   // Read comment
    in >> rating.stars;                  // Read stars
    return in;
}