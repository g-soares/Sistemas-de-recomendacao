#include<stdio.h>
#include<fstream>
#include<vector>
#include"input.h"
#include"alocacao.h"
#include"funcoes.h"

using namespace std;

int main(int argc, char* argv[]){
	if(argc < 3){
		printf("Sintaxe incorreta\n");
		return 0;
	}

	fstream fRatings(argv[1], ios::in);
	fstream fTargets(argv[2], ios::in);
	map<string,int> mapa;
	vector<Colecao> itens;
	vector<Colecao> usuarios;
	int valorTotal = 0, totalDeItens = 0;
	double mediaTotal = 0.0, **matrizDeNotas;

	if(!fTargets.is_open()){
		printf("falha ao abrir o arquivo %s\n",argv[2] );
	}else  if(!fRatings.is_open()){
		printf("falha ao abrir o arquivo %s\n",argv[1]);
	}

	lerEntrada(fRatings, usuarios, itens, mapa);
	fRatings.close();
	matrizDeNotas = alocaMatriz(itens.size(), usuarios.size());
	
	//preenche a matriz de nota
	for(int i = 0; i < (int)itens.size(); i++){
		totalDeItens += itens[i].num;
		valorTotal += itens[i].valorTotal;
		for(int j = 0; j < (int)itens[i].relacoes.size(); j++){
			R usr = itens[i].relacoes[j];
			matrizDeNotas[i][usr.index] = (double)usr.nota - usuarios[usr.index].media();
			itens[i].denominadorNormalizado += (double)matrizDeNotas[i][usr.index]*(double)matrizDeNotas[i][usr.index];
		}
	}
	calculaVizinhos(itens, usuarios);
	calculaSimilaridade(matrizDeNotas, itens);
	mediaTotal = (double)valorTotal/(double)totalDeItens;
	printf("UserId:ItemId,Prediction");
	vector<pair<string,string>> targets = lerTargets(fTargets);

	for(auto it = targets.begin(); it != targets.end(); ++it){
		printf("\n%s:%s,",it->first.c_str(), it->second.c_str());
		printf("%.14f", calculaPredicao(mediaTotal,it->second, it->first,mapa,itens, usuarios, matrizDeNotas));
	}

	desalocaMatriz(itens.size(), matrizDeNotas);

	return 0;
}