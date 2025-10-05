#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <string>
#include <vector>
#include <map>

struct FileInfo {
    std::string nomeArquivo;
    int ocorrencias;
    std::vector<int> linhas;
};

struct AVLNode {
    std::string palavra;
    std::vector<FileInfo> arquivos;
    AVLNode* esquerda;
    AVLNode* direita;
    int altura;
    AVLNode(const std::string& p) : palavra(p), esquerda(nullptr), direita(nullptr), altura(1) {}
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void inserir(const std::string& palavra, const std::string& arquivo, int linha);
    const AVLNode* buscar(const std::string& palavra) const;
    void limpar();
private:
    AVLNode* raiz;
    AVLNode* inserir(AVLNode* node, const std::string& palavra, const std::string& arquivo, int linha);
    AVLNode* buscar(AVLNode* node, const std::string& palavra) const;
    void destruir(AVLNode* node);
    int altura(AVLNode* node);
    int fatorBalanceamento(AVLNode* node);
    AVLNode* rotacaoDireita(AVLNode* y);
    AVLNode* rotacaoEsquerda(AVLNode* x);
    AVLNode* balancear(AVLNode* node);
};

#endif // AVL_TREE_HPP
