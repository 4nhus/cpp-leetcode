#include <unordered_map>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *reverseList(ListNode *head) {
  if (head == nullptr) {
    return head;
  }

  ListNode *prev = nullptr;
  ListNode *curr = head;
  ListNode *next = head->next;

  while (next != nullptr) {
    curr->next = prev;
    prev = curr;
    curr = next;
    next = next->next;
  }

  curr->next = prev;

  return curr;
}

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
  if (list1 == nullptr) {
    return list2;
  } else if (list2 == nullptr) {
    return list1;
  }

  ListNode *head;
  ListNode *curr1 = list1;
  ListNode *curr2 = list2;

  if (list1->val <= list2->val) {
    head = list1;
    curr1 = curr1->next;
  } else {
    head = list2;
    curr2 = curr2->next;
  }

  ListNode *curr3 = head;

  while (curr1 != nullptr && curr2 != nullptr) {
    if (curr1->val <= curr2->val) {
      curr3->next = curr1;
      curr3 = curr3->next;
      curr1 = curr1->next;
    } else {
      curr3->next = curr2;
      curr3 = curr3->next;
      curr2 = curr2->next;
    }
  }

  if (curr1 == nullptr) {
    curr3->next = curr2;
  } else if (curr2 == nullptr) {
    curr3->next = curr1;
  }

  return head;
}

void reorderList(ListNode *head) {
  if (head->next == nullptr) {
    return;
  }

  ListNode *begin = head;
  ListNode *beginNext = head->next;
  ListNode *prev = head;
  ListNode *end = head->next;

  while (true) {
    if (end == nullptr || beginNext->next == nullptr) {
      break;
    }

    while (end->next != nullptr) {
      end = end->next;
      prev = prev->next;
    }

    begin->next = end;

    end->next = beginNext;
    prev->next = nullptr;

    begin = beginNext;
    beginNext = beginNext->next;
    end = beginNext;
    prev = begin;
  }
}

ListNode *removeNthFromEnd(ListNode *head, int n) {
  char numNodes = 1;
  ListNode *curr = head;

  while (curr->next != nullptr) {
    numNodes++;
    curr = curr->next;
  }

  if (n == numNodes) {
    return head->next;
  }

  char currNode = 1;
  curr = head;
  ListNode *prev;

  while (curr != nullptr) {
    if (currNode == numNodes - n + 1) {
      prev->next = curr->next;
      break;
    }

    prev = curr;
    currNode++;
    curr = curr->next;
  }

  return head;
};

class copyListWithRandomPointer {
  class Node {
  public:
    int val;
    Node *next;
    Node *random;

    Node(int _val) {
      val = _val;
      next = NULL;
      random = NULL;
    }
  };

  Node *copyRandomList(Node *head) {
    if (head == nullptr) {
      return nullptr;
    }

    Node *newHead = new Node(head->val);

    unordered_map<Node *, Node *> nodeAddresses;

    nodeAddresses.insert({head, newHead});

    Node *curr = head;
    Node *newCurr = newHead;

    while (curr->next != nullptr) {
      Node *nextNewNode = new Node(curr->next->val);
      nodeAddresses.insert({curr->next, nextNewNode});
      newCurr->next = nextNewNode;
      curr = curr->next;
      newCurr = newCurr->next;
    }

    curr = head;
    newCurr = newHead;

    while (curr != nullptr) {
      if (curr->random != nullptr) {
        newCurr->random = nodeAddresses[curr->random];
      }
      curr = curr->next;
      newCurr = newCurr->next;
    }

    return newHead;
  };
};

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
  ListNode *curr1 = l1;
  ListNode *curr2 = l2;
  ListNode *head;
  int carry = 0;

  if (curr1->val + curr2->val < 10) {
    head = new ListNode(curr1->val + curr2->val);
  } else {
    carry = 1;
    head = new ListNode(curr1->val + curr2->val - 10);
  }

  ListNode *curr3 = head;
  curr1 = curr1->next;
  curr2 = curr2->next;

  while (curr1 != nullptr && curr2 != nullptr) {
    ListNode *newNode;

    if (curr1->val + curr2->val + carry < 10) {
      newNode = new ListNode(curr1->val + curr2->val + carry);
      carry = 0;
    } else {
      newNode = new ListNode(curr1->val + curr2->val + carry - 10);
      carry = 1;
    }

    curr3->next = newNode;
    curr1 = curr1->next;
    curr2 = curr2->next;
    curr3 = curr3->next;
  }

  if (curr1 == nullptr && curr2 == nullptr) {
    if (carry == 1) {
      curr3->next = new ListNode(1);
    }
  } else if (curr1 == nullptr) {
    if (carry == 1) {
      while (curr2 != nullptr) {
        if (curr2->val + carry < 10) {
          curr3->next = new ListNode(curr2->val + carry);
          curr3->next->next = curr2->next;
          carry = 0;
          break;
        } else {
          curr3->next = new ListNode(curr2->val + carry - 10);
          curr3 = curr3->next;
          curr2 = curr2->next;
        }
      }

      if (carry == 1) {
        curr3->next = new ListNode(1);
      }
    } else {
      curr3->next = curr2;
    }
  } else {
    if (carry == 1) {
      while (curr1 != nullptr) {
        if (curr1->val + carry < 10) {
          curr3->next = new ListNode(curr1->val + carry);
          curr3->next->next = curr1->next;
          carry = 0;
          break;
        } else {
          curr3->next = new ListNode(curr1->val + carry - 10);
          curr3 = curr3->next;
          curr1 = curr1->next;
        }
      }

      if (carry == 1) {
        curr3->next = new ListNode(1);
      }
    } else {
      curr3->next = curr1;
    }
  }

  return head;
};

