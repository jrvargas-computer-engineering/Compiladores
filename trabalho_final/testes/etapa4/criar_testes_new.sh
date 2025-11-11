#!/bin/bash

echo "Gerando arquivos de teste organizados da Etapa E4 (Análise Semântica)..."
echo

# -----------------------------
# 1) TESTES DE SUCESSO (CÓDIGO 0)
# -----------------------------
echo "--- Grupo 1: Testes de SUCESSO (código 0) ---"

echo "1.1 - testando casos simples de sucesso"
cat > 1_1_teste_1_1_sucesso_simples.txt << 'EOF'
var x := inteiro,
main -> inteiro :=
[
  x := 10
]
;
EOF

echo "1.2 - função simples de sucesso"
cat > 1_2_teste_1_2_sucesso_funcao.txt << 'EOF'
f -> inteiro := [
    retorna 10 := inteiro
],
main -> inteiro :=
[
    f()
]
;
EOF

echo "1.3 - shadowing local com sucesso"
cat > 1_3_teste_1_3_sucesso_shadowing.txt << 'EOF'
var x := inteiro,
f -> inteiro := [
    var x := decimal
    x := 10.5
    retorna 5 := inteiro
],
main -> inteiro :=
[
    x := 5
]
;
EOF

echo "1.4 - blocos aninhados com sucesso"
cat > 1_4_teste_1_4_sucesso_aninhado.txt << 'EOF'
var x := inteiro,
main -> inteiro :=
[
    [
        var y := inteiro
        [
            var z := inteiro
            x := y + z 
        ]
    ]
]
;
EOF

echo "1.5 - parâmetros funcionando"
cat > 1_5_teste_1_5_sucesso_parametros.txt << 'EOF'
soma -> inteiro com a := inteiro, b := inteiro :=
[
    retorna a + b := inteiro
],

main -> inteiro :=
[
    var resultado := inteiro
    resultado := soma(5, 10)
    retorna resultado := inteiro
]
;
EOF

echo "1.6 - aritmética com float (sucesso)"
cat > 1_6_teste_1_6_sucesso_arit_float.txt << 'EOF'
main -> inteiro :=
[
    var f1 := decimal
    var f2 := decimal
    f1 := 10.5
    f2 := 2.0
    f1 := f1 * (f2 + f1 / f2 - f2)
]
;
EOF

echo "1.7 - operadores relacionais e lógicos com inteiros (sucesso)"
cat > 1_7_teste_1_7_sucesso_rel_log_int.txt << 'EOF'
main -> inteiro :=
[
    var i := inteiro
    i := 10
    se ( (i < 100 & i > 5) | (i == 10 & i != 11) )
    [
        i := 1
    ]
    senao
    [
        i := 0
    ]
]
;
EOF

echo "1.8 - teste simples vazio / função com lista vazia (sucesso)"
cat > 1_8_grupo_simplesnaovazio.txt << 'EOF'
ex_func1 -> inteiro ex_parametro_sem_com := inteiro := [ ];
EOF


echo "1.10 - teste genérico complexo (misturado)"
cat > 1_10_grupo_teste.txt << 'EOF'
var j := inteiro,
var k := inteiro,
var ex_id := inteiro,
var ex_id2 := inteiro,
var teste_args := inteiro,
var c := inteiro,
var teste_atrib := inteiro,
var a := inteiro,
var b := inteiro,

ex_chamada_func -> inteiro := 
[
    retorna 1 := inteiro
],

chamada_funcao -> inteiro com arg1 := inteiro, arg2 := decimal := 
[
    retorna 0 := inteiro
],

// --- Código Original (Corrigido) ---

ex_func1 -> inteiro com ex_parametro_sem_com_e_virgula := inteiro := 
[ 
    se (j > k) [
        var decl_variavel_com_inic := inteiro com 10
        var decl_variavel := decimal
    ]
    
    enquanto ((2+2)*!ex_id | (ex_id2 & ex_chamada_func()) % 3) [
        
        chamada_funcao(teste_args, 12.43) 
        
        retorna c := inteiro
        teste_atrib := a + b
    ]
], 

