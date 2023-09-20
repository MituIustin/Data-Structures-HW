#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include <chrono>


struct ListNode {
    std::string key;
    int value;
    ListNode* next;

    ListNode(const std::string& k, int v) : key(k), value(v), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;

public:
    LinkedList() : head(nullptr) {}

    void insert(const std::string& key, int value) {
        ListNode* newNode = new ListNode(key, value);

        if (head == nullptr || key < head->key) {
            newNode->next = head;
            head = newNode;
        } else {
            ListNode* curr = head;
            while (curr->next && key > curr->next->key) {
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
    }

    void remove(const std::string& key) {
        if (head == nullptr)
            return;

        if (head->key == key) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        ListNode* curr = head;
        while (curr->next) {
            if (curr->next->key == key) {
                ListNode* temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
                return;
            }
            curr = curr->next;
        }
    }

    void printAll() {
        ListNode* curr = head;
        while (curr) {
            std::cout << "Key: " << curr->key << ", Value: " << curr->value << std::endl;
            curr = curr->next;
        }
    }

    bool search(const std::string& key) {
        ListNode* curr = head;
        while (curr) {
            if (curr->key == key) {
                return true; 
            }
            curr = curr->next;
        }
        return false; 
    }
};


struct SkipListNode {
    std::string key;
    int value;
    std::vector<SkipListNode*> next;

    SkipListNode(const std::string& k, int v, int levels) : key(k), value(v), next(levels, nullptr) {}
};

class SkipList {
private:
    int maxLevels;
    int currentLevels;
    SkipListNode* head;

    int randomLevels() {
        int levels = 1;
        while ((std::rand() % 2) && levels < maxLevels)
            levels++;
        return levels;
    }

public:
    SkipList(int levels) : maxLevels(levels), currentLevels(1), head(nullptr) {
        std::srand(std::time(nullptr));
        head = new SkipListNode("", 0, maxLevels);
    }

    void insert(const std::string& key, int value) {
        int levels = randomLevels();
        SkipListNode* newNode = new SkipListNode(key, value, levels);

        std::vector<SkipListNode*> update(maxLevels, nullptr);
        SkipListNode* curr = head;

        for (int i = currentLevels - 1; i >= 0; i--) {
            while (curr->next[i] && curr->next[i]->key.compare(key) < 0) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }

        curr = curr->next[0];

        if (curr && curr->key == key) {
            curr->value = value;
            delete newNode;
            return;
        }

        if (levels > currentLevels) {
            for (int i = currentLevels; i < levels; i++) {
                update[i] = head;
            }
            currentLevels = levels;
        }

        for (int i = 0; i < levels; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }



    void remove(const std::string& key) {
        std::vector<SkipListNode*> update(maxLevels, nullptr);
        SkipListNode* curr = head;

        for (int i = currentLevels - 1; i >= 0; i--) {
            while (curr->next[i] && curr->next[i]->key < key) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }

        if (curr->next[0] && curr->next[0]->key == key) {
            SkipListNode* toRemove = curr->next[0];
            for (int i = 0; i < currentLevels; i++) {
                if (update[i]->next[i] != toRemove)
                    break;
                update[i]->next[i] = toRemove->next[i];
            }

            delete toRemove;

            while (currentLevels > 1 && head->next[currentLevels - 1] == nullptr) {
                currentLevels--;
            }
        }
    }

    void printAll() {
        SkipListNode* curr = head->next[0];
        while (curr) {
            std::cout << "Key: " << curr->key << ", Value: " << curr->value << std::endl;
            curr = curr->next[0];
        }
    }

    bool search(const std::string& key) {
        SkipListNode* curr = head;
        for (int i = currentLevels - 1; i >= 0; i--) {
            while (curr->next[i] && curr->next[i]->key < key) {
                curr = curr->next[i];
            }
        }

        curr = curr->next[0];

        if (curr && curr->key == key) {
            return true; 
        }
        
        return false; 
    }
};

void insert_linked_list(LinkedList & list)
{

    auto start = std::chrono::high_resolution_clock::now();

    std::string nume;
    int nr;

    std::ifstream fin("names.txt");
    std::ifstream gin("numbers.txt");

    for(int i=1; i<=1000; i++)
    {
        fin>>nume;
        gin>>nr;
        list.insert(nume, nr);
    }

    fin.close();
    gin.close();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution time (insert linked list): " << duration.count() << " milliseconds" << std::endl;

}

void insert_skip_list(SkipList & list)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::string nume;
    int nr;

    std::ifstream fin("names.txt");
    std::ifstream gin("numbers.txt");

    for(int i=1; i<=1000; i++)
    {
        fin>>nume;
        gin>>nr;
        list.insert(nume, nr);
    }

    fin.close();
    gin.close();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution time (insert skip list): " << duration.count() << " milliseconds" << std::endl;

}

void search_linked_list(LinkedList & list)
{

    auto start = std::chrono::high_resolution_clock::now();

    std::string nume;
    int nr;

    std::ifstream fin("names.txt");
    std::ifstream gin("numbers.txt");

    for(int i=1; i<=1000; i++)
    {
        fin>>nume;
        bool ok = list.search(nume);
    }

    fin.close();
    gin.close();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution time (search linked list): " << duration.count() << " milliseconds" << std::endl;

}

void search_skip_list(SkipList & list)
{

    auto start = std::chrono::high_resolution_clock::now();

    std::string nume;
    int nr;

    std::ifstream fin("names.txt");
    std::ifstream gin("numbers.txt");

    for(int i=1; i<=1000; i++)
    {
        fin>>nume;
        bool ok = list.search(nume);
    }

    fin.close();
    gin.close();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution time (search skip list): " << duration.count() << " milliseconds" << std::endl;

}

void remove_linked_list(LinkedList & list)
{

    auto start = std::chrono::high_resolution_clock::now();

    std::string nume;
    int nr;

    std::ifstream fin("names.txt");
    std::ifstream gin("numbers.txt");

    for(int i=1; i<=1000; i++)
    {
        fin>>nume;
        list.remove(nume);
    }

    fin.close();
    gin.close();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution time (remove linked list): " << duration.count() << " milliseconds" << std::endl;

}

void remove_skip_list(SkipList & list)
{

    auto start = std::chrono::high_resolution_clock::now();

    std::string nume;
    int nr;

    std::ifstream fin("names.txt");
    std::ifstream gin("numbers.txt");

    for(int i=1; i<=1000; i++)
    {
        fin>>nume;
        list.remove(nume);
    }

    fin.close();
    gin.close();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution time (remove skip list): " << duration.count() << " milliseconds" << std::endl;

}

int main()
{
    LinkedList list1;
    SkipList list2(10);


    insert_linked_list(list1);
    insert_skip_list(list2);

    search_linked_list(list1);
    search_skip_list(list2);
    
    remove_linked_list(list1);
    remove_skip_list(list2);

    list1.printAll();
    list2.printAll();

}

