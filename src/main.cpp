#include <bits/stdc++.h>
using namespace std;

struct Node {
    unsigned long long val;
    Node* next;
    Node(unsigned long long v): val(v), next(nullptr) {}
};

class LinkedQueue {
    Node* head;
    Node* tail;
    size_t sz;
public:
    LinkedQueue(): head(nullptr), tail(nullptr), sz(0) {}
    ~LinkedQueue() {
        while (head) {
            Node* t = head->next;
            delete head;
            head = t;
        }
        tail = nullptr;
        sz = 0;
    }
    void push(unsigned long long v) {
        Node* n = new Node(v);
        if (!tail) { head = tail = n; }
        else { tail->next = n; tail = n; }
        ++sz;
    }
    bool empty() const { return sz == 0; }
    size_t size() const { return sz; }
    unsigned long long front() const { return head->val; }
    void pop() {
        if (!head) return;
        Node* n = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete n;
        --sz;
    }
    void rotate_front_to_back() {
        if (sz <= 1) return;
        Node* n = head;
        head = head->next;
        n->next = nullptr;
        tail->next = n;
        tail = n;
    }
};

static unsigned long long highest_power_of_two_leq(unsigned long long n){
    if (n == 0) return 0;
#if defined(__GNUG__) || defined(__clang__)
    int lz = __builtin_clzll(n);
    int idx = 63 - lz;
    return 1ULL << idx;
#else
    unsigned long long p = 1;
    while ((p << 1) && (p << 1) <= n) p <<= 1;
    return p;
#endif
}

static unsigned long long last_card(unsigned long long n){
    if (n == 0) return 0;
    unsigned long long p = highest_power_of_two_leq(n);
    return 2ULL * (n - p) + 1ULL;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long id, n;
    if (!(cin >> id >> n)) return 0;

    if (id == 1ULL) {
        LinkedQueue q;
        for (unsigned long long i = 1; i <= n; ++i) q.push(i);
        unsigned long long rounds = (n > 0 ? n - 1 : 0);
        for (unsigned long long r = 0; r < rounds; ++r) {
            q.rotate_front_to_back();
            if (!q.empty()) q.pop();
            if (!q.empty()) cout << q.front() << '\n';
        }
    } else if (id == 2ULL) {
        cout << last_card(n) << '\n';
    }
    return 0;
}
