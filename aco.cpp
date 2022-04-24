#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> costo;
vector<vector<float>> feromonas;
vector<vector<float>> t;
int ktotal=10; // numero de hormigas
int N=4; // numero de nodos

void llenarcosto()
{
    vector<int> v;

    v.push_back(0);
    v.push_back(5);
    v.push_back(15);
    v.push_back(1);
    costo.push_back(v);
    v.clear();

    v.push_back(5);
    v.push_back(0);
    v.push_back(4);
    v.push_back(8);
    costo.push_back(v);
    v.clear();

    v.push_back(15);
    v.push_back(4);
    v.push_back(0);
    v.push_back(1);
    costo.push_back(v);
    v.clear();

    v.push_back(1);
    v.push_back(8);
    v.push_back(1);
    v.push_back(0);
    costo.push_back(v);

    vector<float>v1;
    v1.assign(4,1);

    feromonas.assign(4,v1);

    t.assign(4,v1);


    return;
}

void imprimircosto()
{
    for(auto& i:costo)
    {
        for(auto& j:i)
            cout<<j<<" ";
        cout<<endl;
    }

    cout<<endl;

    for(auto& i:feromonas)
    {
        for(auto& j:i)
            cout<<j<<" ";
        cout<<endl;
    }

}

vector<int> recorridoaleatorio()
{
    vector<int> recorrido;
    vector<bool> visitado;
    visitado.assign(4,false);
    int nodoactual=0;

    visitado.at(0)=true;
    recorrido.push_back(0);

    while(nodoactual!=3)
    {
        int nodosig=0;
        while(visitado.at(nodosig)==true)
        {
           nodosig= rand()%(N-1)+1;
           //cout<<nodosig<<endl;
        }

        nodoactual=nodosig;
        visitado.at(nodoactual)=true;
        recorrido.push_back(nodosig);
    }


    return recorrido;
}


int elegircamino(int nodo)
{
    vector<float> probabilidades;
    probabilidades.assign(4,0);
    int nodosig;
    float acum=0;
    for(int i=0;i<N;i++)
    {
        if(i==nodo)
            continue;

        float proba=feromonas.at(nodo).at(i)*(1/(float)costo.at(nodo).at(i));
        acum+=proba;
        probabilidades.at(i)=proba;
    }

    float maximo=0;
    int indice;
    for(int i=0;i<N;i++)
    {
        if(i==nodo)
            continue;
        probabilidades.at(i)/=acum;
        if(probabilidades.at(i)>maximo)
        {
            maximo=probabilidades.at(i);
            indice=i;
        }

    }

    nodosig=indice;

    return nodosig;
}



vector<int> recorridonormal()
{
    vector<int> recorrido;
    vector<bool> visitado;
    visitado.assign(4,false);
    int nodoactual=0;
    visitado.at(0)=true;
    recorrido.push_back(0);

    while(nodoactual!=3)
    {
        int nodosig=0;
        while(visitado.at(nodosig)==true)
        {
           nodosig= elegircamino(nodoactual);
           //cout<<nodosig<<endl;
        }

        nodoactual=nodosig;
        visitado.at(nodoactual)=true;
        recorrido.push_back(nodosig);
    }
    return recorrido;
}




int costorecorrido(vector<int> &v)
{
    int nodoactual=0;
    int tamano=v.size();
    int costorecorrido=0;

    for(int i=1;i<tamano;i++)
    {
        int nodosig=v.at(i);
        costorecorrido+=costo.at(nodoactual).at(nodosig);
        nodoactual=nodosig;

    }
    return costorecorrido;
}

void colocarferomonas(vector<int> &recorrido,int costo)
{
    float delta=1/(float) costo;
    int nodoactual=0;
    int nodosig=recorrido.at(1);
    int tamano=recorrido.size();
    float acum=feromonas.at(nodoactual).at(nodosig)*(1-0.2);
    for(int i=1;i<tamano;i++)
    {
        nodosig=recorrido.at(i);
        feromonas.at(nodoactual).at(nodosig)=acum+delta;
        feromonas.at(nodosig).at(nodoactual)=acum+delta;
        nodoactual=nodosig;
    }


}

int main()
{
    llenarcosto();
   // imprimircosto();

    for(int k=1;k<=ktotal;k++)
    {
        cout<<"HORMIGA #"<<k<<endl;
        vector<int> recorrido;

        if(k<4)
            recorrido=recorridoaleatorio();
        else
            recorrido=recorridonormal();


        for(auto& i:recorrido)
            cout<<i<<" ";
        cout<<endl;


        int costorec=costorecorrido(recorrido);
        //cout<<costorec<<endl;


        colocarferomonas(recorrido, costorec);

        cout<<endl;
        //cout.precision(2);
        for(auto& i:feromonas)
        {
            for(auto& j:i)
                cout<<j<<" ";

            cout<<endl;

        }
        cout<<endl;
    }
    return 0;
}
