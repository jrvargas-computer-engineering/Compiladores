- corrigir erros da etapa 4
- ele rescomenda e estrutura de dados ILOC em formato struct, mas é libre
- assumir que tem infinitos temporários
- geração infinita de rótulos
- tem que manter o sanatize sempre

# geração de código
- uma unica passagem no código para geração de código intermediario
    - criar tudo ao mesmo tempo

# simplificações
- print na tela só no final
- ignorar tipos, vai existir só inteiro
- chamada de função não será traduzido
- existem apenas duas funções 
    - global e função
    - apenas tera tabela global e local
- implimentação de espressões será sempre numérica

# end das variaveis
- simplesmente o deslocamento
- inclusão dos simbolos terá o calculo do deslocamento
- rfp e rdss 
    - fixos
    - definidos
    - não encostar nessas váriaveis o simulador irá decidir

# simulador 
- o simulador ajuda imprimindo o resultado da memória

# implementação professor
- na inserção na tabela q calcula o deslocamento
- A STRUCT TEM QUE TER O VALOR DE DESLOCAMENTO (LEX, VALUE...)

## atribuição:
- primeira coisa é fazer a consulta na tabela
- depois de add o child faz o store do temp
    - store $3.temp 
    - em função do escopo fica sabendo se escreve no rfp ou rdss

### struct asd_tree
- add iloc list
    - iloc_list_t *code;
- add temp
    - temp_t *temp;


# parte subjetiva
-  não pode ignorar
