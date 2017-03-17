// FC14ѡ�ֹ��߰�
// Created by sugar10w, 2017.03
// Last modified by sugar10w, 2017.03.17

#ifndef __FC14_USER_TOOLBOX__
#define __FC14_USER_TOOLBOX__

#include "ai.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

using namespace std; 

// ��������?
const TPosition BRIGDES[] = {{10, 7}, {12, 12}, {13, 2}, {4, 16}, {0, 19}};

// ���
float rand_f();

// ��ȡ TMaskMap
typedef vector<vector<bool> > TMaskMap;
TMaskMap new_TMaskMap(size_t x, size_t y);
TMaskMap new_TMaskMap(const Info& info);
TMaskMap get_border_TMaskMap(const Info& info);
bool check_mask_validity(const TMaskMap& mask, const Info& info);

// ��ȡ�����پ���
unsigned int get_distance(TPosition a, TPosition b);
// ���������Ƿ�Ϸ�
bool check_birth_pos_validity(vector<TPosition>& posSelected, TPosition pos);
// ����ɨ�ף������Χ8���ж��� �ж�/�Ѻ� ��
int count_enemy(int x,int y, const Info& info);
int count_friend(int x,int y, const Info& info);

// ��mask�Ϸ��ò�����size��ը��
vector<TMilitaryCommand> auto_military(const Info& info, TMaskMap& mask, int money, int size);

// ���������
TPosition random_birthplace(vector<TPosition> posSelected, BaseMap* map);

// �Զ�ѡ���׶�
TPosition auto_capital(const Info& info);

// ����
template<typename Index, typename T> class MaxHeap {

public:
    MaxHeap() : n(0) { }

    void add(Index i, T t) {
        num_tree.push_back(i);
        obj_tree.push_back(t);
        n = num_tree.size();

        FilterUp(n-1);
    }

    Index getMax(T& t) {
        if (n>0) {
            t = obj_tree[0];
            return num_tree[0];
        }
        else {
            return -1;
        }
    }

    bool removeMax() {
        if (n<=0) return false;

        num_tree[0] = num_tree[n-1]; obj_tree[0] = obj_tree[n-1];
        --n;
        FilterDown(0);
        return true;
    }

private:

    void FilterUp(int start) {

        Index num_temp = num_tree[start];
        T T_temp = obj_tree[start];
        
        int curr = start;
        int father = (curr - 1)/2;

        while (curr>0) {
            if (num_tree[father] >= num_temp) break;
            else {
                num_tree[curr] = num_tree[father];  obj_tree[curr] = obj_tree[father]; 
                curr = father;
                father = (curr - 1)/2;
            }
        }
        num_tree[curr] = num_temp;  obj_tree[curr] = T_temp;
    }

    void FilterDown(int start) {
        
        Index num_temp = num_tree[start];
        T T_temp = obj_tree[start];

        int curr = start;
        int son = curr*2+1;

        while (son<n) {
            // test l-son and r-son
            if (son<n-1 && num_tree[son]<num_tree[son+1]) son = son+1;
            if (num_tree[son] <= num_temp) break;
            else {
                num_tree[curr] = num_tree[son]; obj_tree[curr] = obj_tree[son];
                curr = son;
                son = curr*2+1;
            }
        }

        num_tree[curr] = num_temp; obj_tree[curr] = T_temp;
    }

    int n;
    vector<Index> num_tree;
    vector<T> obj_tree;

};

#endif

