#include <iostream>
using namespace std;

// definicao de tipo
struct NO {
	int valor;
	NO* esq;
	NO* dir;
};

NO* raiz = NULL;


// headers
// estrutura principal
void menu();
void inicializar();
void inserir();
void exibir();
void exibirQuantidade();
void buscar();
void remover();



// funcoes auxiliares Arvore
NO* insereArvore(NO* no, int valor);
NO* criaNO(int valor);
int elementosArvore(NO* no);
void exibirElementosArvore(NO* no);
void buscarElementoArvore(NO* no, int valor);
NO* buscarElementoArvoreComPai(NO* no, int valor, NO*& pai);
void removerElementoArvore(NO* no, int valor);
//--------------------------


int main()
{
	menu();
}

void menu()
{
	int op = 0;
	while (op != 7) {
		system("cls"); // somente no windows
		cout << "Menu Arvore";
		cout << endl << endl;
		cout << "1 - Inicializar Arvore \n";
		cout << "2 - Exibir quantidade de elementos \n";
		cout << "3 - Inserir elemento \n";
		cout << "4 - Exibir elementos \n";
		cout << "5 - Buscar elemento \n";
		cout << "6 - Remover elemento \n";
		cout << "7 - Sair \n";

		cout << "Opcao: ";
		cin >> op;

		switch (op)
		{
		case 1: inicializar();
			break;
		case 2:exibirQuantidade();
			break;
		case 3: inserir();
			break;
		case 4: exibir();
			break;
		case 5: buscar();
			break;
		case 6: remover();
			break;

		default:
			break;
		}

		system("pause"); // somente no windows
	}
}

void inicializar()
{

	// provisório porque não libera a memoria usada pela arvore
	raiz = NULL;

	cout << "Arvore inicializada \n";

}


void inserir()
{
	int valor;
	cout << "Digite o elemento: ";
	cin >> valor;
	if (raiz == NULL) {
		raiz = criaNO(valor);
	}
	else {
		insereArvore(raiz, valor);
	}


}

void exibirQuantidade() {
	cout << "Quantidade de elementos: " << elementosArvore(raiz) << endl;

}

void exibir() {
	exibirElementosArvore(raiz);
}

void buscar() {
	int valor;
	cout << "Digite o elemento: ";
	cin >> valor;
	buscarElementoArvore(raiz, valor);
}

void remover() {

	int valor;
	cout << "Digite o elemento: ";
	cin >> valor;

	removerElementoArvore(raiz, valor);
	void removerElementoArvore(NO * no, int valor); {
		NO* pai = NULL;
		NO* no = NULL;
		NO* atual = buscarElementoArvoreComPai(no, valor, pai);
		if (atual == NULL) {
			cout << "Elemento nao encontrado \n";
			return;
		}
		// PS: Eu não sei o que tá dando de errado :(
		
		// Caso 1: Sem filhos
		if (atual->esq == NULL && atual->dir == NULL) {
			if (pai == NULL) {
				// O nó a ser removido é a raiz da árvore
				raiz = NULL;
			}
			else if (pai->esq == atual) {
				// O nó a ser removido é um filho à esquerda do pai
				pai->esq = NULL;
			}
			else {
				// O nó a ser removido é um filho à direita do pai
				pai->dir = NULL;
			}
			delete atual;
		}

		// Caso 2: Um filho
		else if (atual->esq == NULL || atual->dir == NULL) {
			NO* filho;
			if (atual->esq != NULL) {
				// O filho está à esquerda
				filho = atual->esq;
			}
			else {
				// O filho está à direita
				filho = atual->dir;
			}
			if (pai == NULL) {
				// O nó a ser removido é a raiz da árvore
				raiz = filho;
			}
			else if (pai->esq == atual) {
				// O nó a ser removido é um filho à esquerda do pai
				pai->esq = filho;
			}
			else {
				// O nó a ser removido é um filho à direita do pai
				pai->dir = filho;
			}
			delete atual;
		}

		// Caso 3: Dois filhos
		else {
			NO* sucessor = atual->dir;
			NO* paiSucessor = atual;
			while (sucessor->esq != NULL) {
				paiSucessor = sucessor;
				sucessor = sucessor->esq;
			}

			atual->valor = sucessor->valor;

			if (paiSucessor->esq == sucessor) {
				// O nó sucessor é um filho à esquerda do paiSucessor
				paiSucessor->esq = sucessor->dir;
			}
			else {
				// O nó sucessor é um filho à direita do paiSucessor
				paiSucessor->dir = sucessor->dir;
			}
			delete sucessor;
		}
	}

}



NO* criaNO(int valor)
{
	NO* novo = (NO*)malloc(sizeof(NO));
	if (novo == NULL)
	{
		return NULL;
	}

	novo->valor = valor;
	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

NO* insereArvore(NO* no, int valor)
{
	if (no->valor > valor && no->esq == NULL) {
		no->esq = criaNO(valor);
		return no->esq;
	}
	else if (no->valor < valor && no->dir == NULL) {
		no->dir = criaNO(valor);
		return no->dir;
	}
	else if (no->valor > valor) {
		return insereArvore(no->esq, valor);
	}
	else if (no->valor < valor) {
		return insereArvore(no->dir, valor);
	}
	else {
		return NULL;
	}


}

int elementosArvore(NO* no)
{
	if (no == NULL) {
		return 0;
	}

	return 1 + elementosArvore(no->esq) + elementosArvore(no->dir);
}

void exibirElementosArvore(NO* no)
{
	if (no == NULL) {
		return;
	}

	cout << no->valor << endl;
	exibirElementosArvore(no->esq);
	exibirElementosArvore(no->dir);

}

void buscarElementoArvore(NO* no, int valor)
{
	if (no == NULL) {
		cout << "Elemento nao encontrado \n";
		return;
	}

	if (no->valor == valor) {
		cout << "Elemento encontrado \n";
		return;
	}

	if (valor < no->valor) {
		buscarElementoArvore(no->esq, valor);
	}
	else {
		buscarElementoArvore(no->dir, valor);
	}
}


// versao nao recursiva
NO* buscarElementoArvoreComPai(NO* no, int valor, NO*& pai)
{
	NO* atual = no;
	pai = NULL;
	while (atual != NULL) {
		if (valor == atual->valor) {
			return atual;
		}
		else {
			pai = atual;

			if (valor < atual->valor) {
				atual = atual->esq;
			}
			else {
				atual = atual->dir;
			}
		}
	}
	return NULL;
}



void removerElementoArvore(NO* no, int valor) {
	NO* pai = NULL;
	NO* atual = buscarElementoArvoreComPai(no, valor, pai);
	if (atual == NULL) {
		cout << "Elemento nao encontrado \n";
		return;
	}


	// caso 1: sem filhos	
	

	// caso 2: um filho	
	

	// caso 3: dois filhos

	// procura o elmento mais a esquerda da sub-arvore da direita
	NO* sucessor = atual->dir;
	NO* paiSucessor = atual;
	while (sucessor->esq != NULL) {
		paiSucessor = sucessor;
		sucessor = sucessor->esq;
	}

	// copia o valor do sucessor para o no atual
	atual->valor = sucessor->valor;

	// se existir uma sub-arvore a direita do sucessor , entao
	// ela deve ser ligada ao pai do sucessor
	if (sucessor->dir != NULL)
	{
		paiSucessor->esq = sucessor->dir;
	}
	else {
		paiSucessor->esq = NULL;
	}

	//libera memoria 
	free(sucessor);


}





