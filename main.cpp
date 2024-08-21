#include "include/LetterFrequencyTrie.h"

#include <iostream>

int main(int argc, char**argv)
{
    if (argc < 3)
    {
        std::cout << "Not enough arguments. Give training data file then letter groups." << std::endl;
    }

    LetterFrequencyTrie lft;
    std::cout << "Parsing training data..";
    lft.ParseFile(argv[1]);
    std::cout << "done." << std::endl;

    std::vector<std::string> groups;

    for (int i = 2; i < argc; i++)
    {
        std::cout << "Adding group: " << argv[i] << std::endl;
        groups.push_back(argv[i]);
    }

    std::cout << "Predicting..";
    std::vector<std::string> results = lft.Predict(groups);
    std::cout << "done." << std::endl;
    std::cout << "Predictions: " << std::endl;

    for (auto r : results)
    {
        std::cout << r << std::endl;
    }

    std::cout << "Predicted to follow " + results[0] << std::endl;
    std::cout << "========================================" << std::endl;
    for (auto fw : lft.PredictNextWord(results[0]))
    {
        std::cout << fw << std::endl;
    }

    std::cout << "Done." << std::endl;

    return 0;
}