#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <map>

struct Livro {
    std::string cpf;
    std::string titulo;
    std::string autor;
    int id;
};

std::list<Livro> listaLivros;
std::map<std::string, std::list<Livro> > emprestimos;
std::map<std::string, std::queue<Livro> > livrosReservados;

void adicionarLivro() {
    Livro livro;

    std::cout << "Adicionar Livro\n";
    std::cout << "Titulo: ";
    std::cin.ignore();
    std::getline(std::cin, livro.titulo);
    std::cout << "Autor: ";
    std::getline(std::cin, livro.autor);
    std::cout << "ID: ";
    std::cin >> livro.id;

    listaLivros.push_back(livro);
    std::cout << "Livro adicionado com sucesso.\n";
}



void removerLivro() {
    std::string titulo;

    std::cout << "Remover Livro\n";
    std::cout << "Titulo do livro: ";
    std::cin.ignore();
    std::getline(std::cin, titulo);

    bool livroEncontrado = false;
    for (std::list<Livro>::iterator it = listaLivros.begin(); it != listaLivros.end(); ++it) {
        if (it->titulo == titulo) {
            listaLivros.erase(it);
            livroEncontrado = true;
            break;
        }
    }

    if (livroEncontrado) {
        std::cout << "Livro removido com sucesso.\n";
    } else {
        std::cout << "Livro nao encontrado.\n";
    }
}

void procurarLivro() {
    std::string titulo;

    std::cout << "Procurar Livro\n";
    std::cout << "Titulo do livro: ";
    std::cin.ignore();
    std::getline(std::cin, titulo);

    bool livroEncontrado = false;
    for (std::list<Livro>::iterator it = listaLivros.begin(); it != listaLivros.end(); ++it) {
        if (it->titulo == titulo) {
            std::cout << "Livro encontrado:\n";
            std::cout << "Titulo: " << it->titulo << "\n";
            std::cout << "Autor: " << it->autor << "\n";
            std::cout << "ID: " << it->id << "\n";
            livroEncontrado = true;
            break;
        }
    }

    if (!livroEncontrado) {
        std::cout << "Livro nao encontrado.\n";
    }
}

void pegarLivroEmprestado() {
    std::string cpf;
    int id;

    std::cout << "Pegar Livro Emprestado\n";
    std::cout << "CPF do usuario: ";
    std::cin.ignore();
    std::getline(std::cin, cpf);
    std::cout << "ID do livro: ";
    std::cin >> id;

    bool livroEncontrado = false;
    for (std::list<Livro>::iterator it = listaLivros.begin(); it != listaLivros.end(); ++it) {
        if (it->id == id) {
            if (it->cpf.empty()) {
                it->cpf = cpf;
                emprestimos[cpf].push_back(*it);
                livroEncontrado = true;
                std::cout << "Livro emprestado com sucesso.\n";
            } else {
                std::cout << "Livro ja emprestado.\n";
            }
            break;
        }
    }

    if (!livroEncontrado) {
        std::cout << "Livro nao encontrado.\n";
    }
}

void devolverLivro() {
    std::string cpf;
    int id;

    std::cout << "Devolver Livro\n";
    std::cout << "CPF do usuario: ";
    std::cin.ignore();
    std::getline(std::cin, cpf);
    std::cout << "ID do livro: ";
    std::cin >> id;

    bool livroEncontrado = false;
    for (std::list<Livro>::iterator it = emprestimos[cpf].begin(); it != emprestimos[cpf].end(); ++it) {
        if (it->id == id) {
            it->cpf = "";
            livroEncontrado = true;
            std::cout << "Livro devolvido com sucesso.\n";
            break;
        }
    }

    if (!livroEncontrado) {
        std::cout << "Livro nao encontrado.\n";
    }
}

void reservarLivro() {
    std::string cpf;
    int id;

    std::cout << "Reservar Livro\n";
    std::cout << "CPF do usuario: ";
    std::cin.ignore();
    std::getline(std::cin, cpf);
    std::cout << "ID do livro: ";
    std::cin >> id;

    bool livroEncontrado = false;
    for (std::list<Livro>::iterator it = listaLivros.begin(); it != listaLivros.end(); ++it) {
        if (it->id == id) {
            if (it->cpf.empty()) {
                it->cpf = cpf;
                livrosReservados[cpf].push(*it);
                livroEncontrado = true;
                std::cout << "Livro reservado com sucesso.\n";
            } else {
                std::cout << "Livro ja reservado.\n";
            }
            break;
        }
    }

    if (!livroEncontrado) {
        std::cout << "Livro nao encontrado.\n";
    }
}

void mostrarLivrosReservados() {
    std::string cpf;

    std::cout << "Mostrar Livros Reservados\n";
    std::cout << "CPF do usuario: ";
    std::cin.ignore();
    std::getline(std::cin, cpf);

    if (livrosReservados.find(cpf) != livrosReservados.end()) {
        std::queue<Livro>& filaReservados = livrosReservados[cpf];
        std::cout << "Livros reservados por " << cpf << ":\n";
        while (!filaReservados.empty()) {
            Livro livro = filaReservados.front();
            std::cout << "Titulo: " << livro.titulo << "\n";
            std::cout << "Autor: " << livro.autor << "\n";
            std::cout << "ID: " << livro.id << "\n";
            filaReservados.pop();
        }
    } else {
        std::cout << "Nenhum livro reservado por " << cpf << ".\n";
    }
}

void mostrarEmprestimos() {
    std::string cpf;

    std::cout << "Mostrar Emprestimos\n";
    std::cout << "CPF do usuario: ";
    std::cin.ignore();
    std::getline(std::cin, cpf);

    if (emprestimos.find(cpf) != emprestimos.end()) {
        std::list<Livro>& listaEmprestimos = emprestimos[cpf];
        std::cout << "Livros emprestados para " << cpf << ":\n";
        for (std::list<Livro>::iterator it = listaEmprestimos.begin(); it != listaEmprestimos.end(); ++it) {
            std::cout << "Titulo: " << it->titulo << "\n";
            std::cout << "Autor: " << it->autor << "\n";
            std::cout << "ID: " << it->id << "\n";
        }
    } else {
        std::cout << "Nenhum livro emprestado para " << cpf << ".\n";
    }
}

int main() {
    int opcao;

    do {
        std::cout << "\n*** Biblioteca ***\n";
        std::cout << "1. Adicionar Livro\n";
        std::cout << "2. Remover Livro\n";
        std::cout << "3. Procurar Livro\n";
        std::cout << "4. Pegar Livro Emprestado\n";
        std::cout << "5. Devolver Livro\n";
        std::cout << "6. Reservar Livro\n";
        std::cout << "7. Mostrar Livros Reservados\n";
        std::cout << "8. Mostrar Emprestimos\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarLivro();
                break;
            case 2:
                removerLivro();
                break;
            case 3:
                procurarLivro();
                break;
            case 4:
                pegarLivroEmprestado();
                break;
            case 5:
                devolverLivro();
                break;
            case 6:
                reservarLivro();
                break;
            case 7:
                mostrarLivrosReservados();
                break;
            case 8:
                mostrarEmprestimos();
                break;
            case 0:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opcao invalida.\n";
                break;
        }
    } while (opcao != 0);

    return 0;
}
