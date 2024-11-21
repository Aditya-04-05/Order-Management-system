#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream inputFile("orders.txt");           // Open the input text file
    std::ofstream outputFile("database/output.csv"); // Create the output CSV file
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    if (!outputFile.is_open())
    {
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    // Write the column headers to the CSV file
    outputFile << "order id,Name,phone,payment paid,payment remaining,orderdate,duedate,status\n";

    std::string line;
    while (getline(inputFile, line))
    {
        outputFile << line << "\n"; // Write each line from the input file to the CSV
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Conversion to CSV completed successfully!" << std::endl;
    return 0;
}
