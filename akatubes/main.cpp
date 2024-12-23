#include <iostream>

using namespace std;

void findBestCombination(int weights[], int n, int maxWeight) {
    int bestWeight = 0;
    int bestCombination[1000];
    int bestCount = 0;

    // Total number of subsets: 2^n
    int totalSubsets = 1;
    for (int i = 0; i < n; i++) {
        totalSubsets *= 2;
    }

    for (int subset = 0; subset < totalSubsets; subset++) {
        int currentWeight = 0;
        int currentCombination[1000];
        int currentCount = 0;
        int temp = subset;

        // Generate subset without bitmasking
        for (int j = 0; j < n; j++) {
            if (temp % 2 == 1) { // Check if the current item is part of the subset
                currentWeight += weights[j];
                currentCombination[currentCount++] = weights[j];
            }
            temp /= 2; // Reduce temp to process the next bit
        }

        // Check if the current combination is better
        if (currentWeight <= maxWeight && currentWeight > bestWeight) {
            bestWeight = currentWeight;
            bestCount = currentCount;
            for (int k = 0; k < currentCount; k++) {
                bestCombination[k] = currentCombination[k];
            }
        }
    }

    // Output the best combination
    cout << "Kombinasi terbaik: ";
    for (int i = 0; i < bestCount; i++) {
        cout << bestCombination[i] << " ";
    }
    cout << "\nBerat total: " << bestWeight << endl;
}

void findBestRecursive(int weights[], int n, int maxWeight, int index, int currentWeight, int currentCombination[], int currentCount, int& bestWeight, int bestCombination[], int& bestCount) {
    if (index == n) {
        if (currentWeight > bestWeight) {
            bestWeight = currentWeight;
            bestCount = currentCount;
            for (int i = 0; i < currentCount; i++) {
                bestCombination[i] = currentCombination[i];
            }
        }
        return;
    }

    // Exclude the current item
    findBestRecursive(weights, n, maxWeight, index + 1, currentWeight, currentCombination, currentCount, bestWeight, bestCombination, bestCount);

    // Include the current item if it does not exceed maxWeight
    if (currentWeight + weights[index] <= maxWeight) {
        currentCombination[currentCount] = weights[index];
        findBestRecursive(weights, n, maxWeight, index + 1, currentWeight + weights[index], currentCombination, currentCount + 1, bestWeight, bestCombination, bestCount);
    }
}

void findBestCombinationRecursive(int weights[], int n, int maxWeight) {
    int bestWeight = 0;
    int bestCombination[1000];
    int bestCount = 0;
    int currentCombination[1000];

    findBestRecursive(weights, n, maxWeight, 0, 0, currentCombination, 0, bestWeight, bestCombination, bestCount);

    // Output the best combination
    cout << "Kombinasi terbaik (rekursif): ";
    for (int i = 0; i < bestCount; i++) {
        cout << bestCombination[i] << " ";
    }
    cout << "\nBerat total: " << bestWeight << endl;
}

int main() {
    // Input data
    int weights[] = {13, 2, 42, 9, 11, 46, 3, 49, 14, 14, 15, 29, 42, 35, 38, 10, 35, 37, 31, 5, 13,22,23,24,25,26,27,28,29,30};
    int n = 30;
    int maxWeight = 50;

    cout << "Input berat barang: ";
    for (int i = 0; i < n; i++) {
        cout << weights[i] << " ";
    }
    cout << "\nBerat maksimal: " << maxWeight << endl;

;
   findBestCombinationRecursive(weights, n, maxWeight);
    return 0;
}

