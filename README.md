# IMD
Pruebas del kernel en Raspberry o Linux

# Propósito
Practicar la compilación y ejecución de drivers (o módulos) en el kernel de Linux.

El ejemplo de driver en la carpeta `./Hello_world`, cuando se monta/desmonta, hace un print en los
logs del kernel.

# Instalacion del kernel en la raspberry:
Se debe usar el sigueinte comando por ssh a la raspberry:

    sudo apt install raspberrypi-kernel-headers

Luego de ese comando se debe actualziar el kernel: 

    sudo apt-get update
    sudo apt-get upgrade

o

    sudo rpi-update

Para ver el kernel instalado se usa el sigueinte comando:

    j@raspberrypi:~/Documents/IMD/Hello_World $ uname -a
    Linux raspberrypi 5.15.76-v7+ #1597 SMP Fri Nov 4 12:13:17 GMT 2022 armv7l GNU/Linux

# Compilar el driver
Para compilar el proyecto se ingresa a la carpeta `Hello_World` y se ejecuta el siguiente comando:

    j@raspberrypi:~/Documents/IMD/Hello_World $ sudo make

Y mostrará lo siguiente en la terminal:

    make -C /lib/modules/5.15.76-v7+/build  M=/home/j/Documents/IMD/Hello_World modules
    make[1]: Entering directory '/usr/src/linux-headers-5.15.76-v7+'
    make[1]: Leaving directory '/usr/src/linux-headers-5.15.76-v7+'

# Montar el driver
Para montar el módulo usaremos el comando `insmod` con privilegio:

    sudo insmod hello_world.ko

Para verificar que se montó al kernel, se usa lsmod.

    j@raspberrypi:~/Documents/IMD/Hello_World $ lsmod | head -3
    Module                  Size  Used by
    hello_world            16384  0
    rfcomm                 49152  4

Para ver el proyecto ejecutando se usa el comando dmesg:

    j@raspberrypi:~/Documents/IMD/Hello_World $ dmesg | tail -3
    [    0.000000] Booting Linux on physical CPU 0x0
    [  820.235985] hwmon hwmon1: Voltage normalised
    [ 1036.484686] Jonathan DEBUG: Kernel Module Inserted Successfully...
    
## Tip
Mostrar las primeras/últimas n líneas de un archivo con `head -n` o `tail -n` respectivamente

# Revisar logs del kernel

El comando `dmesg` muestra los logs del kernel, estos pueden ser extensos así que mostraremos
las últimas 5 lineas con el comando `tail`:

    dmesg | tail -5
    

# Desmontar el driver
Para desmontar se usa el siguiente comando `rmmod`:

    sudo rmmod hello_world.ko

## Mostrar info del driver
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
