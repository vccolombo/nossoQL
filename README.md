### nossoQL

***

nossoQL é um Sistema Gerenciador de Banco de Dados (SGBD) feito para o trabalho da matéria de Organização e Recuperação da Informação na UFSCar, 2019/2. Orientado pelo Prof. Dr. Jander Moreira.

### Integrantes

[**Jean Araujo**](https://github.com/jeanufscar) -- 620394

[**Marco Antonio B. Grivol**](https://github.com/marcogrivol) -- 758619

[**Mayk Tulio Bezerra**](https://github.com/mayktu) -- 727953

[**Renan Dantas Pasquantonio**](https://github.com/renandantasp) -- 760549

[**Sergio Ricardo Hideki Nisikava**](https://github.com/hidekisrn) -- 551848

[**Víctor Cora Colombo**](https://github.com/vccolombo) -- 727356


### Etapas
0. [Especificações geral do projeto.](https://drive.ufscar.br/d/e0f30c670f/files/?p=/2019.08.09-__projeto__-especificacao_projeto.pdf)
1. **~~20/08~~ 23/08** -- [Criação do interpretador de comandos e definição dos metadados da base.](https://drive.ufscar.br/d/e0f30c670f/files/?p=/2019.08.20-__projeto__-comandos_e_metadados.pdf)
2. **03/09** -- [Implementação da manipulação de tabelas e das operações de inserção e busca de registros.](https://bit.ly/2ZaRJ2W)
3. **~~17/09~~ 24/09** -- [Implementação da operação de remoção de registros e estratégia de reutilização de espaço.](https://bit.ly/2kSeoyR)
4. **~~24/09~~ 11/10** -- Acréscimo de controle sobre indexação de metadados.
5. **~~11/10~~ 15/10** -- Implementação da indexação com árvores.
6. **05/11** -- Implementação da indexação com hash.
7. **26/11** -- Testes de larga escala. 

***

### Como instalar e usar

```
git clone https://github.com/vccolombo/nossoQL.git
cd nossoQL
make
./main.exe
```

***

### Como contribuir

Dê uma olhada no [CONTRIBUTE.md](CONTRIBUTE.md) para saber como contribuir com o projeto.

***

### Metadados

Decidimos por modelar nossa base de forma que cada tabela tenha seu próprio arquivo de metadados. Esse arquivo vai conter as seguintes entradas (metadados):

1. Nome da tabela;
2. Número de campos;
3. Nomes dos campos;
4. Tipos dos campos;
5. Número de registros;
6. Último comando de busca realizado;
7. Data de criação da tabela;
8. Quantidade de tabelas criadas ate o momento.
9. Path para o arquivo com os dados;

O arquivo com os dados conterá os valores inseridos na tabela, separados provavelmente por;
