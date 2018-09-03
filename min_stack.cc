#include <iostream>
#include <vector>

using namespace std;

class MinStack {
private:
  vector<int> d;
  vector<int> ms;
public:
  /** initialize your data structure here. */
  MinStack() {
  }

  void push(int x) {
    if(ms.empty() || x <= ms.back()) {
      cout << "push ms: " << x << endl;
      ms.push_back(x);
    }
    cout << "Push: " << x << endl;
    d.push_back(x);
  }

  void pop() {
    if(is_empty()) return;
    if(!ms.empty() &&
       top() == ms.back()) {
      cout << "Pop ms: " << ms.back() << endl;
      ms.pop_back();
    }
    cout << "Pop: " << top() << endl;
    d.pop_back();
  }

  int top() {
    if(is_empty()) return -1;

    return d.back();
  }

  int getMin() {
    if(ms.empty()) return -1;

    return ms.back();
  }

  bool is_empty() {
    return d.empty();
  }
};

void test_minstack() {
  MinStack ms = MinStack();

  ms.push(0);
  ms.push(1);
  ms.push(0);
  cout << "Top: " << ms.top() << endl;
  cout << "Min: " << ms.getMin() << endl;
  ms.pop();
  cout << "Top: " << ms.top() << endl;
  cout << "Min: " << ms.getMin() << endl;
}

int main(int argc, char *argv[])
{
  test_minstack();
  return 0;
}
