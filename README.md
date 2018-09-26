# Tugas Kecil 1 IF4031 - Simple Libev HTTP Server

## Deskripsi
HTTP Server dengan menggunakan Libev yang memberikan akses ke dua buah HTML page dengan ukuran 500 bytes dan 20KB.

## Server Benchmark

### Tools Benchmark yang digunakan
Apache Bench (Ab)

### Cara melakukan testing
1. Memasukkan perintah sebagai berikut untuk melakukan benchmarking terhadap page 500 bytes.
	```shell
	ab -n 10000 -c 10000 http://127.0.0.1:8080/500b.html
	```

2. Memasukkan perintah sebagai berikut untuk melakukan benchmarking terhadap page 20KB.
	```shell
	ab -n 10000 -c 10000 http://127.0.0.1:8080/20k.html
	```

## Server Libev

### Petunjuk Instalasi Server Libev
1. Masuk ke folder proyek Libev
2. Memasukkan perintah berikut untuk melakukan compilation.
	```shell
	$ make
	```

### Eksekusi Server Libev
Memasukkan perintah berikut untuk menjalankan program server Libev
```shell
$ make exec
```

## Authors
Kanisius Kenneth Halim / 13515008

Ferdinandus Richard / 13515066