ex_func2 -> decimal com param := inteiro, param2 := decimal := 
[
]
; 
EOF

echo "1.11 - grupo_var_usada_como_func (incluir como sucesso? manter conteúdo original)"
cat > 1_11_grupo_var_usada_como_func.txt << 'EOF'
funcao_constante -> decimal :=
[
    var contador := inteiro
    var resultado_decimal := decimal com 1.0
    var var_usada_como_func := decimal com 1.0
    resultado_decimal := var_usada_como_func(contador, contador + 1)

    retorna 3.14 := decimal
];
EOF

echo "1.12 - grupo_vazio (arquivo vazio)"
cat > 1_12_grupo_vazio.txt << 'EOF'

EOF



echo "3.8 - redeclaração variável local decimal aninhada (arquivo original)"
cat > 3_8_grupo_redeclaracao_var_dec_nestada.txt << 'EOF'
principal -> inteiro :=
[
    enquanto (1)
    [
        var variavel_decimal := decimal

        se (1)
        [
            se (0)
            [
                
            ]
            senao
            [
                var variavel_decimal := decimal
            ]
        ]
    ]

    retorna 0 := inteiro
];
EOF

echo "3.9 - redeclaração variável local inteiro aninhada (arquivo original)"
cat > 3_9_grupo_redeclaracao_var_int_nestada.txt << 'EOF'
principal -> inteiro :=
[
    enquanto (1)
    [
        var variavel_inteira := inteiro

        se (1)
        [
            se (0)
            [
                
            ]
            senao
            [
                var variavel_inteira := inteiro
            ]
        ]
    ]

    retorna 0 := inteiro
];
EOF

echo "3.10 - redeclaração variável com int inicialização em bloco (arquivo original)"
cat > 3_10_grupo_redeclaracao_var_com_int_nestada.txt << 'EOF'
principal -> inteiro :=
[
    enquanto (1)
    [
        var variavel_inteira := inteiro com 1

        se (1)
        [
            se (0)
            [
                
            ]
            senao
            [
                var variavel_inteira := inteiro com 2
            ]
        ]
    ]

    retorna 0 := inteiro
];
EOF

echo "3.11 - redeclaração variável com decimal inicialização em bloco (arquivo original)"
cat > 3_11_grupo_redeclaracao_var_com_dec_nestada.txt << 'EOF'
principal -> inteiro :=
[
    enquanto (1)
    [
        var variavel_decimal := decimal com 1.0

        se (1)
        [
            se (0)
            [
                
            ]
            senao
            [
                var variavel_decimal := decimal com 2.0
            ]
        ]
    ]

    retorna 0 := inteiro
];
EOF


echo "6.4 - testes adicionais de argumentos e chamadas" 

cat > 6_4_1_8_1_sucesso_funcao_sem_param.txt << 'EOF'
funcao_constante -> decimal :=
[
    retorna 3.14 := decimal
],

principal -> inteiro :=
[
    var x := decimal
    x := funcao_constante()
    retorna 0 := inteiro
];
EOF

cat > 6_4_6_8_8_sucesso_aninhada.txt << 'EOF'
dobro -> inteiro com x := inteiro :=
[
    retorna x * 2 := inteiro
],

triplo -> inteiro com y := inteiro :=
[
    retorna y * 3 := inteiro
],

principal -> inteiro :=
[
    var r := inteiro
    r := triplo(dobro(5))
    retorna 0 := inteiro
];
EOF


cat > 6_4_3_8_3_sucesso_dois_params.txt << 'EOF'
soma -> inteiro com a := inteiro, b := inteiro :=
[
    retorna a + b := inteiro
],

principal -> inteiro :=
[
    var z := inteiro
    z := soma(2, 3)
    retorna 0 := inteiro
];
EOF


# -------------------------------------------
# 1A) SUBGRUPO: OPERAÇÕES ENTRE INT E FLOAT
# -------------------------------------------
echo ""
echo "--- Subgrupo 1A: Operações entre int e float (separados) ---"

echo "1.9 - teste completo (sucesso)"
cat > 1_9_grupo_teste_completo.txt << 'EOF'
// Teste completo explorando todas as funcionalidades da linguagem.
// Agora cobrindo inclusive operadores compostos, OU lógico, 
// inicialização com inteiro, função retornando decimal e chamada sem argumentos.

