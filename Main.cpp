#include <iostream>
#include <fstream>
#include <string.h>
#include <locale>
#include <stdio.h>

#include "Usuario.h"

#define sucesso 0

Usuario usuarioAtual;
using namespace std;

/*Declara��o das Fun��es*/
bool autenticarUsuario(char nome[], char senha[]);
void printaMenuLogin();
void printaMenu();
void limpaEntrada();
void cadastrarUsuario(char nome[], char senha[]);
/*Declara��o das Fun��es*/

int main() {
    setlocale(LC_ALL, "Portuguese");

    int opcao;
    do {

        /*Se n�o existe um usuario*/
        if(!strcmp(usuarioAtual.getSenha(), "") != 0){
            //printf("Usuario Atual: %s", usuarioAtual.nome);
            printaMenuLogin();

            cin >> opcao;
            char nome[tamanhoNome], senha[tamanhoSenha];
            switch (opcao) {
            case 1:
                cout << "   Digite o nome do usu�rio: ";
                limpaEntrada();
                fgets(nome, tamanhoNome, stdin);

                cout << "   Digite a senha do usu�rio: ";
                fgets(senha, tamanhoSenha, stdin);
                cadastrarUsuario(nome, senha);
                break;
            case 2:
                cout << "   Nome: ";
                limpaEntrada();
                fgets(nome, tamanhoNome,stdin);
                cout << "   Senha: ";
                fgets(senha, tamanhoSenha, stdin);

                if (autenticarUsuario(nome,senha)) {
                    cout << "   Autentica��o bem-sucedida.\n";
                }else{
                    cout << "   Usuario ou senha incorretos.\n";
                    system("pause");
                }
                break;
            case 0:
                return sucesso;
            }
        }else{ //Se existe um usuario
            printaMenu();
            cin >> opcao;

            switch(opcao){
                case 3:
                    break;
                case 2:
                    break;
                case 1:
                    break;
                case 0:
                    usuarioAtual.limpaUsuario();
                    break;
            }
        }
    } while (1);

    return 0;
}


void printaMenuLogin(){
        system("cls");
        cout <<"    .....................................................................\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .                            Login                                  .\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .....................................................................\n";

        cout <<"    1 - Cadastrar usu�rio\n";
        cout <<"    2 - Entrar\n";
        cout <<"    0 - Sair\n";
        cout <<"    Digite a op��o: ";
}

void printaMenu(){
        system("cls");
        cout <<"    .....................................................................\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .                             Menu                                  .\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .....................................................................\n";


        printf("\n\n    Perfil: %s\n", usuarioAtual.getNome());

        cout <<"    1 - Feed\n";
        cout <<"    2 - Postagens\n";
        cout <<"    3 - Seguir / N�o seguir\n";
        cout <<"    0 - Sair\n";
        cout <<"    Digite a op��o: ";
}

void limpaEntrada(){
    char lixo[2];
    gets(lixo);
}

bool autenticarUsuario(char nome[], char senha[]) {

    ifstream arquivo("Arquivos/usuarios.bin", ios::binary);
    Usuario usuario;

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de usu�rios." << endl;
        return false;
    }else{

        while (arquivo.read((char*)&usuario, sizeof(Usuario))) {

            if (strcmp(usuario.getNome(),nome) == 0 && strcmp(usuario.getSenha(),senha) == 0) {
                usuarioAtual = usuario;
                arquivo.close();
                return true;
            }
        }
    }

    arquivo.close();

    return false;
}

void cadastrarUsuario(char nome[], char senha[]) {
    ofstream arquivo("Arquivos/usuarios.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de usu�rios." << endl;
        return;
    }

    Usuario usuario;

    usuario.setNome(nome); //Define o nome para o usuario
    usuario.setSenha(senha);

    arquivo.write((char*)&usuario, sizeof(Usuario));
    arquivo.close();

    cout << "Usu�rio cadastrado com sucesso." << endl;
}
