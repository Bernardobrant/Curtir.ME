#include <iostream>
#include <fstream>
#include <string.h>
#include <locale>
#include <stdio.h>

#include "Usuario.h"

#define tamanhoNome 50
#define tamanhoSenha 50
#define sucesso 0
Usuario usuarioAtual;

using namespace std;

/*Declara��o das Fun��es*/
void printaMenuLogin();
void printaMenu();

bool autenticarUsuario();
void cadastrarUsuario();

/*Declara��o das Fun��es*/


int main() {
    setlocale(LC_ALL, "Portuguese");

    int opcao;
    do {

        /*Se n�o existe um usuario*/
        if(!strcmp(usuarioAtual.senha, "") != 0){
            //printf("Usuario Atual: %s", usuarioAtual.nome);
            printaMenuLogin();

            cin >> opcao;
            switch (opcao) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                if (autenticarUsuario()) {
                    cout << "Autentica��o bem-sucedida.\n";
                }else{
                    cout << "Usuario ou senha incorretos.\n";
                    system("pause");
                }
                break;
            case 0:
                return sucesso;
            }
        }else{ //Se existe um usuario
            printaMenu();
            cin >> opcao;
        }
    } while (1);

    return 0;
}


void cadastrarUsuario() {
    ofstream arquivo("Arquivos/usuarios.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de usu�rios." << endl;
        return;
    }

    Usuario usuario;

    cout << "Digite o nome do usu�rio: ";
    gets(usuario.nome);
    fgets(usuario.nome, tamanhoNome, stdin);

    cout << "Digite a senha do usu�rio: ";
    fgets(usuario.senha, tamanhoSenha, stdin);

    arquivo.write((char*)&usuario, sizeof(Usuario));
    arquivo.close();

    cout << "Usu�rio cadastrado com sucesso." << endl;
}

bool autenticarUsuario() {

    ifstream arquivo("Arquivos/usuarios.bin", ios::binary);
    Usuario usuario;
    char nome[tamanhoNome], senha[tamanhoSenha];

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de usu�rios." << endl;
        return false;
    }else{
        cout << "Nome: ";
        gets(nome);
        fgets(nome, tamanhoNome,stdin);
        cout << "Senha: ";
        fgets(senha, tamanhoSenha, stdin);

        while (arquivo.read((char*)&usuario, sizeof(Usuario))) {

            if (strcmp(usuario.nome,nome) == 0 && strcmp(usuario.senha,senha) == 0) {
                usuarioAtual = usuario;
                arquivo.close();
                return true;
            }
        }
    }

    arquivo.close();

    return false;
}

void printaMenuLogin(){
        system("cls");
        cout <<".....................................................................\n";
        cout <<".                                                                   .\n";
        cout <<".                            Login                                  .\n";
        cout <<".                                                                   .\n";
        cout <<".....................................................................\n";

        cout <<"1 - Cadastrar usu�rio\n";
        cout <<"2 - Entrar\n";
        cout <<"0 - Sair\n";
        cout <<"Digite a op��o: \n";
}

void printaMenu(){
        system("cls");
        cout <<".....................................................................\n";
        cout <<".                                                                   .\n";
        cout <<".                             Menu                                  .\n";
        cout <<".                                                                   .\n";
        cout <<".....................................................................\n";


        printf("\n\nPerfil: %s\n", usuarioAtual.nome);

        cout <<"1 - Feed\n";
        cout <<"2 - Postagens\n";
        cout <<"2 - Seguir / N�o seguir\n";
        cout <<"0 - Sair\n";
        cout <<"Digite a op��o: \n";
}

