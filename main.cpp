#include <cstdlib>
#include <stdio.h>
#include <iostream>
using namespace std;

int start;
char Edge[100][100];
int temp1, temp2;
char temp3;
int tempvertex[100], vertex[100], length[100], rank[100];
int route[100][100], forkend[100][100][2];
bool end, havevertex, beSearched[100][100], pass[100];
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
                    forkend[o][p][0] = vertex[i];
                    NumofSon++;
                } else if (NumofSon == 1) {
                    forkend[o][p][1] = vertex[i];
                    NumofSon++;
                }
            }
        }
        if (NumofSon == 0) {
            length[o] = p;
            return;
        } else if (NumofSon == 1) {
            p++;
            search(forkend[o][p - 1][0], o, p);
        } else if (NumofSon == 2) {
            if(Edge[m][forkend[o][p][0]] == 'F'){
            p++;
            search(forkend[o][p - 1][0], o, p);
            count2++;
            for (int k = 0; k < p; k++) {
                route[count2][k] = route[o][k];
            }
            search(forkend[o][p - 1][1], count2, p);
        }else if(Edge[m][forkend[o][p][0]] == 'T'){
            p++;
            search(forkend[o][p - 1][1], o, p);
            count2++;
            for (int k = 0; k < p; k++) {
                route[count2][k] = route[o][k];
            }
            search(forkend[o][p - 1][0], count2, p);
        }
        }
    }
}

int main(int argc, char** argv) {
    for (int i = 0; i < 100; i++) {
        pass[i] = true;
    }
    scanf("%d", &start);
    count1 = 0, count2 = 0;
    while (scanf("%d->%d,%c", &temp1, &temp2, &temp3)) {
        Edge[temp1][temp2] = temp3;
        beSearched[temp1][temp2] = false;
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
    search(start, count2, 0);

    count3 = 0;
    for (int i = 0; i <= count2; i++) {
        rank[i] = i;
    }
    for(int i = 0; i <= count2; i++){
        for(int j = 0; j < length[i]; j++){
            if(!beSearched[route[i][j]][route[i][j + 1]]){
                beSearched[route[i][j]][route[i][j + 1]] = true;
                pass[i] = false;
            }
        }
    }
    for(int i = 0; i < 100; i++){
        if(pass[i] == false)
            count3++;
    }
    for (int i = 0; i <= count2; i++) {
        for (int j = i; j <= count2; j++) {
            if (length[rank[i]] > length[rank[j]]) {
                temp2 = rank[i];
                rank[i] = rank[j];
                rank[j] = temp2;
            } else if (length[rank[i]] == length[rank[j]]) {
                for (int k = 0; k <= length[rank[j]]; k++) {
                    if (route[rank[i]][k] > route[rank[j]][k]) {
                        temp2 = rank[i];
                        rank[i] = rank[j];
                        rank[j] = temp2;
                    }
                }
            }
        }
    }
    cout << "CC=" << count3 << endl;
    for (int i = 0; i <= count2; i++) {
        if(pass[rank[i]])
            continue;
        else{
            for (int j = 0; j < length[rank[i]]; j++) {
                cout << route[rank[i]][j] << ',';
            }
            cout << route[rank[i]][length[rank[i]]] << endl;
        }
    }
    
    return 0;
}