// Declaração de variável global (sem inicialização, como manda a regra)
var g_variavel_inteira := inteiro,

// Função sem parâmetros (retorno decimal, para testar)
funcao_constante -> decimal :=
[
    retorna 3.14 := decimal
],

// Definição de uma função com múltiplos parâmetros.
soma_e_multiplica -> inteiro com a := inteiro, b := inteiro :=
[
    // Declaração de variável local sem inicialização.
    var resultado := inteiro

    // Comando de atribuição com expressão aritmética.
    resultado := a + b * 2

    // Comando de retorno com expressão.
    retorna resultado := inteiro
],

// Definição da função principal, sem parâmetros.
principal -> inteiro :=
[
    // Declaração de variáveis locais.
    var contador := inteiro
    var resultado_decimal := decimal com 1.0
    var inicializado_inteiro := inteiro com 42

    // Comando de atribuição com literal inteiro.
    contador := -contador + (+inicializado_inteiro)
    contador := 0
    g_variavel_inteira := 100

    // Comando de controle de fluxo: ENQUANTO.
    enquanto (contador < 10 & !(g_variavel_inteira == 0))
    [
        // Comando de controle de fluxo: SE / SENAO.
        // Aqui usamos todos os operadores compostos e o OU (|).
        se ((contador <= 5) | (g_variavel_inteira >= 50))
        [
            resultado_decimal := (soma_e_multiplica(contador, contador + 1) * 3) / 2.0
        ]
        senao
        [
            // Teste de operadores compostos restantes.
            se (contador != 7)
            [
                resultado_decimal := funcao_constante()  // chamada sem argumentos
            ]
            senao
            [
                resultado_decimal := 0.0
            ]
        ]

        // Atribuição com expressão para incrementar o contador.
        contador := contador + 1
    ]

    // Comando de retorno com valor literal.
    retorna 0 := inteiro
];
EOF



echo "1A.1 - sucesso: promoção int->float em chamada de função"
cat > 1A_1_8_6_sucesso_promocao.txt << 'EOF'
multiplica_decimal -> decimal com a := decimal, b := decimal :=
[
    retorna a * b := decimal
],

principal -> inteiro :=
[
    var d := decimal
    d := multiplica_decimal(3, 2.5)
    retorna 0 := inteiro
];
EOF

echo "1A.2 - sucesso: promoção em cascata com operação float"
cat > 1A_1_8_9_sucesso_promocao_cascata.txt << 'EOF'
soma -> inteiro com a := inteiro, b := inteiro :=
[
    retorna a + b := inteiro
],

principal -> inteiro :=
[
    var x := decimal
    x := (soma(2, 3) * 4) / 2.0
    retorna 0 := inteiro
];
EOF

echo "1A.3 - erro: operação aritmética int + float (deve falhar)"
cat > 1A_5_1_err_type_arit.txt << 'EOF'
main -> inteiro :=
[
    var i := inteiro
    var f := decimal
    i := 5
    f := 2.0
    i := i + f  
]
;
EOF

echo "1A.4 - erro: comparação entre int e float"
cat > 1A_5_2_err_type_rel.txt << 'EOF'
main -> inteiro :=
[
    var i := inteiro
    var f := decimal
    i := 5
    f := 5.0
    se (i == f) 
    [
        i := 1
    ]
]
;
EOF

echo "1A.5 - erro: operador NOT em float"
cat > 1A_5_3_err_type_not.txt << 'EOF'
main -> inteiro :=
[
    var f := decimal
    f := 5.0
    se (!f) 
    [
        f := 1.0
    ]
]
;
EOF

echo "1A.6 - erro: operador % com float"
cat > 1A_5_4_err_type_mod.txt << 'EOF'
main -> inteiro :=
[
    var f := decimal
    var i := inteiro
    f := 5.0
    i := 10 % f 
]
;
EOF

echo "1A.7 - erro: atribuição int := float"
cat > 1A_5_5_err_type_atrib.txt << 'EOF'
main -> inteiro :=
[
    var i := inteiro
    i := 5.0 
]
;
EOF

