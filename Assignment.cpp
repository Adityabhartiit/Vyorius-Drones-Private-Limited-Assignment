#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <iomanip>

using namespace std;

// Function to load the ratings matrix from a CSV file
vector<vector<int>> loadRatingsMatrix(const string &filename) {
    vector<vector<int>> ratings;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            row.push_back(stoi(cell));
        }
        ratings.push_back(row);
    }

    return ratings;
}

// Function to calculate average ratings for each movie
vector<pair<int, double>> calculateAverageRatings(const vector<vector<int>> &ratings) {
    vector<pair<int, double>> movieAverages; // Pair of movie index and average rating

    for (size_t movieIndex = 0; movieIndex < ratings[0].size(); ++movieIndex) {
        double sum = 0;
        int count = 0;

        for (size_t userIndex = 0; userIndex < ratings.size(); ++userIndex) {
            if (ratings[userIndex][movieIndex] != 0) {
                sum += ratings[userIndex][movieIndex];
                count++;
            }
        }

        double average = (count == 0) ? 0 : sum / count;
        movieAverages.push_back({movieIndex, average});
    }

    return movieAverages;
}

// Function to find the top k movies using a max heap
vector<int> findTopKMovies(const vector<pair<int, double>> &movieAverages, int k) {
    priority_queue<pair<double, int>> maxHeap;

    for (const auto &movie : movieAverages) {
        maxHeap.push({movie.second, movie.first}); // {average, movieIndex}
    }

    vector<int> topKMovies;
    while (k-- > 0 && !maxHeap.empty()) {
        topKMovies.push_back(maxHeap.top().second); // Get movie index
        maxHeap.pop();
    }

    return topKMovies;
}

// Main function
int main() {
    string filename = "ratings.csv";
    vector<vector<int>> ratings = loadRatingsMatrix(filename);

    // Calculate average ratings for each movie
    vector<pair<int, double>> movieAverages = calculateAverageRatings(ratings);

    // Find top k movies
    int k = 3; // Example: Top 3 movies
    vector<int> topKMovies = findTopKMovies(movieAverages, k);

    // Output the top k movies
    cout << "Top " << k << " movies based on average ratings:\n";
    for (int movieIndex : topKMovies) {
        cout << "Movie " << movieIndex + 1 << " with average rating "
             << fixed << setprecision(2) << movieAverages[movieIndex].second << "\n";
    }

    return 0;
}
