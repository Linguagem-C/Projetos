# Sistema de Consulta de cadastro do Conselho Federal de Odontologia (CFO)
### Quantitativos sobre Profissionais e Entidades da área de odontologia no Brasil

* Arquivo markdown, para visualizar melhor execute esse arquivo no firefox ou googleChrome

## Como rodar o código:

* Insira o seguinte código no terminal de comando do linux para rodar o app

	```sh
    g++ cfo_cds.c cfo_city.c cfo_total.c main.c opening.c config.c -o prog
    ./prog
	  OU
    gcc cfo_cds.c cfo_city.c cfo_total.c main.c opening.c config.c -o prog
    ./prog
	```

* Para rodar precisa esta na pasta do projeto onde está os arquivos mencionados na linha de comando.

* Não me responsabilizo se o código não rodar em outros sistemas operacionais devido a manipulação do arquivo, tendo diferenças significativas entre o caminho para os dados de um sistema operacional ao outro, entre outras funcionalidades da propria linguagem C que pode dar problema.

* Funções que tem que modificar para rodar no sistema operacional windows:

  * Linux -> Windows

  * system(clear); -> system(cls);

  * #include "lib/library.h" -> #include "lib\library.h"

* Pode haver mais modificações a fazer ou talvez a sintaxe do windows seja um pouco diferente da mostrada acima, não tenho o sistema operacional para testar.

* Aplicativo feito em C no sistema operacional linux compilado e executado pelo terminal de comandos.

## RELATORIO DA COMPLEXIDADE DO CÓDIGO:

1) Importação do arquivo CSV

* Percorremos 2 laços while um dentro do outro para inserção dos dados do arquivo na arvore na qual o primeiro laço percorre o arquivo e o segundo percorrer a linha quebrando ela no ponto e virgula e inserindo os dados relevantes a cada arvore, por exemplo, arvore de cidade precisa da inserção do campo city para futuras pesquisas, além de sua linha no arquivo, tendo como complexidade computacional O(n)

2) Relatorio:

* A complexidade da inserção de dados ordenados na arvore é O(h), onde h é a altura da arvore

* No pior caso a altura de uma arvore binaria pode ser O(n)

3) Relatorio de um estado:

* O relatorio por estado além de realizar inserção ordenado temos que realizar uma busca, tendo como pior caso O(n) e no melhor caso O(log n)

4) Dados de um municipio especifico:

* A complexidade no pior caso é igual a altura da arvore, o pior caso pode ser O(n), onde n é o número de nós da arvore

* A complexidade no melhor caso é O(log n) na base 2, isso acontece quando a arvore está balanceada.

5) Sair do sistema

* Ao sair do sistema temos que desalocar memoria das arvores onde está os dados do arquivo armazenado, tendo complexidade O(n) devido ao laço para percorrer a arvore
