# Tarea 2 Analisis de Algoritmos

## Compilación

Para compilar el programa se debe ejecutar los comandos siguiendo la siguiente estructura:

```bash
g++ -std=c++11 -O0 -o uhr_escalamiento_bf uhr_escalamiento_bf.cpp
```

Esto generará un ejecutable llamado uhr_escalamiento_bf.

---

## Ejecución

El programa se ejecuta mediante el siguiente comando:

```bash
./uhr_escalamiento_bf <filename>.csv <runs>
```

Donde:

* `<filename>.csv` corresponde al nombre del archivo CSV donde se almacenarán los resultados.
* `<runs>` corresponde a la cantidad de ejecuciones realizadas para cada tamaño de matriz.
---


## Ejemplo de ejecución

```bash
./uhr_escalamiento_bf resultados.csv 32
```

Este ejemplo ejecuta 32 repeticiones para los casos de prueba definidos, almacenando los resultados en el archivo ` resultados.csv` 
