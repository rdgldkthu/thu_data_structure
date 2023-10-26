#include <iostream>
using namespace std;

//单项列表结构体
struct ListNode {
    int data;
    ListNode* succ;
    ListNode(int x) : data(x), succ(nullptr) {}
};

ListNode* getKthFromEnd(ListNode* head, int k) {
    ListNode* slow = head;
    ListNode* fast = head;

    // 将fast指针移动到第k个节点
    for (int i = 0; i < k; ++i) {
        if (fast == nullptr) {
            cerr << "Invalid input: k is larger than the list size." << endl;
            return nullptr;
        }
        fast = fast->succ;
    }

    // 同时移动slow和fast指针，直到fast指针到达列表尾
    while (fast != nullptr) {
        slow = slow->succ;
        fast = fast->succ;
    }

    // 此时slow指向倒数第k个节点
    return slow;
}

void deleteKthFromEnd(ListNode* head, int k) {
    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* prev = nullptr;

    // 将fast指针移动到第k个节点
    for (int i = 0; i < k; ++i) {
        if (fast == nullptr) {
            cerr << "Invalid input: k is larger than the list size." << endl;
            return;
        }
        fast = fast->succ;
    }

    // 同时移动slow和fast指针，直到fast指针到达列表尾（prev指针保存slow的前一个节点）
    while (fast != nullptr) {
        prev = slow;
        slow = slow->succ;
        fast = fast->succ;
    }

    // 删除倒数第k个节点
    if (prev == nullptr) {
        // 如果prev为空，说明要删除的是头节点
        head = slow->succ;
    }
    else {
        prev->succ = slow->succ;
    }

    // 释放内存
    delete slow;
}

int main() {
    //-------------getKthFromEnd
    cout << "-----getKthFromEnd-----" << endl;
    // 示例用法
    ListNode* head = new ListNode(1);
    head->succ = new ListNode(2);
    head->succ->succ = new ListNode(3);
    head->succ->succ->succ = new ListNode(4);
    head->succ->succ->succ->succ = new ListNode(5);

    int k = 2;
    ListNode* result = getKthFromEnd(head, k);
    if (result != nullptr) {
        cout << "倒数第 " << k << " 个节点的值为：" << result->data << endl;
    }

    // 释放内存
    delete head->succ->succ->succ->succ;
    delete head->succ->succ->succ;
    delete head->succ->succ;
    delete head->succ;
    delete head;

    //-------------deleteKthFromEnd
    cout << "-----deleteKthFromEnd-----" << endl;
    // 示例用法
    ListNode* head2 = new ListNode(1);
    head2->succ = new ListNode(2);
    head2->succ->succ = new ListNode(3);
    head2->succ->succ->succ = new ListNode(4);
    head2->succ->succ->succ->succ = new ListNode(5);

    k = 2;
    deleteKthFromEnd(head2, k);

    // 打印删除节点后的列表
    ListNode* current = head2;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->succ;
    }
    cout << endl;

    // 释放内存
    delete head2->succ->succ->succ->succ;
    delete head2->succ->succ->succ;
    delete head2->succ->succ;
    delete head2->succ;
    delete head2;

    return 0;
}