bool hasCycle(ListNode *head) {
  if (head == nullptr || head->next == nullptr) {
    return false;
  }

  ListNode *slow = head;
  ListNode *fast = head->next;

  bool hasCycle = false;

  while (true) {
    slow = slow->next;

    fast = fast->next;
    if (fast == nullptr) {
      break;
    } else if (fast == slow) {
      hasCycle = true;
      break;
    }

    fast = fast->next;
    if (fast == nullptr) {
      break;
    } else if (fast == slow) {
      hasCycle = true;
      break;
    }
  }

  return hasCycle;
};

int findDuplicate(vector<int> &nums) {
  int slow = 0;
  int fast = 0;

  while (true) {
    slow = nums[slow];
    fast = nums[nums[fast]];
    if (slow == fast) {
      break;
    }
  }

  int newSlow = 0;

  while (newSlow != slow) {
    newSlow = nums[newSlow];
    slow = nums[slow];
  }

  return slow;
}

class LRUCache {
public:
  LRUCache(int capacity) : capacity(capacity) {}

  int get(int key) {
    if (map.find(key) == map.end()) {
      return -1;
    } else {
      ListNode *nodeToRead = map[key];

      moveNode(nodeToRead);

      return nodeToRead->val;
    }
  }

  void put(int key, int value) {
    if (map.size() == 0) {
      head = new ListNode(key, value, nullptr);
      tail = head;
      map.insert({key, head});
    } else {
      if (map.find(key) == map.end()) {
        insertNode(key, value);
      } else {
        ListNode *nodeToChange = map[key];
        nodeToChange->val = value;

        moveNode(nodeToChange);
      }

      if (map.size() > capacity) {
        deleteHead();
      }
    }
  }

private:
  struct ListNode {
    int key;
    int val;
    ListNode *next;
    ListNode *prev;
    ListNode(int x, int y, ListNode *z)
        : key(x), val(y), next(nullptr), prev(z) {}
  };

  ListNode *head;
  ListNode *tail;
  unordered_map<int, ListNode *> map;
  int capacity;

  void deleteHead() {
    map.erase(head->key);
    ListNode *temp = head;
    head = head->next;
    head->prev = nullptr;
    delete (temp);
  }

  void insertNode(int key, int value) {
    ListNode *newNode = new ListNode(key, value, tail);
    tail->next = newNode;
    tail = newNode;
    map.insert({key, newNode});
  }

  void moveNode(ListNode *node) {
    if (map.size() > 1 && node != tail) {
      if (node == head) {
        head = head->next;
        head->prev = nullptr;
      }

      tail->next = node;

      if (node->prev != nullptr) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
      }

      node->prev = tail;
      node->next = nullptr;
      tail = node;
    }
  }
};

ListNode *mergeKLists(vector<ListNode *> &lists) {
  if (lists.size() == 0) {
    return nullptr;
  } else if (lists.size() == 1) {
    return lists[0];
  }

  vector<pair<ListNode *, ListNode *>> listPairsToMerge;
  vector<ListNode *> mergedLists;

  if (lists.size() % 2 == 1) {
    mergedLists.push_back(lists[lists.size() - 1]);
    lists.pop_back();
  }

  for (int i = 0; i < lists.size(); i += 2) {
    listPairsToMerge.push_back({lists[i], lists[i + 1]});
  }

  while (true) {
    for (int i = 0; i < listPairsToMerge.size(); i++) {
      mergedLists.push_back(
          mergeTwoLists(listPairsToMerge[i].first, listPairsToMerge[i].second));
    }

    if (mergedLists.size() == 1) {
      return mergedLists[0];
    }

    listPairsToMerge.clear();

    ListNode *oddListOut = nullptr;

    if (mergedLists.size() % 2 == 1) {
      oddListOut = mergedLists[mergedLists.size() - 1];
      mergedLists.pop_back();
    }

    for (int i = 0; i < mergedLists.size(); i += 2) {
      listPairsToMerge.push_back({mergedLists[i], mergedLists[i + 1]});
    }

    mergedLists.clear();

    if (oddListOut != nullptr) {
      mergedLists.push_back(oddListOut);
    }
  }
}

class reverseNodesInKGroup {
  ListNode *reverseKGroup(ListNode *head, int k) {
    if (head->next == nullptr || k == 1) {
      return head;
    }

    int currInGroup = 1;
    ListNode *curr = head;
    ListNode *newHead = head;
    ListNode *tailOfGroup = head;
    ListNode *nextAfterGroup;
    ListNode *firstBeforeGroup = nullptr;

    while (true) {
      while (curr->next != nullptr && currInGroup < k) {
        curr = curr->next;
        currInGroup++;
      }

      if (currInGroup == k) {
        nextAfterGroup = curr->next;
        curr->next = nullptr;
        reverseList(tailOfGroup);
        if (newHead == head) {
          newHead = curr;
        }

        if (firstBeforeGroup != nullptr) {
          firstBeforeGroup->next = curr;
        }

        // reconnect reversed group to rest of list
        tailOfGroup->next = nextAfterGroup;

        // reset for next reversal
        currInGroup = 1;
        firstBeforeGroup = tailOfGroup;
        tailOfGroup = nextAfterGroup;
        curr = nextAfterGroup;

      } else {
        break;
      }

      if (curr == nullptr) {
        break;
      }
    }

    return newHead;
  }

  ListNode *reverseList(ListNode *head) {
    if (head == nullptr) {
      return head;
    }

    ListNode *prev = nullptr;
    ListNode *curr = head;
    ListNode *next = head->next;

    while (next != nullptr) {
      curr->next = prev;
      prev = curr;
      curr = next;
      next = next->next;
    }

    curr->next = prev;

    return curr;
  }
};
