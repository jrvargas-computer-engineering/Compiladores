#!/bin/bash

# --- Configuração ---
COMPILADOR="./etapa4"
TEST_DIR="../testes/etapa4"
SAIDA_DIR="../testes/etapa4/resultados"
TOTAL_TESTES=0
TESTES_PASSARAM=0
# (Cores, etc.)
VERDE='\033[0;32m'
VERMELHO='\033[0;31m'
AZUL='\033[0;34m'
CINZA='\033[0;90m'
RESET='\033[0m'

# --- Listas de Testes (Apenas os nomes dos arquivos) ---

TESTES_SUCESSO=(
    "teste_1_1_sucesso_simples.txt"
    "teste_1_2_sucesso_funcao.txt"
    "teste_1_3_sucesso_shadowing.txt"
    "teste_1_4_sucesso_aninhado.txt"
    "teste_1_5_sucesso_parametros.txt"
    # === NOVOS TESTES (Passo 6) ===
    "teste_1_6_sucesso_arit_float.txt"
    "teste_1_7_sucesso_rel_log_int.txt"
)

TESTES_FALHA=(
    # (Passo 4/5)
    "teste_2_1_err_undeclared_var.txt:10"
    "teste_2_2_err_undeclared_funcao.txt:10"
    "teste_2_3_err_undeclared_escopo.txt:10"
    "teste_2_4_err_undeclared_escopo_funcao.txt:10"
    "teste_3_1_err_declared_global.txt:11"
    "teste_3_2_err_declared_funcao.txt:11"
    "teste_3_3_err_declared_local.txt:11"
    "teste_4_1_err_variable.txt:20"
    "teste_4_2_err_function.txt:21"
    "teste_4_3_err_function_atrib.txt:21"
    # === NOVOS TESTES (Passo 6: ERR_WRONG_TYPE) ===
    "teste_5_1_err_type_arit.txt:30"
    "teste_5_2_err_type_rel.txt:30"
    "teste_5_3_err_type_not.txt:30"
    "teste_5_4_err_type_mod.txt:30"
    "teste_5_5_err_type_atrib.txt:30"
    "teste_5_6_err_type_retorno.txt:30"
    "teste_5_7_err_type_if.txt:30"
    "teste_5_8_err_type_while.txt:30"
    "teste_5_9_err_type_init.txt:30"

    ##
    "teste_7_1_err_missing_args.txt:40"
    "teste_7_2_err_excess_args.txt:41"
    "teste_7_3_err_wrong_type_args.txt:42"
)

# --- Funções de Teste (rodar_teste_sucesso, rodar_teste_falha) ---
# (Cole as funções da sua versão anterior do script aqui)
# (Elas já estão corretas, com a captura de erro e
#  criação de .dot e .png no SAIDA_DIR)
# ...
rodar_teste_sucesso() {
    TESTE_ARQUIVO=$1
    CAMINHO_TESTE="$TEST_DIR/$TESTE_ARQUIVO"
    
    # === MUDANÇA AQUI: Define nomes de saída dinâmicos ===
    NOME_BASE="${TESTE_ARQUIVO%.txt}"
    CAMINHO_DOT="$SAIDA_DIR/$NOME_BASE.dot"
    CAMINHO_PNG="$SAIDA_DIR/$NOME_BASE.png"
    
    echo -n -e "${AZUL}Rodando (sucesso) ${RESET}: $TESTE_ARQUIVO..."
    TOTAL_TESTES=$((TOTAL_TESTES + 1))

    if [ ! -f "$CAMINHO_TESTE" ]; then
        echo -e " ${VERMELHO}[FALHOU]${RESET} (Arquivo $CAMINHO_TESTE não encontrado)"
        return
    fi

    # === MUDANÇA AQUI: Redireciona para o CAMINHO_DOT ===
    ERRO_SAIDA=$({ $COMPILADOR < "$CAMINHO_TESTE" > "$CAMINHO_DOT"; } 2>&1)
    CODIGO_SAIDA=$?

    if [ $CODIGO_SAIDA -eq 0 ]; then
        echo -e " ${VERDE}[PASSOU]${RESET} (Código 0)"
        TESTES_PASSARAM=$((TESTES_PASSARAM + 1))
        
        # === MUDANÇA AQUI: Usa os caminhos de .dot e .png ===
        dot "$CAMINHO_DOT" -Tpng -o "$CAMINHO_PNG"
    else
        echo -e " ${VERMELHO}[FALHOU]${RESET} (Esperava 0, recebeu $CODIGO_SAIDA)"
        if [ ! -z "$ERRO_SAIDA" ]; then
            echo -e "   ${VERMELHO}Saída(stderr):${RESET} $ERRO_SAIDA"
        else
            echo -e "   ${VERMELHO}(Programa não emitiu saída de erro)${RESET}"
        fi
    fi
}

