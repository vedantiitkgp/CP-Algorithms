#include <bits/stdc++.h>

using namespace std;

int N = 1e5 + 2;
int a[N], tree[4*N];

void build(int node, int start, int end){
    if(start == end){
        tree[node] = a[start];
        return;
    }
    int mid = (start + end)/2;
    build(2*node,start,mid);
    build(2*node+1,mid+1,end);
    tree[node] =  tree[2*node] + tree[2*node+1];
}

int query(int node, int start, int end, int l, int r){
     //No Overlap
     if(start>r || end<l){
        return 0;
     }

     //Complete overlap
     if(l<=start && r>=end){
        return tree[node];
     }

     //Partial overlap
     int mid = (start + end)/2;
     return query(2*node,start,mid,l,r) + query(2*node+1,mid+1,end,l,r);
}

int update(int node, int start, int end, int index, int val){
    if(start == end){
        a[start] = val;
        tree[node] = val;
        return ;
    }

    int mid = (start+end)/2;
    if(index<=mid){
        update(2*node,start,mid,index,val);
    }
    else{
        update(2*node+1,mid+1,end,index,val);
    }
    
    tree[node] = tree[2*node] + tree[2*node+1];
    return;
}

int main(){
    int n ;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    build(1,0,n-1);
    return 0;
}