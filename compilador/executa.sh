clear
echo "# Compilando..."
make -f Makefile
echo "# Gerando MEPA..."
./compilador $1 
echo $1
if [ $? == 0 ]; then
    echo "# Montando..."
    make mepa
    if [ $? == 0 ]; then
        echo "# Executando."
        ./mepa
    fi
    echo "# FIM"
fi
