#!/bin/bash

# Caminho para o executável do seu programa em C
PROGRAM="./minishell"

comp="make re && clear && ./minishell"

# Inicializar contadores
total_tests=0
successful_tests=0

# Inicializar número do teste
test_number=0

sed_escape() {
    echo "$1" | sed 's/[][\\.*^$/]/\\&/g'
}

substring_until_char() {

    local full_output="$($PROGRAM <<< "$input" 2>&1)"
    local delimiter="$"
    local position=$(expr index "$full_output" "$delimiter")
    local result="${full_output:0:position}"

    echo "$result"
}

remove_substring() {
    local substring="$1"
    local full_output="$2"
    local control="$3"

    local escaped_substring=$(sed_escape "$substring")

    # Usa sed para substituir todas as ocorrências da substring por uma string vazia
    if [ "$control" == "0" ]; then
        local result=$(echo "$full_output" | sed "s/${escaped_substring}//g")
    else
        local result=$(echo "$full_output" | sed "0,/${escaped_substring}/s///")
    fi
    echo "$result"
}

remove_ansi_codes() {
    local input_string="$1"
    # Usa sed para remover códigos ANSI
    local clean_string=$(echo "$input_string" | sed -r "s/\x1B\[[0-9;]*[mGK]//g")
    echo "$clean_string"
}

# Função para executar um teste
run_test() {
    # Incrementar o número do teste
    ((test_number++))

    # Incrementar o contador total de testes
    ((total_tests++))

    # Entrada de teste
    input="$1"

    # Saída esperada
    expected_output="$2"

    # Executar o programa com a entrada do teste e capturar a saída
    full_output="$($PROGRAM <<< "$input" 2>&1)"

    # Extrair a parte relevante da saída
    substring=$(substring_until_char)
    result=$(remove_substring "$substring" "$full_output" 0)
    actual_output=$(remove_substring " $input" "$result" 1)
    actual_output=$(echo -n "$actual_output" | tr -d '\n')
    actual_output=$(remove_ansi_codes "$actual_output")

    if [ "$actual_output" = "$expected_output" ]; then
        # Incrementar o contador de testes bem-sucedidos
        ((successful_tests++))
        echo -e "\n\e[32mTeste $test_number: OK\e[0]"
    else
        echo -e "\e[31m\nTeste $test_number: X:\e[0m\nEntrada=\"$input\"\n\nSaída Obtida=\n\"$actual_output\"\nSaída Esperada=\n\"$expected_output\"\n"
    fi
}

$comp
clear
chmod 000 files_tester/out.txt
echo -e "Iniciando os testes..."

# Testes
run_test "|" "bash: syntax error near unexpected token \`|' "
run_test "| |" "bash: syntax error near unexpected token \`|' "
run_test "| | |" "bash: syntax error near unexpected token \`|' "
run_test "| >" "bash: syntax error near unexpected token \`|' "
run_test "| <" "bash: syntax error near unexpected token \`|' "
run_test "| >>" "bash: syntax error near unexpected token \`|' "
run_test "| <<" "bash: syntax error near unexpected token \`|' "
run_test "> |" "bash: syntax error near unexpected token \`|' "
run_test "< |" "bash: syntax error near unexpected token \`|' "
run_test ">> |" "bash: syntax error near unexpected token \`|' "
run_test "<< |" "bash: syntax error near unexpected token \`|' "
run_test "ls | |" "bash: syntax error near unexpected token \`|' "

run_test ">" "bash: syntax error near unexpected token \`newline' "
run_test "<" "bash: syntax error near unexpected token \`newline' "
run_test ">>" "bash: syntax error near unexpected token \`newline' "
run_test "<<" "bash: syntax error near unexpected token \`newline' "
run_test "cat <" "bash: syntax error near unexpected token \`newline' "
run_test "ls >" "bash: syntax error near unexpected token \`newline' "

run_test "> >" "bash: syntax error near unexpected token \`>' "
run_test "> > >" "bash: syntax error near unexpected token \`>' "
run_test "< >" "bash: syntax error near unexpected token \`>' "
run_test "<< >" "bash: syntax error near unexpected token \`>' "
run_test ">> >" "bash: syntax error near unexpected token \`>' "

run_test "< <" "bash: syntax error near unexpected token \`<' "
run_test "< < <" "bash: syntax error near unexpected token \`<' "
run_test "> <" "bash: syntax error near unexpected token \`<' "
run_test "<< <" "bash: syntax error near unexpected token \`<' "

run_test ">> >>" "bash: syntax error near unexpected token \`>>' "
run_test ">> >> >>" "bash: syntax error near unexpected token \`>>' "
run_test "> >>" "bash: syntax error near unexpected token \`>>' "
run_test "< >>" "bash: syntax error near unexpected token \`>>' "

run_test "<< <<" "bash: syntax error near unexpected token \`<<' "
run_test "<< << <<" "bash: syntax error near unexpected token \`<<' "
run_test "> <<" "bash: syntax error near unexpected token \`<<' "
run_test "< <<" "bash: syntax error near unexpected token \`<<' "

run_test "cat < teste.txt" "bash: teste.txt: No such file or directory "
run_test "< teste" "bash: teste: No such file or directory "
run_test "ls > /diretorio/inexistente/arquivo.txt" "bash: /diretorio/inexistente/arquivo.txt: No such file or directory "
run_test "echo "Teste" > /pasta/a" "bash: /pasta/a: No such file or directory "
run_test "echo Teste >> /pasta/a" "bash: /pasta/a: No such file or directory "

run_test "cat < files_tester/out.txt" "bash: files_tester/out.txt: Permission denied "
run_test "ls > files_tester/out.txt" "bash: files_tester/out.txt: Permission denied "
run_test "echo "Teste" > /pasta" "bash: /pasta: Permission denied "
run_test "echo "Teste" >> /pasta" "bash: /pasta: Permission denied "

run_test "ls > files_tester/Teste/" "bash: files_tester/Teste/: Is a directory "
run_test "echo "Teste" >> pasta/" "bash: pasta/: Is a directory "
run_test "echo "Teste" >> /pasta/" "bash: /pasta/: Is a directory "

run_test "ls > nome_de_arquivo_com_mais_de_255_caracteres_aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.txt" "bash: nome_de_arquivo_com_mais_de_255_caracteres_aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.txt: File name too long "


# Calcular porcentagem de acertos
percentage=$(echo "scale=2; $successful_tests / $total_tests * 100" | bc)

# Imprimir resultados com cores
echo -e "\n\e[33mTestes realizados: \e[94m$total_tests\e[0m\n\e[33mTestes OK: \e[94m$successful_tests\e[0m\n\e[33mPorcentagem de acertos: \e[94m$percentage%\e[0m\n"

# Limpar recursos, se necessário
# ...

echo -e "Testes concluídos.\n"
make fclean > /dev/null

