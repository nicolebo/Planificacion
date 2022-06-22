# Qplanif

# # Problematica y solucion:

**Qplanif** es un programa que permite visualizar y entender la planificación de procesos. Fue construida en 1998, por lo que para poder compilarlo se necesita de herramientas antiguas que ya no está disponible.
Proceso de solución: Parti identificando las tecnologías y herramientas que utiliza dicho programa (C++, QT3, Flex y bison). Como Qt3 está descontinuada y su código es muy difícil de conseguir, tuve que hacer adaptaciones para que sea compatible con QT4 y QT5, para ello Qt4 cuenta con librerías que dan soporte a QT3. Entonces fui revisando cada línea de código del programa qplanif e hice las adaptaciones necesarias. También surgieron problemas con el
input.y que tenía errores de sintaxis. Una vez hecho estas adaptaciones y correcciones, surgió el problema de no poder compilarlo, ya que no contaba con un sistema operativo compatible con estas tecnología, entonces se me ocurrió utilizar docker, lo cual hace que el producto resultante sea portable.

> **Note:**  ¿Qué es Docker?
>  La idea detrás de Docker es crear contenedores ligeros y portables para las aplicaciones software que puedan ejecutarse en cualquier máquina con Docker instalado, independientemente del sistema operativo que la máquina tenga por debajo, facilitando así también los despliegues


## Automatización del proceso de compilación con docker!

Generación del Dockerfile: Es el archivo el cual posee instrucciones para generar una imagen.

**Utiliza como base ubuntu versión 18.04**
``FROM ubuntu:18.04``

**Instala las librerías que necesito para poder compilar el proyecto**
``RUN apt-get update && apt-get -y install \
    build-essential libpcre3 libpcre3-dev zlib1g zlib1g-dev libssl-dev wget libqt4-dev libqt4-qt3support flex bison vim``

**Agregar la carpeta Qplanif dentro del contenedor**
``ADD Qplanif home/Qplanif/``

### Arranca el proceso de compilación
**Ejecuta bison para el código**
``RUN cd home/Qplanif/src && bison input.y``

**Ejecuta el makefile que tiene las instrucciones para construir el analizador léxico y junto al al analizador sintáctico generado por bison nos genera el archivo linput.out (el ejecutable)**
``RUN cd home/Qplanif/ && make``

**Ejecuta el Qmake utilizando el archivo planif.cc y bin.pro para que junto con el liunput.out. Armar el binario con todas las dependencias necesarias de QT**
``RUN cd home/Qplanif/bin && qmake && make``

**Copia el binario generado al home para hacerlo más accesible**
``RUN cp home/Qplanif/bin/bin home/qplanif``

> **Note:** Bison construye, a partir de la gramática especificada en el archivo input.y, un analizador sintáctico que reconoce entradas sintácticamente correctas para dicha gramática.


## Ejecucion Automatica
Cree un script para automatiazar el inicio de la aplicacion.
``bash run.sh``

Dentro del script se puede encontrar el siguiente codigo:
Baja de docker hub una imagen ya creada por mi (Utilizando el dockerfile) que tiene hecho todo el proceso de compilacion.
``docker pull nlebovits/entrega-ruben:latest``

Habilita a que la consola pueda utilizar la interfaz grafica del dispositivo
``xhost +``

Corre la imagen descargada anteriormente y nos pone dentro del contenedor y ejecuta el binario creado
``docker run --rm -ti --net=host --ipc=host -e DISPLAY=${DISPLAY} -v /tmp/.X11-unix:/tmp/.X11-unix --env="QT_X11_NO_MITSHM=1" -w /home nlebovits/entrega-ruben:latest sh -c ./qplanif``

## Ejecucion Manual
En vez de utilizar el script lo que vamos a hacer es crear una imagen local de docker con el dockerfile.
Para ello dentro del repositorio correr los siguiente comandos:
Crea en base al dockerfile una imagen y la nombre planif
``docker build -t planif .``

Habilita a que la consola pueda utilizar la interfaz grafica del dispositivo
``xhost +``

Corre la imagen creada anteriormente y nos pone dentro del contenedor y ejecuta el binario creado
``docker run --rm -ti --net=host --ipc=host -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix --env="QT_X11_NO_MITSHM=1" planif``
