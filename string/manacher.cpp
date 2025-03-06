#include <bits/stdc++.h>

using namespace std;

struct manacher{
    vector<int> p;
    int max_length = 1;
    int index_of_max_length = 0;

    void run_manacher(string s){
        int n = s.length();
        p.assign(n, 1);
        int l = 1, r = 1;
        for(int i = 1; i < n; i++){
            p[i] = max(0, min(r - i, p[l + (r - i)]));

            while(i + p[i] < n && i - p[i] >= 0 && s[i + p[i]] == s[i - p[i]]) {
                p[i]++;
            }

            if(i + p[i] > r){
                l = i - p[i];
                r = i + p[i];
            }

            if(p[i] > max_length){
                max_length = p[i];
                index_of_max_length = i;
            }
        }
    }

    void build(string s){
        string t;
        for(char c : s){
            t += '#';
            t += c;
        }
        t += '#';
        run_manacher(t);
    }

    int get_palindrome(int cent, int odd){
        int index = 2 * cent + 1 + (!odd);
        return p[index] - 1;
    }

    bool check_palindrome(int l, int r){
        int transformed_l = 2 * l + 1;
        int transformed_r = 2 * r + 1;
        int center = (transformed_l + transformed_r) / 2;
        if(center < 0 || center >= p.size()) return false;
        int required_radius = r - l + 1;
        return p[center] >= required_radius;
    }

    int get_longest_palindrome(){
        return max_length - 1;
    }

    void print_longest_palindrome(string s){
        int len = get_longest_palindrome();
        int index = index_of_max_length;
        cout << s.substr((index - len) / 2, len) << endl;
    }
} m;

int main(){
    string s = "abacaba";
    m.build(s);
    cout << m.get_longest_palindrome() << endl;
    m.print_longest_palindrome(s);
    return 0;
}