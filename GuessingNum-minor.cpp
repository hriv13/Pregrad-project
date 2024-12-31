#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time

using namespace std;

const int MAX_GUESSES = 100; // Maximum number of guesses

// Function to play the guessing game
void playGuessingGame() {
    int number, guess, attempts = 0;
    char playAgain;
    int guesses[MAX_GUESSES]; // Array to store previous guesses

    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    do {
        // Generate a random number between 1 and 100
        number = rand() % 100 + 1;
        attempts = 0;

        cout << "\nWelcome to the Casino Number Guessing Game!" << endl;
        cout << "I have picked a number between 1 and 100.\nCan you guess it?" << endl;

        // Start the guessing loop
        do {
            cout << "\nEnter your guess: ";
            cin >> guess;

            // Store the guess in the array
            guesses[attempts] = guess;
            attempts++;

            if (guess > number) {
                cout << "Too high! Try again." << endl;
            } else if (guess < number) {
                cout << "Too low! Try again." << endl;
            } else {
                cout << "Congratulations! You guessed the number in " << attempts << " attempts." << endl;
            }

            // Display previous guesses
            cout << "Previous guesses: ";
            for (int i = 0; i < attempts; i++) {
                cout << guesses[i] << " ";
            }
            cout << endl;

        } while (guess != number && attempts < MAX_GUESSES); // Loop until the correct guess or max guesses

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y'); // if true then loop starts again

    cout << "\nThanks for playing! Goodbye!" << endl;
}

int main() {
    playGuessingGame(); // Start of the game
    return 0;
}