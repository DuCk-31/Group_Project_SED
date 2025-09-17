#include <iostream> // For input/output operations
using namespace std; // Use the standard namespace

#ifndef RATING_H // Prevent multiple inclusion of this header file
#define RATING_H

// Class representing a rating given by a user
class Rating{
    float stars;         // Number of stars (rating value)
    string raterName;    // Name of the person giving the rating
    string comment;      // Comment for the rating

    public:

    // Constructor with default values for all members
    Rating(float stars = -1.0, string name = string(), string comment = string());

    // Method to prompt user to rate an object
    void rateObj(string username);

    // Method to display the rating information
    void showRating();

    // Method to get the number of stars
    float getStars();

    // Overload output operator to write Rating to output stream
    friend ostream& operator << (ostream& out, Rating rating);

    // Overload input operator to read Rating from input stream
    friend istream& operator >> (istream& in, Rating &rating);

};

#endif // End of include