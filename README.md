# MediaIndex

MediaIndex is a C++ project that allows users to rate and comment on different types of media, including movies, TV shows, and books. The ratings and comments are stored in a MySQL database. The project demonstrates the use of C++ with MySQL, user input handling, and basic database operations.

## Features

- Rate movies, TV shows, and books.
- Add comments to your ratings.
- Store ratings and comments in a MySQL database.
- Simple and intuitive command-line interface.

## Prerequisites

Before you begin, ensure you have the following installed on your machine:

- C++ compiler (e.g., g++)
- MySQL server
- MySQL Connector/C++ library

## Setup

1. **Clone the repository:**

    ```bash
    git clone https://github.com/yourusername/MediaIndex.git
    cd MediaIndex
    ```

2. **Install MySQL Connector/C++:**

    Follow the instructions for your operating system to install the MySQL Connector/C++ library. You can find the installation guide [here](https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-installation.html).

3. **Set up the MySQL database:**

    - Log in to your MySQL server and create a database:

      ```sql
      CREATE DATABASE media_ratings;
      USE media_ratings;
      ```

    - Create the `media_table` table:

      ```sql
      CREATE TABLE media_table (
          id INT AUTO_INCREMENT PRIMARY KEY,
          type VARCHAR(10),
          name VARCHAR(255),
          rating INT,
          comment TEXT
      );
      ```

4. **Update the database connection details:**

    In the `insertIntoDatabase` function, update the following line with your MySQL server details:

    ```cpp
    con = driver->connect("tcp://127.0.0.1:3306", "your_username", "your_password");
    ```

## Build and Run

1. **Compile the program:**

    ```bash
    g++ -o MediaIndex MediaIndex.cpp -lmysqlcppconn
    ```

2. **Run the program:**

    ```bash
    ./MediaIndex
    ```

## Usage

1. When you run the program, you will be prompted to select the type of media you want to rate.
2. Follow the prompts to enter the name, rating, and any comments for the selected media.
3. The entered data will be inserted into the MySQL database.

## Code Overview

- **Main Components:**
  - **HashNode Class:** Represents a media item with its type, name, rating, and comment.
  - **Database Functions:** Functions to insert media items into the MySQL database.
  - **User Interaction Functions:** Functions to handle user input for rating and commenting on media.
  - **Main Menu:** The main function that provides a menu for users to select the type of media to rate.

- **Functions:**
  - **load_words(filename):** Loads words from a file.
  - **is_word_sent(word, sent_filename):** Checks if a word has already been sent.
  - **add_sent_word(word, sent_filename):** Adds a word to the sent words file.
  - **check_word_in_first_api(word, headers):** Checks word definition and example from the first API.
  - **check_word_in_second_api(word):** Checks word definition and example from the second API.
  - **send_email(subject, body, recipient_emails, sender_email, sender_password):** Sends an email with the provided subject, body, and recipient details.

## To-Do
  - Add a user interface for easier interaction.
  - Implement an autofill feature for media names.
  - Create a website for the project.

