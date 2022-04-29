# megabash

## 0. "|" : precisa de dois argumentos, a prioridade de execução é do segundo argumento.
- o que leva o pipe a dar prioridade a um argumento? <br><br>
<strong>0.1. Enquanto o segundo não for encontrado, o comando não fecha.<br>
1.1. Se o primeiro comando trabalhar com texto e o segundo trabalhar alterando texto, então os dois são executados.</strong>

- EX1:<br>
echo oi | tr i @<br>
o@

- EX2:<br>
echo oi | tr i @ | echo fui<br>
fui

- EX3:<br>
echo oi | tr i @ | tr i $<br>
o@<br>
considerou o primeiro tr

- EX4:<br>
echo fui | echo oi | tr i @ | tr i $<br>
o@<br>
da direita pra esquerda, considerou o primeiro parzinho de comandos (echo + tr)

- EX5:<br>
echo fui | echo oi | tr i @ |echo meio| tr i $<br>
me$o<br>
da direita pra esquerda, o primeiro a fazer parzinho de comando (echo + tr) foi executado

- Então, basicamente, vamos ter dois tipos de comandos (até agora): o que trabalha com texto e o que trabalha alterando texto, e NESSE CASO de redirecionamento, ele deve vir depois do texto ter sido especificado.

## 1. ">" : O que vem depois de ">" é um arquivo e o que vem antes é o conteúdo que esse arquivo receberá.
<strong>1.1. Se o arquivo não existir, ele é criado.<br>
1.2. Se o arquivo existir, o seu conteúdo será alterado pelo que vier antes de ">".<br>
1.3. Se não houver conteúdo, ele cria um arquivo vazio.<br>
1.4. Se o conteúdo for inválido, o arquivo fica vazio.</strong>

- EX1:<br>
echo oi | tr i @ | tr i '&' | cat README.md  > file<br>
só cat é executado

- EX2:<br>
echo oi | tr i @ | tr i $ > file<br>
só echo com o primeiro tr são executados

- EX3:<br>
echo oi | tr i @ | cat README.md | tr i $ > file<br>
só cat com o segundo tr são executados

- EX4:<br>
echo oi | tr i @ | cat README.md | tr i $ | ls > file<br>
só ls é executado

- EX5:<br>
ls | echo oi | tr i @ | cat README.md | tr i $ > file<br>
só cat com o segundo tr são executados


## 2. ">>" : parecido com o anterior, porém ele ACRESCENTA ao arquivo o conteúdo e utiliza as mesmas regras explicadas acima.


## 3. "<" : o texto de input utilizado para alterações será o do primeiro arquivo a direita.
<strong>3.1. Se houver mais arquivos no meio, nada será alterado dentro deles. (eles são tipo ignorados)<br>
3.2. Se o comando utilizado for do tipo que trabalha com texto, seu texto será printado no prompt.</strong>

- EX1:<br>
tr 'i' '$' > file < file.txt<br>
pega o conteudo de file.txt, altera com tr, e manda para file

- EX2:<br>
tr 'i' '$' < file < file.txt<br>
pega o conteudo de file.txt, altera com tr, e printa no prompt (nada acontece com file)

- EX3:<br>
tr 'i' '$' < file1 < file.txt < file<br>
pega o conteudo de file e altera com tr, printa a alteração no prompt

- EX4:<br>
ls | tr 'i' '$' < file < file.txt<br>
pega o conteudo de file.txt, altera com tr, e printa no prompt (nada acontece com file e ls é ignorado, talvez pq o texto já esteja sendo especificado em file.txt)

- EX5:<br>
tr 'i' '$' | ls < file < file.txt<br>
printou ls no prompt, mas bugou (tr não foi aplicado)

- EX6:<br>
ls -l < file < file.txt<br>
total 268<br>
-rw-r--r--  1 juliana juliana   2840 Apr 27 21:19 Makefile <br>
-rw-r--r--  1 juliana juliana   3324 Apr 29 00:28 README.md<br>
drwxr-xr-x 12 juliana juliana   4096 Apr 27 22:04 build<br>
-rw-r--r--  1 juliana juliana     17 Apr 29 00:15 file<br>
-rw-r--r--  1 juliana juliana     15 Apr 29 00:12 file.txt<br>
drwxr-xr-x  2 juliana juliana   4096 Apr 27 21:19 includes<br>
drwxr-xr-x  3 juliana juliana   4096 Apr 11 23:08 libs<br>
-rwxr-xr-x  1 juliana juliana 235664 Apr 27 22:13 minishell<br>
-rw-r--r--  1 juliana juliana    474 Apr 14 14:10 readline.supp<br>
drwxr-xr-x 12 juliana juliana   4096 Apr 27 21:19 src

- EX7:<br>
ls -l | tr 'i' '$' < file < file.txt<br>
o$?<br>
o$o$o$o$o$<br>
Aplicou tr em file.txt

## 4. "<<" : cria um texto que pode ser redirecionado pra um arquivo e esse texto é/pode ser alterado por comandos que estão na esquerda.

- EX1:<br>
tr 'i' '$' > file << end<br>
oi<br>
kkk<br>
end<br>
tr é aplicado no arquivo file que receberá o que for especificado no heredoc

- EX2:<br>
< file.txt tr 'i' '$' > file << end<br>
oi<br>
kkk<br>
end<br>
ele IGNORA (É ISSO MESMO???) o file.txt e executa a mesma coisa que o exemplo anterior

- EX3:<br>
tr 'i' '@' > file > file.txt << end<br>
oi<br>
kkk<br>
end<br>
Tudo o que está em file é apagado e o comando tr é aplicado no input do heredoc e mandado para o file.txt<br>
Se o arquivo especificado não existir, ele é criado mesmo assim: se for o primeiro da direita pra esquerda, ele recebe o conteúdo do heredoc, caso contrário, fica vazio.<br>
