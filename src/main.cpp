#include "avl_tree.hpp"
#include "exclusion_list.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#ifdef _WIN32
#include <windows.h>
#endif

// Declaração da função de processamento já implementada
void processarArquivo(const std::string& caminhoArquivo, AVLTree& avl, const ExclusionList& exclusao);

int main(int argc, char** argv) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ExclusionList exclusao;
    AVLTree avl;

    // Carregar arquivo de exclusão a partir de caminho fixo
    const std::string caminhoExclusaoFixo = "config/exclusao.txt";
    exclusao.carregarDeArquivo(caminhoExclusaoFixo);

    if (argc >= 2) {
        // Modo não interativo: argv[1..] = arquivos de texto
        for (int i = 1; i < argc; ++i) {
            std::string caminho = argv[i];
            std::cout << "Processando: " << caminho << std::endl;
            processarArquivo(caminho, avl, exclusao);
        }
    } else {
        // Modo interativo tradicional (sem solicitar arquivo de exclusão)
        int n;
        std::cout << "Quantos arquivos deseja processar? ";
        std::cin >> n;
        std::cin.ignore();
        std::vector<std::string> arquivos;
        for (int i = 0; i < n; ++i) {
            std::string caminho;
            std::cout << "Arquivo " << (i+1) << ": ";
            std::getline(std::cin, caminho);
            arquivos.push_back(caminho);
        }
        for (const auto& arq : arquivos) {
            std::cout << "Processando: " << arq << std::endl;
            processarArquivo(arq, avl, exclusao);
        }
    }

    // Interface de consulta
    std::string consulta;
    while (true) {
        std::cout << "Digite uma palavra para consultar (ou 'sair'): " << std::flush;
        std::getline(std::cin, consulta);
        if (consulta == "sair") break;
        // Normalizar a palavra
        std::string norm;
        for (char c : consulta) {
            if (std::isalpha(static_cast<unsigned char>(c)))
                norm += std::tolower(static_cast<unsigned char>(c));
        }
        if (norm.empty()) {
            std::cout << "Palavra inválida!" << std::endl;
            continue;
        }
        const AVLNode* node = avl.buscar(norm);
        if (!node) {
            std::cout << "Palavra não encontrada." << std::endl;
        } else {
            std::cout << "Palavra: '" << node->palavra << "'\n";
            for (const auto& info : node->arquivos) {
                std::cout << "Arquivo: " << info.nomeArquivo << "\n  " << u8"Ocorrências" << ": " << info.ocorrencias << "\n  Linhas: ";
                for (size_t i = 0; i < info.linhas.size(); ++i) {
                    std::cout << info.linhas[i];
                    if (i < info.linhas.size() - 1) std::cout << ", ";
                }
                std::cout << std::endl;
            }
        }
    }
    std::cout << "Encerrando o sistema." << std::endl;
    return 0;
}
