# guitar-effects

Dependecies:
* python3.4-dev
* portaudio
* fftw

# TODO

* Pipeline de execução dos efeitos (plugins)
* Gravação continua do audio
* Pipeline para gravação -> processamento -> reprodução -> gravar arquivo tmp

```
  -----> Gravação ---------> Processamento ------> Reprodução -------> Arquivo TMP
    Î               |    (pipeline de efeitos)
    |      LOOP     |
    |_______________|
```

# Especificações

## Pipeline de execução de efeitos
```
Basicamente, seria uma fila de execução de plugins que serão executados de forma sequencial, porém, cada um irá executar em uma thread diferente (para que nenhum fique ocioso e cause lag na aplicação).
Portanto, a pipeline deverá manter um ponteiro para cada plugin que irá ser executado, e também garantir controlar os threads de cada plugin, para que o próximo efeito seja aplicado logo após o final da execução do anterior.

Ideias de implementação:
1) Fila de ponteiros para PyPlugins
2) Ao receber um buffer, crie uma nova estrutura que contenha um indice e um ponteiro para o buffer.
    -Esse indice é para ter controle de quais efeitos já foram aplicados.
3) Envia essa estrutura para o primeiro plugin.
4) Ao terminar a execução do plugin, incrementa o indice da estrutura e chama uma função de callback que recebe a estrutura criada no passo 2.
5) Na função de callback, executa o plugin representado pelo indice da estrutura recebida.
    - Então, ao final da execução de um plugin, incrementamos o indice para que possamos executar o próximo na pipeline em uma thread diferente.
6) Na função de callback, se o indice da estrutura for maior que o número de plugins, chegamos ao final da execução da pipeline, portanto, chame o módulo de reprodução de audio.
```
