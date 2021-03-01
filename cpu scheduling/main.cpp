#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
int v[20], rem_wt[20], wt[20], last_seen[20];
vector<pair<int, int>> vec;
queue<int> q;

bool e_singurul_proces(int t, int n)
{
    int nr=0;
    for(int i=0; i<n; i++)
    {
        if(vec[i].first>=t && rem_wt[i]>0)
            nr++;
    }
    if(nr>1) return 0;
    else return 1;
}

void bubbleSort(int n)
{
    int i, j;
    for (i = 1; i <= n-1; i++)
    for (j = i+1; j <=n; j++)
        if (v[i] > v[j])
        {
            int temp=v[i];
            v[i]=v[j];
            v[j]=temp;
        }
}

void FCFS()
{
    cout<<"numarul de procese: ";
    int n;
    cin>>n;
    int s=0, sum=0;
    for(int i=1; i<=n; i++)
    {
        cout<<"burst-time-ul procesului "<<i<<": ";
        cin>>v[i];
        sum+=s;
        s+=v[i];
    }
    cout<<"average wating time este: "<<sum<<"/"<<n<<"="<<(float)sum/n;
}

void SJF()
{
    cout<<"numarul de procese: ";
    int n;
    cin>>n;
    int s=0, sum=0;
    for(int i=1; i<=n; i++)
    {
        cout<<"burst-time-ul procesului "<<i<<": ";
        cin>>v[i];
    }
    bubbleSort(n);
    for(int i=1; i<=n; i++)
    {
        sum+=s;
        s+=v[i];
    }
    cout<<"average wating time este: "<<sum<<"/"<<n<<"="<<(float)sum/n;
}

void priority()
{
    cout<<"numarul de procese: ";
    int n;
    cin>>n;
    int s=0, sum=0;
    for(int i=1; i<=n; i++)
    {
        int x, y;
        cout<<"burst-time-ul procesului "<<i<<": ";
        cin>>x;
        cout<<" cu prioritatea: ";
        cin>>y;
        vec.push_back(make_pair(y, x));
    }
    sort(vec.begin(), vec.end());
    for(int i=0; i<n; i++)
    {
        sum+=s;
        s+=vec[i].second;
    }
    cout<<"average wating time este: "<<sum<<"/"<<n<<"="<<(float)sum/n;
}

void RR()
{
    cout<<"numarul de procese: ";
    int n, ultimul=-1;
    cin>>n;
    int s=0, sum=0, suma_timpilor=0, quantum, t=0;
    for(int i=0; i<n; i++)
    {
        int x, y;
        cout<<"burst-time-ul procesului "<<i<<": ";
        cin>>x;
        rem_wt[i]=x;
        wt[i]=0;
        last_seen[i]=0;
        suma_timpilor+=x;
//        cout<<"cu prioritatea: ";
//        cin>>y;
        cout<<"si mementul de arrival: ";
        cin>>y;
        if(y==0) q.push(i);
        vec.push_back(make_pair(y, x));
    }
    cout<<"quantum: ";
    cin>>quantum;
    while(!q.empty())
    {
        int i=q.front();
        q.pop();
        if(vec[i].first<=t && rem_wt[i]>0)
        {
            cout<<"procesul "<<i<<" mai are de executat "<<rem_wt[i]<<"\n";
            if(rem_wt[i]<quantum)
            {
                cout<<"a asteptat inca "<<t-last_seen[i]<<"\n";
                if(ultimul!=i)
                {
                    wt[i]+=t-last_seen[i];
                }
                for(int timp=t+1; timp<=t+rem_wt[i]; timp++)
                {
                    for(int j=0; j<n; j++)
                        if(vec[j].first==timp)
                            q.push(j);
                }
                t+=rem_wt[i];
                rem_wt[i]=0;
                last_seen[i]=t;
                ultimul=i;
            }
            else
            {
                cout<<"a asteptat inca "<<t-last_seen[i]<<"\n";
                if(ultimul!=i)
                {
                    wt[i]+=t-last_seen[i];
                }
                for(int timp=t+1; timp<=t+quantum; timp++)
                {
                    for(int j=0; j<n; j++)
                        if(vec[j].first==timp)
                            q.push(j);
                }
                t+=quantum;
                rem_wt[i]-=quantum;
                cout<<"mai are de executat inca "<<rem_wt[i]<<"\n";
                ultimul=i;
                last_seen[i]=t;
                q.push(i);
            }
        }
    }
    for(int i=0; i<n; i++)
    {
        sum+=wt[i];
    }
    cout<<"average wating time este: "<<sum<<"/"<<n<<"="<<(float)sum/n;
}


int main()
{
    cout << "1: FCFS\n";
    cout << "2: SJF\n";
    cout << "3: priority scheduling\n";
    cout << "4: RR\n";
    cout<< "5: SJF cu arrival time\n";
    int optiune;
    cin>> optiune;
    if(optiune==1)
    {
        FCFS();
    }
    else if(optiune==2)
    {
        SJF();
    }
    else if(optiune==3)
    {
        priority();
    }
    else if(optiune==4)
    {
        RR();
    }
    return 0;
}
//2, 4, 7, 1, 3, 4, 5, 1, 2, 6, 4, 1, 6, 5, 7, 6, 1, 3
