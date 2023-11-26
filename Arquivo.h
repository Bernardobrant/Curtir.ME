#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <fstream>
using namespace std;


/**
*Este header cont�m algumas informa��es importantes para o funcionamento de v�rias classes que trabalham com arquivos, ela serve para ajudar no funcionamento destas classes
*/

/**
*@brief Fun��o que gera uma exce��o com um texto recebido
*/
void geraExcecao(char problema[]){
    throw problema;
    //cout << problema << endl;
}

/**
*@brief Fun��o que limpa um arquivo bin�rio
*Esta fun��o recebe um nome de arquivo, nisto ela abre o arquivo de modo trunc para deixa-lo limpo
*@see geraExcecao(char problema[])
*@return true caso tenha sido limpo com sucesso e false se n�o foi limpo
*/
bool limparArquivoBinario(char nome[]){
        ofstream arquivo(nome,std::ofstream::out | std::ofstream::trunc);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao limpar o arquivo!");
            return false;
        }
        arquivo.close();
        return true;
}

/**
*@brief Fun��o que copia um arquivo bin�rio em outro
*Esta fun��o recebe dois nomes de arquivos, nisto ela limpar o arquivo de origem, depois abre os arquivos sendo o de origem como leitura e o de destino como escrito, nisto ela copia cada caractere da de origem para a de destino
*@see limparArquivoBinario(char nome[])
*@see geraExcecao(char problema[])
*@return true caso tenha sido copiado com sucesso e false se n�o foi
*/
bool copiarArquivo(char destino[], char origem[]){
    limparArquivoBinario(destino);
    ifstream arquivoOrigem(origem, ios::binary);
    ofstream arquivoDestino(destino, ios::binary | ios::app);
    if (!arquivoDestino.is_open() || !arquivoOrigem.is_open()) {
        geraExcecao("N�o foi poss�vel abrir os arquivos.");
        return false;
    }
    char c;
    while (arquivoOrigem.read((char*)&c, sizeof(char))) {
            arquivoDestino.write((char*)&c, sizeof(char));
    }

    arquivoDestino.close();
    arquivoOrigem.close();
    return true;

}

#endif // ARQUIVO_H
