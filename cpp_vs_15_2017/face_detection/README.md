# Plan de prototipos
# [Ver cronograma aquí](https://instagantt.com/shared/s/548861461553700/latest)

# TODO-list
Definir componentes de hardware necesarios para empezar a buscarlos (televisor)

## iteration 0 [ready]
### [*python-face*] implement basic face detection 
**problema a solucionar:** Se necesita implementar un sistema que sea capaz de detectar caras y pasar esta información a unity.

**estado:** El problema ha sido resuelto.
**descripcion de solución:** Se utilizo el algoritmo haarcascade por defecto de OpenCV entrenado para reconocimiento de caras.

**problema de la solución:** *[interactivo]* El sistema es capaz de detectar caras, pero presenta dificultades reconociendo caras que no están alineadas y caras incompletas 

**siguiente prototipo:** *[interactivo]* Encontrar un algoritmo que detecte caras y sea inmune a rotación y escala. 

## iteration 1 [ready]
###  [*python-face*]  improve correct face detection rate
**problema a solucionar:** Se necesita implementar un sistema que sea capaz de detectar caras rotadas y escaladas para pasar esta información a unity.

**estado:** El problema ha sido resuelto.

**descripcion de solución:** *[interactivo]* Se utilizo un algoritmo de detection de caras basado en el Histogram of Oriented Gradient (HOG) de la libreria DLib en python.

**problema de la solución:** 
- *[interactivo]* El sistema es capaz de detectar caras con mejor tasa de éxitos que el aplicado en la *iteración 1*, sin embargo aun no es totalmente inmune a la orientación de la cara.
- *[interactivo]* El algoritmo es computacionalmente costoso, y reduce significativamente los FPS de la aplicación en Unity.

**siguiente prototipo:** 
- *[interactivo]* Reescribir la aplicación en C++
- *[interactivo]* Aplicar optimizaciones en CPU compilando DLIB usando mínimamente SSE2
- *[interactivo]* Aplicar optimizaciones en GPU compilando DLIB usando CUDA.

## iteration 2 [ready]
### [*cpp-face*] speedup python HOG-based detection app

**problema a solucionar:** Se necesita portar la aplicación escrita en Python durante la *iteración 1* a C++ y aplicar optimizaciones en CPU y GPU.

**estado:** El problema ha sido resuelto.

**descripcion de solución:** 
- *[interactivo]* Se mejoro significativamente la velocidad de la aplicación escrita en la *iteración 1* usando C++, se compilaron las librerías estáticas de DLIB C++ usando optimizaciones del procesador CPU SSE2 y GPU CUDA aunque las versiones optimizadas para GPU no han podido ser probadas aun.
- *[interactivo]* Se implemento el sistema de detección de sonrisas.

**problema de la solución:** 
- *[interactivo]* No se ha podido visualizar la mejora en rendimiento usando las versiones de DLIB optimizadas con CUDA porque se necesita compilar la versión de 64bit de QT para utilizar correctamente el modulo highgui de OpenCV en 64bits.
- *[interactivo]* El sistema aun presenta dificultades reconociendo caras incompletas y caras altamente desalineadas.

**siguiente prototipo:** 
- *[interactivo]* Integrar el sistema de detección de caras y sonrisas con Unity Engine.
- *[interactivo]* Intentar solucionar problema de escala y rotacion con algoritmo de trackeo MOSSE para seguimiento de objeto (combinar MOSSE con HOG: identificar región a trackear con HOG-based y continuar el trackeo de esa región con MOSSE).  
- *[transmedia]* Escribir aplicación basica para detección de objetos arbitrario en una maqueta.

## iteration 3 [ready]
### [*unity-app*] integrate face detection with Unity

**problema a solucionar:** Se necesita integrar la aplicación optimizada en C++ y CUDA con Unity Engine

**estado:** El problema ha sido resuelto.

**notas de la solución:** 
- *[interactivo]* La solucion funciona adecuadamente, permite una experiencia fluida y no consume muchos recursos de computo, se propone continuar desarrollando el sistema de generacion de naturalez procedural y empezar a plantear soluciones para el problema de los gestos que el usuario podra realizar en el ritual.

**siguiente prototipo:** 
- *[interactivo]* Escena de Unity Engine que genera naturaleza de forma generativa usando fractales a medida que el usuario sonríe,

## iteration 4 [scheduling]
### [*python-object*] implement basic object classification app

**problema a solucionar:** Se necesita escribir una aplicación que sea capaz de distinguir entre distintos tipos de objetos que serán construidos para una maqueta (arboles, cabaña, indígena).

**estado:** En progreso.

## iteration 5 [scheduling]
### [*unity-app*] Smile for forest generation

**problema a solucionar:** Se necesita desarrollar una aplicación en Unity Engine que sea capaz de generar naturaleza de manera procedural a medida que el usuario sonría.

**estado:** En progreso.

**siguiente prototipo:** 
- *[interactivo]* Desarrollar un primero prototipo físico del producto interactivo

## iteration 6 [scheduling]
### [*real*] prototipar primer montaje del producto interactivo

**problema a solucionar:** Se necesita desarrollar un primer prototipo de montaje para probar todos los sistemas de software del producto interactivo así como su integración con el hardware.
**estado:** En progreso.
