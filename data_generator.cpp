// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <string>
// #include <random>
// #include <algorithm>
//
// using namespace std;
//
// const vector<string> TOXIC_WORDS = {"trash", "diff", "uninstall", "noob", "report", "thrower", "useless", "bot", "afk", "suck", "garbage", "garbo", "quit", "ez"};
// const vector<string> SAFE_WORDS = {"wp", "gg", "nice", "clean", "clutch", "save", "glhf", "mb", "good"};
// const vector<string> FILLER_WORDS = {"team", "you", "are", "my", "the", "bro", "mid", "game", "play", "stop"};
//
// struct RankProb {
//     string name;
//     double probability;
// };
//
// vector<RankProb> RANKS = {
//     {"Bronze", 0.0},
//     {"Silver", 0.0},
//     {"Gold", 0.0},
//     {"Platinum", 0.0},
//     {"Diamond", 0.0},
//     {"Grandmaster", 0.0},
//     {"Celestial", 0.0}
// };
//
// vector<string> pickRandomUnique(const vector<string>& pool, int count, mt19937& rng) {
//     vector<string> poolCopy = pool;
//     shuffle(poolCopy.begin(), poolCopy.end(), rng);
//     return vector<string>(poolCopy.begin(), poolCopy.begin() + count);
// }
//
// string generateMessage(bool isToxic, mt19937& rng) {
//     const vector<string>& pool = isToxic ? TOXIC_WORDS : SAFE_WORDS;
//
//     uniform_int_distribution<int> sentimentDist(1, 3);
//     uniform_int_distribution<int> fillerDist(2, 4);
//
//     int numSentiment = sentimentDist(rng);
//     int numFiller = fillerDist(rng);
//
//     vector<string> words = pickRandomUnique(pool, numSentiment, rng);
//     vector<string> fillers = pickRandomUnique(FILLER_WORDS, numFiller, rng);
//
//     words.insert(words.end(), fillers.begin(), fillers.end());
//
//     shuffle(words.begin(), words.end(), rng);
//
//     string result = "";
//     for (size_t i = 0; i < words.size(); ++i) {
//         result += words[i];
//         if (i != words.size() - 1) {
//             result += " ";
//         }
//     }
//     return result;
// }
//
// void generateDataset(const string& filename, int numRows) {
//     ofstream outFile(filename);
//     if (!outFile.is_open()) {
//         cerr << "Error opening file!" << endl;
//         return;
//     }
//
//     outFile << "Rank|ChatMessage\n";
//
//     random_device rd;
//     mt19937 rng(rd());
//
//     uniform_real_distribution<double> secretToxDist(0.1, 0.9);
//     cout << "--- SECRET ANSWER KEY (Keep this to check your algorithms later) ---\n";
//     for (auto& rank : RANKS) {
//         rank.probability = secretToxDist(rng);
//         cout << rank.name << " Toxicity Probability: " << (rank.probability * 100) << "%\n";
//     }
//     cout << "-------------------------------------------------------------------\n";
//
//     discrete_distribution<int> rankDist({15, 25, 30, 15, 10, 4, 1});
//     uniform_real_distribution<double> probDist(0.0, 1.0);
//
//     for (int i = 1; i <= numRows; ++i) {
//         RankProb selectedRank = RANKS[rankDist(rng)];
//         bool isToxic = probDist(rng) < selectedRank.probability;
//         string chatMessage = generateMessage(isToxic, rng);
//
//         outFile << selectedRank.name << "|" << chatMessage << "\n";
//     }
//
//     outFile.close();
//     cout << "Successfully generated " << numRows << " rows in " << filename << endl;
// }
//
// int main() {
//     generateDataset("players_dataset.txt", 100000);
//     return 0;
// }