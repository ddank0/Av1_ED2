#include "avl_tree.hpp"
#include "exclusion_list.hpp"
#include <fstream>
#include <sstream>
#include <cctype>

// Função para normalizar uma palavra (minúsculo, sem pontuação)
std::string normalizar(const std::string& palavra) {
    std::string resultado;
    for (char c : palavra) {
        if (std::isalpha(static_cast<unsigned char>(c)))
            resultado += std::tolower(static_cast<unsigned char>(c));
    }
    return resultado;
}

// Função principal para ler arquivo e inserir palavras na AVL
void processarArquivo(const std::string& caminhoArquivo, AVLTree& avl, const ExclusionList& exclusao) {
    std::ifstream file(caminhoArquivo);
    std::string linha;
    int numLinha = 1;
    while (std::getline(file, linha)) {
        std::istringstream iss(linha);
        std::string palavra;
        while (iss >> palavra) {
            std::string norm = normalizar(palavra);
            if (!norm.empty() && !exclusao.contem(norm)) {
                avl.inserir(norm, caminhoArquivo, numLinha);
            }
        }
        numLinha++;
    }
}
