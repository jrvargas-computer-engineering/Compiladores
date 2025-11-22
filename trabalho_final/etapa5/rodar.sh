#!/bin/bash

# Verifica se passou o arquivo de entrada
if [ "$#" -ne 1 ]; then
    echo "Uso: ./rodar.sh <arquivo_teste>"
    exit 1
fi

ARQUIVO_ENTRADA=$1
ARQUIVO_ILOC="saida.iloc"

# 1. Executa o Compilador (etapa5)
echo "[1/2] Compilando $ARQUIVO_ENTRADA..."
./etapa5 < "$ARQUIVO_ENTRADA" > "$ARQUIVO_ILOC"

# Verifica se o compilador rodou com sucesso (retorno 0)
if [ $? -ne 0 ]; then
    echo "❌ Erro de Compilação! Abortando."
    echo ">>> CONTEÚDO DE $ARQUIVO_ILOC (Erros/Debug):"
    cat "$ARQUIVO_ILOC"
    echo "--------------------------------------------"
    exit 1
fi

# 2. Executa o Simulador (ilocsim.py)
# -t: Trace (mostra instrução por instrução executando)
# -s: Stats (mostra o resumo da memória no final)
echo "[2/2] Simulando execução..."
echo "---------------------------------------------------"
python3 ilocsim.py -s -t "$ARQUIVO_ILOC"