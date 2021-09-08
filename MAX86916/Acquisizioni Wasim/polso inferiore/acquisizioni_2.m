%%
%@author Wasim Essbai
%%
close all

%File di interesse: 2, 4, 5, 7, 14
figure('Name', 'Prova 2')
subplot(4,1,1)
plot(prova2polsosxmax.Channel1, 'm')
subplot(4,1,2)
plot(prova2polsosxmax.Channel2, 'r')
subplot(4,1,3)
plot(prova2polsosxmax.Channel3, 'g')
subplot(4,1,4)
plot(prova2polsosxmax.Channel4, 'b')

figure('Name', 'Prova 4')
subplot(4,1,1)
plot(prova4polsosxmax.Channel1, 'm')
subplot(4,1,2)
plot(prova4polsosxmax.Channel2, 'r')
subplot(4,1,3)
plot(prova4polsosxmax.Channel3, 'g')
subplot(4,1,4)
plot(prova4polsosxmax.Channel4, 'b')

figure('Name', 'Prova 5')
subplot(4,1,1)
plot(prova5polsosxmax.Channel1, 'm')
subplot(4,1,2)
plot(prova5polsosxmax.Channel2, 'r')
subplot(4,1,3)
plot(prova5polsosxmax.Channel3, 'g')
subplot(4,1,4)
plot(prova5polsosxmax.Channel4, 'b')

figure('Name', 'Prova 7')
subplot(4,1,1)
plot(prova7polsosxmax.Channel1, 'm')
subplot(4,1,2)
plot(prova7polsosxmax.Channel2, 'r')
subplot(4,1,3)
plot(prova7polsosxmax.Channel3, 'g')
subplot(4,1,4)
plot(prova7polsosxmax.Channel4, 'b')

figure('Name', 'Prova 14')
subplot(4,1,1)
plot(prova14polsosxmax.Channel1, 'm')
subplot(4,1,2)
plot(prova14polsosxmax.Channel2, 'r')
subplot(4,1,3)
plot(prova14polsosxmax.Channel3, 'g')
subplot(4,1,4)
plot(prova14polsosxmax.Channel4, 'b')

%%Selezione finestra
pos_iniziale = 1650;
flag = prova4polsosxmax.timestamp >= prova4polsosxmax.timestamp(pos_iniziale) & prova4polsosxmax.timestamp < prova4polsosxmax.timestamp(pos_iniziale)+10000

milli_zero = prova4polsosxmax.timestamp(pos_iniziale)

time = prova4polsosxmax.timestamp-milli_zero
time = time ./1000

f = figure
plot(time(flag),prova4polsosxmax.Channel1(flag), 'm')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED IR');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])

f = figure
plot(time(flag),prova4polsosxmax.Channel2(flag), 'r')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED RED');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])

f = figure
plot(time(flag),prova4polsosxmax.Channel3(flag), 'g')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED GREEN');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])


f = figure
plot(time(flag),prova4polsosxmax.Channel4(flag), 'b')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED BLU');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])

