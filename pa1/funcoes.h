#include<utility>
#include<vector>

using namespace std;

void calculaVizinhos(vector<Colecao> &itens, vector<Colecao> &usuarios);
void calculaSimilaridade(double **matrizDeNotas, vector<Colecao> &itens);
double predicaoBase(double mediaTotal, string item, string usuario, map<string,int> &mapa, vector<Colecao> &itens, vector<Colecao> &usuarios);
double calculaPredicao(double mediaTotal, string item, string usuario, map<string,int> &mapa, vector<Colecao> &itens, vector<Colecao> &usuarios,  double**matrizDeNotas);
