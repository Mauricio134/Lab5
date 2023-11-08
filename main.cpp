#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "kmeancluster.cpp"

using namespace std;

#define NOMBRE_ARCHIVO "datos.csv"
#define dimension 5

int main(){
    ifstream archivo(NOMBRE_ARCHIVO);
    string linea;
    char delimitador = ',';
    vector<pair<vector<float>,string>> data;
    while (getline(archivo, linea))
    {

        stringstream stream(linea);
        string sepalLength, sepalWidth, petalLength, petalWidth, clase;
        float f;
        vector<float> parteFlotante;
        getline(stream, sepalLength, delimitador);
        istringstream(sepalLength) >> f;
        parteFlotante.push_back(f);
        getline(stream, sepalWidth, delimitador);
        istringstream(sepalWidth) >> f;
        parteFlotante.push_back(f);
        getline(stream, petalLength, delimitador);
        istringstream(petalLength) >> f;
        parteFlotante.push_back(f);
        getline(stream, petalWidth, delimitador);
        istringstream(petalWidth) >> f;
        parteFlotante.push_back(f);
        getline(stream, clase, delimitador);
        data.push_back(make_pair(parteFlotante,clase));
    }

    pair<vector<vector<pair<vector<float>,string>>>, vector<pair<vector<float>,string>>> kmeanClustering = kmean(data);

    TXT(kmeanClustering.first);

    txtCentroides(kmeanClustering.second);

    vector<float> WSS = wssPersonal(kmeanClustering.first,kmeanClustering.second);

    float promWSS = wssProm(WSS);

    archivo.close();
    return 0;
}
