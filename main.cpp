#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    ifstream fin("wordle-nyt-answers-alphabetical.txt");
    int count[26][5] = {};
    int all[26] = {};
    string word;
    vector<string> words;
    while(fin >> word){
        vector<bool> used(26, false);
        words.push_back(word);
        for(int i = 0; i < 5; ++i){
            int ch = word[i] - 'a';
            ++count[ch][i];
            if(!used[ch]){
                ++all[ch];
                used[ch] = false;
            }
        }
    }
    cout << words.size() << endl; 
    auto guess = words;
    ifstream fin2("wordle-nyt-allowed-guesses.txt");
    while(fin2 >> word){
        guess.push_back(word);
    }
    vector<int> scores(guess.size());
    for(size_t i = 0; i < guess.size(); ++i){
        vector<bool> used(26, false);
        for(int j = 0; j < 5; ++j){
            int ch = guess[i][j] - 'a';
            scores[i] += count[ch][j];
            if(!used[ch]){
                scores[i] += all[ch] * 2;
                used[ch] = true;
            }
        }
    }
    vector<int> rank(guess.size());
    for(size_t i = 0; i < guess.size(); ++i){
        rank[i] = i;
    }
    sort(rank.begin(), rank.end(), [&scores](int a, int b){return scores[a] > scores[b];});
    ofstream fout("results.txt");
    fout << "Highest scoring words: " << guess[rank[0]] << ' ' << guess[rank[1]] << ' ' << guess[rank[2]] << '\n';
    fout << "Lowest scoring words: " << guess[rank[rank.size()-1]] << ' ' << guess[rank[rank.size()-2]] << ' ' << guess[rank[rank.size()-3]] << '\n';
    vector<int> crank(26);
    for(int i = 0; i < 26; ++i){
        crank[i] = i;
    }
    sort(crank.begin(), crank.end(), [all](int a, int b){return all[a] > all[b];});
    fout << "Char by word counts: " ;
    for(int i = 0; i < 26; ++i){
        char d = ('a' + crank[i]);
        fout << d << ' ';
    }
    fout << '\n';
    for(int i = 0; i < 5; ++i){
        fout << "Char by appearance in position " << i << ": ";
        sort(crank.begin(), crank.end(), [count, i](int a, int b){return count[a][i] > count[b][i];});
        for(int j = 0 ; j < 26; ++j){
            char d = ('a' + crank[j]);
            fout << d << ' ';
        }
        fout << '\n';
    }
    int prank[5] = {0, 1, 2, 3, 4};
    for(int i = 0; i < 26; ++i){
        fout << "Position by char " << static_cast<char>('a'+i) << ": ";
        sort(prank, prank + 5, [count, i](int a, int b){return count[i][a] > count[i][b];});
        for(int j = 0; j < 5; ++j){
            fout << prank[j];
        }
        fout << '\n';
    }
}