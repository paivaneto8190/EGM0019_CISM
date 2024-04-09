import pandas as pd
import matplotlib.pyplot as plt

# Lê um arquivo .CSV e o transforma em um DataFrame
#pd.options.display.max_rows = 9999 

dados1 = pd.read_csv('Teste_PI/Kp1Ki005.csv')
dados2 = pd.read_csv('Teste_PI/Kp6Ki01.csv')
dados3 = pd.read_csv('Teste_PI/Kp6Ki001.csv')
dados4 = pd.read_csv('Teste_PI/Kp8Ki005.csv')

#Grafico Velocidade x Tempo

plt.figure(figsize = ((12, 10)))
plt.subplot(2, 2, 1)
plt.plot(dados1['Tempo(s)'], dados1['Setpoint(RPM)'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados1['Tempo(s)'], dados1['Vel(RPM)'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados1['Tempo(s)'], dados1['erro(RPM)'], linestyle='-', marker='_', color = 'green', markersize = 1)
plt.legend(['Setpoint','Velocidade','erro'])
plt.title('Kp = 0,7')
plt.xlabel('Tempo (s)')
plt.ylabel('Velocidade do motor')
plt.grid()

plt.subplot(2, 2, 2)
plt.plot(dados2['Tempo(s)'], dados2['Setpoint(RPM)'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados2['Tempo(s)'], dados2['Vel(RPM)'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados2['Tempo(s)'], dados2['erro(RPM)'], linestyle='-', marker='_', color = 'green', markersize = 1)
plt.legend(['Setpoint','Velocidade','erro'])
plt.title('Kp = 1,0')
plt.xlabel('Tempo (s)')
plt.ylabel('Velocidade do motor')
plt.grid()

plt.subplot(2, 2, 3)
plt.plot(dados3['Tempo(s)'], dados3['Setpoint(RPM)'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados3['Tempo(s)'], dados3['Vel(RPM)'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados3['Tempo(s)'], dados3['erro(RPM)'], linestyle='-', marker='_', color = 'green', markersize = 1)
plt.legend(['Setpoint','Velocidade','erro'])
plt.title('Kp = 1,5')
plt.xlabel('Tempo (s)')
plt.ylabel('Velocidade do motor')
plt.grid()

plt.subplot(2, 2, 4)
plt.plot(dados4['Tempo(s)'], dados4['Setpoint(RPM)'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados4['Tempo(s)'], dados4['Vel(RPM)'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados4['Tempo(s)'], dados4['erro(RPM)'], linestyle='-', marker='_', color = 'green', markersize = 1)
plt.legend(['Setpoint','Velocidade','erro'])
plt.title('Kp = 2,0')
plt.xlabel('Tempo (s)')
plt.ylabel('Velocidade do motor')
plt.grid()

#Gráfico Acoes de Controle x Tempo

plt.figure(figsize = ((12, 10)))
plt.plot(dados1['Tempo(s)'], dados1['AcaoP'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados2['Tempo(s)'], dados2['Controle'], linestyle='-', marker='_', color = 'green', markersize = 2)
plt.plot(dados3['Tempo(s)'], dados3['Controle'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados4['Tempo(s)'], dados4['Controle'], linestyle='-', marker='_', color = 'orange', markersize = 2)
plt.legend(['Kp = 0,7','Kp = 1,0', 'Kp = 1,5', 'Kp = 2,0'])
plt.xlabel('Tempo (s)')
plt.ylabel('Acoes de Controle')
plt.grid()

'''plt.figure(figsize = ((12, 10)))
plt.subplot(2, 2, 1)
plt.plot(dados1['Tempo(s)'], dados1['AcaoP'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados1['Tempo(s)'], dados1['Controle'], linestyle='-', marker='_', color = 'green', markersize = 1)
plt.legend(['AcaoP','Controle'])
plt.title('Kp = 0,7')
plt.xlabel('Tempo (s)')
plt.ylabel('Acoes de Controle')
plt.grid()

plt.subplot(2, 2, 2)
plt.plot(dados2['Tempo(s)'], dados2['AcaoP'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados2['Tempo(s)'], dados2['Controle'], linestyle='-', marker='_', color = 'green', markersize = 1)
plt.legend(['AcaoP','Controle'])
plt.title('Kp = 1,0')
plt.xlabel('Tempo (s)')
plt.ylabel('Acoes de Controle')
plt.grid()

plt.subplot(2, 2, 3)
plt.plot(dados3['Tempo(s)'], dados3['AcaoP'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados3['Tempo(s)'], dados3['Controle'], linestyle='-', marker='_', color = 'green', markersize = 1)
plt.legend(['AcaoP','Controle'])
plt.title('Kp = 1,5')
plt.xlabel('Tempo (s)')
plt.ylabel('Acoes de Controle')
plt.grid()

plt.subplot(2, 2, 4)
plt.plot(dados4['Tempo(s)'], dados4['AcaoP'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados4['Tempo(s)'], dados4['Controle'], linestyle='-', marker='_', color = 'green', markersize = 1)
plt.legend(['AcaoP','Controle'])
plt.title('Kp = 2,0')
plt.xlabel('Tempo (s)')
plt.ylabel('Acoes de Controle')
plt.grid()'''

plt.show() 