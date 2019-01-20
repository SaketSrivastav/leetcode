#include <iostream>

using namespace std;

class ListNode {
public:
  int d;
  struct ListNode *next;

  ListNode() { d = -1; next = nullptr; }
  ListNode(int val) { d = val; next = nullptr; }
};

class MyLinkedList {
  ListNode *root;
  ListNode *tail;
  int num_nodes;
public:
  /** Initialize your data structure here. */
  MyLinkedList() {
    root = nullptr;
    tail = nullptr;
    num_nodes = 0;
  }

  ListNode * getRoot() {
    return root;
  }
  /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
  int get(int index) {
    ListNode *tmp = nullptr;
    int i = 0;
    tmp = root;
    while(tmp != nullptr) {
      if(i == index)
        return tmp->d;

      tmp = tmp->next;
      i++;
    }

    return -1;
  }

  /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
  void addAtHead(int val) {
    ListNode *tmp = nullptr;

    // If this is first element
    if(root == nullptr) {
      root = new ListNode(val);
      tail = root;
      num_nodes++;
      return;
    }

    tmp = new ListNode(val);
    tmp->next = root;
    root = tmp;
    num_nodes++;
  }

  /** Append a node of value val to the last element of the linked list. */
  void addAtTail(int val) {
    ListNode *tmp = nullptr;

    // If this is first element
    if(root == nullptr) {
      root = new ListNode(val);
      tail = root;
      num_nodes++;
      return;
    }

    tmp = new ListNode(val);
    tail->next = tmp;
    tail = tmp;
    num_nodes++;
  }

  /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
  void addAtIndex(int index, int val) {
    ListNode *tmp = nullptr;
    ListNode *prev = nullptr;
    int i = 0;

    if(!root && index>0) return;
    if(index > num_nodes) return;

    // If this is first element
    if(index == 0) {
      addAtHead(val);
      return;
    }

    if(index == num_nodes) {
      addAtTail(val);
      return;
    }

    tmp = root;
    while(tmp != nullptr) {
      if(i == index) {
        ListNode *tmp1 = new ListNode(val);
        tmp1->next = tmp;
        prev->next = tmp1;
        num_nodes++;
        break;
      }
      prev = tmp;
      tmp = tmp->next;
      i++;
    }
  }

  /** Delete the index-th node in the linked list, if the index is valid. */
  void deleteAtIndex(int index) {
    ListNode *tmp = root;
    ListNode *prev;
    int i = 0;

    if(!root) return;
    if(index > num_nodes) return;

    while(tmp != nullptr) {
      if(i == index) {
        prev->next = tmp->next;
        cout << "Deleting " << tmp->d << endl;
        delete tmp;
        break;
      }
      prev = tmp;
      tmp = tmp->next;
    }

    return;
  }

  friend ostream & operator<<(ostream & out, MyLinkedList sll) {
    ListNode *tmp = nullptr;

    tmp = sll.getRoot();
    while(tmp != nullptr) {
      cout << tmp->d << " ";
      tmp = tmp->next;
    }
    cout << endl;
    return out;
  }

};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList obj = new MyLinkedList();
 * int param_1 = obj.get(index);
 * obj.addAtHead(val);
 * obj.addAtTail(val);
 * obj.addAtIndex(index,val);
 * obj.deleteAtIndex(index);
 */


void test_slist() {
  MyLinkedList sll = MyLinkedList();
  for (int i = 0; i < 10; ++i) {
    if(i % 2 == 0)
      sll.addAtHead(i);
    else if (i % 3 == 0)
      sll.addAtIndex(i, i-2);
    else
      sll.addAtTail(i);
  }

  cout << sll;
}

int main(int argc, char *argv[])
{
  test_slist();
  return 0;
}