echo "1A.8 - erro: inicialização com tipo incorreto (decimal com inteiro literal)"
cat > 1A_5_9_err_type_init.txt << 'EOF'
main -> inteiro :=
[
    var d := decimal com 5 
]
;
EOF

echo

# -----------------------------
# 2) TESTES DE ERRO: DECLARAÇÕES (ERR_UNDECLARED = 10)
# -----------------------------
echo "--- Grupo 2: ERR_UNDECLARED (código 10) ---"

echo "2.1 - variavel não declarada"
cat > 2_1_teste_2_1_err_undeclared_var.txt << 'EOF'
main -> inteiro :=
[
    x := 5
]
;
EOF

echo "2.2 - chamada de função não declarada"
cat > 2_2_teste_2_2_err_undeclared_funcao.txt << 'EOF'
main -> inteiro :=
[
    funcao_fantasma()
]
;
EOF

echo "2.3 - uso fora de escopo (variável definida em bloco)"
cat > 2_3_teste_2_3_err_undeclared_escopo.txt << 'EOF'
main -> inteiro :=
[
    [
        var x := inteiro
    ]
    x := 5
]
;
EOF

echo "2.4 - uso de variável definida apenas em outra função (undeclared em função)"
cat > 2_4_teste_2_4_err_undeclared_escopo_funcao.txt << 'EOF'
f1 -> inteiro := [
    var x := inteiro
],

f2 -> inteiro := [
    x := 10 
]
;
EOF

echo "2.5 - grupo_operando_nao_declarado (arquivo original)"
cat > 2_5_grupo_operando_nao_declarado.txt << 'EOF'
soma_e_multiplica -> inteiro com a := inteiro, b := inteiro :=
[
    var resultado_decimal := inteiro
    resultado_decimal := nao_declarado * 3

    retorna 0 := inteiro
]
;
EOF

echo "2.6 - grupo_atribuicao_nao_declarada (arquivo original)"
cat > 2_6_grupo_atribuicao_nao_declarada.txt << 'EOF'
soma_e_multiplica -> inteiro com a := inteiro, b := inteiro :=
[
    resultado_decimal := 3

    retorna 0 := inteiro
]
;
EOF

echo "2.7 - grupo_func_nao_declarada (arquivo original)"
cat > 2_7_grupo_func_nao_declarada.txt << 'EOF'
funcao_constante -> decimal :=
[
    var resultado_decimal := decimal com 1.0
    resultado_decimal := var_usada_como_func(contador, contador + 1)

    retorna 3.14 := decimal
]
;
EOF

echo

# ---------------------------------------
# 3) TESTES DE ERRO: DUPLA DECLARAÇÃO (ERR_DECLARED = 11)
# ---------------------------------------
echo "--- Grupo 3: ERR_DECLARED (código 11) ---"

echo "3.1 - dupla declaração global"
cat > 3_1_teste_3_1_err_declared_global.txt << 'EOF'
var x := inteiro,
var y := decimal,
var x := inteiro 
;
EOF

echo "3.2 - dupla declaração de função"
cat > 3_2_teste_3_2_err_declared_funcao.txt << 'EOF'
f -> inteiro := [ ],
g -> inteiro := [ ],
f -> decimal := [ ] 
;
EOF

echo "3.3 - dupla declaração local/confusa (nested)"
cat > 3_3_teste_3_3_err_declared_local.txt << 'EOF'
main -> inteiro :=
[
    var x := inteiro
    [
        var y := inteiro
        var x := decimal 
    ]
    var x := decimal 
]
;
EOF

echo "3.4 - redeclaração de função decimal (arquivo original)"
cat > 3_4_grupo_redeclaracao_func_dec.txt << 'EOF'
funcao_decimal -> decimal :=
[
    retorna 3.14 := decimal
],

funcao_decimal -> decimal :=
[
    retorna 3.14 := decimal
];
EOF

echo "3.5 - redeclaração de função inteiro (arquivo original)"
cat > 3_5_grupo_redeclaracao_func_int.txt << 'EOF'
funcao_inteiro -> inteiro :=
[
    retorna 3 := inteiro
],

