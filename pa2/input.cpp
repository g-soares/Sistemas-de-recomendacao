#include"input.h"
#include<sstream>
#include<fstream>
#include<iostream>

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

vector<map<string,string>> lerConteudo(fstream &arquivo,  map<string,int> &mapa, int max){
	string entrada,aux ;
	int ini, tam;
	vector<map<string,string>> conteudo(max);
	
	//ignora o cabeçalho
	getline(arquivo,entrada);

	while(!arquivo.eof()){
		getline(arquivo, entrada);
		if(entrada.size() > 0){
			map<string, string> item;
			item["id"] = entrada.substr(0,8);
			
			ini = entrada.find("Title")+8;
			tam = entrada.find("Year")-3 -ini;
			verificaString(item, entrada.substr(ini,tam), "Title");

			ini = tam+7+3+ini;
			tam = entrada.find("Rated")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "Year");

			ini = tam+8+3+ini;
			tam = entrada.find("Released")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "Rated");

			ini = tam+11+3+ini;
			tam = entrada.find("Runtime") -3-ini;
			verificaString(item, entrada.substr(ini,tam), "Released");

			ini = tam+10+3+ini;
			tam = entrada.find("Genre")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "Runtime");

			ini = tam+8+3+ini;
			tam = entrada.find("Director")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "Genre");

			ini = tam+11+3+ini;
			tam = entrada.find("Writer")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "Director");

			ini = tam+9+3+ini;
			tam = entrada.find("Actors")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "Writer");

			ini = tam+9+3+ini;
			tam = entrada.find("Plot")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "Actors");

			ini = tam+7+3+ini;
			tam = entrada.find("Language")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "Plot");

			ini = tam+11+3+ini;
			tam = entrada.find("Country")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "Language");

			ini = tam+10+3+ini;
			tam = entrada.find("Awards")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "Country");

			ini = tam+9+3+ini;
			tam = entrada.find("Poster")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "Awards");

			ini = tam+9+3+ini;
			tam = entrada.find("Metascore")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "Poster");

			ini = tam+12+3+ini;
			tam = entrada.find("imdbRating")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "Metascore");

			ini = tam+13+3+ini;
			tam = entrada.find("imdbVotes")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "imdbRating");

			ini = tam+12+3+ini;
			tam = entrada.find("imdbID")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "imdbVotes");

			ini = tam+9+3+ini;
			tam = entrada.find("Type")-3-ini;
			verificaString(item, entrada.substr(ini,tam), "imdbID");

			ini = tam+7+3+ini;
			tam =entrada.find("Response")-3-ini;
			verificaString(item, entrada.substr(ini,tam),"Type");

			ini = tam+11+3+ini;
			tam = entrada.find("}")-1-ini;
			verificaString(item, entrada.substr(ini,tam), "Response");

			if(mapa.find(item["id"]) != mapa.end()){
				conteudo.at(mapa[item["id"]]) = item;
			}
		}
	}
	return conteudo;
}

void verificaString(map<string, string> &item, string entrada, string tag){
	if(entrada == "N/A"){
		item[tag] = "";
	}
	else{
		item[tag] = entrada;
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