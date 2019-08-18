### Como contribuir

***

1. Dê Fork no repositório.
2. Clone o seu repositório `git clone https://github.com/<seu_usuario>/nossoQL`	
3. Adicione o repositório principal como upstream `git remote add upstream https://github.com/vccolombo/nossoQL`
4. Crie um branch para fazer as edições `git branch -b <nome_do_branch>`
5. Edite os códigos que deseja.
6. Adicione os códigos no git `git add .`
Caso esse comando não seja o ideal para você, olhe a [documentação do git add](https://git-scm.com/docs/git-add).
7. Comite as modificações `git commit -m "<mensagem do seu commit>"`
A mensagem do seu commit deve dizer o que esse commit faz e ser pensada da seguinte forma: "Se aceito, esse commit irá... [mensagem do seu commit]".
Não escreva COMO seu commit faz a modificação, e sim que modificação ele faz. Caso queira adicionar uma explicação de como ele faz isso, use apenas o `git commit` e escreva a mensagem na tela que se abrirá. Siga [esse tutorial](https://chris.beams.io/posts/git-commit/) se precisar de ajuda.
8. Dê push para seu repo no Github `git push origin <nome_do_branch>`
9. Abra um [Pull Request](https://help.github.com/en/articles/creating-a-pull-request) com sua modificação.

### Como fazer daqui pra frente?

Garanta que seu repositório está em dia com o projeto usando os comandos

```shell
git fetch upstream
git checkout master
git merge upstream/master
git push
```

e siga a partir do passo IV na seção acima.