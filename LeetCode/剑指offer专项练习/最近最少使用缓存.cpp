// 运用所掌握的数据结构，设计和实现一个  LRU (Least Recently Used，最近最少使用) 缓存机制 。

// 实现 LRUCache 类：
// LRUCache(int capacity) 以正整数作为容量 capacity 初始化 LRU 缓存
// int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
// void put(int key, int value) 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字-值」。
// 当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/OrIXps
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
#include <unordered_map>
using std::unordered_map;

class List
{
public:
    int val;
    List* pre;
    List* next;
    List():pre(nullptr), next(nullptr) {};
    
};


class LRUCache {
public:
    LRUCache(int capacity) {
        head->next = tail;
        tail->pre = head;
        m_capcity = capacity;
    }
    
    int get(int key) {
        if(!ump.count(key))
            return -1;
        List* cur = new List;
        tail->val = ump[key]->val;
        tail->next = cur;
        cur->pre = tail;
        cur = ump[key];
        cur->pre->next = cur->next;
        cur->next->pre = cur->pre;
        ump[key] = tail;
        delete cur;
        tail = ump[key]->next;
        return ump[key]->val;
    }
    
    void put(int key, int value) {
        List* cur = new List;
        tail->next = cur;
        cur->pre = tail;
        tail->val = value;
        if(ump.count(key)) {
            cur = ump[key];
            cur->pre->next = cur->next;
            cur->next->pre = cur->pre;
            ump[key] = tail;
            tail = ump[key]->next;
            delete cur;
        }
        else {
            ump.insert(std::make_pair(key, tail));
            tail = cur;
            list_size++;
            if(list_size > m_capcity) {
                head = head->next;
                delete head->pre;
                head->pre = nullptr;
                for(auto &it: ump) {
                    if(it.second == head) {
                        ump.erase(it.first);
                        break;
                    }
                }
                list_size--;
            }
        }
    }

private:
    int m_capcity;
    unordered_map<int, List*> ump;
    int list_size = 0;
    List* head = new List;
    List* tail = new List;
};