Esto es sólo un controlador de dispositivo de linux básico. Esto explicará cómo pasar los argumentos al controlador de dispositivo de linux.


Visualizar en la raspberry:

    cat /proc/devices | grep "etx_Dev"

Leer el valor de un registro:

    sudo cat /dev/etx_device

Para visualizar los datos del archivo, secciones de codigo:

    objdump -h hello_world.ko

