// Filename: main.cpp
// Description: A menu-driven program to analyze and display grocery item
// purchase frequencies. Reads input from a file and provides options to
// search for item frequency, print all frequencies, show a histogram,
// and create a backup file.
// Author: Andrei Shostak
// Date: 04/21/2024

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <cctype>
#include <algorithm>

// Class to handle frequency operations
class FrequencyTracker {
private:
    std::map<std::string, int> frequencies; // Map to store item frequencies

public:
    FrequencyTracker(const std::string& filename) {
        // Read input file and populate frequencies map
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error: Unable to open input file." << std::endl;
            return;
        }

        std::string item;
        while (file >> item) {
            // Convert to lowercase for case-insensitive counting
            std::transform(item.begin(), item.end(), item.begin(), ::tolower);
            frequencies[item]++;
        }
        file.close();

        // Create output file "frequency.dat"
        std::ofstream outFile("frequency.dat");
        if (!outFile) {
            std::cerr << "Error: Unable to create output file." << std::endl;
            return;
        }

        for (const auto& pair : frequencies) {
            outFile << pair.first << " " << pair.second << std::endl;
        }
        outFile.close();
    }

    int getFrequency(const std::string& item) {
        // Convert to lowercase for case-insensitive search
        std::string lowercaseItem = item;
        std::transform(lowercaseItem.begin(), lowercaseItem.end(), lowercaseItem.begin(), ::tolower);

        // Return frequency of the given item
        auto it = frequencies.find(lowercaseItem);
        if (it != frequencies.end()) {
            return it->second;
        }
        return 0;
    }

    void printFrequencies() {
        // Print all item frequencies
        for (const auto& pair : frequencies) {
            std::cout << std::setw(15) << std::left << pair.first << pair.second << std::endl;
        }
    }

    void printHistogram() {
        // Print histogram of item frequencies
        for (const auto& pair : frequencies) {
            std::cout << std::setw(15) << std::left << pair.first << std::string(pair.second, '*') << std::endl;
        }
    }
};

int main() {
    FrequencyTracker tracker("CS210_Project_Three_Input_File.txt");

    int choice;
    std::string item;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Search item frequency\n";
        std::cout << "2. Print all frequencies\n";
        std::cout << "3. Print histogram\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        // Input validation for choice
        if (!(std::cin >> choice) || choice < 1 || choice > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid choice. Try again." << std::endl;
            continue;
        }

        switch (choice) {
        case 1:
            std::cout << "Enter item: ";
            std::cin >> item;

            // Input validation for item
            if (std::all_of(item.begin(), item.end(), ::isdigit)) {
                std::cerr << "Invalid item. Item should not be a number." << std::endl;
                break;
            }

            std::cout << "Frequency of " << item << ": " << tracker.getFrequency(item) << std::endl;
            break;
        case 2:
            tracker.printFrequencies();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            std::cout << "Exiting..." << std::endl;
            break;
        }
    } while (choice != 4);

    return 0;
}