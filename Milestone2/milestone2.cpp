#include <bits/stdc++.h>

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
    
    for(auto c:s){
        if(c == ','){
            res.push_back(temp);
            temp = 0;
        }
        else if(c != '(' && c != ')'){
            temp = temp*10 + (c-'0');
            
        }
    }
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

void solve(int i,int j,float x,float y,vector<float>& shift,float radius,float sizex,float sizey,vector<vector<float>>& directions,set<pair<int,int>>& vis){

    if(vis.count({i,j}))
        return;
    vis.insert({i,j});

    float actualDistance = sqrt(pow(shift[0]+x,2)+pow(shift[1]+y,2));
    float diagPointDistance = sqrt(pow(shift[0]+(x+sqrt(pow(sizex,2)+pow(sizey,2))),2)+pow(shift[1]+(y),2));
    if(actualDistance<=radius || diagPointDistance<=radius){
        cout<<'('<<i<<','<<j<<"):("<<shift[0]+x<<','<<shift[1]+y<<')'<<endl;

        for(auto v:directions){
            solve(i+v[0],j+v[1],x+v[0]*sizex,y+v[1]*sizey,shift,radius,sizex,sizey,directions,vis);
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("Input/TestCase1.txt","r",stdin);
        freopen("TestCase1.txt","w",stdout);
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
    
    vector<vector<float>> directions = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}};
    set<pair<int,int>> vis;
    
    solve(0,0,0,0,shift,diameter/2,sizex,sizey,directions,vis);
    
}