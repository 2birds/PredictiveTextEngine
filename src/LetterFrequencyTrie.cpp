#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

#include "include/Node.h"
#include "include/LetterFrequencyTrie.h"

LetterFrequencyTrie::LetterFrequencyTrie()
{
    head_ = new Node();
}

LetterFrequencyTrie::~LetterFrequencyTrie()
{
    delete head_;
}

void LetterFrequencyTrie::splitAndCleanString(const std::string &line, std::vector<std::string> &tokens)
{
    std::stringstream ss;

    for (int i = 0; i < line.size(); i++)
    {
        char c = line.at(i);

        if (c < 'a')
        {
            c += 32;
        }

        if (c >= 'a' && c <= 'z')
        {
            ss << c;
        }
        else
        {
            tokens.push_back(ss.str());
            ss.str("");
            ss.clear();
        }
    }

    ss.seekg(0, std::ios::end);
    if (ss.tellg())
    {
        tokens.push_back(ss.str());
    }
}

void LetterFrequencyTrie::ParseFile(const std::string &fname)
{
    Node* lastNode = nullptr;
    Node* currentNode = nullptr;

    std::ifstream inputFile;
    inputFile.open(fname);

    if (!inputFile.is_open())
    {
        std::cout << "Couldn't open file! Quitting." << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::vector<std::string> tokens;
        splitAndCleanString(line, tokens);
        for (auto t : tokens)
        {
            currentNode = head_->AddChildren(t);
            if (lastNode != nullptr && currentNode != nullptr)
            {
                lastNode->AddFollower(currentNode);
            }

            if (currentNode != nullptr)
            {
                lastNode = currentNode;
            }
        }
    };

    std::cout << "Terminus count: " << head_->getTermini() << std::endl;
    std::cout << "Done" << std::endl;
}

std::vector<std::string> LetterFrequencyTrie::Predict(const char* letterGroups)
{
    std::vector<std::string> groups;
    splitAndCleanString(letterGroups, groups);
    return Predict(groups);
}

std::vector<std::string> LetterFrequencyTrie::Predict(const std::vector<std::string> &letterGroups)
{
    std::vector<word_score_t> predictions = predict_(letterGroups);
    std::sort(predictions.begin(),
              predictions.end(),
              [](word_score_t w1, word_score_t w2)
              { return w1.second > w2.second; });

    std::vector<std::string> results;
    for (auto w : predictions)
    {
        results.push_back(w.first);
    }

    return results;
}

std::vector<LetterFrequencyTrie::word_score_t> LetterFrequencyTrie::predict_(const std::vector<std::string> &letterGroups, Node *currentNode)
{
    if (currentNode == nullptr)
    {
        currentNode = head_;
    }

    std::vector<word_score_t> results;
    std::vector<Node *> nodes;

    // Get letters which appear at this depth in the tree
    for (int i = 0; i < letterGroups.at(0).size(); i++)
    {
        Node *n = (currentNode->GetChild(letterGroups.at(0).at(i)));
        if (n != nullptr)
        {
            nodes.push_back(currentNode->GetChild(letterGroups.at(0).at(i)));
        }
    }

    // // Sort here so results are ordered by most likely
    // std::sort(nodes.begin(),
    //           nodes.end(),
    //          [](Node* n1, Node* n2) { return n2->GetCount() < n1->GetCount(); });

    // From most to least likely words, get children or add to results
    for (auto n : nodes)
    {
        if (letterGroups.size() == 1)
        {
            results.push_back(std::make_pair(std::string(1, n->GetCharacter()), n->GetCount()));
        }
        else
        {
            for (auto res : predict_(std::vector<std::string>(letterGroups.begin() + 1, letterGroups.end()), n))
            {
                std::stringstream parts;
                parts << n->GetCharacter() << res.first;
                results.push_back(std::make_pair(parts.str(), res.second));
            }
        }
    }

    return results;
}

Node* LetterFrequencyTrie::getNodeFromWord(const std::string &word)
{
    Node * current = head_;
    for (int i = 0; i < word.size(); i++)
    {
        current = current->GetChild(word.at(i));
        if (current == nullptr)
        {
            break;
        }
    }

    return current;
}

std::vector<std::string> LetterFrequencyTrie::PredictNextWord(const std::string& word)
{
    Node* n = getNodeFromWord(word);
    if (n != nullptr)
    {
        return n->GetFollowers();
    }
    else
    {
        std::cout << "Node not found" << std::endl;
        return std::vector<std::string>();
    }
}