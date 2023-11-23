#ifndef MANIPULADORDECOMENTARIO_H
#define MANIPULADORDECOMENTARIO_H

#include "manipuladorDeUsuario.h"
#include "Comentario.h"

#define mostrarTodos -1 // Utilizado no metodo exibirComentariosPorId()

class manipuladorDeComentario
{
    public:
        manipuladorDeComentario();
        void criaArquivosNescessarios();
        bool adicionaAoArquivo(Comentario coment);
        void printaComentario(Comentario coment);
        void exibirComentariosPorId(int idPost, int quantidade);


    private:
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          Implementa��o dos Metodos da Classe manipuladorDeComentario                         */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Metodo que cria todos os documentos nescessarios para o funcionamento da classe
void manipuladorDeComentario::criaArquivosNescessarios(){

    //Arquivos de comentarios
    ifstream ifs2("Arquivos/comentarios.bin");
    if (!ifs2) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/comentarios.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            cout << "Erro ao criar o arquivo de coment�rios." << endl;

            return;
        }
        cout << "Arquivo de coment�rios criado\n";
        arquivo.close();
    }
}

//Metodo que adiciona um coment�rio a um arquivo bin�rio
bool manipuladorDeComentario::adicionaAoArquivo(Comentario coment){
    ofstream arquivo("Arquivos/comentarios.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de comentarios.");
        return false;
    }

    arquivo.write((char*)&coment, sizeof(Comentario));
    arquivo.close();

    cout << "Coment�rio adicionado." << endl;

    return true;
}

void manipuladorDeComentario::exibirComentariosPorId(int idPost, int quantidade){
    int i = 0;
    ifstream arquivo("Arquivos/comentarios.bin", ios::binary);
    Comentario coment;

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de coment�rios.");
    }else{

        while (arquivo.read((char*)&coment, sizeof(Comentario))) {
            if(quantidade != mostrarTodos){
                if(coment.GetIDpostagem() == idPost && i < quantidade){
                    this->printaComentario(coment);
                    i++;
                }
            }else{
                if(coment.GetIDpostagem() == idPost){
                    this->printaComentario(coment);
                    i++;
                }
            }

        }
    }

    if(i == 0){
        cout << "\n                 Nenhum coment�rio!\n" << endl;
    }

}
void manipuladorDeComentario::printaComentario(Comentario coment){

        cout <<   "\n\n             | - ";
        cout << coment.Getconteudo() << endl;
        cout << "\n               Comentado por "<<  coment.GetnomeUsuario() << endl;
        cout <<   "\n             L \n";
}

 manipuladorDeComentario::manipuladorDeComentario(){
 }

#endif // MANIPULADORDECOMENTARIO_H
