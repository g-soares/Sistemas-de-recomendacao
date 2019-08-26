#include"estruturas.h"

using namespace std;

vector<string> separaLinha(string entrada, char delimitador);
void adicionaElemento(vector<Colecao> &mapa, string nome, string item, int count);
void atualizaElemento(vector<Colecao> &vetor, int pos, int item, string nota);
void lerEntrada(fstream &arquivo, vector<Colecao> &usuarios, vector<Colecao> &itens, map<string,int> &mapa);
vector<pair<string,string>> lerTargets(fstream &arquivo);
vector<map<string,string>> lerConteudo(fstream &arquivo,  map<string,int> &mapa, int max);
void verificaString(map<string, string> &item, string entrada, string tag);