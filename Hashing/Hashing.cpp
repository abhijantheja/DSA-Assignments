#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <math.h>
using namespace std;
class PhoneRecord
{
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string &n, const string &org, const vector<string> &numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}
    // Getter methods
    string getName() const
    {
        return name;
    }
    string getOrganisation() const
    {
        return organisation;
    }
    vector<string> getPhoneNumbers() const
    {
        return phoneNumbers;
    }
};
class HashTableRecord
{
private:
    int key;
    PhoneRecord *element; // Pointer to PhoneRecord
    HashTableRecord *next;
public:
    // Constructor
    HashTableRecord(int k, PhoneRecord *rec)
        : key(k), element(rec), next(nullptr) {}

    // Getter methods
    int getKey() const
    {
        return key;
    }

    PhoneRecord *getRecord() const
    {
        return element;
    }

    HashTableRecord *getNext() const
    {
        return next;
    }

    void setNext(HashTableRecord *nxt)
    {
        next = nxt;
    }
};
vector<string> phonedata;
vector<string> phnum;
vector<string> subpart;
class PhoneBook
{
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord *hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook()
    {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i)
        {
            hashTable[i] = nullptr;
        }
    }
    // Add your own implementation for hashing
    long long computeHash(const string &str)
    {
        string s = str;
        int x = 263, m = 263;
        long long p = 1000000007, sum = 0;
        ;
        for (int i = 0; i < s.size(); i++)
        {
            long long temp, temp1, temp2;
            temp = pow(x, i);
            temp1 = temp % p;
            temp2 = s[i] * temp1;
            sum += temp2;
        }
        long long hashvalue = sum % m;
        return hashvalue;
    }
    // Add your own implementation for adding a contact
    void addContact(PhoneRecord *record)
    {
        string name;
        string sub;
        int key;
        HashTableRecord *next;
        next = NULL;
        name = record->getName();
        for (int j = 0; j <= record->getName().size(); j++)
        {
            if (name[j] != ' ' && name[j] != '\0')
            {
                sub += name[j];
            }
            else
            {
                key = computeHash(sub);
                HashTableRecord *new_node = new HashTableRecord(key, record);
                if (hashTable[key] == nullptr)
                {
                    hashTable[key] = new_node;
                    hashTable[key]->setNext(nullptr);
                }
                else
                {
                    HashTableRecord *temp = hashTable[key];
                    while (temp->getNext() != nullptr)
                    {
                        temp = temp->getNext();
                    }
                    temp->setNext(new_node);
                }

                sub.clear();
            }
        }
    }
    // Add your own implementation for deleting a contact
    bool deleteContact(const string *searchName)
    { 
        PhoneRecord *deleted = fetchContacts(searchName)[0];
        string element = deleted->getName();
        string sub;
        int key;
        int count = 0, count1 = 0;
        for (int i = 0; i <= deleted->getName().size(); i++)
        {
            
            if (element[i] != ' ' && element[i] != '\0')
            {
                sub += element[i];
            }
            else
            {
                count1++;
                key = computeHash(sub);
                if (hashTable[key]->getRecord()->getName() == deleted->getName())
                {
                    HashTableRecord *tobedeleted = hashTable[key];
                    hashTable[key] = hashTable[key]->getNext();
                    delete tobedeleted;
                    count++;
                    sub.clear();
                }
                else
                {
                    HashTableRecord *temp = hashTable[key];
                    while ((temp != nullptr) && (temp->getNext()->getRecord()->getName() != deleted->getName()))
                    {
                        temp = temp->getNext();
                        
                    }     
                    HashTableRecord *tobedeleted = temp->getNext();
                    temp->setNext(tobedeleted->getNext());
                    delete tobedeleted;
                    count++;
                      
                    sub.clear();
                     
                }
            }
        }
        if (count == count1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // Add your own implementation for fetching contacts
    vector<PhoneRecord *> fetchContacts(const string *query)
    {
        string sub;
        string s = *query;
        vector<string> name;
        vector<PhoneRecord *> rec;
        for (int j = 0; j <= s.size(); j++)
        {
            if (s[j] != ' ' && s[j] != '\0')
            {
                sub += s[j];
            }
            else
            {
                name.push_back(sub);
                sub.clear();
            }
        }
        for (int j = 0; j < name.size(); j++)
        {
            int key = computeHash(name[j]);
            HashTableRecord *temp = hashTable[key];
            while (temp != NULL)
            {
                rec.push_back(temp->getRecord());
                temp = temp->getNext();
            }
        }
        vector<pair<PhoneRecord *, int>> newrec;
        for (auto i : rec)
        {
            int p = 1;
            for (int j = 0; j < newrec.size(); j++)
            {
                if (newrec[j].first->getName() == i->getName())
                {
                    p = 0;
                    newrec[j].second++;
                    break;
                }
            }
            if (p == 1)
            {
                newrec.emplace_back(i, 1);
            }
        }    
        sort(newrec.begin(), newrec.end(), [](pair<PhoneRecord *, int> &a, pair<PhoneRecord *, int> &b)
             { return a.second > b.second; });  
        vector<PhoneRecord *> result;
        for (const auto &pair : newrec)
        {
            PhoneRecord *ph = pair.first;
            for(int j=0;j<name.size();j++)
            {
               
                if(ph->getName().find(name[j])!=string::npos)
                {
                     
                    result.emplace_back(ph);
                    break;
                }
            }   
            
        }   
        return result;
    }
    // Add your own implementation for counting records pointing to a contact
    int countRecordsPointingTo(const PhoneRecord *record) const
    {
        string element;
        string sub;
        int count1 = 0;
        element = record->getName();
        for (int i = 0; i <= record->getName().size(); i++)
        {
            if (element[i] != ' ' && element[i] != '\0')
            {
                sub += element[i];
            }
            else
            {
                count1++;
            }
        }
        return count1;
    }
     // Add your own implementation for reading records from a file
    void readRecordsFromFile(const string &filename)
    {
        string line;
        string element;
        ifstream file(filename);
        stringstream buffer;
        if (file.is_open())
        {
            buffer << file.rdbuf();
            file.close();
            element = buffer.str();
        }
        istringstream stream(element);
        while (getline(stream, line, '\n'))
        {
            phonedata.push_back(line);
        }
        for (int i = 0; i < phonedata.size(); i++)
        {
            istringstream stream(phonedata[i]);
            string element;
            string name;
            string organisation;
            int itr = 1;
            while (getline(stream, element, ','))
            {
                if (itr == 1)
                {
                    name = element;
                    itr++;
                }
                else if (itr == 2)
                {
                    phnum.push_back(element);
                    itr++;
                }
                else if (itr >= 3)
                {
                    if (element[0] >= '0' && element[0] <= '9')
                    {

                        phnum.push_back(element);
                        itr++;
                    }
                    else
                    {
                        organisation = element;
                        PhoneRecord *record = new PhoneRecord(name, organisation, phnum);
                        addContact(record);
                        phnum.clear();
                    }
                }
            }
        }
    }
};
