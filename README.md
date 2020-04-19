# Lexer

Repositorio con el analizador lexico de Chocopy creado en C++

### La estructura del lexer es la siguiente:
- Carpeta casos: Donde estan los casos dados por el profesor y los mismos archivos convertidos por problemas EOL(Ver nota)
- Carpeta  respuesta: Es la respuesta sacada manualmente de los casos. Esto se hizo con motivo de comparar con el resultado automatica y asi verificar que este correcto el codigo
- Carpeta resultados: Es donde se guardan los resultados del analisis lexico realizado automaticamente
- lexer.cpp: Archivo con el codigo del analizador lexico
- Makefile: Permite compilar la aplicacion sin problemas
- todo.sh: Permite correr todos los casos de prueba y guardar los resultados obtenidos en la carpeta Resultados
- ChocoPy.pdf: Donde se encuentra un resumen del lenguaje ChocoPy con algunas de las convenciones utilizadas

### Compilacion y ejecucion
Se puede llevar a cabo por medio de 2 formas:
1. Usando el comando **make** o **g++ --std=c++11 lexer.cpp -o lexer** para el proceso de compilacion y para la ejecucion con el comando **./lexer L1.txt** donde el L1.txt es el archivo 1 de los casos de prueba.
2. Si por el contrario se desea probar todos los casos de pruebas basta con usar el comando **chmod +x todo.sh** para darle permisos y despues el comando **./todo.sh**  para ejecutarlo. O como alternativa se puede usar el comando **sh todo.sh** que no requiere permisos.

En ambas formas los resultados son guardados en en la carpeta Resultados. Esta carpeta se crea automaticamente con el script de todo.sh en caso de que se realize el testeo por el metodo 1 toca verificar que se encuentre creada la carpeta.

### Nota:
- Los archivos de prueba   fueron creados en windows y por problemas de compactibilidad con linux toca convertirlos a unix antes de correr el codigo, esto se realizo con ayuda de una utilidad para linux llamada dos2unix. El problema en cuestion es conocido como End of the Line(EOL) y consiste en que en Windows en los archivos para el final de linea utiliza "\r\n" mientras que en Linux se usa "\n".
