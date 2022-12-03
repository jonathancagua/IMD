# IMD
Pruebas del kernel en Raspberry
# Instalacion del kernel en la raspberry:
Se debe usar el sigueinte comando por ssh a la raspberry:

    sudo apt install raspberrypi-kernel-headers

Luego de ese comando se debe actualziar el kernel: 

    sudo rpi-update

Para ver el kernel instalado se usa el sigueinte comando:

    j@raspberrypi:~/Documents/IMD/Hello_World $ uname -a
    Linux raspberrypi 5.15.76-v7+ #1597 SMP Fri Nov 4 12:13:17 GMT 2022 armv7l GNU/Linux

## Compilar el proyecto.
Para compilar el proyecto se ingresa a la carpeta y se ejecuta el siguiente comando:

    j@raspberrypi:~/Documents/IMD/Hello_World $ sudo make
    make -C /lib/modules/5.15.76-v7+/build  M=/home/j/Documents/IMD/Hello_World modules
    make[1]: Entering directory '/usr/src/linux-headers-5.15.76-v7+'
    make[1]: Leaving directory '/usr/src/linux-headers-5.15.76-v7+'

## Cargar proyecto
Para cargar se debe usar el comando insmod con privilegio:

    sudo insmod hello_world.ko

Para listar se usa lsmod.

    j@raspberrypi:~/Documents/IMD/Hello_World $ lsmod
    Module                  Size  Used by
    hello_world            16384  0
    rfcomm                 49152  4

Para ver el proyecto ejecutando se usa el comando dmesg:

    j@raspberrypi:~/Documents/IMD/Hello_World $ dmesg
    [    0.000000] Booting Linux on physical CPU 0x0
    [  820.235985] hwmon hwmon1: Voltage normalised
    [ 1036.484686] Jonathan DEBUG: Kernel Module Inserted Successfully...
## Desmontar proyecto
Para desmontar se usa el sigueinte comando:

    sudo rmmod hello_world.ko

## Mostrar info proyecto
Para mostrar informacion del modulo

    j@raspberrypi:~/Documents/IMD/Hello_World $ modinfo hello_world.ko
    filename:       /home/j/Documents/IMD/Hello_World/hello_world.ko
    version:        1:1.0
    description:    hello world driver
    author:         JC<jonathan.cagua@gmail.com>
    license:        GPL
    srcversion:     0A51D4AD6B1C970AA4E05FC
    depends:
    name:           hello_world
    vermagic:       5.15.76-v7+ SMP mod_unload modversions ARMv7 p2v8



