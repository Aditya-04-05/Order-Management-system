#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#include <bits/stdc++.h>

int main()
{

    string ifile;

    string ofile;
    cout << "Enter date: " << endl;
    cin >> ifile;
    ofile = ifile;
    ifile += ".txt";
    ofile += "output.csv";

    std::ifstream inputFile(ifile);  // Open the input text file
    std::ofstream outputFile(ofile); // Create the output CSV file

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

    // Write column headers to the CSV file
    outputFile << "Order ID,Customer Name,Phone Number,Payment Paid,Payment Remaining,Due Date,Status\n";

    std::string line, orderId, customerName, phoneNumber, paymentPaid, paymentRemaining, dueDate, status;

    while (getline(inputFile, line))
    {
        // Parse relevant fields
        if (line.find("Order ID") != std::string::npos)
        {
            orderId = line.substr(line.find(":") + 2);
        }
        else if (line.find("Customer Name") != std::string::npos)
        {
            customerName = line.substr(line.find(":") + 2);
        }
        else if (line.find("Phone Number") != std::string::npos)
        {
            phoneNumber = line.substr(line.find(":") + 2);
        }
        else if (line.find("Payment Paid") != std::string::npos)
        {
            paymentPaid = line.substr(line.find(":") + 2);
        }
        else if (line.find("Payment Remaining") != std::string::npos)
        {
            paymentRemaining = line.substr(line.find(":") + 2);
        }
        else if (line.find("Due Date") != std::string::npos)
        {
            dueDate = line.substr(line.find(":") + 2);
        }
        else if (line.find("Status") != std::string::npos)
        {
            status = line.substr(line.find(":") + 2);
        }
        else if (line.find("----------------------------------------") != std::string::npos)
        {
            // Write the collected data to the CSV file when a record ends
            outputFile << orderId << "," << customerName << "," << phoneNumber << ","
                       << paymentPaid << "," << paymentRemaining << "," << dueDate << "," << status << "\n";
        }
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Conversion to CSV completed successfully!" << std::endl;
    return 0;
}
