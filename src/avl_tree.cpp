#include "avl_tree.hpp"
#include <algorithm>

AVLTree::AVLTree() : raiz(nullptr) {}

AVLTree::~AVLTree() {
    limpar();
}

void AVLTree::limpar() {
    destruir(raiz);
    raiz = nullptr;
}

void AVLTree::destruir(AVLNode* node) {
    if (node) {
        destruir(node->esquerda);
        destruir(node->direita);
        delete node;
    }
}

int AVLTree::altura(AVLNode* node) {
    return node ? node->altura : 0;
}

int AVLTree::fatorBalanceamento(AVLNode* node) {
    return altura(node->esquerda) - altura(node->direita);
}

AVLNode* AVLTree::rotacaoDireita(AVLNode* y) {
    AVLNode* x = y->esquerda;
    AVLNode* T2 = x->direita;
    x->direita = y;
    y->esquerda = T2;
    y->altura = std::max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = std::max(altura(x->esquerda), altura(x->direita)) + 1;
    return x;
}

AVLNode* AVLTree::rotacaoEsquerda(AVLNode* x) {
    AVLNode* y = x->direita;
    AVLNode* T2 = y->esquerda;
    y->esquerda = x;
    x->direita = T2;
    x->altura = std::max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = std::max(altura(y->esquerda), altura(y->direita)) + 1;
    return y;
}

AVLNode* AVLTree::balancear(AVLNode* node) {
    int fb = fatorBalanceamento(node);
    if (fb > 1) {
        if (fatorBalanceamento(node->esquerda) < 0)
            node->esquerda = rotacaoEsquerda(node->esquerda);
        return rotacaoDireita(node);
    }
    if (fb < -1) {
        if (fatorBalanceamento(node->direita) > 0)
            node->direita = rotacaoDireita(node->direita);
        return rotacaoEsquerda(node);
    }
    return node;
}

void AVLTree::inserir(const std::string& palavra, const std::string& arquivo, int linha) {
    raiz = inserir(raiz, palavra, arquivo, linha);
}

AVLNode* AVLTree::inserir(AVLNode* node, const std::string& palavra, const std::string& arquivo, int linha) {
    if (!node) {
        AVLNode* novo = new AVLNode(palavra);
        FileInfo info{arquivo, 1, {linha}};
        novo->arquivos.push_back(info);
        return novo;
    }
    if (palavra < node->palavra) {
        node->esquerda = inserir(node->esquerda, palavra, arquivo, linha);
    } else if (palavra > node->palavra) {
        node->direita = inserir(node->direita, palavra, arquivo, linha);
    } else {
        // Palavra já existe, atualizar info do arquivo
        auto it = std::find_if(node->arquivos.begin(), node->arquivos.end(), [&](const FileInfo& f){ return f.nomeArquivo == arquivo; });
        if (it != node->arquivos.end()) {
            it->ocorrencias++;
            it->linhas.push_back(linha);
        } else {
            FileInfo info{arquivo, 1, {linha}};
            node->arquivos.push_back(info);
        }
        return node;
    }
    node->altura = std::max(altura(node->esquerda), altura(node->direita)) + 1;
    return balancear(node);
}

const AVLNode* AVLTree::buscar(const std::string& palavra) const {
    return buscar(raiz, palavra);
}

AVLNode* AVLTree::buscar(AVLNode* node, const std::string& palavra) const {
    if (!node) return nullptr;
    if (palavra < node->palavra) return buscar(node->esquerda, palavra);
    if (palavra > node->palavra) return buscar(node->direita, palavra);
    return node;
}
