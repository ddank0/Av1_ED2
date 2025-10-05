#include "exclusion_list.hpp"
#include <fstream>
#include <algorithm>

ExclusionList::ExclusionList() {}

void ExclusionList::carregarDeArquivo(const std::string& caminho) {
    std::ifstream file(caminho);
    std::string palavra;
    while (file >> palavra) {
        lista.push_back(palavra);
    }
    ordenar();
}

void ExclusionList::adicionarPalavra(const std::string& palavra) {
    lista.push_back(palavra);
    ordenar();
}

void ExclusionList::ordenar() {
    std::sort(lista.begin(), lista.end());
}

bool ExclusionList::contem(const std::string& palavra) const {
    return std::binary_search(lista.begin(), lista.end(), palavra);
}
