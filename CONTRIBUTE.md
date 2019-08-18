### Como contribuir

***

1. Clone o repositório `git clone https://github.com/vccolombo/nossoQL`	
2. Crie um branch para fazer as edições `git branch -b <nome_do_branch>`
3. Edite os códigos que deseja.
4. Adicione os códigos no git `git add .`
Caso esse comando não seja o ideal para você, olhe a [documentação do git add](https://git-scm.com/docs/git-add).
5. Comite as modificações `git commit -m "<mensagem do seu commit>"`
A mensagem do seu commit deve dizer o que esse commit faz e ser pensada da seguinte forma: "Se aceito, esse commit irá... [mensagem do seu commit]".
Não escreva COMO seu commit faz a modificação, e sim que modificação ele faz. Caso queira adicionar uma explicação de como ele faz isso, use apenas o `git commit` e escreva a mensagem na tela que se abrirá. Siga [esse tutorial](https://chris.beams.io/posts/git-commit/) se precisar de ajuda.
6. Dê push para o repo no Github `git push origin <nome_do_branch>`

### Como fazer daqui pra frente?

Garanta que seu repositório está em dia com o projeto usando os comandos

```shell
git fetch
git checkout master
git pull
```

e siga a partir do passo II na seção acima.