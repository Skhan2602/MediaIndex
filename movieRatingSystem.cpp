#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum MEDIATYPE { BOOK, MOVIE, SHOW }; // Enumeration for media types
#define DEFAULT_TYPE BOOK
const string DEFAULT_COMMENT = "No comment"; // Default comment if no comment is provided

class HashNode {
public:
    // Default constructor
    HashNode() {
        type = DEFAULT_TYPE;
        m_name = "Lion King";
        m_rating = 1;
        m_comment = "No comment";
    }

    // Parameterized constructor
    HashNode(MEDIATYPE m_type, string name, int rating, string comment) {
        type = m_type;
        m_name = name;
        m_rating = rating;
        m_comment = comment;
    }

    // Get the type of media as a string
    string getType() {
        string text = "";
        switch (type) {
        case BOOK: text = "BOOK"; break;
        case MOVIE: text = "MOVIE"; break;
        case SHOW: text = "SHOW"; break;
        default: text = "UNKNOWN"; break;
        }
        return text;
    }

    // Get the name of the media
    string getName() {
        return m_name;
    }

    // Get the rating of the media
    int getRating() {
        return m_rating;
    }

    // Get the comment about the media
    string getComment() {
        return m_comment;
    }

private:
    MEDIATYPE type; // Media type
    string m_name; // Media name
    int m_rating; // Media rating
    string m_comment; // Media comment
};

// Function to insert a HashNode into the database
void insertIntoDatabase(HashNode& node) {
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    try {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "your_username", "your_password"); // Connect to MySQL server
        con->setSchema("media_ratings"); // Use the media_ratings schema

        stmt = con->createStatement();
        // Insert the HashNode data into the media_table
        stmt->execute("INSERT INTO media_table (type, name, rating, comment) VALUES ('" + node.getType() + "', '" + node.getName() + "', '" + to_string(node.getRating()) + "', '" + node.getComment() + "')");
        
        delete stmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "Error: " << e.what() << endl; // Print error message if insertion fails
    }
}

// Function to ask the user if they have any comments
int mediaComment() {
    string mediaCommentChoice = " ";
    while (mediaCommentChoice != "yes" && mediaCommentChoice != "no") {
        cout << "Do you have any comments?" << endl;
        cin >> mediaCommentChoice;
    }
    return (mediaCommentChoice == "yes") ? 1 : 0;
}

// Function to pick a movie and create a HashNode for it
HashNode pickMovie() {
    string moviePicked = " ";
    int movieRating = 0;
    string movieComment = " ";
    int movieCommentChoice = 0;
    
    cout << "What movie do you want to rate?" << endl;
    cin.ignore();
    getline(cin, moviePicked);

    cout << "What would you rate this movie?" << endl;
    cin >> movieRating;

    movieCommentChoice = mediaComment();
    if (movieCommentChoice == 1) {
        cout << "What comments do you have on this movie?" << endl;
        cin.ignore();
        getline(cin, movieComment);
    }
    else {
        movieComment = DEFAULT_COMMENT;
    }

    HashNode tempNode = HashNode(MOVIE, moviePicked, movieRating, movieComment);
    insertIntoDatabase(tempNode); // Insert the HashNode into the database
    return tempNode;
}

// Function to pick a TV show and create a HashNode for it
HashNode pickShow(){
    string showPicked = " ";
    int showRating = 0;   
    string showComment = " ";
    int showCommentChoice = 0;

    cout << "What show do you want to rate?" << endl;
    cin.ignore();
    getline(cin, showPicked);

    cout << "What would you rate this show?" << endl;
    cin >> showRating;

    showCommentChoice = mediaComment();
    if(showCommentChoice == 1){
        cout << "What comments do you have on this show?" << endl;
        cin.ignore();
        getline(cin,showComment);
    }
    else{
        showComment = DEFAULT_COMMENT;
    }

    HashNode tempNode = HashNode(MOVIE, showPicked, showRating, showComment);
    return tempNode;
}

// Function to pick a book and create a HashNode for it
HashNode pickBook(){
    string bookPicked = " ";
    int bookRating = 0;   
    string bookComment = " ";
    int bookCommentChoice = 0;

    cout << "What book do you want to rate?" << endl;
    cin.ignore();
    getline(cin, bookPicked);

    cout << "What would you rate this book?" << endl;
    cin >> bookRating;

    bookCommentChoice = mediaComment();
    if(bookCommentChoice == 1){
        cout << "What comments do you have on this book?" << endl;
        cin.ignore();
        getline(cin,bookComment);
    }
    else{
        bookComment = DEFAULT_COMMENT;
    }

    HashNode tempNode = HashNode(MOVIE, bookPicked, bookRating, bookComment);
    return tempNode;
}

// Main menu function to choose the type of media to rate
void mainMenu(){
    vector<HashNode> mediaList;
    string ratingChoice = " ";

    while(ratingChoice != "1"  && ratingChoice != "Movies" && ratingChoice != "2" && ratingChoice != "TV shows" && ratingChoice != "3" && ratingChoice != "Books"){
        cout << "What type of media would you like to rate?" << endl;
        cout << " 1. Movies \n 2.TV shows \n 3.Books" << endl;
        cin >> ratingChoice;
    }

    if(ratingChoice == "1" || ratingChoice == "Movies"){
        HashNode tempNode2 = pickMovie();
        mediaList.push_back(tempNode2);
        mainMenu();
    }
    else if(ratingChoice == "2" || ratingChoice == "TV shows"){
        HashNode tempNode3 = pickShow();
        mediaList.push_back(tempNode3);
        mainMenu();
    }
    else if(ratingChoice == "3" || ratingChoice == "Books"){
        HashNode tempNode4 = pickBook();
        mediaList.push_back(tempNode4);
        mainMenu();
    }
}

int main(){
    mainMenu();
    return 0;
}
