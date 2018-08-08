# CA_System
Systema Context-aware para la elección de protocolos en cruce tipo X

## Versiones
>Omnet++ 5.1.1

>Inet 3.6.2

>veins 4.6

>sumo 0.30.0

### Notas

* Importar el proyecto de veins seleccionando "search for nested projects"
* Recordar escribir el siguiente comando dentro de la carpeta de veins, para ejecutar sumo através de python:
```
 python sumo-launchd.py -vv -c sumo-gui
```
* Recordar agregar directorios de compilación a los subproyectos: veins_inet y CA_System.
mas información en el siguiente [Link](https://stackoverflow.com/questions/44385671/error-when-building-veins-inet-subproject). 
* Recordar copiar el contenido de /src/modules/messages/WaveShortMessage.msg al directorio de veins.
* Para correr simulador en servidor remoto con puertos TCP cerrados cambiar linea 405 de sumo-launchd.py en la carpeta de Veins a 2 "remote_port = 5555 #find_unused_port()"
* Para correr sumo sin interfaz gráfica y para que no se interrumpan multiples corridas utilizar la siguiente linea para ejecutar sumo-launchd:
```
 python sumo-launchd.py -vv 
```