# Lista de Tarefas - Compiladores Etapa 5 (Geração de Código ILOC)

## 1. Infraestrutura de Dados (Setup)
Antes de gerar código, é preciso ter onde armazená-lo em memória.

- [ ] **Definir a estrutura `ILOC_Node`**: Criar uma struct/classe que represente uma instrução ILOC em memória.
    - Deve conter campos para: Rótulo (opcional), Código da Operação (ex: `add`, `loadAI`), Argumentos (até 3 strings) e Ponteiros (próximo/anterior).
- [ ] **Definir a estrutura de Lista**: Criar funções para manipular listas encadeadas de instruções ILOC.
    - [ ] Função `create_instruction(...)`.
    - [ ] Função `append_instruction(...)` (adiciona no fim).
    - [ ] Função `concat_lists(...)` (une o código de dois nós filhos).
- [ ] **Atualizar a estrutura da AST**: Adicionar campos nos nós da árvore para armazenar os atributos sintetizados:
    - [ ] `code`: Ponteiro para o início da lista de instruções geradas pelo nó.
    - [ ] `temp`: String com o nome do registrador temporário onde o resultado do nó está armazenado (ex: "r5").

## 2. Geradores de Nomes e Tabela de Símbolos
Preparar o terreno para endereçamento e registradores únicos.

- [ ] **Implementar `make_temp()`**: Função que retorna um nome de registrador temporário único a cada chamada (ex: `r0`, `r1`, `r2`...).
- [ ] **Implementar `make_label()`**: Função que retorna um rótulo único a cada chamada (ex: `L0`, `L1`, `L2`...).
- [ ] **Calcular Endereços (Offsets)**: Modificar a inserção na Tabela de Símbolos (provavelmente na Etapa 4 ou início da 5).
    - [ ] Manter um contador de bytes para variáveis Globais (base `rbss`).
    - [ ] Manter um contador de bytes para variáveis Locais (base `rfp`).
    - [ ] Salvar o `offset` calculado dentro da entrada da variável na tabela.

## 3. Geração de Expressões Simples
O objetivo aqui é fazer `x = 2 + 3` funcionar.

- [ ] **Traduzir Literais**: No nó da AST de literal (int), gerar `loadI valor => r_novo`.
- [ ] **Traduzir Variáveis (Leitura)**: No nó identificador:
    - [ ] Buscar o offset e o escopo na tabela de símbolos.
    - [ ] Se global: gerar `loadAI rbss, offset => r_novo`.
    - [ ] Se local: gerar `loadAI rfp, offset => r_novo`.
- [ ] **Traduzir Operações Aritméticas**: Nos nós binários (`+`, `-`, `*`, `/`):
    - [ ] Concatenar lista de código do filho esquerdo + filho direito.
    - [ ] Gerar instrução da operação (ex: `add r_esq, r_dir => r_novo`).
    - [ ] Adicionar instrução ao final da lista.
- [ ] **Traduzir Atribuição**: No nó de atribuição (`=`):
    - [ ] Concatenar código da expressão (filho).
    - [ ] Buscar offset da variável destino.
    - [ ] Gerar `storeAI r_expr => base, offset` (onde base é `rfp` ou `rbss`).

## 4. Expressões Lógicas (Simplificação)
Conforme o enunciado: "Implemente tradução numérica para expressões lógicas".

- [ ] **Comparadores**: Implementar `cmp_EQ`, `cmp_LT`, `cmp_GE`, etc.
    - Eles devem gerar um valor 0 ou 1 em um registrador.
- [ ] **Booleanos**: Implementar `and`, `or` e `xor` (ou `neg`).
    - Usar as instruções aritméticas/lógicas do ILOC (`and r1, r2 => r3`) ao invés de criar desvios (short-circuit não é obrigatório nesta simplificação).

## 5. Controle de Fluxo
A parte mais complexa. Exige uso de `make_label`, `cbr` e `jumpI`.

- [ ] **Implementar IF (sem Else)**:
    - [ ] Gerar código da condição.
    - [ ] Criar 2 labels: `L_true` e `L_next`.
    - [ ] Gerar `cbr r_cond -> L_true, L_next`.
    - [ ] Definir label `L_true`.
    - [ ] Colocar código do bloco IF.
    - [ ] Definir label `L_next`.
- [ ] **Implementar IF-ELSE** (Se a gramática suportar):
    - [ ] Requer 3 labels (`L_true`, `L_false`, `L_next`) e `jumpI` ao final do bloco true.
- [ ] **Implementar WHILE**:
    - [ ] Criar labels `L_cond`, `L_body`, `L_next`.
    - [ ] Definir `L_cond`.
    - [ ] Colocar código da condição.
    - [ ] Gerar `cbr r_cond -> L_body, L_next`.
    - [ ] Definir `L_body`.
    - [ ] Colocar código do bloco do while.
    - [ ] Gerar `jumpI -> L_cond` (loop).
    - [ ] Definir `L_next`.

## 6. Saída e Integração
Garantir que o compilador cospe o resultado correto.

- [ ] **Output na raiz**: Garantir que, ao finalizar a análise sintática, o nó raiz da AST tenha a lista completa concatenada.
- [ ] **Função de Impressão**: Criar rotina que percorre a lista encadeada imprimindo as instruções formatadas (ex: `add r1, r2 => r3`) para a saída padrão (`stdout`).
- [ ] **Main**: Chamar a função de impressão ao final do sucesso da compilação.

## 7. Testes e Validação
- [ ] **Script de Teste**: Criar um script shell que:
    1. Roda `./etapa5 < teste.lang > saida.iloc`
    2. Roda `python3 ilocsim.py -s -t saida.iloc`
- [ ] **Validar Aritmética**: Verificar se o valor final na memória/registradores está correto para contas simples.
- [ ] **Validar Fluxo**: Verificar se o simulador seguiu o caminho correto em ifs e loops.

## 8. Validação com ilocsim.py
- [ ] **Verificar Convenção de Nomes**: Confirmar se `make_temp` gera `rN` e `make_label` gera `LN`.
- [ ] **Teste de Escrita Global**:
    - Criar programa que escreve em variável global.
    - Rodar simulador com `-s`.
    - Verificar se o endereço `0 + offset` contém o valor correto.
- [ ] **Teste de Escrita Local**:
    - Criar programa que escreve em variável local.
    - Rodar simulador com `-s`.
    - Verificar se o endereço `1024 + offset` contém o valor correto.
- [ ] **Debug de Fluxo**:
    - Usar a flag `-t` para ver se os `cbr` e `jumpI` estão indo para os rótulos corretos (`L...`) gerados.