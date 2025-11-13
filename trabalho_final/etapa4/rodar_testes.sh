#!/bin/bash

# --- Configuração ---
COMPILADOR="./etapa4"
TEST_DIR="../testes/etapa4"
TEST_S_DIR="../testes/E4"
SAIDA_DIR="../testes/etapa4/resultados"
SAIDA_S_DIR="../testes/E4/resultados"
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
    "1_10_grupo_teste.txt"
    "1_12_grupo_vazio.txt"
    "1_1_teste_1_1_sucesso_simples.txt"
    "1_2_teste_1_2_sucesso_funcao.txt"
    "1_3_teste_1_3_sucesso_shadowing.txt"
    "1_4_teste_1_4_sucesso_aninhado.txt"
    "1_5_teste_1_5_sucesso_parametros.txt"
    "1_6_teste_1_6_sucesso_arit_float.txt"
    "1_7_teste_1_7_sucesso_rel_log_int.txt"
    "1_8_grupo_simplesnaovazio.txt"
    "3_8_grupo_redeclaracao_var_dec_nestada.txt"
    "3_9_grupo_redeclaracao_var_int_nestada.txt"
    "3_10_grupo_redeclaracao_var_com_int_nestada.txt"
    "3_11_grupo_redeclaracao_var_com_dec_nestada.txt"
    "6_4_1_8_1_sucesso_funcao_sem_param.txt"
    "6_4_6_8_8_sucesso_aninhada.txt"  
    "6_4_3_8_3_sucesso_dois_params.txt"
    "6_5_sucesso_3_params.txt"
    "6_6_operacao_parametros.txt"
    "teste_final_etapa_3.txt"
)

TESTES_INT_FLOAT=(
    "1_9_grupo_teste_completo.txt"
    "1A_1_8_6_sucesso_promocao.txt"
    "1A_1_8_9_sucesso_promocao_cascata.txt"
    "1A_5_1_err_type_arit.txt"
    "1A_5_2_err_type_rel.txt"
    "1A_5_3_err_type_not.txt"
    "1A_5_4_err_type_mod.txt"
    "1A_5_5_err_type_atrib.txt"
    "1A_5_9_err_type_init.txt"
)

TESTS_UNDECLARED=(
    "2_1_teste_2_1_err_undeclared_var.txt:10"
    "2_2_teste_2_2_err_undeclared_funcao.txt:10"
    "2_3_teste_2_3_err_undeclared_escopo.txt:10"
    "2_4_teste_2_4_err_undeclared_escopo_funcao.txt:10"
    "2_5_grupo_operando_nao_declarado.txt:10"
    "2_6_grupo_atribuicao_nao_declarada.txt:10"
    "2_7_grupo_func_nao_declarada.txt:10"
)

TESTES_DUPLA_DECLARACAO=(
    "3_1_teste_3_1_err_declared_global.txt:11"
    "3_2_teste_3_2_err_declared_funcao.txt:11"
    "3_3_teste_3_3_err_declared_local.txt:11"
    "3_4_grupo_redeclaracao_func_dec.txt:11"
    "3_5_grupo_redeclaracao_func_int.txt:11"
    "3_6_grupo_redeclaracao_var_global_dec.txt:11"
    "3_7_grupo_redeclaracao_var_global_int.txt:11"
)

TESTE_ERR_VARIABLE=(
    "1_11_grupo_var_usada_como_func.txt:20"
    "4_1_teste_4_1_err_variable_used_as_func.txt:20"
    "4_5_grupo_var_usada_como_func.txt:20"
)

TESTE_ERR_FUNCTION=(
    "4_2_teste_4_2_err_function.txt:21"
    "4_3_teste_4_3_err_function_atrib.txt:21"
    "4_4_grupo_func_usada_como_var.txt:21"
)

TESTE_WRONG_TYPE=(
    "5_2_teste_5_6_err_type_retorno.txt:30"
)

TESTE_MISSING_ARGS=(
    "6_1_teste_7_1_err_missing_args.txt:40"
    "6_4_4_8_4_err_missing_arg.txt:40"

)
TESTE_EXCESS_ARGS=(
    "6_2_teste_7_2_err_excess_args.txt:41"
    "6_4_2_8_2_err_excesso_sem_param.txt:41"
    "6_4_5_8_5_err_excesso_args.txt:41"

)
TESTE_WRONG_TYPE_ARGS=(
    "6_3_teste_7_3_err_wrong_type_args.txt:42"
    "6_4_7_8_10_mistos_ok_erro.txt:42"
)

SUCESSO_IF=(
    "7_1_teste_err_type_if.txt"
    "7_2_err_type_while.txt"
    "7_3_if_int.txt"
    "7_4_ifelse_int_int.txt"
    "7_5_if_float.txt"
    "7_6_ifelse_float_float.txt"
    "7_9_if_nested_int.txt"
)

FALHA_IF=(
    "7_7_err_ifelse_int_float.txt:30"
    "7_8_err_ifelse_float_int.txt:30"
    "7_10_err_if_nested_conflict.txt:30"
)

