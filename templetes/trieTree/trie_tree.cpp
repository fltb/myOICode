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
using std::shared_ptr;

template<typename T, typename N>
class BaseTrieTree
{
private:

    virtual T & push(const string & str, size_t cur, N & now);
    virtual int pop(const string & str, size_t cur, N & now);
    virtual void update_sum(const string & str, size_t cur, N & now);
    virtual void update_rm_sum(const string & str, size_t cur, N & now);
    virtual bool find(const string & str, size_t cur, N & now);
    virtual int get_sum(const string & str, size_t cur, N & now);

protected:

    shared_ptr<N> root;

public:

    BaseTrieTree()
    {
        root = unique_ptr<N>(new N());
    }

    virtual ~BaseTrieTree(){}

    virtual T & operator[](const string & str)
    {
        return push(str, 0, *root);
    }

    virtual T & push(const string & str)
    {
        return push(str, 0, *root);
    }

    virtual int pop(const string & str)
    {
        return pop(str, 0, *root);
    }

    virtual int size()
    {
        return root->des_sum;
    }

    virtual int size(const string & str)
    {
        return get_sum(str, 0, *root);
    }

    virtual bool exsist(const string & str)
    {
        return find(str, 0, *root);
    }
};

template<typename T, typename N>
void BaseTrieTree<T, N>::update_sum(const string & str, size_t cur, N & now)
{
    now.des_sum++;
    if (cur >= str.size())
    {
        return;
    }
    update_sum(str, cur + 1, now.son(str[cur]));
}

template<typename T, typename N>
void BaseTrieTree<T, N>::update_rm_sum(const string & str, size_t cur, N & now)
{
    now.des_sum--;
    if (cur >= str.size())
    {
        return;
    }
    update_rm_sum(str, cur + 1, now.son(str[cur]));
}

template<typename T, typename N>
int BaseTrieTree<T, N>::get_sum(const string & str, size_t cur, N & now)
{
    if (cur >= str.size())
    {
        return now.des_sum;
    }
    return get_sum(str, cur + 1, now.son(str[cur]));
}

template<typename T, typename N>
bool BaseTrieTree<T, N>::find(const string & str, size_t cur, N & now)
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

template<typename T, typename N>
T & BaseTrieTree<T, N>::push(const string & str, size_t cur, N & now)
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

template<typename T, typename N>
int BaseTrieTree<T, N>::pop(const string & str, size_t cur, N & now)
{
    if (cur > str.size())
    {
        throw "WHAT???";
    }
    if (cur == str.size())
    {
        update_rm_sum(str, 0, *root);
        return 0;
    }
    char key = str[cur];
    if (now.has_son(key))
    {
        N & son = now.son(key);
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

template<typename T>
struct Node
{
    enum
    {
        NO_SON,
        NOT_A_CHAR,
        SON_HAS_VAL,
        CHAR_NUM = 26 + 1
    };
    int has_bit, des_sum;
    unique_ptr<T> val_ptr;
    shared_ptr<Node> sons[CHAR_NUM];
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
            sons[key].reset();
        }
    }
};

template<typename T>
class TrieTree : public BaseTrieTree<T, Node<T> >
{
};

int main()
{
    TrieTree<int> tr;
    tr["sbc"] = 1;
    tr["ash"] = 1;
    tr["as"] = 1;
    tr["as"]++;
    
    cout << "size:" << tr.size() << "\n";
    cout << "size a:" << tr.size("a") << "\n";
    cout << "size ash" << tr.size("ash") << "\n";
    cout << tr["ash"] << "\n";
    cout << tr["as"] << "\n";

    cout << std::to_string(tr.exsist("a")) << " " << std::to_string(tr.exsist("as")) << "\n";

    tr.pop("sbc");

    cout << "size: " << tr.size();
    return 0;
}