funcao_inteiro -> inteiro :=
[
    retorna 3 := inteiro
];
EOF

echo "3.6 - redeclaração variável global decimal (arquivo original)"
cat > 3_6_grupo_redeclaracao_var_global_dec.txt << 'EOF'
var g_variavel_decimal := decimal,
var g_variavel_decimal := decimal;
EOF

echo "3.7 - redeclaração variável global inteiro (arquivo original)"
cat > 3_7_grupo_redeclaracao_var_global_int.txt << 'EOF'
var g_variavel_inteira := inteiro,
var g_variavel_inteira := inteiro;
EOF

echo
# ---------------------------------------
# 4) TESTES DE ERRO: USO INCORRETO (ERR_VARIABLE = 20 / ERR_FUNCTION = 21)
# ---------------------------------------
echo "--- Grupo 4: Uso incorreto de identificadores (ERR_VARIABLE/ERR_FUNCTION) ---"

echo "4.1 - variável usada como função (ERR_VARIABLE)"
cat > 4_1_teste_4_1_err_variable_used_as_func.txt << 'EOF'
var x := inteiro,
main -> inteiro :=
[
    x(10) 
]
;
EOF

echo "4.2 - função usada como variável em expressão (ERR_FUNCTION)"
cat > 4_2_teste_4_2_err_function.txt << 'EOF'
f -> inteiro := [ ],
main -> inteiro :=
[
    var x := inteiro
    x := f + 5 
]
;
EOF

echo "4.3 - atribuição da função para variável (ERR_FUNCTION/usage)"
cat > 4_3_teste_4_3_err_function_atrib.txt << 'EOF'
var x := inteiro,
f -> inteiro := [ ],
main -> inteiro :=
[
    x := f 
]
;
EOF

echo "4.4 - grupo_func_usada_como_var (arquivo original) - função usada como variável"
cat > 4_4_grupo_func_usada_como_var.txt << 'EOF'
func_usada_como_var -> decimal :=
[
    retorna 3.14 := decimal
],

soma_e_multiplica -> inteiro com a := inteiro, b := inteiro :=
[
    var resultado_decimal := inteiro
    resultado_decimal := func_usada_como_var * 3

    retorna 0 := inteiro
]
;
EOF

echo "4.5 - grupo_var_usada_como_func (arquivo original) - variável usada como função"
cat > 4_5_grupo_var_usada_como_func.txt << 'EOF'
funcao_constante -> decimal :=
[
    var contador := inteiro
    var resultado_decimal := decimal com 1.0
    var var_usada_como_func := decimal com 1.0
    resultado_decimal := var_usada_como_func(contador, contador + 1)

    retorna 3.14 := decimal
];
EOF

echo

# ---------------------------------------
# 5) TESTES DE ERRO: TIPAGEM (ERR_WRONG_TYPE = 30)
# ---------------------------------------
echo "--- Grupo 5: ERR_WRONG_TYPE (código 30) ---"

echo "5.2 - testando retorno com tipo errado"
cat > 5_2_teste_5_6_err_type_retorno.txt << 'EOF'
main -> decimal :=
[
    retorna 5 := decimal 
]
;
EOF

echo

# ---------------------------------------
# 6) TESTES DE ERRO: ARGUMENTOS (ERR_MISSING_ARGS=40 / ERR_EXCESS_ARGS=41 / ERR_WRONG_TYPE_ARGS=42)
# ---------------------------------------
echo "--- Grupo 6: Erros de argumentos (ERR_MISSING_ARGS/ERR_EXCESS_ARGS/ERR_WRONG_TYPE_ARGS) ---"

echo "6.1 - falta de argumento em chamada"
cat > 6_1_teste_7_1_err_missing_args.txt << 'EOF'
soma -> inteiro com a := inteiro, b := inteiro :=
[
    retorna a + b := inteiro
],
main -> inteiro :=
[
    soma(5) 
]
;
EOF

echo "6.2 - excesso de argumentos em chamada"
cat > 6_2_teste_7_2_err_excess_args.txt << 'EOF'
soma -> inteiro com a := inteiro :=
[
    retorna a := inteiro
],
main -> inteiro :=
[
    soma(5, 10) 
]
;
EOF

