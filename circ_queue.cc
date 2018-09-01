#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef enum code{
  OK = 0,
  FULL,
  EMPTY,
  MAX,
} e_code;

void get_error_str(e_code c, string &e_m) {
  switch(c) {
  case OK: e_m = "OK"; break;
  case FULL: e_m = "Queue is full"; break;
  case EMPTY: e_m = "Queue is empty"; break;
  default: e_m = "Invalid error code"; break;
  }
}

class Circ_Queue {
private:
  vector<int> d;
  uint32_t h;
  uint32_t t;
  e_code e;
public:
  Circ_Queue() { h = t = -1 ; e = OK; }
  Circ_Queue(size_t s) { d.resize(s); h = t  = -1; e = OK; }

  friend ostream & operator<< (ostream &out, Circ_Queue cq) {
    out << " (t,h,s) = (" << cq.t << ", " << cq.h << ", " << cq.get_q_size() << ")\n";
    return out;
  }

  int get_q_size() {
    return d.size();
  }

  bool is_empty() {
    return h == -1 ? true : false;
  }

  bool is_full() {
    return ((t+1) % d.size() == h) ? true : false;
  }

  void enqueue(int item) {
    do {
      e = MAX;
      cout << "Enqueue: " << item << endl;
      if(is_full()) { e = FULL ; break; }
      if(is_empty()) { h = 0; }
      t = (t + 1) % d.size();
      d[t] = item;
      e = OK;
    } while(0);

    if(e != OK) {
      string e_msg;
      get_error_str(e, e_msg);
      cout << "Enqueue failed: errcode " << e << " : " << e_msg << endl;
    } else {
      cout << "Enqueued: " << item << endl;
    }
  }

  int deque() {
    int item;
    do {
      e = MAX;
      if(is_empty()) { e = EMPTY; break; }

      if(h == t) { item = d[h]; h = t = -1; e = OK; break; }

      item = d[h];
      h = (h+1) % d.size();
      e = OK;

    }while(0);

    if(e != OK) {
      string e_msg;
      get_error_str(e, e_msg);
      cout << "Dequeue failed: errcode " << e << " : " << e_msg << endl;
    } else {
      cout << "Dequeued: " << item << endl;
    }

    return item;
  }

  int front() {
    int item;
    do {
      e = MAX;
      if(is_empty()) return -1;
      item = d[h];
      e = OK;
    } while(0);

    return item;
  }

  int back() {
    int item;
    do {
      e = MAX;
      if(is_empty()) return -1;
      item = d[t];
      e = OK;
    } while(0);

    return item;
  }

  void print_cqueue() {
    int i = h;
    if(is_empty()) return;
    do{
      cout << d[i] << " ";
      i = (i+1) % d.size();
    }while(i != h);
    cout << endl;
  }
};

int test_circ_queue() {
  Circ_Queue c_q = Circ_Queue(5);

  cout << c_q;

  for(int i = 0; i<6; i++) {
    // cout << c_q;
    c_q.enqueue(i);
  }

  c_q.print_cqueue();

  for(int i = 0; i<6 ; i++) {
    c_q.deque();
    c_q.print_cqueue();
  }

  for(int i = 0; i<6; i++) {
    if(i%2 == 1)
      c_q.enqueue(i+10);
    else
      c_q.deque();
  }

  return 0;
}

int test_built_in_queue()
{
  queue<int> q;

  for(int i = 0; i<6; i++) {
    cout << "Enqueue: " << i << endl;
    q.push(i);
    cout << "back: " << q.back() << endl;
  }

  for(int i = 0; i<6 ; i++) {
    cout << "Dequeue: " << q.front() << endl;
    q.pop();
  }
  return 0;
}

int main(int argc, char *argv[])
{
  test_circ_queue();
  test_built_in_queue();
  return 0;
}
