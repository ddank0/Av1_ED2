# Sistema de Indexação de Palavras com Árvore AVL (C++)

Este projeto lê um conjunto de arquivos de texto grandes, indexa suas palavras em uma Árvore AVL e permite consultar:
- Em quais arquivos cada palavra aparece
- Quantas ocorrências por arquivo
- Em quais linhas a palavra aparece

Palavras irrelevantes (pronomes, advérbios etc.) são filtradas por uma lista de exclusão ordenada com pesquisa binária.

---

## Requisitos
- Compilador C++17 (ex.: g++/MinGW no Windows)
- Windows com console configurável para UTF-8

---

## Estrutura do Projeto
- `src/avl_tree.hpp` / `src/avl_tree.cpp`: implementação da Árvore AVL
- `src/exclusion_list.hpp` / `src/exclusion_list.cpp`: lista de exclusão com busca binária
- `src/leitor_arquivos.cpp`: leitura linha a linha, normalização e indexação
- `src/main.cpp`: integração e interface de consulta (interativa ou via argumentos)
- `run.cmd`: script para compilar e executar (suporta `--build`, `--test` e modo normal)
- `config/exclusao.txt`: lista de palavras a serem ignoradas (usada automaticamente)
- `data/texto1.txt`: arquivo de teste
- `tests/queries.txt`: consultas automatizadas (uma por linha)

---

## Compilação
### Usando script (recomendado)
Na raiz do projeto, execute:
```
run.cmd --build
```
O script compila e gera `src\bin\indexador.exe` sem executar.

### Manualmente (linha de comando)
Na raiz do projeto:
```
g++ -std=c++17 -O2 -o src\bin\indexador.exe src\main.cpp src\leitor_arquivos.cpp src\avl_tree.cpp src\exclusion_list.cpp
```

---

## Execução
### Modo de teste automatizado (`--test`)
Executa com o arquivo de exclusão fixo `config\exclusao.txt`, processa `data\texto1.txt` e injeta as consultas de `tests\queries.txt` automaticamente.
```
run.cmd --test
```
Exemplo de saída esperada (parcial):
```
Processando: data\texto1.txt

Digite uma palavra para consultar (ou 'sair'): Palavra: 'rato'
Arquivo: data\texto1.txt
  Ocorrências: 2
  Linhas: 1, 3
```

### Modo normal (interativo)
```
run.cmd
```
Executa com o arquivo de exclusão fixo `config\exclusao.txt`. Após a indexação dos arquivos informados (inicialmente `data\texto1.txt` pelo script), você digita as consultas no terminal e usa `sair` para encerrar.

### Modo por argumentos (não interativo)
Agora apenas os arquivos de dados são argumentos. O arquivo de exclusão é fixo (não é passado por argumento):
```
src\bin\indexador.exe data\texto1.txt [outros_arquivos.txt...]
```
Você pode redirecionar consultas:
```
src\bin\indexador.exe data\texto1.txt < tests\queries.txt
```

---

## Formato dos Arquivos
### Lista de exclusão (`config/exclusao.txt`)
- Uma palavra por linha
- Sem pontuação
- Case-insensitive (o sistema normaliza para minúsculo)

### Arquivos de texto (ex.: `data/texto1.txt`)
- Qualquer arquivo `.txt`
- Palavras são extraídas ignorando pontuação e normalizadas para minúsculo

### Consultas (`tests/queries.txt`)
- Uma palavra por linha (ex.: `rato`, `roma`, `rainha`, `sair`)

---

## Observações de Encoding
- O console utiliza UTF-8; se vir caracteres incorretos, altere a fonte para uma TrueType (ex.: Consolas) e mantenha a página de código em UTF-8.

---

## Limitações e Diretrizes
- Normalização: somente caracteres alfabéticos A-Z/a-z são considerados (acentos são preservados se presentes no arquivo, mas filtragem ignora pontuação)
- Memória: para arquivos muito grandes, o consumo depende do número de palavras únicas e linhas registradas
- Performance: Árvore AVL garante buscas/inserções O(log N)

---

## PRD
O documento de requisitos está em `PRD_Indexador_AVL.md` e reflete o status atual.
