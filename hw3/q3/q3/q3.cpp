#include <iostream>
using namespace std;

//单项列表结构体
struct ListNode {
    int data;
    ListNode* succ;
    ListNode(int x) : data(x), succ(nullptr) {}
};

//接受两个列表的头节点作为输入参数，查找并返回这两个列表的第一个公共节点
ListNode* getIntersectionNode(ListNode* head1, ListNode* head2) {
    int len1 = 0; //第一个列表的长度
    int len2 = 0; //第二个列表的长度
    ListNode* current1 = head1; //第一个列表中的当前节点
    ListNode* current2 = head2; //第二个列表中的当前节点

    //计算列表长度 O(n)
    while (current1 != nullptr) {
        len1++;
        current1 = current1->succ;
    }
    while (current2 != nullptr) {
        len2++;
        current2 = current2->succ;
    }

    //重置列表指针起点 O(n)
    current1 = head1;
    current2 = head2;
    if (len1 > len2) {
        for (int i = 0; i < len1 - len2; i++) {
            current1 = current1->succ;
        }
    }
    else {
        for (int i = 0; i < len2 - len1; i++) {
            current2 = current2->succ;
        }
    }

    //同时移动两个指针，直到相遇 O(n)
    while (current1 != nullptr && current2 != nullptr) {
        if (current1 == current2) {
            return current1; //返回第一个公共节点
        }
        current1 = current1->succ;
        current2 = current2->succ;
    }

    //若没有公共节点，则返回nullptr O(1)
    return nullptr;
}

int main()
{
    return 0;
}
