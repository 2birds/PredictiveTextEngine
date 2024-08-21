#include "include/LetterFrequencyTrie.h"
#include "include/LetterFrequencyTrieCBindings.h"

#include <memory>
#include <sstream>

LetterFrequencyTrie lft;
char** predictions;
size_t nPredictions = 0;

void cleanup()
{
    if (predictions != nullptr)
    {
        for (int p = 0; p < nPredictions; p++)
        {
            delete predictions[p];
        }

        delete predictions;
    }
}

bool ParseFile(const char *fname)
{
    try
    {
        lft.ParseFile(fname);
        return true;
    }
    catch (std::exception &)
    {
        return false;
    }
}

bool Predict(char * groups, char* results, int* maxResults)
{
    std::vector<std::string> preds = lft.Predict(const_cast<const char*>(groups));
    std::cout << "preds.size(): " << preds.size() << std::endl;

    std::cout << "Dereferencing maxResults: " << std::endl;
    std::cout << *maxResults << std::endl;

    if (preds.size() == 0)
    {
        *maxResults = 0;
        return false;
    }

    std::stringstream ss;

    size_t characters = 0;
    int r = 0;
    while (r < preds.size() && (characters + preds.at(r).size() + 1) < *maxResults)
    {
        std::cout << preds.at(r) << std::endl;
        ss << preds.at(r);
        ss << " ";
        characters += preds.at(r).size() + 1;
        r++;
        std::cout << "r = " << r << std::endl;
    }
    std::cout << "Built results string" << std::endl;

    std::string resultString = ss.str();

    strncpy_s(results, *maxResults, resultString.c_str(), resultString.size());
    std::cout << "Copied results string" << std::endl;

    std::cout << "Assigning null terminator" << std::endl;
    results[resultString.size()-1] = 0;
    std::cout << "Done" << std::endl;
    // std::copy(resultString.begin(), resultString.end(), results);
    std::cout << "Assigning maxResults" << std::endl;
    *maxResults = static_cast<int>(resultString.size());
    std::cout << "Done" << std::endl;

    return true;
}

bool PredictNextWord(char * currentWord, char* results, int* maxResults)
{
    std::vector<std::string> preds = lft.PredictNextWord(const_cast<const char*>(currentWord));
    std::cout << "preds.size(): " << preds.size() << std::endl;

    std::cout << "Dereferencing maxResults: " << std::endl;
    std::cout << *maxResults << std::endl;

    if (preds.size() == 0)
    {
        *maxResults = 0;
        return false;
    }

    std::stringstream ss;

    size_t characters = 0;
    int r = 0;
    while (r < preds.size() && (characters + preds.at(r).size() + 1) < *maxResults)
    {
        std::cout << preds.at(r) << std::endl;
        ss << preds.at(r);
        ss << " ";
        characters += preds.at(r).size() + 1;
        r++;
        std::cout << "r = " << r << std::endl;
    }
    std::cout << "Built results string" << std::endl;

    std::string resultString = ss.str();

    strncpy_s(results, *maxResults, resultString.c_str(), resultString.size());
    std::cout << "Copied results string" << std::endl;

    std::cout << "Assigning null terminator" << std::endl;
    results[resultString.size()-1] = 0;
    std::cout << "Done" << std::endl;
    // std::copy(resultString.begin(), resultString.end(), results);
    std::cout << "Assigning maxResults" << std::endl;
    *maxResults = static_cast<int>(resultString.size());
    std::cout << "Done" << std::endl;

    return true;
}