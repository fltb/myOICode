#include <cstddef>
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <memory>
using std::cin;
using std::cout;
using std::unique_ptr;
using std::string;
using std::vector;

template<typename T>
class TrieTree
{
private:
    enum
    {
        NO_SON,
        NOT_A_CHAR,
        SON_HAS_VAL,
        CHAR_NUM = 26 + 1
    };
    struct Node
    {
        int has_bit, des_sum;
        unique_ptr<T> val_ptr;
        unique_ptr<Node> sons[CHAR_NUM];
        Node()
        {
            val_ptr = nullptr;
            des_sum = has_bit = 0;
        }

        bool ifhas(int key)
        {
            return (1<<key) & has_bit;
        }

        void addhas(int key)
        {
            has_bit |= (1<<key);
        }

        void rmhas(int key)
        {
            has_bit ^= (1<<key);
        }

        int tokey(char ch)
        {
            if (ch >= 'a' && ch <= 'z')
            {
                return ch - 'a';
            }
            if (ch >= 'A' && ch <= 'Z')
            {  
                return ch - 'A';
            }
            throw NOT_A_CHAR;
        }

        bool has_son(char ch)
        {
            int key = tokey(ch);
            if (!ifhas(key))
            {
                return false;
            }
            else
            {
                return true;    
            }
        }

        Node & son(char ch)
        {
            int key = tokey(ch);
            if (!ifhas(key))
            {
                throw NO_SON;
            }
            return *sons[key];
        }

        void push_son(char ch)
        {
            int key = tokey(ch);
            if (!ifhas(key))
            {
                addhas(key);
                sons[key] = unique_ptr<Node>(new Node());
            }
        }

        void rm_son(char ch)
        {
            int key = tokey(ch);
            if (ifhas(key))
            {
                if (sons[key]->has_bit > 0)
                {
                    throw SON_HAS_VAL;
                }
                rmhas(key);
                delete sons[key].release();
            }
        }
    };
    unique_ptr<Node> root;
    vector<T> vals;
    T & find(const string & str, size_t cur, Node & now);
    T & push(const string & str, size_t cur, Node & now);
    int pop(const string & str, size_t cur, Node & now);
    void update_sum(const string & str, size_t cur, Node & now);
    int get_sum(const string & str, size_t cur, Node & now);
public:

    TrieTree()
    {
        root = unique_ptr<Node>(new Node());
    }

    T & operator[](const string & str)
    {
        return find(str, 0, *root);
    }

    T & push(const string & str)
    {
        return push(str, 0, *root);
    }

    int pop(const string & str)
    {
        return pop(str, 0, *root);
    }

    int size()
    {
        return root->des_sum;
    }

    int size(const string & str)
    {
        return get_sum(str, 0, *root);
    }

};

template<typename T>
void TrieTree<T>::update_sum(const string & str, size_t cur, TrieTree::Node & now)
{
    if (cur >= str.size())
    {
        return;
    }
    now.des_sum++;
    update_sum(str, cur + 1, now.son(str[cur]));
}

template<typename T>
int TrieTree<T>::get_sum(const string & str, size_t cur, TrieTree::Node & now)
{
    if (cur >= str.size())
    {
        return now.des_sum;
    }
    return get_sum(str, cur + 1, now.son(str[cur]));
}

template<typename T>
T & TrieTree<T>::find(const string & str, size_t cur, TrieTree::Node & now)
{
    if (cur >= str.size())
    {
        if (now.val_ptr == nullptr)
        {
            now.val_ptr = unique_ptr<T>(new T());
        }
        return *now.val_ptr;
    }
    char key = str[cur];
    if (now.has_son(key))
    {
        return find(str, cur + 1, now.son(key));
    }
    else
    {
        return push(str, cur, now);
    }
}

template<typename T>
T & TrieTree<T>::push(const string & str, size_t cur, TrieTree::Node & now)
{
    if (cur > str.size())
    {
        throw "WHAT???";
    }
    if (cur == str.size())
    {
        if (now.val_ptr == nullptr)
        {
            update_sum(str, 0, *root);
            now.val_ptr = unique_ptr<T>(new T());
        }
        return *now.val_ptr;
    }
    char key = str[cur];
    now.push_son(key);
    return push(str, cur + 1, now.son(key));
}

template<typename T>
int TrieTree<T>::pop(const string & str, size_t cur, TrieTree::Node & now)
{
    if (cur > str.size())
    {
        throw "WHAT???";
    }
    if (cur == str.size())
    {
        return 0;
    }
    char key = str[cur];
    if (now.has_son(key))
    {
        Node & son = now.son(key);
        pop(str, cur + 1, son);
        if (son.has_bit == 0)
        {
            now.rm_son(key);
        }
    }
    else
    {
        return -1;
    }
    return 0;
}

const int MAXN = 1000 + 2;

int main()
{
    std::ios::sync_with_stdio(false);
    TrieTree<vector<int> > tree;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; ++j)
        {
            string now;
            cin >> now;
            auto node = tree[now];
            if (node.empty() || node.back() != i)
            {
                tree[now].push_back(i);
            }
        }
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        string q;
        cin >> q;
        auto now = tree[q];
        auto it = now.begin();
        if (it != now.end())
        {
            cout << *it;
            ++it;
        }
        while (it != now.end())
        {
            cout << " " << *it;
            ++it;
        }
        cout << "\n";
    }

    return 0;
}