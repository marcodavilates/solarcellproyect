from math import exp
from math import pow
from math import log

Iscn = float(input("Ingrese la corriente de cortocircuito: "))
Voc = float(input("Ingrese el voltaje de circuito abierto: "))
Impp = float(input("Ingrese la corriente de maxima potencia: "))
Vmpp = float(input("Ingrese el voltaje de maxima potencia: "))
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
rmpp = Vmpp/Impp
rs = 0
rsm = (Voc - Vmpp)/Impp
rss =rsm/1000
vt1 = (1.25*1.381*pow(10,-23)*t)/(1.602*pow(10,-19))
N0 = rmpp*(Vmpp-(Ns*vt))
N1 = (Ns*vt1)-(Iscn*rmpp)
N2 = Iscn - Impp
D0 = (Iscn*Impp) - Vmpp - (Ns*vt1)
D1 = Impp - Iscn
rsh = ((N2*pow(rs,2))+(N1*rs)+N0)/((D1*rs) + D0)
B = -Vmpp + (Ns*vt*Impp*Voc)/Iscn*Vmpp
C = Iscn - Impp - (Ns*vt*Impp)/Vmpp
D = Impp - Iscn - (Iscn*exp((Vmpp+(Impp*rs)-Voc)/Ns*vt))
rscomp = -1*(B*D0 - D*N0)/(C*D0 + B*D1 - D*N1)
rshcomp = (B + C*rs)/D
vtp=vt
while(abs(rs-rscomp)>0.0001 and rs>rscomp and rsh > rshcomp):
    rs = rs + rss
    vt = ((Iscn*rs)-Voc)/(Ns*log(abs((Ns*vtp*rs)/((Iscn*rsh + Iscn*rs -Voc)*(rsh - rs)))))
    N0 = rmpp*(Vmpp-(Ns*vt))
    N1 = (Ns*vt1)-(Iscn*rmpp)
    N2 = Iscn - Impp
    D0 = (Iscn*Impp) - Vmpp - (Ns*vt1)
    D1 = Impp - Iscn
    rsh = abs(((N2*pow(rs,2))+(N1*rs)+N0)/((D1*rs) + D0))
    B = -Vmpp + (Ns*vt*Impp*Voc)/Iscn*Vmpp
    C = Iscn - Impp - (Ns*vt*Impp)/Vmpp
    D = Impp - Iscn - (Iscn*exp((Vmpp+(Impp*rs)-Voc)/Ns*vt))
    rscomp = -1*(B*D0 - D*N0)/(C*D0 + B*D1 - D*N1)
    rshcomp = (B + C*rs)/D
    vtp=vt
print(rs)
print(rsh)

