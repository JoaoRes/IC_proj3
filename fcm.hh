#include <vector>
#include <set>
#include <iostream>
#include <fstream>
using namespace std;


class fcm{
    public:
        void define_alphabet(string inF);
        void generate_matrix(int k);
    private:
        set<char> alphabet;
        fstream inFile;
};

void fcm::define_alphabet(string inF){
    if(not inF.empty()) {
        inFile.open(inF);
        char c;
        while (inFile.get(c)) {    
            alphabet.insert(tolower(c));
        }
    }else{
        cout << "No In File to open" << endl;
    }

    for (char c : alphabet){
        cout << c;
    }
}

void increment_neighbor(std::vector<char> &arr, int idx)
{

    for (int i = idx; i < arr.size(); ++i)
        arr.at(i) = arr.at(i - 1) + 1;
}

bool _next_combination(int n, int r, std::vector<char> &curr_comb,
                       int idx)
{

    if (idx < 0)
        return false;

    if (curr_comb.at(idx) < n - r + idx + 1) {
        ++curr_comb.at(idx);
        increment_neighbor(curr_comb, idx + 1);
        return true;
    }
    else
        return _next_combination(n, r, curr_comb, idx - 1);
}

bool next_combination(int n, int r, std::vector<char> &curr_comb)
{

    return _next_combination(n, r, curr_comb, r - 1);
}

void fcm::generate_matrix(int k){
    vector<char> vector_alpha;
    vector_alpha.assign(alphabet.begin(), alphabet.end());
    cout << next_combination(alphabet.size(), k, vector_alpha) << endl;

}
