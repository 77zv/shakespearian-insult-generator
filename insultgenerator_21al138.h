/*
 * insultgenerator_21al138.h
 *
 *      Author: Antony Li
 *      Header file for the InsultGenerator class.
 */

#ifndef INSULTGENERATOR_21AL138_H
#define INSULTGENERATOR_21AL138_H

#include <string>
#include <vector>
#include <stdexcept>

class FileException : public std::runtime_error {
public:
    FileException(const std::string& message);
};

class NumInsultsOutOfBounds : public std::runtime_error {
public:
    NumInsultsOutOfBounds(const std::string& message);
};

class InsultGenerator {
public:
    // Public member functions
    void initialize();
    std::string talkToMe() const;
    std::vector<std::string> generate(int num) const;
    void generateAndSave(std::string filename, int num) const;

private:
    std::vector<std::vector<std::string> > columns;
    std::vector<std::string> insults;
};

#endif // INSULTGENERATOR_21AL138_H
