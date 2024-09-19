/*
 * insultgenerator_21al138.cpp
 *
 *      author: antony li
 *      implementation of the insultgenerator class.
 */

#include "insultgenerator_21al138.h"
#include <fstream>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <set>
FileException::FileException(const std::string &message) : std::runtime_error(message) {}

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const std::string &message) : std::runtime_error(message) {}

void InsultGenerator::initialize()
{
    std::ifstream file("InsultsSource.txt");
    if (!file.is_open())
    {
        throw FileException("Failed to open InsultsSource.txt");
    }

    columns.resize(3);
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string word;
        for (int i = 0; i < 3; ++i)
        {
            if (std::getline(iss, word, '\t'))
            {
                columns[i].push_back(word);
            }
            else
            {
                throw FileException("Invalid file format: each line must contain 3 tab-separated words");
            }
        }
    }

    if (file.bad())
    {
        throw FileException("Error occurred while reading the file");
    }
}

std::string InsultGenerator::talkToMe() const {
    if (columns.size() != 3 || columns[0].empty() || columns[1].empty() || columns[2].empty()) {
        throw FileException("Insult columns are not properly initialized");
    }

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist1(0, columns[0].size() - 1);
    std::uniform_int_distribution<> dist2(0, columns[1].size() - 1);
    std::uniform_int_distribution<> dist3(0, columns[2].size() - 1);

    // Pick one word from each column
    std::string word1 = columns[0][dist1(gen)];
    std::string word2 = columns[1][dist2(gen)];
    std::string word3 = columns[2][dist3(gen)];

    std::string word = "Thou " + word1 + " " + word2 + " " + word3 + "!";
    return word;
}

std::vector<std::string> InsultGenerator::generate(int num) const {
    if (num < 1 || num > 10000) {
        throw NumInsultsOutOfBounds("Number of insults out of bounds");
    }

    std::set<std::string> uniqueInsults;
    while (uniqueInsults.size() < num) {
        uniqueInsults.insert(talkToMe());
    }

    std::vector<std::string> insults(uniqueInsults.begin(), uniqueInsults.end());
    return insults;
}

void InsultGenerator::generateAndSave(std::string filename, int num) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw FileException("Failed to open file for writing");
    }

    std::vector<std::string> insults = generate(num);
    for (const auto &insult : insults) {
        file << insult << std::endl;
    }
}
