# Trabajo Final: Corrector Ortografico

Santiago Rotman
### Uso
Para compila el programa se debe escribir en la consola:
```
$make main
```
Para ejecutar el programa, usamos los argumentos camino al diccionario, al texto corregir y el camino al archivo de salida
```
$./main diccionario.txt texto.txt salida
```
La salida del programa estara en el archivo "/salida" y tendra un bloque de la siguiente forma por cada palabra que no este en el diccionario:
```
    Linea N, "PALABRA" no esta en el diccionario.
    Quizas quiso decir: SUGERENCIA1, SUGERENCIA2, ... SUGERENCIA5
```

### Para correr los test:
Test del los componentes del trie:
```
$make testTrie
```
```
$./testTrie
```
Test del los componentes de la cola:
```
$make testQueue
```
```
$./testQueue
```
Test de busqueda:
```
$make testSearch
```
```
$./testSearch
```
