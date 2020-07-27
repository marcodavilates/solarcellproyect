from math import exp
from math import pow
import sys

Iscn = float(input("Ingrese la corriente de cortocircuito: "))
Voc = float(input("Ingrese el voltaje de circuito abierto: "))
Kv = float(input("Ingrese el coeficiente de V/T: "))*(-1)
Ki = float(input("Ingrese el coeficiente de I/T: "))
tn = float(input("Ingrese la  temperatura nominal: "))+273.15
Gn = float(input("Ingrese la irradiancia nominal: "))
G = float(input("Ingrese la irradiancia requerida: "))
t = float(input("Ingrese la  temperatura requerida: "))+273.15
Ns = float(input("Ingrese el numero de celdas conectadas en serie: "))
a = float(input("Constante del diodo: "))
q = 1.60217646*pow(10, -19)
k = 1.3806503*pow(10, -23)
vt = (Ns*k*t)/q
print(vt)
Dt = t - tn
iph = (Iscn + Ki*Dt)*G/Gn
print(iph)
io = (Iscn + Ki*Dt)/(exp((Voc+(Kv*Dt))/(vt*a))-1)
print(io)