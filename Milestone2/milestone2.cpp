#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <set>
#include <utility>
#include <fstream>

using namespace std;

#define ll long long int
#define vi vector<int> 

float extract(string s){
    auto pos = s.find(':');
    s = s.substr(pos+1);
    return stof(s);
}

vector<float> extractCoord(string s){
    auto pos = s.find(':');
    s = s.substr(pos+1);
    vector<float> res;
    float temp=0;
    bool sign=false;
    for(auto c:s){
        if(c == ','){
            if(sign)
                temp*=-1;
            res.push_back(temp);
            sign = false;
            temp = 0;
        }
        else if(c == '-')
            sign = true;
        else if(c != '(' && c != ')'){
            temp = temp*10 + (c-'0');
            
        }
    }
    if(sign)
        temp*=-1;
    res.push_back(temp);
    
    return res;
}

vector<float> extractSize(string s){
    vector<float> res;
    auto pos = s.find(':');
    s = s.substr(pos+1);
    
    float temp=0;
    for(auto c:s){
        if(c == 'x'){
            res.push_back(temp);
            temp = 0;
        }
        else{
            temp = temp*10 + (c-'0');
        }
    }
    res.push_back(temp);
    return res;
}

void solve(float x,float y,float radius,float sizex,float sizey,vector<vector<float>>& directions,set<pair<int,int>>& vis){

    queue<pair<int,int>> q;
    q.push({0,0});

    while(!q.empty()){
        auto curr = q.front();
        q.pop();
        int i = curr.first;
        int j = curr.second;

        if(vis.count({i,j}))
            continue;
        vis.insert({i,j});

        float bottomLeft = sqrt(pow(x+i*sizex,2) + pow(y+j*sizey,2));
        float bottomRight = sqrt(pow(x+(i+1)*sizex,2) + pow(y+j*sizey,2));
        float topLeft = sqrt(pow(x+i*sizex,2) + pow(y+(j+1)*sizey,2));
        float topRight = sqrt(pow(x+(i+1)*sizex,2) + pow(y+(j+1)*sizey,2));
        
        if(bottomLeft<radius || bottomRight<radius || topLeft<radius || topRight<radius){
            cout<<'('<<i<<','<<j<<"):("<<x+i*sizex<<','<<y+j*sizey<<')'<<endl;
            
            for(auto v:directions){
                int newi = i+v[0];
                int newj = j+v[1];
                q.push({newi,newj});
            }
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("Input/TestCase4.txt","r",stdin);
        freopen("TestCase4.txt","w",stdout);
    #endif

    string s;
    float diameter,sizex,sizey,diex,diey;
    cin>>s;
    diameter = extract(s);
    cin>>s;
    vector<float> size = extractSize(s);
    
    sizex = size[0];
    sizey = size[1];
    
    cin>>s;
    vector<float> shift = extractCoord(s);
    
    cin>>s;
    vector<float> die = extractCoord(s);

    diex = die[0]-sizex/2;
    diey = die[1]-sizey/2;

    shift[0] = diex;
    shift[1] = diey;
    
    vector<vector<float>> directions = {{-1,0},{0,-1},{0,1},{1,0}};
    set<pair<int,int>> vis;
    
    solve(diex,diey,diameter/2,sizex,sizey,directions,vis);
    
    return 0;
}
