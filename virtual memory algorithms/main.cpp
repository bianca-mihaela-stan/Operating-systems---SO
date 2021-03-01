#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int v[50];
vector<int> vec;
int gasire_j(int low, int n)
{
    int maxx=0, val_max=-1, ok=0;
    //pentru fiecare element din vector
    for(int i=0; i<vec.size(); i++)
    {
        ok=0;
        //caut pozitia urmatoare in v
        for(int q=low+1; q<=n; q++)
        {
            if(vec[i]==v[q])
            {
                cout<<"il caut pe "<<vec[i]<<" si il gasesc la pozitia "<<q<<" in v\n";
                if(maxx<q)
                {
                    cout<<"fac update la minim, deci minn="<<q<<"si val_min="<<i<<"\n";
                    maxx=q;
                    val_max=i;
                }
                ok=1;
                break;
            }
        }
        if(ok==0)
        {
            cout<<"pe "<<vec[i]<<" nu il gasesc deloc\n";
            val_max=i;
            maxx=1e9;
        }
    }
    return val_max;
}

int gasire_j_lru(int low, int n)
{
    int minn=1e9, val_min=-1, ok=0;
    //pentru fiecare element din vector
    for(int i=0; i<vec.size(); i++)
    {
        ok=0;
        //caut pozitia urmatoare in v
        for(int q=low-1; q>=1; q--)
        {
            if(vec[i]==v[q])
            {
                cout<<"il caut pe "<<vec[i]<<" si il gasesc la pozitia "<<q<<" in v\n";
                if(minn>q)
                {
                    cout<<"fac update la minim, deci minn="<<q<<"si val_min="<<i<<"\n";
                    minn=q;
                    val_min=i;
                }
                ok=1;
                break;
            }
        }
//        if(ok==0)
//        {
//            cout<<"pe "<<vec[i]<<" nu il gasesc deloc\n";
//            val_max=i;
//            maxx=1e9;
//        }
    }
    return val_min;
}




void FIFO()
{
    int n;
    cout<<"numarul de cifre: ";
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>v[i];
    }
    cout<<"numarul de pagini: ";
    int x;
    cin>>x;
    int page_faults=0, i=1;
    while(vec.size()<x)
    {
        int ok=0;
        for(int j=0; j<vec.size(); j++)
        {
            if(vec[j]==v[i])
                ok=1;
        }
        if(ok==0)
        {
            cout<<v[i]<<" nu se afla in lista\n";
            vec.push_back(v[i]);
            page_faults++;
        }
        i++;
    }
    int j=0;
    while(i<=n)
    {
        int ok=0;
        for(int q=0; q<vec.size(); q++)
        {
            if(vec[q]==v[i])
                ok=1;
        }
        if(ok==0)
        {
            cout<<v[i]<<" nu se afla in lista, e pus pe pozitia "<<j<<"\n";
            vec[j]=v[i];
            j=(j+1)%x;
            page_faults++;
        }
        i++;
    }
    cout<<"page faults: "<<page_faults;
}

void OPT()
{
    int n;
    cout<<"numarul de cifre: ";
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>v[i];
    }
    cout<<"numarul de pagini: ";
    int x;
    cin>>x;
    int page_faults=0, i=1;
    while(vec.size()<x)
    {
        int ok=0;
        for(int j=0; j<vec.size(); j++)
        {
            if(vec[j]==v[i])
                ok=1;
        }
        if(ok==0)
        {
            cout<<v[i]<<" nu se afla in lista\n";
            vec.push_back(v[i]);
            page_faults++;
        }
        i++;
    }
    int j;//=gasire_j(i, n);
    while(i<=n)
    {
        int ok=0;
        for(int q=0; q<vec.size(); q++)
        {
            if(vec[q]==v[i])
                ok=1;
        }
        if(ok==0)
        {
            j=gasire_j(i, n);
            cout<<v[i]<<" nu se afla in lista, e pus pe pozitia "<<j<<"\n";
            vec[j]=v[i];
            //gasire_j(i, n);
            page_faults++;
        }
        i++;
    }
    cout<<"page faults: "<<page_faults;
}

void LRU()
{
    int n;
    cout<<"numarul de cifre: ";
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>v[i];
    }
    cout<<"numarul de pagini: ";
    int x;
    cin>>x;
    int page_faults=0, i=1;
    while(vec.size()<x)
    {
        int ok=0;
        for(int j=0; j<vec.size(); j++)
        {
            if(vec[j]==v[i])
                ok=1;
        }
        if(ok==0)
        {
            cout<<v[i]<<" nu se afla in lista\n";
            vec.push_back(v[i]);
            page_faults++;
        }
        i++;
    }
    int j;//=gasire_j(i, n);
    while(i<=n)
    {
        int ok=0;
        for(int q=0; q<vec.size(); q++)
        {
            if(vec[q]==v[i])
                ok=1;
        }
        if(ok==0)
        {
            j=gasire_j_lru(i, n);
            cout<<v[i]<<" nu se afla in lista, e pus pe pozitia "<<j<<"\n";
            vec[j]=v[i];
            //gasire_j(i, n);
            page_faults++;
        }
        i++;
    }
    cout<<"page faults: "<<page_faults;
}



int main()
{
    cout << "1: FIFO\n";
    cout << "2: OPT\n";
    cout << "3: LRU\n";
    int optiune;
    cin>> optiune;
    if(optiune==1)
    {
        FIFO();
    }
    if(optiune==2)
    {
        OPT();
    }
    if(optiune==3)
    {
        LRU();
    }
    return 0;
    //7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
}
