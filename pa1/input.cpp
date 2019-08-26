#include"input.h"
#include<sstream>
#include<fstream>

using namespace std;

vector<string> separaLinha(string entrada, char delimitador){
	vector<string> tokens;
	string token;
	istringstream linha{entrada};
	while(getline(linha, token, delimitador)){
		tokens.push_back(token);
	}
	return tokens;
}

void adicionaElemento(vector<Colecao> &vetor, string nome, string item, int count){
	Colecao aux;
	aux.id = count;
	aux.identificador = nome;
	vetor.push_back(aux);
}

void atualizaElemento(vector<Colecao> &vetor, int pos, int item, string nota){
	vetor[pos].valorTotal +=(double)stoi(nota);
	vetor[pos].num++;
	vetor[pos].relacoes.push_back(R(item,stoi(nota)));
}

void lerEntrada(fstream &arquivo, vector<Colecao> &usuarios, vector<Colecao> &itens, map<string,int> &mapa){
	string usuario, item, nota, entrada;
	int countItem = 0;
	int countUser = 0;

	//ignora o cabeçalho
	getline(arquivo,entrada);

	while(!arquivo.eof()){
		getline(arquivo, entrada);
		if (entrada.size() > 0){
			vector<string> tokens = separaLinha(entrada, ':');
			usuario = tokens[0];
			tokens = separaLinha(tokens[1], ',');
			item = tokens[0];
			nota = tokens[1];

			if(mapa.find(item) == mapa.end()){
				mapa[item] = countItem;
				adicionaElemento(itens, item, usuario, countItem);
				countItem++;
			}

			if(mapa.find(usuario) == mapa.end()){
				mapa[usuario] = countUser;
				adicionaElemento(usuarios, usuario, item, countUser);
				countUser++;
			}
			atualizaElemento(usuarios, mapa[usuario], mapa[item], nota);
			atualizaElemento(itens, mapa[item], mapa[usuario], nota);
		}
	}
}

vector<pair<string,string>> lerTargets(fstream &arquivo){
	vector<pair<string,string>> v;
	string entrada;

	//ignora o cabeçalho
	getline(arquivo, entrada);

	while(!arquivo.eof()){
		getline(arquivo, entrada);
		if(entrada.size() > 0){
			vector<string> tokens = separaLinha(entrada, ':');
			v.push_back(make_pair(tokens[0],tokens[1]));
		}
	}

	return v;
}