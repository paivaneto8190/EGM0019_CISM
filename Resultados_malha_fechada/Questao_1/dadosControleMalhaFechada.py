import pandas as pd
import matplotlib.pyplot as plt

# Lê um arquivo .CSV e o transforma em um DataFrame
#pd.options.display.max_rows = 9999 

dados = pd.read_csv('Teste_p/Kp7.csv')

plt.figure(figsize = ((12, 6)))
plt.subplot(1, 2, 1)
plt.plot(dados['Tempo(s)'], dados['Setpoint(RPM)'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados['Tempo(s)'], dados['Vel(RPM)'], linestyle='-', marker='_', color = 'blue', markersize = 2)
plt.plot(dados['Tempo(s)'], dados['erro(RPM)'], linestyle='-', marker='_', color = 'green', markersize = 1)
plt.title('Comparacao do setpoint com a velocidade do motor')
plt.legend(['Setpoint','Velocidade','erro'])
plt.xlabel('Tempo (s)')
plt.ylabel('Velocidade do motor')

plt.subplot(1, 2, 2)
plt.plot(dados['Tempo(s)'], dados['AcaoP'], linestyle='-', marker='_', color = 'green', markersize = 2)
plt.plot(dados['Tempo(s)'], dados['AcaoI'], linestyle='-', marker='_', color = 'red', markersize = 2)
plt.plot(dados['Tempo(s)'], dados['Controle'], linestyle='-', marker='_', color = 'b', markersize = 2)
plt.title('Valores das acoes de controle')
plt.xlabel('Tempo (s)')
plt.ylabel('Acoes do controlador')
plt.legend(['Proporcional','Integrativa', 'Controle'])

plt.grid()
plt.show() 