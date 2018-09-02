#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class MyStack {
private:
  vector<int> d;
public:
  MyStack() {d.resize(5);}
  MyStack(int size) {d.resize(size);}

  void push(int val) {
    d.push_back(val);
  }

  int top() {
    return d.back();
  }

  bool is_empty() {
    return d.empty();
  }

  int pop() {
    int val = -1;
    if(is_empty())
      return -1;

    val = top();
    d.pop_back();
    return val;
  }
};

void test_stack() {
  stack<int> st;

  cout << "testing built in stack" << endl;
  for(int i=0; i<5; i++) {
    cout << "Push " << i << endl;
    st.push(i);
  }

  cout << "top " << st.top() << endl;

  for (int i=0; i < 5; ++i) {
    cout << "Pop " << st.top() << endl;
    st.pop();
  }

}

void test_mystack() {
  MyStack st = MyStack(5);

  cout << "testing my stack" << endl;
  for(int i=0; i<5; i++) {
    cout << "Push " << i << endl;
    st.push(i);
  }

  cout << "top " << st.top() << endl;

  for (int i=0; i < 5; ++i) {
    cout << "Pop " << st.pop() << endl;
  }

}

int main(int argc, char *argv[])
{
  test_mystack();
  test_stack();
  return 0;
}
