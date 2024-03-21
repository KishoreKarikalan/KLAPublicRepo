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

// void solve(int i,int j,float x,float y,vector<float>& shift,float radius,float sizex,float sizey,vector<vector<float>>& directions,set<pair<int,int>>& vis,int val,int diePerRecticle){

//     if(vis.count({i,j}))
//         return;
//     vis.insert({i,j});
    
//     float actualDistance = sqrt(pow(shift[0]+x,2)+pow(shift[1]+y,2));
//     float actualDistance1 = sqrt(pow(shift[0]+x+sizex,2)+pow(shift[1]+y,2));
//     float diagPointDistance = sqrt(pow(shift[0]+(x+sqrt(pow(sizex,2)+pow(sizey,2))),2)+pow(shift[1]+(y+sqrt(pow(sizex,2)+pow(sizey,2))),2));
//     float diagPointDistance1 = sqrt(pow(shift[0]+(x+sqrt(pow(sizex,2)+pow(sizey,2)))-sizex,2)+pow(shift[1]+(y+sqrt(pow(sizex,2)+pow(sizey,2))),2));
//     if(actualDistance<radius || diagPointDistance<radius || diagPointDistance1<radius || actualDistance1<radius){
//         cout<<'('<<i<<','<<j<<"):("<<shift[0]+x<<','<<shift[1]+y<<')'<<endl;

//         for(auto v:directions){
//             int tempx = x+v[0]*sizex;
//             if(i%2 == 0)
//                 tempx += (int)i/2*val;
//             int tempy = y+v[1]*sizey;
//             if(j%2 == 0)
//                 tempy += (int)j/2*val;
            
//             solve(i+v[0],j+v[1],tempx,tempy,shift,radius,sizex,sizey,directions,vis,val,diePerRecticle);
//         }
//     }
// }

void solve(float x,float y,float radius,float sizex,float sizey,vector<float>& dieStreet,vector<float>& recticleStreet,vector<float>& diePerRecticle,vector<vector<float>>& directions,set<pair<int,int>>& vis){
    queue<pair<int,int>> q;
    unordered_map<string,pair<int,int>> hash;
    q.push({0,0});
    hash["00"] = {x,y};

    while(!q.empty()){
        auto curr = q.front();
        q.pop();
        int i = curr.first;
        int j = curr.second;
        
        pair<int,int> llc = hash[to_string(i)+to_string(j)];

        if(vis.count({i,j}))
            continue;
        vis.insert({i,j});

        float bottomLeft = sqrt(pow(llc.first,2) + pow(llc.second,2));
        float bottomRight = sqrt(pow(llc.first+sizex,2) + pow(llc.second,2));
        float topLeft = sqrt(pow(llc.first,2) + pow(llc.second+sizey,2));
        float topRight = sqrt(pow(llc.first+sizex,2) + pow(llc.second+sizey,2));
        
        if(bottomLeft<radius || bottomRight<radius || topLeft<radius || topRight<radius){
            cout<<'('<<i<<','<<j<<"):("<<llc.first<<','<<llc.second<<')'<<endl;
            
            for(auto v:directions){
                int newi = i+v[0];
                int newj = j+v[1];
                q.push({newi,newj});
                hash[to_string(newi)+to_string(newj)]={v[0]*dieStreet[0]+llc.first,v[1]*dieStreet[1]+llc.second};

                
            }
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

    cin>>s;
    vector<float> dieStreet = extractCoord(s);

    cin>>s;
    vector<float> recticleStreet = extractCoord(s);

    cin>>s;
    vector<float> diePerRecticle = extractSize(s);
    
    vector<vector<float>> directions = {{-1,0},{0,-1},{0,1},{1,0}};
    set<pair<int,int>> vis;
    
    solve(diex,diey,diameter/2,sizex,sizey,dieStreet,recticleStreet,diePerRecticle,directions,vis);
    
}