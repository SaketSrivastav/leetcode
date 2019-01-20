#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

void list_print(ListNode *head) {
  ListNode *tmp = head;

  while(tmp != nullptr) {
    printf("%d -> ", tmp->val);
    tmp = tmp->next;
  }
  printf("null\n");
}

class Solution {
public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int carry = 0, sum;
    ListNode *result = NULL, *tmpNode = NULL, *tL1 = NULL, *tL2 = NULL;

    result = new ListNode(0);
    if(l1 == nullptr && l2 == nullptr) return result;
    if(l1 == nullptr) return l2;
    if(l2 == nullptr) return l1;

    tmpNode = result;
    tL1 = l1;
    tL2 = l2;
    while(tL1 && tL2) {
      sum = tL1->val + tL2->val + carry;
      tmpNode->next = new ListNode(sum % 10);
      carry = sum / 10;
      tL1 = tL1->next;
      tL2 = tL2->next;
      tmpNode = tmpNode->next;
    }

    if(tL1 == nullptr && tL2 != nullptr) {
      while(tL2 != nullptr) {
        sum = tL2->val + carry;
        tmpNode->next = new ListNode(sum % 10);
        carry = sum / 10;
        tL2 = tL2->next;
        tmpNode = tmpNode->next;
      }
    }

    if(tL2 == nullptr && tL1 != nullptr) {
      while(tL1 != nullptr) {
        sum = tL1->val + carry;
        tmpNode->next = new ListNode(sum % 10);
        carry = sum / 10;
        tL1 = tL1->next;
        tmpNode = tmpNode->next;
      }
    }

    if(tL1 == nullptr && tL2 == nullptr && carry > 0) {
      tmpNode->next = new ListNode(carry);
    }

    return result->next;
  }
};

int main(int argc, char *argv[])
{
  ListNode *l1 = NULL, *l2 = NULL, *result = NULL;
  Solution soln;
  l1 = new ListNode(2);
  l1->next = new ListNode(4);
  l1->next->next = new ListNode(3);

  l2 = new ListNode(5);
  l2->next = new ListNode(6);
  l2->next->next = new ListNode(4);
  l2->next->next->next = new ListNode(1);

  printf("l1 = ");
  list_print(l1);

  printf("l2 = ");
  list_print(l2);

  printf("result = ");
  result = soln.addTwoNumbers(l1, l2);
  list_print(result);

  return 0;
}
