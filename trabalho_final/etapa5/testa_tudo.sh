#!/bin/bash

# Caminho onde estão os testes (ajuste se necessário)
# TEST_DIR="../testes/etapa5/teste_sucesso"
TEST_DIR="../testes/etapa5/teste"

# Verifica se a pasta existe
if [ ! -d "$TEST_DIR" ]; then
    echo "Erro: Pasta de testes '$TEST_DIR' não encontrada."
    exit 1
fi

echo "========================================="
echo " INICIANDO BATERIA DE TESTES (ETAPA 5) "
echo "========================================="

# Contador de testes
count=0

# Loop por todos os arquivos .txt da pasta
for testfile in "$TEST_DIR"/*.txt; do
    # Verifica se existem arquivos (caso o glob não encontre nada)
    [ -e "$testfile" ] || continue

    count=$((count+1))
    filename=$(basename "$testfile")
    
    echo ""
    echo "---------------------------------------------------"
    echo "[$count] Testando: $filename"
    echo "---------------------------------------------------"
    
    # Chama o seu script individual para este arquivo
    # O comando '2>&1' garante que erros também apareçam
    ./rodar.sh "$testfile"
    
    # Verifica o código de saída do rodar.sh (caso você tenha configurado exit codes)
    if [ $? -eq 0 ]; then
        echo ">> Execução finalizada."
    else
        echo ">> ALERTA: Ocorreu um erro na execução deste teste."
    fi
done

echo ""
echo "========================================="
echo " FIM: $count testes executados."
echo "========================================="