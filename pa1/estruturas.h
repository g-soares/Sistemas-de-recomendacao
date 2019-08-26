#include<string>
#include<map>
#include<vector>

using namespace std;

struct R{
	public:
		int index;
		int nota;
		R(int i, int n){
			index = i;
			nota = n;
		}
};

struct Colecao{
	public:
		string identificador;
		int id = 0;
		double valorTotal = 0.0;
		int num = 0;
		double denominadorNormalizado = 0.0;
		vector<R> relacoes;
		vector<int> vizinhos;
		map<string, double> simi; 
		double media(){ return (double)(valorTotal)/(double)(num);}
};