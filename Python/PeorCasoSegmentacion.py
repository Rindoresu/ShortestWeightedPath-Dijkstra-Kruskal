import numpy as np
import pandas as pd

h = 1000
w = 2000

tests = np.zeros(h+1,w)


tests[0][0] = w
tests[0][1] = h
for i in range(1,h+1):
    for j in range(0,w):
        tests[i][j] = 0

df = pd.DataFrame(tests)

path = '/home/leandro/CLionProjects/algoritmos3-tp2/Python/'
file = 'imagenNegra.csv'

df.to_csv(path_or_buf=path+file, index=False, header=False, sep=' ')


"""n_ini = 5
n_fin = 30
prim_columna = [n_ini]
sec_columna = [n_fin]

for i in range(n_ini, n_fin+1):
    prim_columna.append(i)
    sec_columna.append(2**i)
    for j in range(i-1):
        prim_columna.append(1)
        sec_columna.append(1)
    prim_columna.append(2**i)
    sec_columna.append(2**i - 1)

tests = {'A': prim_columna,
         'B': sec_columna}

df = pd.DataFrame(tests)

path = '/home/leandro/CLionProjects/algoritmos3-tp1/Python/'
file = 'MaloBacktrackingPseudopolinomial.csv'

df.to_csv(path_or_buf=path+file, index=False, header=False, sep=' ')


n_ini = 5
n_fin = 30
prim_columna = [n_ini]
sec_columna = [n_fin]

for i in range(n_ini, n_fin+1):
    prim_columna.append(i)
    sec_columna.append(i+1)
    for j in range(i-1):
        prim_columna.append(1)
        sec_columna.append(1)
    prim_columna.append(i+1)
    sec_columna.append(i)

tests = {'A': prim_columna,
         'B': sec_columna}

df = pd.DataFrame(tests)

path = '/home/leandro/CLionProjects/algoritmos3-tp1/Python/'
file = 'MaloBacktrackingLineal.csv'

df.to_csv(path_or_buf=path+file, index=False, header=False, sep=' ')

n_ini = 5
n_fin = 30
prim_columna = [n_ini]
sec_columna = [n_fin]

for i in range(n_ini, n_fin+1):
    prim_columna.append(i)
    sec_columna.append(2 ** i)
    for j in range(i):
        prim_columna.append((2 ** i) + 1)
        sec_columna.append(1)


tests = {'A': prim_columna,
         'B': sec_columna}

df = pd.DataFrame(tests)

path = '/home/leandro/CLionProjects/algoritmos3-tp1/Python/'
file = 'BuenoBacktrackingFacti.csv'

df.to_csv(path_or_buf=path+file, index=False, header=False, sep=' ')

n_ini = 5
n_fin = 30
prim_columna = [n_ini]
sec_columna = [n_fin]

for i in range(n_ini, n_fin+1):
    prim_columna.append(i)
    sec_columna.append(2**i)
    for j in range(i):
        prim_columna.append(1)
        sec_columna.append(j+1)


tests = {'A': prim_columna,
         'B': sec_columna}

df = pd.DataFrame(tests)

path = '/home/leandro/CLionProjects/algoritmos3-tp1/Python/'
file = 'BuenoBacktrackingOpti.csv'

df.to_csv(path_or_buf=path+file, index=False, header=False, sep=' ')

n_ini = 5
n_fin = 30
prim_columna = [n_ini]
sec_columna = [n_fin]

for i in range(n_ini, n_fin+1):
    prim_columna.append(i)
    sec_columna.append(i)
    for j in range(i):
        prim_columna.append(i + 1)
        sec_columna.append(1)


tests = {'A': prim_columna,
         'B': sec_columna}

df = pd.DataFrame(tests)

path = '/home/leandro/CLionProjects/algoritmos3-tp1/Python/'
file = 'BuenoBacktrackingFactiLin.csv'

df.to_csv(path_or_buf=path+file, index=False, header=False, sep=' ')

n_ini = 5
n_fin = 30
prim_columna = [n_ini]
sec_columna = [n_fin]

for i in range(n_ini, n_fin+1):
    prim_columna.append(i)
    sec_columna.append(i)
    for j in range(i):
        prim_columna.append(1)
        sec_columna.append(j+1)


tests = {'A': prim_columna,
         'B': sec_columna}

df = pd.DataFrame(tests)

path = '/home/leandro/CLionProjects/algoritmos3-tp1/Python/'
file = 'BuenoBacktrackingOptiLin.csv'

df.to_csv(path_or_buf=path+file, index=False, header=False, sep=' ')"""
