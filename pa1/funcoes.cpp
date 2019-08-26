#include<math.h>
#include"estruturas.h"
#include"funcoes.h"

using namespace std;

//calcula a similaridade de todos os itens
void calculaSimilaridade(double **matrizDeNotas, vector<Colecao> &itens){
	double numerador;
	for(int i = 0; i < (int)itens.size(); i++){

		//calcula a similaridade utilizando somente os itens da lista de vizinhos
		for(int j = 0; j < (int)itens[i].vizinhos.size(); j++){
			numerador = 0.0;
			int vizinho = itens[i].vizinhos[j];

			//otimização para evitar calcular similaridade(i,j) e similaridade(j,i)
			//também evita similaridade(i,i)
			if(i < vizinho){
				for(int k = 0; k < (int)itens[i].relacoes.size(); k++){
					int indexUsr = itens[i].relacoes[k].index;
					numerador += matrizDeNotas[i][indexUsr]*matrizDeNotas[vizinho][indexUsr];
				}
				itens[i].simi[itens[vizinho].identificador] = 
				itens[vizinho].simi[itens[i].identificador] = 
				numerador/sqrt(itens[i].denominadorNormalizado)*
				sqrt(itens[vizinho].denominadorNormalizado);

				//verifica se ocorreu algum erro do tipo 0/0 no cálculo
				if(isnan(itens[i].simi[itens[vizinho].identificador])){
					itens[i].simi[itens[vizinho].identificador] = 
					itens[vizinho].simi[itens[i].identificador] = 0.0;
				}
			}
		}
	}
}

/*constroi a lista de vizinho dos itens
um item é vizinho de outro se existe um usuário comum entre os dois*/
void calculaVizinhos(vector<Colecao> &itens, vector<Colecao> &usuarios){
	for(int u = 0; u < (int)usuarios.size(); u++){
		for(int i = 0; i+1 < (int)usuarios[u].relacoes.size(); i++){
			R item1 = usuarios[u].relacoes[i];
			for(int j = i+1; j < (int)usuarios[u].relacoes.size(); j++){
				R item2 = usuarios[u].relacoes[j];
				itens[item1.index].vizinhos.push_back(item2.index);
				itens[item2.index].vizinhos.push_back(item1.index);
			}
		}
	}
}

//calcula a predição utilizando a media total, a media do item e a media do usuário
double predicaoBase(double mediaTotal, string item, string usuario, map<string,int> &mapa, vector<Colecao> &itens, vector<Colecao> &usuarios){
	double vItem, vUsuario, valor;
	vUsuario = (mapa.find(usuario) == mapa.end()) ? 0.0 : usuarios[mapa[usuario]].media() - mediaTotal;
	vItem = (mapa.find(item) == mapa.end()) ? 0.0 : itens[mapa[item]].media() - mediaTotal;
	valor = mediaTotal + vUsuario + vItem;

	if(valor > 10.0){
		valor = 10.0;
	}else if(0.0 > valor){
		valor = 0.0;
	}

	return valor;
}

//calcula a predição
double calculaPredicao(double mediaTotal, string item, string usuario, map<string,int> &mapa, vector<Colecao> &itens, vector<Colecao> &usuarios, double**matrizDeNotas){
	double  valor, simi, sumSimi, numerador, auxValor;
	int indexUsuario, atual; 
	numerador = 0.0;
	sumSimi = 0.0;
	numerador = 0.0;
	valor = predicaoBase(mediaTotal, item, usuario, mapa, itens, usuarios);

	//verifica se o item e o usuário já foram vistos
	if(mapa.find(usuario) != mapa.end() && mapa.find(item) != mapa.end()){
		indexUsuario = mapa[usuario];

		//calcula o numerador e o denominador da função de similaridade
		for(int i = 0; i < (int)usuarios[indexUsuario].relacoes.size(); i++){
			atual = usuarios[indexUsuario].relacoes[i].index;
			simi = itens[atual].simi[item];
			numerador += simi*matrizDeNotas[atual][indexUsuario];
			sumSimi += abs(simi);
		}

		//verifica se os itens consumidos têm similaridade com o novo item
		if(sumSimi != 0.0){
			auxValor = usuarios[indexUsuario].media() + ((double)numerador/(double)sumSimi);

			if(auxValor > 10.0){
				auxValor = 10.0;
			}else if( 0.0 > auxValor){
				auxValor = 0.0;
			}

			valor = (valor+auxValor)/2;
		}
	}

	return valor;
}