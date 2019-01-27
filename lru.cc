#include <iostream>
#include<unordered_map>

using namespace std;

class DllNode
{
public:
    int key;
    int value;
    DllNode *next;
    DllNode *prev;

    DllNode(int key, int value)
    {
        this->key = key;
        this->value = value;
        this->prev = NULL;
        this->next = NULL;
    }

    void removeBindings()
    {
        if(this->prev != NULL) {
            this->prev->next = this->next;
        }

        if(this->next != NULL) {
            this->next->prev = this->prev;
        }

        this->prev = NULL;
        this->next = NULL;
    }
};

class DllList
{
public:
    DllNode *head;
    DllNode *tail;

    DllList()
    {
        head = NULL;
        tail = NULL;
    }

    // Delete tail node
    void removeTail()
    {
        if(this->tail == NULL)
            return;

        if(this->tail == this->head) {
            this->head = NULL;
            this->tail = NULL;
            return;
        }

        // Update tail to previous one
        this->tail = this->tail->prev;
        this->tail->next = NULL;
    }

    // Set node to head
    void setToHead(DllNode *node)
    {
        if(this->head == node)
            return;

        // If list is empty
        if(this->head == NULL)
        {
            this->head = node;
            this->tail = node;
        } else if(this->head == this->tail) { // inserting node after first node
            this->tail->prev = node;
            this->head = node;
            this->head->next = tail;
        } else {
            // If last node then just remove it
            if(this->tail == node) {
                this->removeTail();
            }

            node->removeBindings();
            this->head->prev = node;
            node->next = head;
            head = node;
        }
    }
};

class LRU
{
public:
    unordered_map<int, DllNode*> cache;
    int maxSize;
    int currSize;
    DllList recentList;

    LRU(int maxSize) {
        this->maxSize = maxSize > 0 ? maxSize : 1;
        this->currSize = 0;
        recentList = DllList();
    }

    void replaceKey(int key, int value)
    {
        if(this->cache.find(key) == this->cache.end())
            return;

        this->cache[key]->value = value;
    }

    void updateMostRecent(DllNode *node)
    {
        if(node == NULL) {
            cout << "Error: cannot update NULL node" << endl;
            return;
        }

        this->recentList.setToHead(node);
    }

    void evictLeastRecent() {
        int rkey = this->recentList.tail->key;
        cout << "Evicting: " << rkey << endl;
        this->recentList.removeTail();
        this->cache.erase(rkey);
    }

    void insert(int key, int value)
    {
        // Key not found
        if(this->cache.find(key) == this->cache.end()) {
            if(this->maxSize == this->currSize) {
                this->evictLeastRecent();
            } else {
                this->currSize++;
            }

            this->cache[key] = new DllNode(key, value);
        } else {
            this->replaceKey(key, value);
        }

        this->updateMostRecent(this->cache[key]);
    }

    int getMostRecentKey()
    {
        return this->recentList.head->key;
    }

    int getValueFromKey(int key) {
        if(this->cache.find(key) == this->cache.end())
            return -1;

        // Very important line
        this->updateMostRecent(this->cache[key]);
        return this->cache[key]->value;
    }
};

int main(int argc, char *argv[])
{
    LRU * cache = new LRU(5);

    srand(time(NULL));

    for(int i=0; i<10; i++)
    {
        int num = rand() % 10;
        int value = rand() % 100;
        cout << "Insert " << num << ", " << value << endl;
        cache->insert(num, value);
        cout << "Most recent: " << cache->getMostRecentKey() << endl;
    }

    return 0;
}
