#include <vector>
#include <iostream>
using namespace std;

class LinkedList {
public:
    int value;
    LinkedList* next;

    LinkedList(int value);
    void addMany(vector<int> values);
    vector<int> getNodesInArray();
};

void removeKthNodeFromEnd(LinkedList* head, int k) {
    int cnt = 0;
	LinkedList *tmp = head, *delNode = head, *delPrev = NULL;
	while(tmp != NULL) {
		if(cnt >= k) {
			delPrev = delNode;
			delNode = delNode->next;
		}
		tmp = tmp->next;
		cnt++;
	}

	// Delete node pointed by delNode
	if(cnt >= k && delPrev) {
		delPrev->next = delNode ? delNode->next : NULL;
		delNode->next = NULL;
		return;
	}

	return;
}
