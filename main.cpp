#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

int start, extvertex[100],temp1, temp2, temp4, tempvertex[100], vertex[100], length[100], rank[100], route[500][500], forkend[100][100][2], count1, count2, count3, NumofSon, count4;
char Edge[500][500], temp3, ext[100][3], tempext[3];
bool end, havevertex, beSearched[500][500], pass[100], startchange;

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
            if (Edge[m][forkend[o][p][0]] == 'F') {
                p++;
                search(forkend[o][p - 1][0], o, p);
                count2++;
                for (int k = 0; k < p; k++) {
                    route[count2][k] = route[o][k];
                }
                search(forkend[o][p - 1][1], count2, p);
            } else if (Edge[m][forkend[o][p][0]] == 'T') {
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
    count1 = 0, count2 = 0, count4 = 0;
    while (scanf("%d->%d,%c", &temp1, &temp2, &temp3)) {
        Edge[temp1][temp2] = temp3;
        beSearched[temp1][temp2] = false;
        tempvertex[count1] = temp2;
        count1++;
    }

    scanf("EXT");
    while (scanf("%d,%s", &temp4, tempext)) {
        extvertex[count4] = temp4;
        strcpy(ext[count4], tempext);
        count4++;
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
    startchange = false;
    if (count4 > 0) {
        for (int i = 0; i < count4; i++) {
            if (extvertex[i] == start)
                startchange = true;
            vertex[count3] = extvertex[i] * 10 + 1;
            count3++;
            vertex[count3] = extvertex[i] *10 + 2;
            count3++;
        }
        for (int i = 0; i < count4; i++) {
            for (int j = 0; j < count3; j++) {
                if (Edge[vertex[j]][extvertex[i]] == 'T') {
                    Edge[vertex[j]][extvertex[i]] = 'M';
                    Edge[vertex[j]][extvertex[i] * 10 + 1] = 'T';
                } else if (Edge[vertex[j]][extvertex[i]] == 'F') {
                    Edge[vertex[j]][extvertex[i]] = 'M';
                    Edge[vertex[j]][extvertex[i] * 10 + 1] = 'F';
                } else if (Edge[vertex[j]][extvertex[i]] == 'N') {
                    Edge[vertex[j]][extvertex[i]] = 'M';
                    Edge[vertex[j]][extvertex[i] * 10 + 1] = 'N';
                } else if (Edge[extvertex[i]][vertex[j]] == 'T') {
                    Edge[extvertex[i]][vertex[j]] = 'M';
                    Edge[extvertex[i] * 10 + 2][vertex[j]] = 'T';
                    if (ext[i][0] == 'O') {
                        Edge[extvertex[i] * 10 + 1][extvertex[i] * 10 + 2] = 'F';
                        Edge[extvertex[i] * 10 + 1][vertex[j]] = 'T';
                    }
                } else if (Edge[extvertex[i]][vertex[j]] == 'F') {
                    Edge[extvertex[i]][vertex[j]] = 'M';
                    Edge[extvertex[i] * 10 + 2][vertex[j]] = 'F';
                    if (ext[i][0] == 'A') {
                        Edge[extvertex[i] * 10 + 1][extvertex[i] * 10 + 2] = 'T';
                        Edge[extvertex[i] * 10 + 1][vertex[j]] = 'F';
                    }
                }
            }
        }
    }
    if (startchange)
        search(start * 10 + 1, count2, 0);
    else
        search(start, count2, 0);

    count3 = 0;
    for (int i = 0; i <= count2; i++) {
        rank[i] = i;
    }
    for (int i = 0; i <= count2; i++) {
        for (int j = 0; j < length[i]; j++) {
            if (!beSearched[route[i][j]][route[i][j + 1]]) {
                beSearched[route[i][j]][route[i][j + 1]] = true;
                pass[i] = false;
            }
        }
    }
    for (int i = 0; i < 100; i++) {
        if (pass[i] == false)
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
                    if (route[rank[i]][k] < route[rank[j]][k])
                        break;
                    else if (route[rank[i]][k] > route[rank[j]][k]) {
                        temp2 = rank[i];
                        rank[i] = rank[j];
                        rank[j] = temp2;
                        break;
                    }
                }
            }
        }
    }

    cout << "CC=" << count3 << endl;
    for (int i = 0; i <= count2; i++) {
        if (pass[rank[i]])
            continue;
        else {
            for (int j = 0; j < length[rank[i]]; j++) {
                cout << route[rank[i]][j] << ',';
            }
            cout << route[rank[i]][length[rank[i]]] << endl;
        }
    }

    return 0;
}

