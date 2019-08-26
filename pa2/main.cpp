#include<stdio.h>
#include<fstream>
#include"input.h"

using namespace std;

int main(int argc, char* argv[]){

	if(argc < 4){
		printf("Sintaxe incorreta\n");
		return 0;
	}

	fstream fContent(argv[1],ios::in);
	fstream fRatings(argv[2], ios::in);
	fstream fTargets(argv[3], ios::in);
	map<string,int> mapa;
	vector<Colecao> itens;
	vector<Colecao> usuarios;
	int totalDeItens = 0;
	float mediaGlobal = 0.0;

	if(!fTargets.is_open()){
		printf("falha ao abrir o arquivo %s\n",argv[3] );
	}else  if(!fRatings.is_open()){
		printf("falha ao abrir o arquivo %s\n",argv[2]);
	}else if (!fContent.is_open()){
		printf("falha ao abrir o arquivo %s\n",argv[1]);
	}

	lerEntrada(fRatings, usuarios, itens, mapa);
	totalDeItens = (int)itens.size();
	vector<map<string,string>> conteudo = lerConteudo(fContent, mapa, totalDeItens);
	fRatings.close();
	fContent.close();

	vector<string> featuresItens(totalDeItens);
	vector<string> tokens;
	vector<string> partesItem;
	unsigned int max = 250;

	/*
	Criar um vetor com a representação de cada documento
	Um documento é representado por uma string que contém seus gêneros separados por espaço
	*/
	for(auto elem : conteudo){
		int index = mapa[elem["id"]];
		featuresItens[index] = "";
		
		if(elem["Genre"] != "" && elem["Genre"].find("\"") == string::npos && elem["Genre"].size() < max){
			tokens = separaLinha(elem["Genre"],',');

			for(string s : tokens){
				featuresItens[index] += s;
				featuresItens[index] += " ";
			}
		}

		if(elem["imdbRating"] != "" && elem["imdbRating"].find(".") != string ::npos ) {
			mediaGlobal+= stof(elem["imdbRating"]);
		}
	}

	mediaGlobal /= totalDeItens;
	vector<pair<string,string>> targets = lerTargets(fTargets);
	printf("UserId:ItemId,Prediction");
	//calcula a predição para cada tupla do arquido targets.csv
	for(auto tuplas : targets){
		printf("\n%s:%s,",tuplas.first.c_str(), tuplas.second.c_str());
		double valor = 0;
		string usuario = tuplas.first;
		string item = tuplas.second;

		//verifica se o item e o usuário são desconhecidos
		if(mapa.find(usuario) == mapa.end() && mapa.find(item) == mapa.end()){
			valor = mediaGlobal;
		}//verifica se o usuário é desconhecido
		else if(mapa.find(usuario) == mapa.end()){
			if(conteudo[mapa[item]]["imdbRating"] != ""){
				valor = stof(conteudo[mapa[item]]["imdbRating"]);
			}else{
				valor = mediaGlobal;
			}
		}//verifica se o item é desconhecido
		else if(mapa.find(item) == mapa.end()){
			valor = usuarios[mapa[usuario]].media();
		}//calcula a nota baseado nas features do item e no histórico do usuário
		else{
			vector<string> features = separaLinha(featuresItens[mapa[item]], ' ');
			vector<R> itensConsumidos = usuarios[mapa[usuario]].relacoes;
			valor = usuarios[mapa[usuario]].media();
			for(string f : features){
				int count = 0, nota = 0;
				for(R tupla : itensConsumidos){
					auto aux = featuresItens[tupla.index].find(f);
					while(aux != string::npos){
						count++;
						nota += tupla.nota;
						aux = featuresItens[tupla.index].find(f,aux+1);
					}
				}
				if(count > 0){
					valor += ((double)nota/count) - usuarios[mapa[usuario]].media();
				}
			}
		}

		if(valor > 10.0){
			valor = 10.0;
		}else if (0.0 > valor){
			valor = 0.0;
		}

		printf("%.14f",valor );

	}

	return 0;
}