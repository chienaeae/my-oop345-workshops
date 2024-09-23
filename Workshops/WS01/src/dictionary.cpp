#include "dictionary.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include "settings.h"

using namespace std;

namespace seneca
{
    Dictionary::Dictionary() : m_words(nullptr), m_capacity(0), m_size(0) {}

    Dictionary::Dictionary(const char *filename) : m_words(nullptr), m_capacity(0), m_size(0)
    {
        m_capacity = readWordsNumber(filename);

        ifstream fs(filename);
        if (m_capacity == 0 || !fs.is_open())
        {
            return;
        }

        m_words = new Word[m_capacity];

        string line;
        while (getline(fs, line))
        {

            // word,pos,definition
            size_t p1 = line.find(',');
            string word = line.substr(0, p1);

            size_t p2 = line.find(',', p1 + 1);
            string posStr = line.substr(p1 + 1, p2 - p1 - 1);

            string definition = line.substr(p2 + 1);

            m_words[m_size].m_word = word;
            m_words[m_size].m_definition = definition;
            m_words[m_size].m_pos = getPartOfSpeech(posStr);
            m_size++;
        }
    }

    Dictionary::Dictionary(const Dictionary &other) : m_words(nullptr), m_capacity(0), m_size(0)
    {
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        if (m_capacity != 0)
        {
            m_words = new Word[m_capacity];

            for (int i = 0; i < m_size; ++i)
            {
                m_words[i] = other.m_words[i];
            }
        }
    }

    Dictionary &Dictionary::operator=(const Dictionary &other)
    {
        if (this != &other)
        {
            delete[] m_words;
            m_capacity = other.m_capacity;
            m_size = other.m_size;
            m_words = nullptr;
            if (m_capacity != 0)
            {
                m_words = new Word[m_capacity];

                for (int i = 0; i < m_size; ++i)
                {
                    m_words[i] = other.m_words[i];
                }
            }
        }

        return *this;
    }

    Dictionary::Dictionary(Dictionary &&other) noexcept : m_words(nullptr), m_capacity(0), m_size(0)
    {
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_words = other.m_words;

        other.m_capacity = 0;
        other.m_size = 0;
        other.m_words = nullptr;
    }

    Dictionary &Dictionary::operator=(Dictionary &&other) noexcept
    {
        if (this != &other)
        {
            delete[] m_words;
            m_capacity = other.m_capacity;
            m_size = other.m_size;
            m_words = other.m_words;

            other.m_capacity = 0;
            other.m_size = 0;
            other.m_words = nullptr;
        }

        return *this;
    }

    Dictionary::~Dictionary()
    {
        delete[] m_words;
    }

    int Dictionary::readWordsNumber(const char *filename)
    {
        ifstream fs(filename);
        if (!fs.is_open())
        {
            return 0;
        }

        int wordsNumber = 0;
        string line;
        while (getline(fs, line))
        {
            ++wordsNumber;
        }

        return wordsNumber;
    }

    void Dictionary::searchWord(const char *word)
    {
        bool found = false;
        for (int i = 0; i < m_size; ++i)
        {
            if (m_words[i].m_word == word)
            {
                if (!found)
                {
                    cout << m_words[i].m_word << " -";
                    found = true;
                }
                else
                {
                    cout << setw(m_words[i].m_word.size() + 2) << setfill(' ') << " -";
                }

                if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown)
                {
                    cout << " (" << toString(m_words[i].m_pos) << ")";
                }

                cout << " " << m_words[i].m_definition << endl;

                if (!g_settings.m_show_all)
                {
                    return;
                }
            }
        }

        if (!found)
        {
            cout << "Word '" << word << "' was not found in the dictionary." << endl;
        }
    }

}