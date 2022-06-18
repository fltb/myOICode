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
        CHAR_NUM = 2
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
            if (ch >= '0' && ch <= '1')
            {
                return ch - '0';
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
    T & push(const string & str, size_t cur, Node & now);
    int pop(const string & str, size_t cur, Node & now);
    void update_sum(const string & str, size_t cur, Node & now);
    void update_rm_sum(const string & str, size_t cur, Node & now);
    bool find(const string & str, size_t cur, TrieTree::Node & now);
    int get_sum(const string & str, size_t cur, Node & now);
public:

    TrieTree()
    {
        root = unique_ptr<Node>(new Node());
    }

    T & operator[](const string & str)
    {
        return push(str, 0, *root);
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

    bool exsist(const string & str)
    {
        return find(str, 0, *root);
    }

    friend int get_ans(const string & str, TrieTree & tree);
    friend int get_ans(const string & str, size_t cur, Node & now);
};

template<typename T>
void TrieTree<T>::update_sum(const string & str, size_t cur, TrieTree::Node & now)
{
    now.des_sum++;
    if (cur >= str.size())
    {
        return;
    }
    update_sum(str, cur + 1, now.son(str[cur]));
}

template<typename T>
void TrieTree<T>::update_rm_sum(const string & str, size_t cur, TrieTree::Node & now)
{
    now.des_sum--;
    if (cur >= str.size())
    {
        return;
    }
    update_rm_sum(str, cur + 1, now.son(str[cur]));
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
bool TrieTree<T>::find(const string & str, size_t cur, TrieTree::Node & now)
{
    if (cur >= str.size())
    {
        return !(now.val_ptr == nullptr);
    }
    char key = str[cur];
    if (now.has_son(key))
    {
        return find(str, cur + 1, now.son(key));
    }
    else
    {
        return false;
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
        update_sum(str, 0, *root);
        if (now.val_ptr == nullptr)
        {
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

int get_ans(const string & str, size_t cur, TrieTree<int>::Node & now)
{
    int sum = 0;
    if (cur >= str.size())
    {
        sum += now.des_sum;
        return sum;
    }
    if (now.val_ptr != nullptr)
    {
        sum += *now.val_ptr;
    }

    if (!now.has_son(str[cur]))
    {
        return sum;
    }

    return sum + get_ans(str, cur + 1, now.son(str[cur]));
}

int get_ans(const string & str, TrieTree<int> & tree)
{
    return get_ans(str, 0, *tree.root);
}

int main()
{
    TrieTree<int> tree;
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < m; ++i)
    {
        int s;
        string str;
        cin >> s;
        for (int j = 0; j < s; ++j)
        {
            int num;
            cin >> num;
            str += char('0' + num);
        }
        tree[str]++;
    }

    for (int i = 0; i < n; ++i)
    {
        int s;
        string str;
        cin >> s;
        for (int j = 0; j < s; ++j)
        {
            int num;
            cin >> num;
            str += char('0' + num);
        }
        cout << get_ans(str, tree) << "\n";
    }
    return 0;
}
