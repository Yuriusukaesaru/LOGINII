# ERROR CRITICO 1: flags mal escritos. es -Wpedantic y es -Werror.

# ERROR CRÍTICO 2: Te he comentado que lo que diferencía una receta de su target es la IDENTACIÓN.
# Por alguna razón tu editor NO ESTÁ GUARDANDO EL CARACTER TABULADOR COMO TAL. Hay que revisarlo.

# ERROR CRÍTICO 3: Yo hice una nueva estructura de archivos y carpetas que no estás tomando
# en cuenta. En ese sentido tampoco estás creando la carpeta bin/ donde debería ir tu ejecutable.

# ERROR CRÍTICO 4: Debemos agregar el std=c++20

# SUGERENCIA 1: solo romper lineas cuando sea necesario

# SUGERENCIA 2: usar nombres de ejecutables mas representativos

# SUGERENCIA 3: Usaremos el flag -g para que agrege lo necesario para depuración

# OBSERVACIÓN 1: Powershell no me acepta el flag -p para crear un archivo si no existe.
# Omitiremos esa línea. Debemos crear bin/ manualmente por ahora hasta encontrar una solución.
# Se te queda de tarea

# target msvc: Es una locura, jaja, no le entiendo, me marca error y no sè porquè. Compilarè en Windows
# con Clang
# msvc: src/main.cpp
	# cl.exe src/main.cpp /std:c++20 /Z7 /W4 /Febin/login.exe

clang: src/main.cpp
	clang++ src/main.cpp -g -std=c++20 -Wall -Wextra -Wpedantic -Werror -o bin/login.exe

minGW: src/main.cpp
	g++ src/main.cpp -g -std=c++20 -Wall -Wextra -Wpedantic -Werror -o bin/login.exe

.PHONY: clean
clean:
	rm bin/* main.obj