TESTES_S_FALHA=(
    "qwe00:10"
    "qwe01:10"
    "qwe02:10"
    "qwe03:10"
    "qwe10:10"
    "qwe11:10"
    "qwe12:10"
    "qwe13:10"
    "qwe14:10"
    "qwe15:10"
    "qwe16:11"
    "qwe17:11"
    "qwe18:11"
    "qwe19:11"
    "qwe20:11"
    "qwe21:11"
    "qwe22:11"
    "qwe23:11"
    "qwe24:11"
    "qwe27:11"
    "qwe28:11"
    "qwe29:11"
    "qwe34:20"
    "qwe35:20"
    "qwe36:20"
    "qwe37:20"
    "qwe38:21"
    "qwe39:21"
    "qwe40:21"
    "qwe41:21"
    "qwe42:40"
    "qwe43:40"
    "qwe44:41"
    "qwe45:41"
    "qwe46:42"
    "qwe47:42"
    "qwe48:42"
    "qwe49:42"
    "qwe50:42"
    "qwe51:42"
    "qwe52:42"
    "qwe53:42"
    "qwe54:42"
    "qwe55:42"
    "qwe56:42"
    "qwe57:42"
    "qwe58:42"
    "qwe59:42"
    "qwe60:42"
    "qwe61:42"
    "qwe62:42"
    "qwe63:42"
    "qwe64:42"
    "qwe65:30"
    "qwe66:30"
    "qwe67:30"
    "qwe68:30"
    "qwe69:30"
    "qwe70:30"
    "qwe71:30"
    "qwe72:30"
    "qwe73:30"
    "qwe74:30"
    "qwe75:30"
    "qwe76:30"
    "qwe77:30"
    "qwe78:30"
    "qwe79:30"
    "qwe80:30"
    "qwe81:30"
    "qwe82:30"
)


TESTES_S_SUCESSO=(
    "qwe04"
    "qwe05"
    "qwe06"
    "qwe07"
    "qwe08"
    "qwe09"
    "qwe30"
    "qwe31"
    "qwe32"
    "qwe33"
    "qwe25"
    "qwe26"
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
##############################
rodar_teste_s_sucesso() {
    TESTE_ARQUIVO=$1
    CAMINHO_TESTE="$TEST_S_DIR/$TESTE_ARQUIVO"
    
    # === MUDANÇA AQUI: Define nomes de saída dinâmicos ===
    NOME_BASE="${TESTE_ARQUIVO%.txt}"
    CAMINHO_DOT="$SAIDA_S_DIR/$NOME_BASE.dot"
    CAMINHO_PNG="$SAIDA_S_DIR/$NOME_BASE.png"
    
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

rodar_teste_s_falha() {
    TESTE_INFO=$1
    TESTE_ARQUIVO=$(echo "$TESTE_INFO" | cut -d':' -f1)
    CODIGO_ESPERADO=$(echo "$TESTE_INFO" | cut -d':' -f2)
    CAMINHO_TESTE="$TEST_S_DIR/$TESTE_ARQUIVO"
    
    # === MUDANÇA AQUI: Define nome do .dot (para debug) ===
    NOME_BASE="${TESTE_ARQUIVO%.txt}"
    CAMINHO_DOT="$SAIDA_S_DIR/$NOME_BASE.dot"
    
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

if [ ! -d "$TEST_S_DIR" ]; then
    echo -e "${VERMELHO}Erro: Diretório de testes '$TEST_S_DIR' não encontrado.${RESET}"
    echo "Verifique se você está no diretório correto."
    exit 1
fi

if [ ! -d "$SAIDA_S)DIR" ]; then
    echo -e "${CINZA}Info: Diretório de saída '$SAIDA_S)DIR' não encontrado.${RESET}"
    echo -e "${CINZA}Criando diretório...${RESET}"
    mkdir -p "$SAIDA_S_DIR"
    if [ $? -ne 0 ]; then
        echo -e "${VERMELHO}Não foi possível criar o diretório de saída. Saindo.${RESET}"
        exit 1
    fi
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
echo "--- 2. Testes com operação entre INT e FLOAT"
#for teste in "${TESTES_INT_FLOAT[@]}"; do
#    rodar_teste_sucesso "$teste"
#done
echo "comentadas no script de teste"

echo ""
echo "--- 3. Testes ERR_UNDECLARED ---"
for teste in "${TESTS_UNDECLARED[@]}"; do
    rodar_teste_falha "$teste"
done

echo "--- 4. Testes ERR_DECLARED---"
for teste in "${TESTES_DUPLA_DECLARACAO[@]}"; do
    rodar_teste_falha "$teste"
done

echo "--- 5. Testes ERR_VARIABLE ---"
for teste in "${TESTE_ERR_VARIABLE[@]}"; do
    rodar_teste_falha "$teste"
done

echo "--- 6. Testes  ERR_FUNCTION ---"
for teste in "${TESTE_ERR_FUNCTION[@]}"; do
    rodar_teste_falha "$teste"
done

echo "--- 6. Testes  WRONG_TYPE ---"
for teste in "${TESTE_WRONG_TYPE[@]}"; do
    rodar_teste_falha "$teste"
done

echo "--- 6. Testes  ERR_MISSING_ARGS ---"
for teste in "${TESTE_MISSING_ARGS[@]}"; do
    rodar_teste_falha "$teste"
done

echo "--- 6. Testes  ERR_EXCESS_ARGS ---"
for teste in "${TESTE_EXCESS_ARGS[@]}"; do
    rodar_teste_falha "$teste"
done

echo "--- 6. Testes  ERR_WRONG_TYPE_ARGS ---"
for teste in "${TESTE_WRONG_TYPE_ARGS[@]}"; do
    rodar_teste_falha "$teste"
done


echo ""
echo "--- 7. Testes de Sucesso if/while ---"
for teste in "${SUCESSO_IF[@]}"; do
    rodar_teste_sucesso "$teste"
done


echo ""
echo "--- 8. Testes de Erro if/while ---"
for teste in "${FALHA_IF[@]}"; do
    rodar_teste_falha "$teste"
done

echo ""
echo "--- 9. Testes de SUCESSO Schnnor ---"
for teste in "${TESTES_S_SUCESSO[@]}"; do
    rodar_teste_s_sucesso "$teste"
done

echo ""
echo "--- 10. Testes de FALHA Schnorr ---"
for teste in "${TESTES_S_FALHA[@]}"; do
    rodar_teste_s_falha "$teste"
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