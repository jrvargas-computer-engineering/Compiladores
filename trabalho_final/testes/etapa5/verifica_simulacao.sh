#!/bin/bash

# ================= CONFIGURAÇÕES =================
COMPILADOR="./etapa5"
SIMULADOR="ilocsim.py"

# Caminho padrão (ajuste se necessário)
DIR_PADRAO="../testes/etapa5/test/pass"
DIR_TESTES="${1:-$DIR_PADRAO}"

# Arquivos temporários
MEU_ILOC="temp_meu.iloc"
MINHA_SIM="temp_minha_sim.txt"
REF_SIM="temp_ref_sim.txt"
MEM_MEU="temp_mem_meu.txt"
MEM_REF="temp_mem_ref.txt"

# Cores
VERDE='\033[0;32m'
VERMELHO='\033[0;31m'
AZUL='\033[0;34m'
AMARELO='\033[1;33m'
NC='\033[0m' # No Color

# ================= VERIFICAÇÕES =================
echo -e "${AZUL}>>> Iniciando Verificação (Baseado nos arquivos .iloc)${NC}"
echo "Diretório alvo: $DIR_TESTES"

if [ ! -d "$DIR_TESTES" ]; then
    echo -e "${VERMELHO}[ERRO] Diretório não encontrado!${NC}"
    exit 1
fi

make -s
if [ $? -ne 0 ]; then
    echo -e "${VERMELHO}[ERRO] Falha no make.${NC}"; exit 1;
fi

count_pass=0
count_fail=0

echo "----------------------------------------------------------------------"
printf "%-15s | %-12s | %-12s | %s\n" "Teste" "Compilação" "Simulação" "Status"
echo "----------------------------------------------------------------------"

# ================= LOOP DE TESTES =================
# Itera sobre os gabaritos (.iloc) para encontrar as entradas
for arquivo_gabarito in "$DIR_TESTES"/*.iloc; do
    
    # Se não encontrar nenhum .iloc, o loop pode rodar com o asterisco literal. Abortar.
    [ -e "$arquivo_gabarito" ] || continue

    # Pega o nome base (ex: pass00.iloc -> pass00)
    nome_base=$(basename "$arquivo_gabarito" .iloc)
    
    # Define o arquivo de entrada (sem extensão, conforme sua indicação)
    arquivo_entrada="${arquivo_gabarito%.iloc}"

    # Verifica se o arquivo de entrada realmente existe
    if [ ! -f "$arquivo_entrada" ]; then
        # Tenta com .txt caso exista misturado
        if [ -f "$arquivo_entrada.txt" ]; then
            arquivo_entrada="$arquivo_entrada.txt"
        else
            printf "%-15s | ${AMARELO}%-12s${NC} | %-12s | Entrada não encontrada\n" "$nome_base" "N/A" "N/A"
            continue
        fi
    fi

    # 1. Executa SEU parser
    $COMPILADOR < "$arquivo_entrada" > "$MEU_ILOC" 2> /dev/null
    if [ $? -ne 0 ]; then
        printf "%-15s | ${VERMELHO}%-12s${NC} | %-12s | Erro Compilação\n" "$nome_base" "FALHA" "-"
        ((count_fail++))
        continue
    fi

    # 2. Executa Simulador (Seu ILOC vs Gabarito)
    python3 "$SIMULADOR" -s "$MEU_ILOC" > "$MINHA_SIM" 2>&1
    python3 "$SIMULADOR" -s "$arquivo_gabarito" > "$REF_SIM" 2>&1

    # 3. Compara apenas a memória e registradores (ignora contagem de instruções)
    # O grep pega do início da lista de registradores até o fim
    grep -A 1000 "register" "$MINHA_SIM" > "$MEM_MEU"
    grep -A 1000 "register" "$REF_SIM" > "$MEM_REF"

    diff -w -B "$MEM_MEU" "$MEM_REF" > /dev/null
    ret_diff=$?

    if [ $ret_diff -eq 0 ]; then
        printf "%-15s | ${VERDE}%-12s${NC} | ${VERDE}%-12s${NC} | ${VERDE}OK${NC}\n" "$nome_base" "Sucesso" "Igual"
        ((count_pass++))
    else
        # Tenta comparar só a memória (ignora registradores temporários diferentes)
        grep -A 1000 "memory" "$MINHA_SIM" > "$MEM_MEU"
        grep -A 1000 "memory" "$REF_SIM" > "$MEM_REF"
        diff -w -B "$MEM_MEU" "$MEM_REF" > /dev/null
        
        if [ $? -eq 0 ]; then
             printf "%-15s | ${VERDE}%-12s${NC} | ${AMARELO}%-12s${NC} | ${AMARELO}OK (Regs diferem)${NC}\n" "$nome_base" "Sucesso" "Mem OK"
             ((count_pass++))
        else
             printf "%-15s | ${VERDE}%-12s${NC} | ${VERMELHO}%-12s${NC} | ${VERMELHO}DIFERENTE${NC}\n" "$nome_base" "Sucesso" "Falha"
             ((count_fail++))
        fi
    fi

done

# Limpeza
rm -f "$MEU_ILOC" "$MINHA_SIM" "$REF_SIM" "$MEM_MEU" "$MEM_REF"

echo "----------------------------------------------------------------------"
echo -e "Resumo: ${VERDE}$count_pass passaram${NC} / ${VERMELHO}$count_fail falharam${NC}"