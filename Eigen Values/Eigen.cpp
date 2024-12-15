#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to multiply a matrix by a vector
vector<double> multiplyMatrixVector(const vector<vector<double>>& matrix, const vector<double>& vec) {
    int n = matrix.size();
    vector<double> result(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < vec.size(); j++) {
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}

// Function to find the maximum value in a vector and its index
pair<double, int> findMax(const vector<double>& vec) {
    double maxVal = fabs(vec[0]);
    int index = 0;
    for (int i = 1; i < vec.size(); i++) {
        if (fabs(vec[i]) > maxVal) {
            maxVal = fabs(vec[i]);
            index = i;
        }
    }
    return { maxVal, index };
}

// Function to normalize a vector
void normalizeVector(vector<double>& vec) {
    double norm = 0;
    for (double val : vec) {
        norm += val * val;
    }
    norm = sqrt(norm);
    for (double& val : vec) {
        val /= norm;
    }
}

// Function to invert a 2x2 matrix
vector<vector<double>> invertMatrix2x2(const vector<vector<double>>& matrix) {
    double det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    return { {matrix[1][1] / det, -matrix[0][1] / det},
            {-matrix[1][0] / det, matrix[0][0] / det} };
}

int main() {
    // Matrix A consisting of submatrices B, C, and D
    vector<vector<double>> A = {
        {8, 0, 0, 0},
        {0, 5, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 10}
    };

    vector<vector<double>> C = {
        {5, 2},
        {2, 2}
    };

    vector<vector<double>> C_inv = invertMatrix2x2(C);

    // Initial vectors for iterations
    vector<double> x1 = { 0.9, 0.55 };
    vector<double> x2 = { -0.45, 0.96 };

    // Lambda and eigenvector storage
    double lambda1 = 8.0;
    double lambda4 = 10.0;
    vector<double> eigvec1 = { 1, 0, 0, 0 };
    vector<double> eigvec4 = { 0, 0, 0, 1 };

    double lambda2 = 0, lambda3 = 0;
    vector<double> eigvec2(2), eigvec3(2);

    // Power method for matrix C (lambda2 and eigenvector)
    vector<double> x = x1;
    for (int iter = 0; iter < 2; iter++) {
        x = multiplyMatrixVector(C, x);
        pair<double, int> maxVal = findMax(x);
        lambda2 = maxVal.first;
        normalizeVector(x);
    }
    eigvec2 = x;

    // Power method for matrix C_inv (lambda3 and eigenvector)
    x = x2;
    for (int iter = 0; iter < 2; iter++) {
        x = multiplyMatrixVector(C_inv, x);
        pair<double, int> maxVal = findMax(x);
        lambda3 = maxVal.first;
        normalizeVector(x);
    }
    lambda3 = 1 / lambda3; // Reciprocal for C_inv
    eigvec3 = x;

    // Comparing all eigenvalues
    vector<pair<double, vector<double>>> eigenvalues = {
        {lambda1, eigvec1},
        {lambda2, { 0, eigvec2[0], eigvec2[1], 0}},
        {lambda3, { 0, eigvec3[0], eigvec3[1], 0}},
        {lambda4, eigvec4}
    };

    auto maxEig = *max_element(eigenvalues.begin(), eigenvalues.end(), [](auto& a, auto& b) { return a.first < b.first; });
    auto minEig = *min_element(eigenvalues.begin(), eigenvalues.end(), [](auto& a, auto& b) { return a.first < b.first; });


    cout << "\nMaximum Eigenvalue: " << maxEig.first << "\nCorresponding Eigenvector: [ ";
    for (double val : maxEig.second) {
        cout << val << " ";
    }
    cout << "]\n";

    cout << "\nMinimum Eigenvalue: " << (int)minEig.first << "\nCorresponding Eigenvector: [ ";
    for (double val : minEig.second) {
        cout << val << " ";
    }
    cout << "]\n";

    normalizeVector(maxEig.second);

    cout << "\nDeflating matrix...\n";
    vector<vector<double>> D = A;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            D[i][j] -= (maxEig.first * maxEig.second[i] * maxEig.second[j]);
        }
    }

    cout << "Deflated Matrix: \n";
    for (const auto& row : D) {
        for (double val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }

    return 0;
}
