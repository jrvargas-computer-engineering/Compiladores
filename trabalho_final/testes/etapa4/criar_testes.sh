#!/bin/bash

echo "Criando arquivos de teste para a E4 (Sintaxe Corrigida)..."

# --- Categoria 1: Testes de Sucesso (Código 0) ---

cat > teste_1_1_sucesso_simples.txt << EOF
var x := inteiro,
main -> inteiro :=
[
  x := 10
]
;
EOF

cat > teste_1_2_sucesso_funcao.txt << EOF
f -> inteiro () := [
    retorna 10 := inteiro
],
main -> inteiro :=
[
    f()
]
;
EOF

cat > teste_1_3_sucesso_shadowing.txt << EOF
var x := inteiro,
f -> inteiro () := [
    var x := flutuante; 
    x := 10.5;
    retorna 5 := inteiro
],
main -> inteiro :=
[
    x := 5
]
;
EOF

cat > teste_1_4_sucesso_aninhado.txt << EOF
var x := inteiro,
main -> inteiro :=
[
    [
        var y := inteiro;
        [
            var z := inteiro;
            x := y + z 
        ]
    ]
]
;
EOF

cat > teste_1_5_sucesso_parametros.txt << EOF
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

# === NOVOS TESTES DE SUCESSO (Passo 6) ===
echo "Criando novos testes de SUCESSO para o Passo 6..."

cat > teste_1_6_sucesso_arit_float.txt << EOF
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

cat > teste_1_7_sucesso_rel_log_int.txt << EOF
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
# --- Categoria 2: Testes de ERR_UNDECLARED (Código 10) ---

cat > teste_2_1_err_undeclared_var.txt << EOF
main -> inteiro :=
[
    x := 5
]
;
EOF

cat > teste_2_2_err_undeclared_funcao.txt << EOF
main -> inteiro :=
[
    funcao_fantasma()
]
;
EOF

cat > teste_2_3_err_undeclared_escopo.txt << EOF
main -> inteiro :=
[
    [
        var x := inteiro
    ]
    x := 5
]
;
EOF

cat > teste_2_4_err_undeclared_escopo_funcao.txt << EOF
f1 -> inteiro () := [
    var x := inteiro
],

f2 -> inteiro () := [
    x := 10 
]
;
EOF

# --- Categoria 3: Testes de ERR_DECLARED (Código 11) ---

cat > teste_3_1_err_declared_global.txt << EOF
var x := inteiro,
var y := flutuante,
var x := inteiro 
;
EOF

cat > teste_3_2_err_declared_funcao.txt << EOF
f -> inteiro () := [ ],
g -> inteiro () := [ ],
f -> flutuante () := [ ] 
;
EOF

cat > teste_3_3_err_declared_local.txt << EOF
main -> inteiro :=
[
    var x := inteiro
    [
        var y := inteiro;
        var x := flutuante 
    ]
    var x := flutuante 
]
;
EOF

# --- Categoria 4: Testes de Uso (Código 20 ou 21) ---

cat > teste_4_1_err_variable.txt << EOF
var x := inteiro,
main -> inteiro :=
[
    x(10) 
]
;
EOF

# Corrigido: Declara 'x' para isolar o erro ERR_FUNCTION
cat > teste_4_2_err_function.txt << EOF
f -> inteiro () := [ ],
main -> inteiro :=
[
    var x := inteiro;
    x := f + 5 
]
;
EOF

cat > teste_4_3_err_function_atrib.txt << EOF
var x := inteiro,
f -> inteiro () := [ ],
main -> inteiro :=
[
    x := f 
]
;
EOF

# === NOVA CATEGORIA 5: Testes de ERR_WRONG_TYPE (Código 30) ===
echo "Criando novos testes de FALHA (Passo 6: ERR_WRONG_TYPE)..."

cat > teste_5_1_err_type_arit.txt << EOF
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

cat > teste_5_2_err_type_rel.txt << EOF
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

cat > teste_5_3_err_type_not.txt << EOF
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

cat > teste_5_4_err_type_mod.txt << EOF
main -> inteiro :=
[
    var f := decimal
    var i := inteiro
    f := 5.0
    i := 10 % f 
]
;
EOF

cat > teste_5_5_err_type_atrib.txt << EOF
main -> inteiro :=
[
    var i := inteiro
    i := 5.0 
]
;
EOF

cat > teste_5_6_err_type_retorno.txt << EOF
main -> decimal :=
[
    retorna 5 := decimal 
]
;
EOF

cat > teste_5_7_err_type_if.txt << EOF
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

cat > teste_5_8_err_type_while.txt << EOF
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

cat > teste_5_9_err_type_init.txt << EOF
main -> inteiro :=
[
    var d := decimal com 5 
]
;
EOF

echo "Todos os novos arquivos de teste foram criados!"