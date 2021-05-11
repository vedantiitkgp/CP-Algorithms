//https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/

#include<bits/stdc++.h>
#define MAX 1000

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<string, string> pss;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef vector<ll> vl;
typedef vector<vl> vvl;

int preced(char s)
{
    if(s=='^') return 3;
    else if(s=='/' || s=='*') return 2;
    else if(s=='+'||s=='-') return 1;
    else return -1;
}

string infix_postfix(string s)
{
    string result;
    stack<char> st;
    for(int i=0;i<s.length();i++)
    {
        char c = s[i];
        if((c>='a'&& c <='z')||(c>='A'&&c<='Z')||(c>='0'&& c<='9'))
        {
            result += c;
        }
        else if(c=='(')
        {
            st.push(c);
        }
        else if(c==')')
        {
            while((!st.empty())&&(st.top()!='('))
            {
                char ch = st.top();
                result += ch;
                st.pop();
            }
            st.pop();
        }
        else
        {
            while((!st.empty())&&(preced(c)<=preced(st.top())))
            {
                char ch = st.top();
                result += ch;
                st.pop();
            }
            st.push(c);
        }
    }

    while(!st.empty())
    {
        char ch = st.top();
        result+=ch;
        st.pop();
    }
    
    return result;
}

string prefix_infix(string s)
{
    string result;
    stack <string> st;

    for(int i=s.length()-1;i>=0;i--)
    {
        if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^')
        {
            string a = st.top();
            st.pop();
            string b = st.top();
            st.pop();
            string final = '(' + a + s[i] + b + ')';
            st.push(final);
        }
        else
        {
            string temp;
            temp += s[i];
            st.push(temp);
        }
    }
    return st.top();
}

string postfix_infix(string s)
{
    string result;
    stack <string> st;

    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^')
        {
            string a = st.top();
            st.pop();
            string b = st.top();
            st.pop();
            string final = '(' + b + s[i] + a + ')';
            st.push(final);
        }
        else
        {
            string temp;
            temp += s[i];
            st.push(temp);
        }
    }
    return st.top();
}

string postfix_prefix(string s)
{
    string result;
    stack <string> st;

    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^')
        {
            string a = st.top();
            st.pop();
            string b = st.top();
            st.pop();
            string final = s[i] + b + a ;
            st.push(final);
        }
        else
        {
            string temp;
            temp += s[i];
            st.push(temp);
        }
    }
    return st.top();
}

string prefix_postfix(string s)
{
    string result;
    stack <string> st;

    for(int i=s.length()-1;i>=0;i--)
    {
        if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^')
        {
            string a = st.top();
            st.pop();
            string b = st.top();
            st.pop();
            string final = a + b + s[i] ;
            st.push(final);
        }
        else
        {
            string temp;
            temp += s[i];
            st.push(temp);
        }
    }
    return st.top();
}

string infix_prefix(string s)
{
    return postfix_prefix(infix_postfix(s));
}

void print_string(string s)
{
    cout<<s<<endl;
}

int main()
{
    string infix1 = "a+b*(c^d-e)^(f+g*h)-i";
    //print_string(infix_postfix(infix1));
    string infix2 = "((A+B)*(C-D))";
    //print_string(infix_prefix(infix2));
    string prefix1 = "*+AB-CD";
    //print_string(prefix_infix(prefix1));
    string prefix2 = "*-A/BC-/AKL";
    //print_string(prefix_postfix(prefix2));
    string postfix1 = "AB+CD-*";
    //print_string(postfix_infix(postfix1));
    string postfix2 = "ABC/-AK/L-*";
    //print_string(postfix_prefix(postfix2));
    return 0;
}