echo "6.3 - tipo errado em argumentos de função"
cat > 6_3_teste_7_3_err_wrong_type_args.txt << 'EOF'
soma -> inteiro com a := inteiro, b := decimal :=
[
    retorna a := inteiro
],
main -> inteiro :=
[
    var f := decimal
    f := 10.5
    soma(f, 5) 
]
;
EOF

echo "6.4 - testes adicionais de argumentos e chamadas (erro mistos)"


cat > 6_4_2_8_2_err_excesso_sem_param.txt << 'EOF'
funcao_constante -> inteiro :=
[
    retorna 1 := inteiro
],

principal -> inteiro :=
[
    var y := inteiro
    y := funcao_constante(10)
    retorna 0 := inteiro
];
EOF


cat > 6_4_4_8_4_err_missing_arg.txt << 'EOF'
subtrai -> inteiro com a := inteiro, b := inteiro :=
[
    retorna a - b := inteiro
],

principal -> inteiro :=
[
    var r := inteiro
    r := subtrai(5)
    retorna 0 := inteiro
];
EOF

cat > 6_4_5_8_5_err_excesso_args.txt << 'EOF'
produto -> inteiro com a := inteiro, b := inteiro :=
[
    retorna a * b := inteiro
],

principal -> inteiro :=
[
    var r := inteiro
    r := produto(2, 3, 4)
    retorna 0 := inteiro
];
EOF


cat > 6_4_7_8_10_mistos_ok_erro.txt << 'EOF'
mistura -> decimal com a := decimal, b := decimal, c := inteiro :=
[
    retorna (a * b) := decimal
],

principal -> inteiro :=
[
    var r := decimal
    r := mistura(2.1, 3.5, 4)  
    r := mistura(2, 3.5, 4) // erro: primeiro argumento deveria ser decimal
    retorna 0 := inteiro
];

EOF


cat > 6_5_sucesso_3_params.txt << 'EOF'
soma -> inteiro com a := inteiro, b := inteiro, c := inteiro :=
[
    retorna a + b := inteiro
],

principal -> inteiro :=
[
    var z := inteiro
    z := soma(2, 3, 4)
    retorna 0 := inteiro
];

EOF

cat > 6_6_operacao_parametros.txt << 'EOF'
soma -> inteiro com a := inteiro, b := inteiro, c := inteiro :=
[
    retorna a + b := inteiro
],

principal -> inteiro :=
[
    var z := inteiro
    var y := inteiro
    z := soma(2, 3, (4 + y))
    retorna 0 := inteiro
];

EOF



# ---------------------------------------
# 7) TESTE IF ELSE
# ---------------------------------------

echo "7.1 - se com teste não-booleano (float)"
cat > 7_1_teste_err_type_if.txt << 'EOF'
main -> inteiro :=
[
    var f := decimal
    f := 1.0
    se (f) 
    [
        f := 0.0
    ]
]
;
EOF

echo "7.2 - enquanto com teste não-booleano (float)"
cat > 7_2_err_type_while.txt << 'EOF'
main -> inteiro :=
[
    var f := decimal
    f := 1.0
    enquanto (f) 
    [
        f := 0.0
    ]
]
;
EOF

echo "7.3 - if simples com bloco int"
cat > 7_3_if_int.txt << 'EOF'
main -> inteiro := 
[
    var i := inteiro
    se (i < 10)
    [
        i := 1
    ]
]
;
EOF

echo "7.4 - if-else com blocos int"
cat > 7_4_ifelse_int_int.txt << 'EOF'
main -> inteiro := 
[
    var i := inteiro
    se (i > 5)
    [
        i := 1
    ]
    senao
    [
        i := 0
    ]
]
;
EOF

echo "7.5 - if simples com bloco float"
cat > 7_5_if_float.txt << 'EOF'
main -> decimal := 
[
    var f := decimal
    se (f < 3.5)
    [
        f := 0.1
    ]
]
;
EOF

