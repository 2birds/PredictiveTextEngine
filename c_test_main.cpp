#include "include/LetterFrequencyTrieCBindings.h"

#include <iostream>

int main(int argc, const char**argv)
{
    if (argc < 3)
    {
        std::cout << "Not enough arguments. Give training data file then letter groups." << std::endl;
    }

    std::cout << "Parsing training data..";
    if (!ParseFile(argv[1]))
    {
        std::cout << "Failed to parse file. Quitting." << std::endl;
    }
    std::cout << "done." << std::endl;

    std::cout << "Predicting..";

    // Inputs to "predict"
    int maxResults = 100;
    char * groups = new char[100];
    char * results = new char[maxResults];

    // Marshall the groups into a space-separated string
    std::stringstream ss;
    for (int a = 2; a < argc; a++)
    {
        ss << *(argv + a) << " ";
    }
    strncpy_s(groups, 100, ss.str().c_str(), 100);

    Predict(groups, results, &maxResults);

    std::cout << "done." << std::endl;
    std::cout << "Got " << maxResults << " predictions:" << std::endl;
    std::cout << "Predictions: " << std::endl;

    std::cout << results << std::endl;

    int i = 0;
    while (i < maxResults && results[i] != ' ')
    {
        i++;
    }

    memset(groups, 0, 100);

    strncpy_s(groups, 100, (const char *)results, i);

    maxResults = 100;
    // Reusing arrays, why not
    PredictNextWord(groups, results, &maxResults);
    std::cout << "Words predicted to follow first prediction: " << std::endl;
    std::cout << results << std::endl;

    return 0;
}