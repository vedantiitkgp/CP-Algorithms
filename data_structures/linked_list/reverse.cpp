#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr){};
    ListNode(int x) : val(x), next(nullptr){};
    ListNode(int x, ListNode *next) : val(x), next(next){};
};

ListNode *reverse_list(ListNode *head, int left, int right)
{
    if (left >= right || head == NULL)
    {
        return head;
    }

    ListNode *dummy = new ListNode();
    dummy->next = head;
    ListNode *prev = dummy;
    ListNode *curr;

    for (int i = 1; i < left; i++)
    {
        prev = prev->next;
    }

    curr = prev->next;

    for (int i = left; i < right; i++)
    {
        ListNode *temp = prev->next;
        prev->next = curr->next;
        curr->next = curr->next->next;
        prev->next->next = temp;
    }

    return dummy->next;
}

void addNode(ListNode *head, int val)
{
    ListNode *temp = new ListNode(val);
    head->next = temp;
    return;
}

ListNode *buildLinkedlist(vector<int> arr)
{
    ListNode *head = new ListNode();
    ListNode *itr = head;
    for (int i = 0; i < arr.size(); i++)
    {
        addNode(itr, arr[i]);
        itr = itr->next;
    }
    return head->next;
}

int main()
{
    vector<int> arr{1, 2, 3, 4, 5};
    ListNode *head = buildLinkedlist(arr);
    ListNode *itr = head;
    while (itr != NULL)
    {
        cout << itr->val << " ";
        itr = itr->next;
    }
    cout << endl;

    head = reverse_list(head, 2, 4);
    while (head != NULL)
    {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
    return 0;
}