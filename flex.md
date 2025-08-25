# Flex: Ferramenta para Geração de Analisadores Léxicos

Flex é uma ferramenta de software livre inspirada na ferramenta **Lex**, desenvolvida pela GNU na década de 90, que tem como principal função gerar analisadores léxicos.  
Ela é uma ferramenta fundamental para a construção de compiladores e é amplamente utilizada para tokenizar dados em diversas áreas, não apenas em compiladores.

No contexto de compiladores, o Flex é a ferramenta que transforma um conjunto de expressões regulares em um programa de computador que atua como um analisador léxico.

---

## Funcionamento e Mecanismos do Flex

### Entrada e Saída
- **Entrada:**  
  O Flex recebe como entrada um arquivo de especificação (tipicamente com extensão `.l`, por exemplo, `scanner.l`), que define padrões de texto usando expressões regulares e as ações C correspondentes a serem executadas quando um padrão é reconhecido.
- **Processamento:**  
  Ao executar o comando:
  ```bash
  flex scanner.l
  ```
  Ele gera um arquivo-fonte em C (por exemplo, `lex.yy.c`), que contém a função `yylex` (também referida como `getToken` na disciplina).
- **Observação:**  
  Este arquivo `.c` gerado **não deve ser editado manualmente**, pois é automaticamente gerado e possui um tamanho considerável (milhares de linhas), contendo o "autômato" que detecta os tokens.

---

### yylex (getToken)
- A função `yylex` (ou `getToken`) é o **coração do analisador léxico** gerado.
- Cada vez que é chamada, ela lê um fluxo de caracteres do arquivo de entrada e retorna um token (tipicamente um número inteiro que representa o tipo do token).
- Quando não há mais tokens para serem lidos, `yylex` retorna zero, indicando o **fim do arquivo (EOF)**.
- O analisador sintático (o "coração do compilador") chama `getToken` sempre que precisa de um token.

---

### Estrutura do Arquivo `.l`
Um arquivo `.l` é dividido em três seções, separadas por `%%`:

1. **Definições (seção superior):**  
   Contém configurações do Flex (como opções `noyywrap` e `yylineno`) e código C (como diretivas `#include`, variáveis globais e comentários de múltiplas linhas).

2. **Regras e Ações (seção do meio):**  
   É onde se definem as expressões regulares e o código C associado.  
   - Se um padrão (expressão regular) é reconhecido na entrada, o código C correspondente é executado.  
   - Tipicamente, este código retorna o valor do token (ex: `return TK_TIPO`).  
   - Regras sem uma ação explícita fazem com que a entrada correspondente seja consumida, mas ignorada (útil para espaços em branco e comentários).

3. **Funções C (seção inferior):**  
   Pode conter funções auxiliares ou a própria função `main` do programa.

---

### Variáveis Globais Importantes
- **yytext:**  
  Aponta para o último lexema reconhecido (a sequência de caracteres que "casou" com uma expressão regular).  
  Se o valor precisar ser guardado, deve-se duplicar seu conteúdo (ex: usando `strdup`), pois o ponteiro pode apontar para outros locais posteriormente.

- **yyleng:**  
  Armazena o tamanho do `yytext`.

- **yylineno:**  
  Guarda o número da linha atual, especialmente se a opção `yylineno` for usada.

---

### Resolução de Ambiguidade e Prioridade
- O Flex utiliza a regra que reconhece o **lexema mais longo**.  
  Exemplo: se `"42AC"` pode ser um literal inteiro (`42`) e um identificador (`42AC`), o Flex escolherá o identificador, pois é o lexema mais longo.
- Entre regras que reconhecem o mesmo comprimento de lexema, a **regra que aparece primeiro** no arquivo `.l` tem precedência.

---

### Ignorando Entradas e Erros
- Espaços em branco (espaços, tabulações, quebras de linha) são tipicamente ignorados, definindo uma regra sem ação para eles.
- Um padrão genérico `(.)` no final das regras pode ser usado para capturar e sinalizar erros léxicos (tokens não reconhecidos por nenhuma outra regra), retornando um token de erro.

---

## Conceitos Teóricos Subjacentes
- Internamente, o Flex implementa a **construção de Thompson**, que transforma expressões regulares em um **Autômato Finito Não Determinístico (AFND)**.
- Em seguida, ele aplica o **algoritmo de subconjuntos** para converter esse AFND em um **Autômato Finito Determinístico (AFD)**, que é executável e mais eficiente.
- O AFD é então traduzido para código C (o arquivo `lex.yy.c`).

---

## Aplicações
Além de compiladores, o Flex é útil para qualquer tarefa que envolva **filtragem e transformação de texto** ou **análise de dados**.  
É uma ferramenta de "superpoder" que permite resolver problemas rapidamente e de forma eficiente.
