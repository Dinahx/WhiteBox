/* 
 * File:   main.cpp
 * Author: huxu
 *
 * Created on 2012年11月13日, 下午6:37
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>
using namespace std;

int start;
char Edge[100][100];
int temp1, temp2;
char temp3;
int tempvertex[100], vertex[100], length[100];
int route[100][100];
bool end, havevertex;
int count1, count2, count3, NumofSon;

void search(int m, int o, int p) {
    end = false;
    if (p >= 2) {
        for (int j = 0; j < p; j++) {
            if (m == route[o][j])
                end = true;
        }
    }
    route[o][p] = m;
    if (end) {
        length[o] = p;
        return;
    } else {
        NumofSon = 0;
        for (int i = 0; i < count3; i++) {
            if (Edge[m][vertex[i]] == 'T' || Edge[m][vertex[i]] == 'F' || Edge[m][vertex[i]] == 'N') {
                if (NumofSon == 0) {
                    temp1 = vertex[i];
                    NumofSon++;
                } else if (NumofSon == 1) {
                    temp2 = vertex[i];
                    NumofSon++;
                }
            }
        }
        if (NumofSon == 0) {
            length[o] = p;
            return;
        } else if (NumofSon == 1) {
            p++;
            search(temp1, o, p);
        } else if (NumofSon == 2) {
            p++;
            search(temp1, o, p);
            for (int k = 0; k <= p; k++) {
                route[o + 1][k] = route[o][k];
            }
            count2++;
            o++;
            search(temp2, o, p);
        }
    }
}

int main(int argc, char** argv) {

    scanf("%d", &start);
    count1 = 0, count2 = 0;
    while (scanf("%d->%d,%c", &temp1, &temp2, &temp3)) {
        Edge[temp1][temp2] = temp3;
        tempvertex[count1] = temp2;
        count1++;
    }

    vertex[0] = start;
    count3 = 1;
    for (int i = 0; i < count1; i++) {
        havevertex = false;
        for (int j = 0; j <= i; j++) {
            if (tempvertex[i] == vertex[j])
                havevertex = true;
        }
        if (!havevertex) {
            vertex[count3] = tempvertex[i];
            count3++;
        }
    }

    for(int i = 0; i < count3; i++){
        cout << vertex[i];
    }
    
    search(start, 0, 0);

    cout << "CC=" << count2 + 1 << endl;
    for (int i = 0; i <= count2; i++) {
        for (int j = 0; j < length[count2]; j++) {
            cout << route[i][j] << ',';
        }
        cout << route[i][length[count2]] << endl;
    }
    return 0;
}

