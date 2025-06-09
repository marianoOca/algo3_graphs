Dentro del directorio de cada ejercicio ingresar en consola:

    - Para correr todas las instancias:
        make
        for i in ./instancias/*.txt; do echo ${i} >> ./resultados/tiempos.txt; timeout 600 ./resolucion < ${i}; done

    - Para correr una sola instancia:
        make
        echo './instancias/nombre-instancia' >> ./resultados/tiempos.txt; ./resolucion < ./instancias/nombre-instancia

    - Para borrar el ejecutable:
        make clean

    - Para generar las instancias, dentro del directorio instancias:
        python generador.py

Con Docker:
    - Instrucciones para compilar y ejecutar el programa usando una o todas las instancias:

        Iniciar Docker y escribir en la consola (desde el directorio raíz del TP):

        $ cd <EJ>
        $ docker build -t <EJ> .
        $ docker run --rm -v <P>:/tp/tiempos <EJ> <I>

        Donde:
          * <EJ> es el nombre de la carpeta del ejercicio
          * <P> es el directorio *absoluto* donde se quiere que se emitan los resultados.
          * <I> (opcional) nombre de la instancia a ejecutar.

    - Ejemplo:

        $ cd ejercicio_2
        $ docker build -t ejercicio_2 .
        $ docker run --rm -v C:\Users\Lucas\tp\ejercicio_2:/tp/tiempos ejercicio_2

    - Sugerencia:

        Al terminar, borrar imagenes de Docker viejas con el siguiente comando (~1.15 GB cada una):
        $ docker rmi <EJ> && docker images prune
