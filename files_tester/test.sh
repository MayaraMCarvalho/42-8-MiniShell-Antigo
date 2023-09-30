#!/bin/bash

PROGRAM="./minishell"

substring_until_char() {

    local full_output="$($PROGRAM <<< "$input" 2>&1)"
    local delimiter="$"
    local position=$(expr index "$full_output" "$delimiter")
    local result="${full_output:0:position}"

    echo "$result"
}

remove_substring() {
    local full_output="$($PROGRAM <<< "$input" 2>&1)"
    substring=$(substring_until_char)

    # Usa sed para substituir todas as ocorrências da substring por uma string vazia
    local result=$(echo "$full_output" | sed "s/$substring//g")
    echo "$result"
}

clear
result=$(substring_until_char)
result=$(remove_substring)
echo "Resultado: $result"



