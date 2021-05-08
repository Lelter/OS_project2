#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
int N = 14;
int start = 90;
struct cipan {
    string name;
    int pos;
    int dis;

};


vector<cipan> my;

void init() {
    ifstream myfile("../input.txt");
    for (int i = 0; i < N; ++i) {
        cipan temp;
        myfile >> temp.name >> temp.pos;
        temp.dis = 0;
        my.push_back(temp);
    }
}

void FIFS() {
    vector<cipan> temp;
    temp = my;
    int cur = start;
    double sum = 0;
    cout << "磁盘名字" << "\t" << "磁盘位置" << "\t" << "移动道数" << endl;
    for (int i = 0; i < temp.size(); ++i) {
        temp[i].dis = abs(cur - temp[i].pos);
        sum += temp[i].dis;
        cout << temp[i].name << "\t" << "\t" << temp[i].pos << "\t" << "\t" << temp[i].dis << endl;
        cur = temp[i].pos;
    }
    cout << "平均移动道数为：" << sum / N << endl;
}

bool cmp1(const cipan &s1, const cipan &s2) {
    return s1.dis > s2.dis; //从大到小
}

bool cmp2(const cipan &s1, const cipan &s2) {
    return s1.pos < s2.pos;
}

void SSTF() {
    vector<cipan> temp;
    temp = my;
    int cur = start;
    double sum = 0;
    cout << "磁盘名字" << "\t" << "磁盘位置" << "\t" << "移动道数" << endl;
    while (!temp.empty()) {
        for (int i = 0; i < temp.size(); ++i) {
            temp[i].dis = abs(cur - temp[i].pos);
        }
        sort(temp.begin(), temp.end(), cmp1);
        cout << temp.back().name << "\t" << "\t" << temp.back().pos << "\t" << "\t" << temp.back().dis << endl;
        cur = temp.back().pos;
        sum += temp.back().dis;
        temp.pop_back();
    }
    cout << "平均移动道数为：" << sum / N << endl;
}

void SCAN() {
    vector<cipan> temp;
    vector<cipan> left;
    vector<cipan> right;
    temp = my;
    int cur = start;
    double sum = 0;
    int min_start = 100000;
    int min_start_pos = 0;
    int choose = 1;//0表示左边，1表示右边
    cout << "磁盘名字" << "\t" << "磁盘位置" << "\t" << "移动道数" << endl;
    for (int i = 0; i < temp.size(); ++i) {
        temp[i].dis = abs(start - temp[i].pos);
    }
    for (int i = 0; i < temp.size(); ++i) {
        if (temp[i].dis < min_start) {
            min_start = temp[i].dis;
            min_start_pos = i;
        }
    }
    min_start=temp[min_start_pos].pos;
    sort(temp.begin(), temp.end(), cmp2);
    for (int i = 0; i < temp.size(); ++i) {
        if (temp[i].pos <= min_start) {
            left.push_back(temp[i]);
        } else {
            right.push_back(temp[i]);
        }
    }
    reverse(left.begin(), left.end());
    vector<cipan> temp1;
    temp1 = right;
    temp1.insert(temp1.end(), left.begin(), left.end());
    for (int i = 0; i < temp1.size(); ++i) {
        temp1[i].dis = abs(cur - temp1[i].pos);
        cout << temp1[i].name << "\t\t" << temp1[i].pos << "\t\t" << temp1[i].dis << endl;
        sum += temp1[i].dis;
        cur = temp1[i].pos;

    }
    cout << "平均移动道数为：" << sum / N << endl;
}


int main() {
    init();
    cout << "1.先来先服务算法" << endl;
    cout << "2.最短优先算法" << endl;
    cout << "3.电梯调度算法" << endl;
    int a = 0;
    while (true) {
        cin >> a;
        if (a == 1)
            FIFS();
        if (a == 2)
            SSTF();
        if (a == 3)
            SCAN();
        if (a == 4)
            break;
    }
}
