#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define vi vector<int> 

float extract(string s){
    auto pos = s.find(':');
    s = s.substr(pos+1);
    return stof(s);
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("Input/TestCase3.txt","r",stdin);
        freopen("TestCase3.txt","w",stdout);
    #endif
    string s;
    float diameter,points,angle;
    cin>>s;
    diameter = extract(s);
    cin>>s;
    points = extract(s);
    cin>>s;
    angle = extract(s) * 3.14159265358979323846/180;
    
    pair<float,float> endpoint1 = {diameter/2*cos(angle),diameter/2*sin(angle)};
    pair<float,float> endpoint2 = {-endpoint1.first,-endpoint1.second};

    vector<pair<float,float>> res;

    float xdiff,ydiff;
    xdiff = (endpoint1.first - endpoint2.first)/(points-1);
    ydiff = (endpoint1.second - endpoint2.second)/(points-1);

    for(int i=0;i<points-1;i++){
        res.push_back({endpoint2.first,endpoint2.second});
        endpoint2.first += xdiff;
        endpoint2.second += ydiff;
    }
    res.push_back({endpoint2.first,endpoint2.second});
    for(auto p:res){
        cout<<'('<<p.first<<", "<<p.second<<')'<<endl;
    }

}