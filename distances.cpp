#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <map>
#include <iomanip>

using namespace std;

template <typename T, typename R>
R eu(vector<T>a, vector<T>b)
{
    R sum = 0;
    for (int i = 0; i < a.size(); i++)
    {
        sum += pow(b[i]-a[i], 2);
    }
    return sqrt(sum);
}

template <typename T>
void print(vector<T> v)
{
    copy(v.begin(), v.end(), std::ostream_iterator<T>(std::cout, " "));
    cout << endl;
}

int rand1000()
{
    return rand()%1000;
}

float roundoff(float value, unsigned char prec)
{
  float pow_10 = pow(10.0f, (float)prec);
  return round(value * pow_10) / pow_10;
}

int main(int argc, char* argv[])
{
    // Obtener parametros de entrada
    if (argc != 3){
        cout << "usage: distances [#vectores][#dimensiones]" << endl;
        return 1;
    }
    const int cant_v = atoi(argv[1]);
    const int d = atoi(argv[2]);

    // Generar vectores
    std::srand(std::time(0));
    vector< vector<int> > vectores(cant_v);
    for (int i = 0; i < cant_v; i++)
    {
        vectores[i].resize(d,0);
        std::generate(vectores[i].begin(),vectores[i].end(),rand1000);
    }

    // Comparar y almacenar distancias truncadas
    vector<float> distancias;
    for (int i = 1; i < cant_v; i++)
    {
        float dist = eu<int,float>(vectores[0],vectores[i]);
        distancias.push_back(roundoff(dist,1));
    }
    
    // Contar elementos
    std::map<float,int> histograma;
    float min = *std::min_element(distancias.begin(), distancias.end());
    float max = *std::max_element(distancias.begin(), distancias.end());

    for (int i = 0; i < distancias.size(); i++)
    {
        if (histograma.count(distancias[i]))
            histograma[distancias[i]]++;
        else
            histograma[distancias[i]] = 1;
    }

    // Guardarlos en un archivo csv
    ofstream data;
    string filename("files/");
    filename += argv[1];
    filename += "v-";
    filename += argv[2];
    filename += "d.csv";
    data.open(filename);
    data << std::setprecision(2) << std::fixed;
    data << "distancia,cant" << endl;
    for (auto i : histograma)
        data << i.first << "," << i.second << endl;
    return 0;
}