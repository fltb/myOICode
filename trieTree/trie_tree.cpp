#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
using std::cout;
using std::cin;
using std::unique_ptr;
using std::string;
using std::vector;

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
        int sonsum;
        int val;
        unique_ptr<Node> sons[CHAR_NUM];
        vector<int> has;
        Node()
        {
            val = 0;
            sonsum = 0;
            has = vector<int>(CHAR_NUM, 0);
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
            if (!has[key])
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
            if (!has[key])
            {
                throw NO_SON;
            }
            return *sons[key];
        }

        void push_son(char ch)
        {
            int key = tokey(ch);
            if (!has[key])
            {
                sonsum++;
                has[key] = true;
                sons[key] = unique_ptr<Node>(new Node());
            }
        }

        void rm_son(char ch)
        {
            int key = tokey(ch);
            if (has[key])
            {
                if (sons[key]->sonsum > 0)
                {
                    throw SON_HAS_VAL;
                }
                sonsum--;
                has[key] = false;
                delete sons[key].release();
            }
        }
    };
    unique_ptr<Node> root;
public:

    TrieTree()
    {
        root = unique_ptr<Node>(new Node());
    }

    // return val, if not find is 0
    int find(const string & str, size_t cur, Node & now)
    {
        if (cur >= str.size())
        {
            return now.val;
        }
        char key = str[cur];
        if (now.has_son(key))
        {
            return find(str, cur + 1, now.son(key));
        }
        else
        {
            return 0;
        }
    }

    int find(const string & str)
    {
        return find(str, 0, *root);
    }

    int push(const string & str, size_t cur, Node & now)
    {
        if (cur > str.size())
        {
            throw "WHAT???";
        }
        if (cur == str.size())
        {
            now.val++;
            return 0;
        }
        char key = str[cur];
        now.push_son(key);
        return push(str, cur + 1, now.son(key));
    }

    int push(const string & str)
    {
        return push(str, 0, *root);
    }

    int pop(const string & str, size_t cur, Node & now)
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
            if (son.val == 0 && son.sonsum == 0)
            {
                now.rm_son(key);
            }
        }
        else
        {
            return -1;
        }
    }

    int pop(const string & str)
    {
        return pop(str, 0, *root);
    }

};

int main()
{
    TrieTree tr;
    tr.push("sbc");
    tr.push("ash");
    tr.push("as");
    tr.push("as");
    
    cout << tr.find("ash") << "\n";
    cout << tr.find("as") << "\n";

    tr.pop("sbc");

    cout << tr.find("sbc") << "\n";
    return 0;
}