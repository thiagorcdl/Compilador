#!/bin/bash

for i in in/PgmasTeste/*; do
	echo -e "\n\n\nTestando $i:"
	./compilador $i/pgma.pas > /dev/null
	diff MEPA $i/MEPA
done
