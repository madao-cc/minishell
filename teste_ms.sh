#!/bin/bash

clear

#PROGRAM="make valgrind"
PROGRAM="./minishell"

echo -e "\n-----------------------------"
echo -e "--         TESTES          --"
echo -e "-----------------------------\n"

echo -e "# 00"
echo "echo \"\"" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo \"\""
echo ""
echo -e "\n-------------------------------\n"

echo -e "# 01"
echo "echo ''" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo ''"
echo ''
echo -e "\n-------------------------------\n"

echo -e "# 02"
echo "echo \$" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo $"
echo $
echo -e "\n-------------------------------\n"

echo -e "# 03"
echo "echo \"\$ \"" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo \"$ \""
echo "$ "
echo -e "\n-------------------------------\n"

#echo -e "# 03.1"
#echo "echo \$ " | $PROGRAM
#echo -e "\n"
#echo -e "BASH: echo $ "
#echo $ 
#echo -e "\n-------------------------------\n"

echo -e "# 04"
echo "echo \"\$a\"" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo \"\$a\""
echo "$a"
echo -e "\n-------------------------------\n"

echo -e "# 04.1"
echo "echo \$a" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo \$a"
echo $a
echo -e "\n-------------------------------\n"

echo -e "# 04.2"
echo "echo '\$a'" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo '\$a'"
echo '$a'
echo -e "\n-------------------------------\n"

echo -e "# 05"
echo "echo \"\$a aa\"" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo \"\$a aa\""
echo "$a aa"
echo -e "\n-------------------------------\n"

echo -e "# 05.1"
echo "echo \$a aa" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo $a aa"
echo $a aa
echo -e "\n-------------------------------\n"

echo -e "# 05.2"
echo "echo '\$a aa'" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo '$a aa'"
echo '$a aa'
echo -e "\n-------------------------------\n"

echo -e "# 06"
echo "echo \$\".\"" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo \$\".\""
echo $"."
echo -e "\n-------------------------------\n"

echo -e "# 07"
echo "echo \$'.'" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo \$'.'"
echo $'.'
echo -e "\n-------------------------------\n"

echo -e "# 08"
echo "echo \"\$\"\"\"" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo \"$\"\"\""
echo "$"""
echo -e "\n-------------------------------\n"

echo -e "# 08.1"
echo "echo \$\"\"" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo $\"\""
echo $""
echo -e "\n-------------------------------\n"

echo -e "# 09"
echo "echo \"\$''\"" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo \"$''\""
echo "$''"
echo -e "\n-------------------------------\n"

echo -e "# 09.1"
echo "echo \$''" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo $''"
echo $''
echo -e "\n-------------------------------\n"

echo -e "# 10"
echo "echo \$USER" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo \$USER"
echo $USER
echo -e "\n-------------------------------\n"

echo -e "# 11"
echo "echo \$USER_" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo \$USER_"
echo $USER_
echo -e "\n-------------------------------\n"

echo -e "# 12"
echo "echo \"\$USER\"" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo \"\$USER\""
echo "$USER"
echo -e "\n-------------------------------\n"

echo -e "# 13"
echo "echo '\$USER'" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo '\$USER'"
echo '$USER'
echo -e "\n-------------------------------\n"

echo -e "# 14"
echo "echo \"'\$USER'\"" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo \"'\$USER'\""
echo "'$USER'"
echo -e "\n-------------------------------\n"

echo -e "# 15"
echo "echo '\"\$USER\"'" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo '\"\$USER\"'"
echo '"$USER"'
echo -e "\n-------------------------------\n"

echo -e "# 16"
echo "echo aaa\$USER_bbb\$SHELL\"   |   <>   | \$MAIL aaa\"'   <> \$USER-ddd'" | $PROGRAM
echo -e "\n"
echo -e "BASH: echo aaa\$USER_bbb\$SHELL\"   |   <>   | \$MAIL aaa\"'   <> \$USER-ddd'"
echo aaa$USER_bbb$SHELL"   |   <>   | $MAIL aaa"'   <> $USER-ddd'
echo -e "\n-------------------------------\n"

echo -e "# 17"
echo "echo | " | $PROGRAM
echo -e "\n"
echo -e "BASH: echo | "
echo | 
echo -e "\n-------------------------------\n"