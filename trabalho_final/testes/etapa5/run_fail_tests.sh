#!/bin/bash

# --- Configurações ---
# Caminho relativo fornecido por você
TEST_DIR="../testes/etapa5/test/fail"
# Nome do seu executável (ajuste se necessário, ex: ./etapa5)
COMPILER="./etapa5"

# --- Cores para facilitar a leitura ---
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Verifica se o executável existe
if [ ! -f "$COMPILER" ]; then
    echo -e "${RED}Erro: Executável '$COMPILER' não encontrado neste diretório.${NC}"
    echo "Certifique-se de rodar este script na raiz do projeto (onde está o Makefile/executável)."
    exit 1
fi

# Verifica se o diretório de testes existe
if [ ! -d "$TEST_DIR" ]; then
    echo -e "${RED}Erro: Diretório de testes '$TEST_DIR' não encontrado.${NC}"
    exit 1
fi

echo -e "${BLUE}=========================================================${NC}"
echo -e "${BLUE}    Rodando Testes de Falha (Expectativa: Erros)         ${NC}"
echo -e "${BLUE}=========================================================${NC}"

count_pass=0
count_fail=0

# Loop por todos os arquivos no diretório
for file in "$TEST_DIR"/*; do
    # Garante que é um arquivo
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        
        echo -e "\n---------------------------------------------------------"
        echo -e "Teste: ${YELLOW}$filename${NC}"
        
        # 1. Extrair e mostrar o comentário (descrição do erro esperado)
        # Procura linhas começando com // ou /*
        echo -e "${CYAN}Descrição do Erro Esperado (do arquivo):${NC}"
        comments=$(grep -E "^//|^/\*" "$file")
        if [ -z "$comments" ]; then
            # Se não achar com grep, mostra as 3 primeiras linhas
            head -n 3 "$file"
        else
            echo "$comments"
        fi

        # 2. Executar o compilador
        # Redirecionamos stderr para stdout (2>&1) para capturar mensagens de erro
        output=$($COMPILER < "$file" 2>&1)
        ret_val=$?

        # 3. Validar o resultado
        echo -e "\n${CYAN}Resultado da Execução:${NC}"
        
        if [ $ret_val -ne 0 ]; then
            # SUCESSO: O compilador falhou, como deveria ser
            echo -e "${GREEN}[OK] O compilador rejeitou o código (Exit Code: $ret_val).${NC}"
            echo -e "Mensagem retornada pelo seu parser:"
            echo -e "${RED}$output${NC}" # Mostra em vermelho a mensagem de erro do seu programa
            ((count_pass++))
        else
            # FALHA: O compilador aceitou algo que deveria estar errado
            echo -e "${RED}[FALHA CRÍTICA] O compilador aceitou o código (Exit Code: 0).${NC}"
            echo "Deveria ter retornado erro, mas passou."
            ((count_fail++))
        fi
    fi
done

echo -e "\n========================================================="
echo -e "Resumo:"
echo -e "${GREEN}Passaram (Falharam corretamente): $count_pass${NC}"
if [ $count_fail -gt 0 ]; then
    echo -e "${RED}Falharam (Aceitaram código inválido): $count_fail${NC}"
else
    echo -e "${RED}Falharam (Aceitaram código inválido): 0${NC}"
fi
echo -e "========================================================="