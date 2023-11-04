#include <iostream>
#include <fstream>
#include <string.h>
#include <locale>
#include <stdio.h>

#include "Usuario.h"
#include "manipuladorDeUsuario.h"

#define sucesso 0

manipuladorDeUsuario manipuladorUsuarios;

/*Declara��o das Fun��es*/

void printaMenuLogin();
void printaMenu();
void limpaEntrada();

/*Declara��o das Fun��es*/

int main() {
    setlocale(LC_ALL, "Portuguese");

    manipuladorUsuarios.criaArquivosNescessarios();
    system("pause");
    int opcao;

    do {

        /*Se n�o existe um usuario*/
        if(!usuarioAtual.existe()){
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

                manipuladorUsuarios.cadastrarUsuario(nome,senha);
                break;
            case 2:
                cout << "   Nome: ";
                limpaEntrada();
                fgets(nome, tamanhoNome,stdin);
                cout << "   Senha: ";
                fgets(senha, tamanhoSenha, stdin);

                if (manipuladorUsuarios.autenticarUsuario(nome,senha)) {
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
