# huffman
proyecto 2 EDAA

Para compilar

	```
	$ g++ Comprimir.cpp -o compresor
	$ g++ Descomprimir.cpp -o descompresor
	```

Para comprimir
	```
	$ ./compresor <archivo_a_comprimir> <archivo_comprimido>
	```

Para descomprimir
	```
	$ ./descompresor <archivo_comprimido> <archivo_descomprimido>
	```

Para chequear si el archivo original es idéntico al archivo descomprimido se puede utilizar
el comando diff o md5sum.