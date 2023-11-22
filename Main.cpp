#include <iostream>
#include <fstream>
#include <string.h>
#include <locale>
#include <stdio.h>

#include "Usuario.h"
#include "Postagem.h"
#include "Comentario.h"

#include "manipuladorDeUsuario.h"
#include "manipuladorDePostagem.h"
#include "manipuladorDeComentario.h"
#define sucesso 0

manipuladorDeUsuario manipuladorUsuarios;
manipuladorDePostagem manipuladorPostagens;
manipuladorDeComentario manipuladorComentarios;

/*Declara��o das Fun��es*/

void printaMenuLogin();
void printaMenu();
void limpaEntrada();
void printaMenuPostagens();
void printaMenuFeed();

/*Declara��o das Fun��es*/

int main() {

    setlocale(LC_ALL, "Portuguese");

    manipuladorUsuarios.criaArquivosNescessarios();
    manipuladorPostagens.criaArquivosNescessarios();
    manipuladorComentarios.criaArquivosNescessarios();


    //manipuladorComentarios.exibirComentariosPorId(1, mostrarTodos);


    cout << "Numero de usuarios: " << manipuladorUsuarios.numeroDeUsuarios() << endl;
    cout << "Numero de postagens: " << manipuladorPostagens.numeroDePostagens() << endl;
    system("pause");
    int opcao;

    do {
        /*Se n�o existe um usuario*/
        if(!usuarioAtual.existe()){
            printaMenuLogin();

            cin >> opcao;
            char nome[tamanhoNome], senha[tamanhoSenha];
            switch (opcao) {
            case 1: //Cadastrar Usuario

                cout << "   Digite o nome do usu�rio: ";
                limpaEntrada();
                fgets(nome, tamanhoNome, stdin);

                cout << "   Digite a senha do usu�rio: ";
                fgets(senha, tamanhoSenha, stdin);

                if(manipuladorUsuarios.procuraUsuarioNome(nome).existe() == true){
                    cout << "\n\nEste nome de usu�rio j� existe no sistema, tente outro nome!\n\n\n\n";
                    system("pause");
                }else{

                    manipuladorUsuarios.cadastrarUsuario(nome,senha);
                }
                break;
            case 2: //Entrar com usuario e senha
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
                case 2: // Adiciona uma postagem
                    goto postagemStop;
                    break;
                case 1: // Exibe o feed
                    int opcaoFeed;
                    manipuladorPostagens.mostrarFeed();
                    printaMenuFeed();

                    break;
                case 0:
                    usuarioAtual.limpaUsuario();
                    break;
            }


            postagemStop:
                if(opcao == 2){
                    while(1){
                        printaMenuPostagens();
                        int opcaoPostagens;
                        cin >> opcaoPostagens;
                        limpaEntrada();

                        if(opcaoPostagens == 1){ //Adicionar Postagens
                                char texto[tamanhoTextoPostagens];
                                cout << "Digite o conteudo da postagem:\n";
                                fgets(texto, tamanhoTextoPostagens, stdin);
                                Postagem novaPostagem(usuarioAtual.getId(), 0,texto);
                                manipuladorPostagens.adicionaAoArquivo(novaPostagem);
                                system("pause");
                        }else if(opcaoPostagens == 2){ // Alterar uma postagem
                                while(1){
                                    int numeroPostagem;
                                    cout << "Qual postagem deseja alterar (0 para voltar) : \n";
                                    cin >> numeroPostagem;

                                    limpaEntrada();

                                    if(numeroPostagem == 0){
                                        goto postagemStop;
                                    }

                                    if( manipuladorPostagens.ehMinhaPostagem(usuarioAtual.getId(),numeroPostagem)){

                                        char texto[tamanhoTextoPostagens];
                                        cout << "Digite o conteudo da postagem:\n";
                                        fgets(texto, tamanhoTextoPostagens, stdin);
                                        Postagem postAlterado(usuarioAtual.getId(), numeroPostagem, texto);
                                        manipuladorPostagens.salvaPostagem(postAlterado);
                                        break;
                                    }else{
                                        cout << "Voc� n�o t�m esta postagem.\n\n";
                                        system("pause");

                                    }
                                }

                        }else if(opcaoPostagens == 3){ // Seguir ou n�o seguir outro usu�rio
                            break;
                        }else if(opcaoPostagens == 0){
                            break;
                        }else{
                            cout << "Digite uma op��o v�lida.\n";
                        }
                    }
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
        cout <<"    0 - Fechar\n";
        cout <<"    Digite a op��o: ";
}

void printaMenu(){
        system("cls");
        cout <<"    .....................................................................\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .                             Menu                                  .\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .....................................................................\n";


        printf("\n\n    ID: %d Perfil: %s\n",usuarioAtual.getId(),usuarioAtual.getNome());

        cout <<"    1 - Feed\n";
        cout <<"    2 - Postagens\n";
        cout <<"    3 - Seguir / N�o seguir\n";
        cout <<"    0 - Sair\n";
        cout <<"    Digite a op��o: ";
}

void printaMenuPostagens(){
        system("cls");
        cout <<"    .....................................................................\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .                            Postagens                              .\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .....................................................................\n";


        printf("\n\n    ID: %d Perfil: %s\n",usuarioAtual.getId(),usuarioAtual.getNome());

        cout <<"    1 - Adicionar uma Postagem\n";
        cout <<"    2 - Mudar postagem\n";
        cout <<"    0 - Voltar\n";
        cout <<"    Digite a op��o: ";
}

void printaMenuFeed(){
        int opcao;
        int idPostagem;
        char textoComentario[tamanhoTextoComentarios];
        int IDpostagem;
        Comentario comentario;

        while(1){
            printf("\n\n    ID: %d Perfil: %s\n",usuarioAtual.getId(),usuarioAtual.getNome());

            cout <<"    1 - Curtir uma Postagem\n";
            cout <<"    2 - Comentar uma postagem\n";
            cout <<"    3 - Detalhar uma postagem (Mostrar postagem e todos os seus coment�rios)\n";
            cout <<"    0 - Voltar\n";
            cout <<"    Digite a op��o: ";
            cin >> opcao;

            switch(opcao){
                case 1: //Adiciona uma curtida a uma postagem escolhida
                    cout << "   Digite o Id da postagem: ";
                    cin >> idPostagem;
                    if(manipuladorPostagens.buscaPostagem(idPostagem).existe()){
                        manipuladorPostagens.adicionaCurtida(manipuladorPostagens.buscaPostagem(idPostagem));
                    }else{
                        cout << "\n\n  Esta postagem n�o existe!\n";
                    }

                    break;
                case 2: // Adiciona um coment�rio a uma postagem escolhida
                        cout << "Qual o Id da postagem que voc� deseja comentar: ";
                        scanf("%d", &IDpostagem);
                        limpaEntrada();
                        cout << "Digite o coment�rio: " << endl;
                        fgets(textoComentario, tamanhoTextoComentarios, stdin);

                        comentario.SetIDusuario(usuarioAtual.getId());
                        comentario.Setconteudo(textoComentario);
                        comentario.SetIDpostagem(IDpostagem);
                        comentario.SetnomeUsuario(usuarioAtual.getNome());
                        comentario.SetnumeroComentario(0);

                        manipuladorComentarios.adicionaAoArquivo(comentario);
                    break;
                case 3: // Mostra uma postagem com seus coment�rios
                        cout << "Qual o Id da postagem que voc� deseja detalhar: ";
                        scanf("%d", &IDpostagem);
                        limpaEntrada();
                        manipuladorPostagens.detalhar(IDpostagem);
                    break;
                case 0:
                    return;

            }
        }
}

void limpaEntrada(){
    getchar();
}
