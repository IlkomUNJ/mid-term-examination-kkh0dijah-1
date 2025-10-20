#ifndef CUSTOMMATRIX_H
#define CUSTOMMATRIX_H

#include <iostream>

using namespace std;

class CustomMatrix {
public:
    bool mat[7][7] = {0};

    CustomMatrix() {
        for (int i = 0; i < 7; ++i)
            for (int j = 0; j < 7; ++j)
                mat[i][j] = false;
    }

    CustomMatrix(bool m[7][7]) {
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                mat[i][j] = m[i][j];
            }
        }
    }

    void fillMatrix(bool m[7][7]) {
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                mat[i][j] = m[i][j];
            }
        }
    }

    bool isNonEmpty() const {
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                if (mat[i][j]) {
                    return true;
                }
            }
        }
        return false;
    }

 
    void dump() const {
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                // Mencetak '1' untuk segmen (true), '0' untuk latar belakang (false)
                cout << (mat[i][j] ? '1' : '0') << " ";
            }
            cout << endl;
        }
    }
};

#endif // CUSTOMMATRIX_H
