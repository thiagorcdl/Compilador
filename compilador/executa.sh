echo "# Compilando..."
make -f Makefile
echo "# Gerando MEPA..."
./compilador $1 
if [ $? == 0 ]; then
    arch="32"
    if [ `uname -m` == "x86_64" ]; then
        arch=`uname -m`
    fi
    echo "# Montando..."
    as mepa$arch.s -o mepa.o
    if [ $? == 0 ]; then
        echo "# Ligando..."
        ld mepa.o -o mepa -lc -dynamic-linker /lib/ld-linux.so.2  
        if [ $? == 0 ]; then
            echo "# Executando."
            ./mepa
        fi
    fi
    echo "# FIM"
fi
