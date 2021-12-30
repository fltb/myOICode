#include <cstddef>
#include <iostream>
#include <string>
#include <memory>
using std::cout;
using std::unique_ptr;
using std::string;

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
        int has_bit;
        T val;
        unique_ptr<Node> sons[CHAR_NUM];
        Node()
        {
            has_bit = 0;
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

    Node & find(const string & str, size_t cur, Node & now);
    Node & push(const string & str, size_t cur, Node & now);
    int pop(const string & str, size_t cur, Node & now);

public:

    TrieTree()
    {
        root = unique_ptr<Node>(new Node());
    }

    T & operator[](const string & str)
    {
        return find(str, 0, *root).val;
    }

    T & push(const string & str)
    {
        return push(str, 0, *root).val;
    }

    int pop(const string & str)
    {
        return pop(str, 0, *root);
    }

};

template<typename T>
typename TrieTree<T>::Node & TrieTree<T>::find(const string & str, size_t cur, TrieTree::Node & now)
{
    if (cur >= str.size())
    {
        return now;
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
typename TrieTree<T>::Node & TrieTree<T>::push(const string & str, size_t cur, TrieTree::Node & now)
{
    if (cur > str.size())
    {
        throw "WHAT???";
    }
    if (cur == str.size())
    {
        return now;
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
        now.val--;
        return 0;
    }
    char key = str[cur];
    if (now.has_son(key))
    {
        Node & son = now.son(key);
        return pop(str, cur + 1, son);
        if (son.val == 0 && son.has_bit == 0)
        {
            now.rm_son(key);
        }
    }
    else
    {
        return -1;
    }
}

int main()
{
    TrieTree<int> tr;
    tr["sbc"] = 1;
    tr["ash"] = 1;
    tr["as"] = 1;
    tr["as"]++;
    
    cout << tr["ash"] << "\n";
    cout << tr["as"] << "\n";

    tr.pop("sbc");

    cout << tr["sbc"] << "\n";
    return 0;
}