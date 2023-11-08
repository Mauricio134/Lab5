import matplotlib.pyplot as plt
import numpy as np

nombre_archivo = "clusters.txt"
nombre_archivo1 = "centroides.txt"
nombre_archivo2 = "WSS.txt"


grupos = []
centroides = []
cluster = []

x = []
y = []
with open(nombre_archivo, "r") as archivo:
    for linea in archivo:
        if linea.strip() == "************":
            cluster.append(x)
            cluster.append(y)
            grupos.append(cluster)
            x = []
            y = [] 
            cluster = []
        else:
            partes = linea.split()
            if len(partes) == 2:
                valor1, valor2 = partes
                x.append(float(valor1))
                y.append(float(valor2))

with open(nombre_archivo1, "r") as archivo:
    # Leer cada línea del archivo
    for linea in archivo:
        if linea.strip() == "************":
            cluster.append(x)
            cluster.append(y)
            centroides.append(cluster)
            x = []
            y = [] 
            cluster = []
        else:
            partes = linea.split()
            if len(partes) == 2: 
                valor1, valor2 = partes
                x.append(float(valor1)) 
                y.append(float(valor2))

WSS = 0
with open(nombre_archivo2, "r") as archivo:
        WSS = float(archivo.readline().strip())

for i in range(len(grupos)):
    x = grupos[i][0]
    y = grupos[i][1]

    color = np.random.rand(3,)
    
    plt.scatter(x, y, label=f'Grupo {i + 1}', c=[color], marker='o')

for i in range(len(centroides)):
    x = centroides[i][0]
    y = centroides[i][1]
    
    plt.scatter(x, y, c="y", s=200, marker='o')


plt.xlabel('Eje X')
plt.ylabel('Eje Y')

plt.title('Gráfico de Kmeans con WSS = ' + str(WSS))

plt.legend()

plt.show()