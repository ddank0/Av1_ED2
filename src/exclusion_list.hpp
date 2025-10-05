#ifndef EXCLUSION_LIST_HPP
#define EXCLUSION_LIST_HPP
#include <string>
#include <vector>

class ExclusionList {
public:
    ExclusionList();
    void carregarDeArquivo(const std::string& caminho);
    void adicionarPalavra(const std::string& palavra);
    void ordenar();
    bool contem(const std::string& palavra) const;
private:
    std::vector<std::string> lista;
};

#endif // EXCLUSION_LIST_HPP
