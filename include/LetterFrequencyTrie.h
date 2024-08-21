#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#ifdef WIN32
#ifdef CXX_LIB
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif
#else
#define DLLEXPORT
#endif

class Node;

class LetterFrequencyTrie
{
    private:
    typedef std::pair<std::string, uint32_t> word_score_t;

    public:
    DLLEXPORT LetterFrequencyTrie();
    DLLEXPORT ~LetterFrequencyTrie();

    // Give the path to a file containing a large body of text from which to generate a dictionary
    DLLEXPORT void ParseFile(const std::string& fname);

    // Give the groups of letters you that may constitute the 1st, 2nd, ..nth letters of the word as a vector of strings
    // Predictions will be returned as a list of strings ordered from strongest to weakest match
    DLLEXPORT std::vector<std::string> Predict(const char* letterGroups);
    DLLEXPORT std::vector<std::string> Predict(const std::vector<std::string>& letterGroups);
    DLLEXPORT std::vector<std::string> PredictNextWord(const std::string& word);
    
    private:
    Node* getNodeFromWord(const std::string& word);
    void splitAndCleanString(const std::string& line, std::vector<std::string>& tokens);
    std::vector<word_score_t> predict_(const std::vector<std::string>& letterGroups, Node* currentNode = nullptr);

    private:
    Node* head_;
};