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
