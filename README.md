# Randomic-Numbers-With-MPI

### Descripción del juego
Este es un juego usando **MPI** que consiste en lo siguiente:

1. Cada proceso se inventa un número y se lo comunica al resto.
2. Si todos los procesos han pensado el mismo número, se acaba el juego.
3. Si no, se repite el proceso (se vuelve 1). Si ya ha habido 1000 repeticiones, se finaliza con un error.
4. Al final hay que indicar por pantalla (una sola vez) cúantas veces se ha tenido que repetir el proceso para que todos pensaran el mismo número.

Se dispone de la siguiente funcion para inventar los números:
int piensa_un_numero(); (devuelve un número aleatorio)

Utiliza operaciones de comunicacion colectiva de MPI para todas las comunicaciones necesarias.