echo "7.6 - if-else com blocos float"
cat > 7_6_ifelse_float_float.txt << 'EOF'
main -> decimal := 
[
    var f := decimal
    se (f == 0.0)
    [
        f := 2.0
    ]
    senao
    [
        f := 4.0
    ]
]
;
EOF

echo "7.7 - if-else com blocos int e float (erro esperado)"
cat > 7_7_err_ifelse_int_float.txt << 'EOF'
main -> inteiro := 
[
    var i := inteiro
    var f := decimal
    se (i == 10)
    [
        i := 1
    ]
    senao
    [
        f := 2.0
    ]
]
;
EOF

echo "7.8 - if-else com blocos float e int (erro esperado)"
cat > 7_8_err_ifelse_float_int.txt << 'EOF'
main -> decimal := 
[
    var i := inteiro
    var f := decimal
    se (f < 1.0)
    [
        f := 3.2
    ]
    senao
    [
        i := 0
    ]
]
;
EOF

echo "7.9 - if aninhado com blocos int (ok)"
cat > 7_9_if_nested_int.txt << 'EOF'
main -> inteiro := 
[
    var i := inteiro
    se (i < 5)
    [
        se (i == 1)
        [
            i := 2
        ]
        senao
        [
            i := 3
        ]
    ]
    senao
    [
        i := 4
    ]
]
;
EOF

echo "7.10 - if aninhado com conflito interno (erro esperado)"
cat > 7_10_err_if_nested_conflict.txt << 'EOF'
main -> inteiro := 
[
    var i := inteiro
    var f := decimal
    se (i < 5)
    [
        se (i == 1)
        [
            f := 2.0
        ]
        senao
        [
            i := 3
        ]
    ]
    senao
    [
        i := 4
    ]
]
;
EOF


# ---------------------------------------
# FINAL) TESTE IGUAL ETAPA 3
# ---------------------------------------
cat > teste_final_etapa_3.txt << 'EOF'
// Teste completo explorando todas as funcionalidades da linguagem.
// Agora cobrindo inclusive operadores compostos, OU lógico, 
// inicialização com decimal, função retornando decimal e chamada sem argumentos.

// Declaração de variável global (sem inicialização, como manda a regra)
var g_variavel_decimal := decimal,

// Função sem parâmetros (retorno decimal, para testar)
funcao_constante -> decimal :=
[
    retorna 3.14 := decimal
],

// Definição de uma função com múltiplos parâmetros (decimais).
soma_e_multiplica -> decimal com a := decimal, b := decimal :=
[
    // Declaração de variável local sem inicialização.
    var resultado := decimal

    // Comando de atribuição com expressão aritmética.
    resultado := a + b * 2.0

    // Comando de retorno com expressão.
    retorna resultado := decimal
],

// Definição da função principal, sem parâmetros.
principal -> decimal :=
[
    // Declaração de variáveis locais.
    var contador := decimal
    var resultado_decimal := decimal com 1.0
    var inicializado_decimal := decimal com 42.0

    // Comando de atribuição com literal decimal.
    contador := -contador + (+inicializado_decimal)
    contador := 0.0
    g_variavel_decimal := 100.0

    // Comando de controle de fluxo: ENQUANTO.
    enquanto (contador < 10.0 & !(g_variavel_decimal == 0.0))
    [
        // Comando de controle de fluxo: SE / SENAO.
        // Aqui usamos todos os operadores compostos e o OU (|).
        se ((contador <= 5.0) | (g_variavel_decimal >= 50.0))
        [
            resultado_decimal := (soma_e_multiplica(contador, contador + 1.0) * 3.0) / 2.0
        ]
        senao
        [
            // Teste de operadores compostos restantes.
            se (contador != 7.0)
            [
                resultado_decimal := funcao_constante()  // chamada sem argumentos
            ]
            senao
            [
                resultado_decimal := 0.0
            ]
        ]

        // Atribuição com expressão para incrementar o contador.
        contador := contador + 1.0
    ]

    // Comando de retorno com valor literal.
    retorna 0.0 := decimal
];
EOF
echo "Gerando arquivo de teste final IGUAL ETAPA 3 "
echo


echo "Todos os arquivos de teste foram criados com sucesso."