rodar_teste_falha() {
    TESTE_INFO=$1
    TESTE_ARQUIVO=$(echo "$TESTE_INFO" | cut -d':' -f1)
    CODIGO_ESPERADO=$(echo "$TESTE_INFO" | cut -d':' -f2)
    CAMINHO_TESTE="$TEST_DIR/$TESTE_ARQUIVO"
    
    # === MUDANÇA AQUI: Define nome do .dot (para debug) ===
    NOME_BASE="${TESTE_ARQUIVO%.txt}"
    CAMINHO_DOT="$SAIDA_DIR/$NOME_BASE.dot"
    
    echo -n -e "${AZUL}Rodando (falha)   ${RESET}: $TESTE_ARQUIVO..."
    TOTAL_TESTES=$((TOTAL_TESTES + 1))

    if [ ! -f "$CAMINHO_TESTE" ]; then
        echo -e " ${VERMELHO}[FALHOU]${RESET} (Arquivo $CAMINHO_TESTE não encontrado)"
        return
    fi

    # === MUDANÇA AQUI: Redireciona para o CAMINHO_DOT ===
    # (O .dot provavelmente ficará vazio se o compilador sair com erro, o que é ok)
    ERRO_SAIDA=$({ $COMPILADOR < "$CAMINHO_TESTE" > "$CAMINHO_DOT"; } 2>&1)
    CODIGO_SAIDA=$?

    if [ $CODIGO_SAIDA -eq "$CODIGO_ESPERADO" ]; then
        echo -e " ${VERDE}[PASSOU]${RESET} (Recebeu código $CODIGO_SAIDA, como esperado)"
        TESTES_PASSARAM=$((TESTES_PASSARAM + 1))
        if [ ! -z "$ERRO_SAIDA" ]; then
            echo -e "   ${CINZA}Saída(stderr):${RESET} $ERRO_SAIDA"
        else
            echo -e "   ${CINZA}(Programa saiu com código $CODIGO_SAIDA, mas sem saída de erro)${RESET}"
        fi
    elif [ $CODIGO_SAIDA -eq 0 ]; then
        echo -e " ${VERMELHO}[FALHOU]${RESET} (Esperava $CODIGO_ESPERADO, recebeu 0 - NÃO PEGOU O ERRO)"
    else
        echo -e " ${VERMELHO}[FALHOU]${RESET} (Esperava $CODIGO_ESPERADO, recebeu $CODIGO_SAIDA - CÓDIGO ERRADO)"
    fi
    
    if [ $CODIGO_SAIDA -ne "$CODIGO_ESPERADO" ]; then
        if [ ! -z "$ERRO_SAIDA" ]; then
            echo -e "   ${VERMELHO}Saída(stderr):${RESET} $ERRO_SAIDA"
        else
            echo -e "   ${VERMELHO}(Programa não emitiu saída de erro)${RESET}"
        fi
    fi
}
# ...

# --- Execução ---

echo "--- Iniciando Testes da Etapa 4 ---"

if [ ! -f "$COMPILADOR" ]; then
    echo -e "${VERMELHO}Erro: Compilador '$COMPILADOR' não encontrado.${RESET}"
    echo "Por favor, compile seu projeto (ex: make) e tente novamente."
    exit 1
fi

if [ ! -d "$TEST_DIR" ]; then
    echo -e "${VERMELHO}Erro: Diretório de testes '$TEST_DIR' não encontrado.${RESET}"
    echo "Verifique se você está no diretório correto."
    exit 1
fi

if [ ! -d "$SAIDA_DIR" ]; then
    echo -e "${CINZA}Info: Diretório de saída '$SAIDA_DIR' não encontrado.${RESET}"
    echo -e "${CINZA}Criando diretório...${RESET}"
    mkdir -p "$SAIDA_DIR"
    if [ $? -ne 0 ]; then
        echo -e "${VERMELHO}Não foi possível criar o diretório de saída. Saindo.${RESET}"
        exit 1
    fi
fi


echo ""
echo "--- 1. Testes de Sucesso (Devem retornar 0) ---"
for teste in "${TESTES_SUCESSO[@]}"; do
    rodar_teste_sucesso "$teste"
done

echo ""
echo "--- 2. Testes de Falha (Devem retornar códigos de erro) ---"
for teste in "${TESTES_FALHA[@]}"; do
    rodar_teste_falha "$teste"
done


echo ""
echo "--- Resumo dos Testes ---"
if [ $TESTES_PASSARAM -eq $TOTAL_TESTES ]; then
    echo -e "${VERDE}TODOS OS $TOTAL_TESTES TESTES PASSARAM!${RESET}"
else
    FALHAS=$((TOTAL_TESTES - TESTES_PASSARAM))
    echo -e "${VERMELHO}$FALHAS de $TOTAL_TESTES testes FALHARAM.${RESET}"
fi
echo "--------------------------"