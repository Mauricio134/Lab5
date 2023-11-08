#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

#define cantClusters 3

float distanciaEuclidiana(const vector<float> & p1, const vector<float> & p2){
    float distancia = 0;
    for(int i = 0; i < p1.size(); i++){
        distancia += pow((p1[i]-p2[i]),2);
    }
    distancia = sqrt(distancia);
    return distancia;
}

vector<float> cambiarCentroide(const vector<pair<vector<float>,string>> & conjunto){
    vector<float> nuevoCentro;
    int filas = conjunto.size();
    int columnas = conjunto[0].first.size();
    for(int i = 0; i < columnas; i++){
        float suma = 0;
        for(int j = 0; j < filas; j++){
            suma += conjunto[j].first[i];
        }
        suma /= filas;
        nuevoCentro.push_back(suma);
    }
    return nuevoCentro;
}

pair<vector<vector<pair<vector<float>,string>>>,vector<pair<vector<float>,string>>> kmean(const vector<pair<vector<float>,string>> & datos){
    srand(time(NULL));
    vector<pair<vector<float>,string>> centroides(cantClusters);
    vector<vector<pair<vector<float>,string>>> grupo(cantClusters);
    for(int i = 0; i < cantClusters; i++){
        centroides[i] = datos[rand() % datos.size()];
    }
    for(int i = 0; i < datos.size(); i++){
        float distActual = 1e9;
        int cluster = 0;
        for(int j = 0; j < centroides.size(); j++){
            float nuevaDistancia = distanciaEuclidiana(datos[i].first, centroides[j].first);
            if(nuevaDistancia < distActual){
                distActual = nuevaDistancia;
                cluster = j;
            }
        }
        grupo[cluster].push_back(datos[i]);
        centroides[cluster].first = cambiarCentroide(grupo[cluster]);
        centroides[cluster].second = " ";
    }
    return make_pair(grupo, centroides);
}

vector<float> wssPersonal(const vector<vector<pair<vector<float>,string>>> & kmean, const vector<pair<vector<float>,string>> & centroides){
    vector<float> WSS;
    for(int i = 0; i < kmean.size(); i++){
        float suma = 0;
        for(int k = 0; k < kmean[i].size(); k++){
            suma += distanciaEuclidiana(kmean[i][k].first, centroides[i].first);
        }
        WSS.push_back(suma);
    }
    return WSS;
}

float wssProm(const vector<float> & WSS){
    ofstream archivo("WSS.txt");
    float suma = 0;
    for(int i = 0; i < WSS.size(); i++){
        suma += WSS[i];
    }
    suma /= WSS.size();
    archivo << suma;
    return suma;
}

void TXT(const vector<vector<pair<vector<float>,string>>> & KMEAN){
    ofstream archivo("clusters.txt");
    for(int i = 0; i < KMEAN.size(); i++){
        for(int j = 0; j < KMEAN[i].size(); j++){
            archivo << KMEAN[i][j].first[0] << " " << KMEAN[i][j].first[1] << "\n";
        }
        archivo << "************\n";
    }
}
void txtCentroides(const vector<pair<vector<float>,string>> & centroides){
    ofstream archivo("centroides.txt");
    for(int i = 0; i < centroides.size(); i++){
        archivo << centroides[i].first[0] << " " << centroides[i].first[1] << "\n";
        archivo << "************\n";
    }

}