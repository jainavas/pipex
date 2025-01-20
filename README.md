# pipex

## Descripción del Proyecto

**pipex** es un proyecto diseñado para dominar el manejo de pipes y redirección en la línea de comandos de Unix/Linux. El objetivo es realizar el procesamiento de datos entre archivos y comandos, utilizando las funciones del sistema permitidas.

## Reglas del Juego

- **Nombre del programa**: `pipex`
- **Archivos a entregar**: `Makefile`, `*.h`, `*.c`
- **Funciones Permitidas**:
  - `open`, `close`, `read`, `write`
  - `malloc`, `free`, `perror`, `strerror`, `access`, `dup`, `dup2`
  - `execve`, `exit`, `fork`, `pipe`, `unlink`, `wait`, `waitpid`
- **Librerías permitidas**: `libft`

## Ejecución del Programa

El programa `pipex` se ejecutará con los siguientes argumentos:
```shell
./pipex archivo1 comando1 comando2 archivo2
```

Donde:
- `archivo1`: es el nombre del archivo de entrada.
- `archivo2`: es el nombre del archivo de salida.
- `comando1` y `comando2`: son comandos de shell con sus respectivos parámetros.

El resultado de ejecutar el programa debe ser el mismo que usar la línea de comandos siguiente:
```shell
< archivo1 comando1 | comando2 > archivo2
```

## Ejemplos de Uso

```shell
# Ejemplo 1
$> ./pipex infile "ls -l" "wc -l" outfile
Deberá producir resultados equivalentes a:
$> <infile ls -l | wc -l >outfile

# Ejemplo 2
$> ./pipex infile "grep a1" "wc -w" outfile
Deberá producir resultados equivalentes a:
$> <infile grep a1 | wc -w >outfile
```

## Requisitos del Proyecto

- Debes entregar un **Makefile** que compile tus archivos fuente. No debe hacer relink.
- Debes gestionar errores minuciosamente. Tu programa no debe salir de forma inesperada (e.g., segmentation fault, bus error, double free).
- No debe haber fugas de memoria.
- En caso de duda sobre la gestión de errores, sigue el comportamiento de los comandos de shell estándar:
```shell
< file1 cmd1 | cmd2 > file2
```

## Implementación y Buenas Prácticas

- Asegúrate de utilizar las funciones del sistema de manera eficiente.
- Documenta tu código comentando las secciones clave para facilitar la comprensión.
- Realiza pruebas exhaustivas para verificar que tu programa maneje correctamente todos los casos, incluidas entradas inválidas y errores.

---

¡Bienvenido al mundo de pipex! Demuestra tu destreza en el manejo de pipes y redirección, y lleva tu programación al siguiente nivel.
