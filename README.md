# IMD
Pruebas del kernel en Raspberry o Linux

# Propósito
Practicar la compilación y ejecución de módulos para kernel de Linux.

# Requisitos
En una terminal de la Raspberry:

    sudo apt-get update
    sudo apt-get upgrade

o

    sudo rpi-update

**Instalar los headers:**

    sudo apt install raspberrypi-kernel-headers

Para ver el kernel instalado:

    uname -a

La salida en la terminal sería:

    Linux raspberrypi 5.15.76-v7+ #1597 SMP Fri Nov 4 12:13:17 GMT 2022 armv7l GNU/Linux

# Paso a paso
A continuación se muestra el paso a paso para el ejemplo en `./0_Hello_world`.
El resto de ejemplos se ejecuta de manera similar

# Compilar el módulo
Entrar a la carpeta `0_Hello_world`

    cd 0_Hello_world

Compilar con el comando:

    sudo make

La salida en la terminal:

    make -C /lib/modules/5.15.76-v7+/build  M=/home/j/Documents/IMD/Hello_World modules
    make[1]: Entering directory '/usr/src/linux-headers-5.15.76-v7+'
    make[1]: Leaving directory '/usr/src/linux-headers-5.15.76-v7+'

# Montar el driver
Para montar el módulo usaremos el comando `insmod` con privilegio:

    sudo insmod hello_world.ko

Para verificar que se montó al kernel, se usa lsmod.

    lsmod | head -3

La salida en la terminal:

    Module                  Size  Used by
    hello_world            16384  0
    rfcomm                 49152  4

Para ver el proyecto ejecutando se usa el comando dmesg:

    dmesg | tail -3

Su salida sería:

    [    0.000000] Booting Linux on physical CPU 0x0
    [  820.235985] hwmon hwmon1: Voltage normalised
    [ 1036.484686] Jonathan DEBUG: Kernel Module Inserted Successfully...

## Tip
`head -n` o `tail -n` muestran respectivamente las primeras/últimas n lineas.

# Desmontar el driver
Para desmontar se usa el siguiente comando `rmmod`:

    sudo rmmod hello_world.ko

Verificar el log:

    dmesg | tail -3

La salida en la terminal:

    [  820.235985] hwmon hwmon1: Voltage normalised
    [ 1036.484686] Jonathan DEBUG: Kernel Module Inserted Successfully...
    [ 7542.193394] Jonathan DEBUG: Kernel Module Removed Successfully...


## Mostrar info del driver
Para mostrar informacion del módulo.

    modinfo hello_world.ko

La salida en la terminal:

    filename:       /home/j/Documents/IMD/0_Hello_world/hello_world.ko
    version:        1:1.0
    description:    hello world driver
    author:         JC<jonathan.cagua@gmail.com>
    license:        GPL
    srcversion:     0A51D4AD6B1C970AA4E05FC
    depends:
    name:           hello_world
    vermagic:       5.15.76-v7+ SMP mod_unload modversions ARMv7 p2v8
