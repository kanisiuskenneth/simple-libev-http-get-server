# Tugas Kecil 1 IF4031 - Simple Libev HTTP Server

## Deskripsi
HTTP Server dengan menggunakan Libev yang memberikan akses ke dua buah HTML page dengan ukuran 500 bytes dan 20KB.

## Server Benchmark

### Tools Benchmark yang digunakan
Apache Bench (Ab)

### Cara melakukan testing
1. Meletakkan HTML page 500 byte dan 20KB pada direktori `/var/www/html`

2. Menyalakan server Apache dengan memasukkan perintah berikut.
	```shell
	$ sudo service apache2 start
	```

3. Memasukkan perintah untuk melihat memory usage setiap 0.1 detik, melihat initial dan peak memory usage dan mencari selisihnya.
	```shell
	$ watch -n 0,1 free
	```

4. Memasukkan perintah sebagai berikut untuk melakukan benchmarking terhadap page 500 bytes.
	```shell
	$ ab -n 10000 -c 10000 http://127.0.0.1/500b.html
	```

5. Memasukkan perintah sebagai berikut untuk melakukan benchmarking terhadap page 20KB.
	```shell
	$ ab -n 10000 -c 10000 http://127.0.0.1/20k.html
	```

6. Mematikan server Apache dan menyalakan server Nginx dengan perintah berikut.
	```shell
	$ sudo service apache2 stop
	$ sudo service nginx start
	```

7. Melakukan langkah 4 dan 5 dengan server Nginx.

### Hasil Testing Server Apache
1. Testing C10K 500 byte HTML Page
	<table>
		<tr>
			<th>Eksperimen</th>
			<th>Response Time</th>
			<th>Memory Usage</th>
		</tr>
		<tr>
			<td>1</td>
			<td>Timeout (8412 reqs)</td>
			<td>~110000 KB</td>
		</tr>
		<tr>
			<td>2</td>
			<td>Timeout (7888 reqs)</td>
			<td>~98000 KB</td>
		</tr>
		<tr>
			<td>3</td>
			<td>Timeout (7045 reqs)</td>
			<td>~89000 KB</td>
		</tr>
	</table>

2. Testing C10K 20 KB HTML Page
	<table>
		<tr>
			<th>Eksperimen</th>
			<th>Response Time</th>
			<th>Memory Usage</th>
		</tr>
		<tr>
			<td>1</td>
			<td>Timeout (7674 reqs)</td>
			<td>~97000 KB</td>
		</tr>
		<tr>
			<td>2</td>
			<td>Timeout (7052 reqs)</td>
			<td>~95000 KB</td>
		</tr>
		<tr>
			<td>3</td>
			<td>Timeout (6766 reqs)</td>
			<td>~96000 KB</td>
		</tr>
	</table>

### Hasil Testing Server Nginx
1. Testing C10K 500 byte HTML Page
	<table>
		<tr>
			<th>Eksperimen</th>
			<th>Response Time</th>
			<th>Memory Usage</th>
		</tr>
		<tr>
			<td>1</td>
			<td>1545.122 ms</td>
			<td>~101000 KB</td>
		</tr>
		<tr>
			<td>2</td>
			<td>1363.030 ms</td>
			<td>~95000 KB</td>
		</tr>
		<tr>
			<td>3</td>
			<td>1110.557 ms</td>
			<td>~94000 KB</td>
		</tr>
	</table>

2. Testing C10K 20 KB HTML Page
	<table>
		<tr>
			<th>Eksperimen</th>
			<th>Response Time</th>
			<th>Memory Usage</th>
		</tr>
		<tr>
			<td>1</td>
			<td>1062.133 ms</td>
			<td>~95000 KB</td>
		</tr>
		<tr>
			<td>2</td>
			<td>1060.449 ms</td>
			<td>~103000 KB</td>
		</tr>
		<tr>
			<td>3</td>
			<td>1235.089 ms</td>
			<td>~100000 KB</td>
		</tr>
	</table>

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