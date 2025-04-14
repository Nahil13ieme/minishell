#!/bin/bash

MINISHELL="./minishell"
TMP_OUTPUT="ms_output.txt"
TMP_EXPECTED="expected_output.txt"

function clean_output() {
    sed '/minishell\|^\s*$/d'
}

function run_test() {
    local description="$1"
    local command="$2"

    echo "=== $description ==="

    echo "$command" | $MINISHELL 2>/dev/null | clean_output > "$TMP_OUTPUT"
    echo "$command" | bash > "$TMP_EXPECTED"

    if diff -u "$TMP_EXPECTED" "$TMP_OUTPUT" > /dev/null; then
        echo "✅ Passed"
    else
        echo "❌ Failed"
        echo "Command: $command"
        echo "--- Expected:"
        cat "$TMP_EXPECTED"
        echo "--- Got:"
        cat "$TMP_OUTPUT"
    fi
    echo
}

### TESTS — ENVIRONNEMENT ET VARIABLES ###

# export simple
run_test "Simple export" "export A=1 && echo \$A"

# export + overwrite
run_test "Overwrite export" "export VAR=hello && export VAR=world && echo \$VAR"

# export + unset
run_test "Unset variable" "export TMP=bye && unset TMP && echo \$TMP"

# export avec espaces
run_test "Variable with space" "export MSG='hello world' && echo \"\$MSG\""

# export chaîne avec caractères spéciaux
run_test "Special characters" "export STR='@!#\$%^&*()_+' && echo \$STR"

# export vide
run_test "Empty variable" "export EMPTY= && echo \$EMPTY"

# export avec égal dans la valeur
run_test "Multiple equal signs" "export TEST_EQ='a=b=c=d' && echo \$TEST_EQ"

# variable non existante
run_test "Undefined variable" "echo \$I_DONT_EXIST"

# variable avec chiffre dans le nom (valide)
run_test "Digit in variable name" "export VAR1=42 && echo \$VAR1"

# variable qui contient une autre variable
run_test "Nested variable" "export A=hello && export B=\$A && echo \$B"

# export puis echo dans une autre commande
run_test "Export across commands" "export TESTHELLO=world" 
run_test "Echo after export" "echo \$TESTHELLO"

# unset puis réexport
run_test "Unset and re-export" "export X=1 && unset X && export X=2 && echo \$X"

# substitution vide
run_test "Empty substitution" "echo \$"

# substitution dans une string
run_test "Variable inside string" "export WHO=world && echo \"hello \$WHO\""

# export de var avec quote dans la valeur
run_test "Quote inside value" "export QUOTE='he\"llo' && echo \$QUOTE"

# export avec expansion dans la valeur
run_test "Expansion in assignment" "export BASE=ok && export COPY=\$BASE && echo \$COPY"

# export d’un nombre très long
run_test "Very long variable" "export LONG=\$(printf 'x%.0s' {1..10000}) && echo \${#LONG}"

# export suivi d’un pipe (pour plus tard si tu implémente pipe)
run_test "Export then pipe" "export PIPE_TEST=1 && echo \$PIPE_TEST | cat"

# unset inexistant
run_test "Unset non-existing var" "unset NOT_SET && echo OK"

# variable en majuscule/minuscule
run_test "Case sensitivity" "export Foo=Bar && echo \$Foo && echo \$FOO"

# variable utilisée dans une autre export
run_test "Reference in export" "export A=42 && export B=\$A && echo \$B"

# export multiple vars
run_test "Multiple export same line" "export A=1 B=2 C=3 && echo \$A \$B \$C"

# export avec nom de var non valide
run_test "Invalid variable name" "export 1INVALID=bad && echo \$1INVALID"

# echo avec variable collée à un mot
run_test "Variable glued to string" "export USER=42 && echo \"hello\$USER\""

### FIN DES TESTS ###

# Nettoyage
rm -f "$TMP_OUTPUT" "$TMP_EXPECTED"
