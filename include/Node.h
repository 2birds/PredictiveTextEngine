#pragma once

#include <stdint.h>

#include <map>
#include <memory>
#include <string>

int terminus_count = 0;

class Node
{
    private:
    typedef std::map<char, Node*> node_map_t;
    typedef std::map<Node*, int> follower_map_t;

    public: 
    int getTermini()
    {
        return terminus_count;
    }

    // Header for 
    Node() :
    parent_(nullptr),
    character_(0),
    count_(0)
    {
        following_.reset(new follower_map_t);
    }

    Node(Node* parent, char c) : 
    parent_(parent),
    character_(c),
    count_(0)
    {
        following_.reset(new follower_map_t);
    }

    ~Node()
    {
        node_map_t::iterator it;
        for (it = children_.begin(); it != children_.end(); it++)
        {
            delete (it->second);
        }
        children_.clear();
    }

    char GetCharacter() const
    {
        return character_;
    }

    std::string GetWord()
    {
        if (GetCount() == 0)
        {
            return "";
        }

        std::stringstream ss;
        Node *current = this;

        while (current->GetParent() != nullptr)
        {
            ss << current->GetCharacter();
            current = current->GetParent();
        }

        std::string reversedWord = ss.str();
        return std::string(reversedWord.rbegin(), reversedWord.rend());
    }

    uint32_t GetCount() const
    {
        return count_;
    }

    void IncrementCount()
    {
        count_++;
    }

    Node* GetParent() const
    {
        return parent_;
    }

    Node* GetChild(const char c) const
    {
        node_map_t::const_iterator it = children_.find(c);

        if (it == children_.end())
        {
            return nullptr;
        }
        return it->second;
    }

    /*
    Node* AddChild(const char c)
    {
        node_map_t::iterator it = children_.find(c);

        Node *n;
        if (it == children_.end())
        {
            n  = children_.insert(std::make_pair(c, new Node(this, c))).first->second;
        }
        else
        {
            n = it->second;
            n->IncrementCount();
        }

        return n;
    }
*/

    // Return terminal node
    Node* AddChildren(const std::string& s)
    {
        if (s.size() == 0)
        {
            return nullptr;
        }

        node_map_t::iterator it = children_.find(s.at(0));

        Node *n;
        if (it == children_.end())
        {
            n  = children_.insert(std::make_pair(s.at(0), new Node(this, s.at(0)))).first->second;
        }
        else
        {
            n = it->second;
        }

        if (s.size() == 1) // Increment if it's the terminal character
        {
            n->IncrementCount();

            if (n->GetCount() == 1)
            {
                terminus_count++;
            }

            return n;
        }
        else
        {
            return n->AddChildren(s.substr(1));
        }
    }

    // Tracking words following other words
    void AddFollower(Node * following)
    {
        if (following == nullptr)
        {
            return;
        }
        follower_map_t::iterator it;
        it = following_->find(following);

        if (it == following_->end())
        {
            following_->insert({following, 1});
        }
        else
        {
            it->second += 1;
        }
    }

    // Return following words in decreasing likelyhood order with the most likely at the front
    std::vector<std::string> GetFollowers()
    {
        // Sets don't admit words if the compare function evaluates the same when you swap the params around.
        // Need to avoid that. All words matter <3
        // Higher count should go first
        // If counts are the same, go on alphabetical first
        // If one is a substring of the other, shortest word first
        auto followerCmp = [](const std::pair<Node*, int> &s1, const std::pair<Node*, int> &s2)
        {
          if (s1.second == s2.second)
          {
            auto word1 = s1.first->GetWord();
            auto word2 = s2.first->GetWord();
            auto wordSize = (word1.size() < word2.size()) ? word1.size() : word2.size();
            for (int i = 0; i < wordSize; i++)
            {
                if (word1.at(i) != word2.at(i))
                {
                    return word1.at(i) < word2.at(i);
                }
            }

            return word1.size() < word2.size();

          }
          return s1.second > s2.second;
        };

        auto sortedPredictions = std::set<std::pair<Node*, int>, decltype(followerCmp)>(followerCmp);

        follower_map_t::iterator it = following_->begin();
        follower_map_t::iterator endit = following_->end();
        for (; it != endit; it++)
        {
            auto res = sortedPredictions.insert(*it);
        }

        std::vector<std::string> followers;

        for (auto w : sortedPredictions)
        {
            followers.push_back(w.first->GetWord());
        }

        return followers;
    }

    private:

    const char character_;
    uint32_t count_;
    Node* parent_;
    node_map_t children_;
    
    // Terminal nodes of words following this one, and the frequency
    std::shared_ptr<follower_map_t> following_;
};
