import pandas as pd
import matplotlib.pyplot as plt

# Lê um arquivo .CSV e o transforma em um DataFrame

dados1 = pd.read_csv('Teste_PID/Kp6Ki001Kd8.csv')
dados2 = pd.read_csv('Teste_PID/Kp6Ki001Kd98.csv')
dados3 = pd.read_csv('Teste_PID/Kp8Ki001Kd8.csv')
dados4 = pd.read_csv('Teste_PID/Kp8Ki001Kd98.csv')

#Grafico Velocidade x Tempo

plt.figure(figsize = ((12, 10)))
plt.subplot(2, 2, 1)
plt.plot(dados1['Tempo(s)'], dados1['Setpoint(RPM)'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados1['Tempo(s)'], dados1['Vel(RPM)'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados1['Tempo(s)'], dados1['erro(RPM)'], linestyle='-', marker='_', color = 'green', markersize = 1)
plt.legend(['Setpoint','Velocidade','erro'])
plt.title('Kp = 0,6, Ki = 0,001 e Kd = 0,8 (1)')
plt.xlabel('Tempo (s)')
plt.ylabel('Velocidade do motor (RPM)')
plt.grid()

plt.subplot(2, 2, 2)
plt.plot(dados2['Tempo(s)'], dados2['Setpoint(RPM)'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados2['Tempo(s)'], dados2['Vel(RPM)'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados2['Tempo(s)'], dados2['erro(RPM)'], linestyle='-', marker='_', color = 'green', markersize = 1)
plt.legend(['Setpoint','Velocidade','erro'])
plt.title('Kp = 0,6, Ki = 0,001 e Kd = 0,98 (2)')
plt.xlabel('Tempo (s)')
plt.ylabel('Velocidade do motor (RPM)')
plt.grid()

plt.subplot(2, 2, 3)
plt.plot(dados3['Tempo(s)'], dados3['Setpoint(RPM)'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados3['Tempo(s)'], dados3['Vel(RPM)'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados3['Tempo(s)'], dados3['erro(RPM)'], linestyle='-', marker='_', color = 'green', markersize = 1)
plt.legend(['Setpoint','Velocidade','erro'])
plt.title('Kp = 0,8, Ki = 0,001 e Kd = 0,8 (3)')
plt.xlabel('Tempo (s)')
plt.ylabel('Velocidade do motor (RPM)')
plt.grid()

plt.subplot(2, 2, 4)
plt.plot(dados4['Tempo(s)'], dados4['Setpoint(RPM)'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados4['Tempo(s)'], dados4['Vel(RPM)'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados4['Tempo(s)'], dados4['erro(RPM)'], linestyle='-', marker='_', color = 'green', markersize = 1)
plt.legend(['Setpoint','Velocidade','erro'])
plt.title('Kp = 0,8, Ki = 0,001 e Kd = 0,98 (4)')
plt.xlabel('Tempo (s)')
plt.ylabel('Velocidade do motor (RPM)')
plt.grid()

#Gráfico Acoes de Controle x Tempo

plt.figure(figsize = ((12, 10)))
plt.subplot(2, 2, 1)
plt.plot(dados1['Tempo(s)'], dados1['AcaoP'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados1['Tempo(s)'], dados1['AcaoI'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados1['Tempo(s)'], dados1['AcaoD'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados1['Tempo(s)'], dados1['Controle'], linestyle='-', marker='_', color = 'blue', markersize = 1)
plt.legend(['Proporcional', 'Integrativa', 'Derivativa', 'Controle'])
plt.title('Kp = 0,6, Ki = 0,001 e Kd = 0,8 (1)')
plt.xlabel('Tempo (s)')
plt.ylabel('Velocidade do motor (RPM)')
plt.grid()

plt.subplot(2, 2, 2)
plt.plot(dados2['Tempo(s)'], dados2['AcaoP'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados2['Tempo(s)'], dados2['AcaoI'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados2['Tempo(s)'], dados2['AcaoD'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados2['Tempo(s)'], dados2['Controle'], linestyle='-', marker='_', color = 'blue', markersize = 1)
plt.legend(['Proporcional', 'Integrativa', 'Derivativa', 'Controle'])
plt.title('Kp = 0,6, Ki = 0,001 e Kd = 0,98 (2)')
plt.xlabel('Tempo (s)')
plt.ylabel('Ações de Controle')
plt.grid()

plt.subplot(2, 2, 3)
plt.plot(dados3['Tempo(s)'], dados3['AcaoP'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados3['Tempo(s)'], dados3['AcaoI'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados3['Tempo(s)'], dados3['AcaoD'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados3['Tempo(s)'], dados3['Controle'], linestyle='-', marker='_', color = 'blue', markersize = 1)
plt.legend(['Proporcional', 'Integrativa', 'Derivativa', 'Controle'])
plt.title('Kp = 0,8, Ki = 0,001 e Kd = 0,8 (3)')
plt.xlabel('Tempo (s)')
plt.ylabel('Ações de Controle')
plt.grid()

plt.subplot(2, 2, 4)
plt.plot(dados4['Tempo(s)'], dados4['AcaoP'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados4['Tempo(s)'], dados4['AcaoI'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados4['Tempo(s)'], dados4['AcaoD'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados4['Tempo(s)'], dados4['Controle'], linestyle='-', marker='_', color = 'blue', markersize = 1)
plt.legend(['Proporcional', 'Integrativa', 'Derivativa', 'Controle'])
plt.title('Kp = 0,8, Ki = 0,001 e Kd = 0,98 (4)')
plt.xlabel('Tempo (s)')
plt.ylabel('Ações de Controle')
plt.grid()

plt.show() 