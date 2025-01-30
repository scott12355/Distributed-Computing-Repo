#include <fstream>
#include <iostream>
#include <vector>

/**
 * The current year.
 */
const int year = 2025;

/**
 * Prompts the user to enter their name and then prints a greeting message.
 */
void printUsersName() {
    std::string userName; // Declare string variable
    std::cout << "What is your name? "; // Ask user for their name
    std::cin >> userName; // Get the user's name from the console and assign to userName
    std::cout << "Hello, " << userName << "!\n"; // Output the user's name to the console
}

/**
 * Prompts the user to enter their age and then prints their age and estimated birth year.
 */
void printUserAge() {
    int userAge; // Declare integer variable
    std::cout << "What is your age? "; // Ask user for their age
    std::cin >> userAge; // Get the user's age from the console and assign to userAge
    std::cout << "You are " << userAge << " years old!\n"; // Output the user's age to the console
    std::cout << "You were likely born in " << year - userAge << "!\n"; // Output the user's birth year to the console
}

/**
 * Calculates the average of a vector of integers.
 *
 * @param numbers A vector of integers.
 * @return The average of the integers in the vector.
 */
double getAverage(const std::vector<int> &numbers) {
    double sum = 0;
    for (int i = 0; i < numbers.size(); i++) {
        sum += numbers[i];
        std::cout << numbers[i] << " "; // Output each number in the vector
    }
    std::cout << "\nSum: " << sum << ", Size: " << numbers.size() << std::endl; // Output the sum and size of the vector
    return sum / numbers.size(); // Return the average
}




/**
 * Prompts the user to enter five integers and stores them in a vector.
 *
 * @param numbers A reference to a vector of integers.
 * @return The vector containing the entered integers.
 */
std::vector<int> get_vector(std::vector<int> &numbers) {
    for (int i = 0; i < 5; i++) {
        int input;
        std::cout << "Enter a number: "; // Ask user for a number
        std::cin >> input; // Get the number from the console
        numbers.push_back(input); // Add the number to the vector
    }
    return numbers; // Return the vector
}

void read_from_file() {
    std::string filename = "numbers.txt";
    std::ifstream myfile(filename);
    std::vector<int> values;
    double sum, averageValue, value;
    sum = 0;

    if (myfile.is_open())
    {
        while (!myfile.eof())
        {
            myfile >> value;

            values.push_back(value);
        }

        for (int i = 0; i < values.size(); i++)
        {
            sum += values[i];
        }

        averageValue = sum / values.size();

        std::cout << "Average value: " << averageValue << "\n";
    }
    else
    {
        std::cout << "Unable to open file " << filename << "\n";
    }

}

/**
 * The main function of the program.
 *
 * @return Exit status of the program.
 */
int main(int, char **) {
    std::cout << "Hello, from Week1!\n";
    const std::string name = "Scott";
    std::cout << "Hello, this app was made by " << name << "!\n";

    printUsersName(); // Call function to print user's name
    printUserAge(); // Call function to print user's age

    std::vector<int> numbers;
    numbers = get_vector(numbers); // Get a vector of numbers from the user

    const double average = getAverage(numbers); // Calculate the average of the numbers
    std::cout << "Average is " << average << "\n"; // Output the average

    read_from_file();

    return 0; // Return exit status

}