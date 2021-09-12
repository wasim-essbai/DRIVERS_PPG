%%
%@author Wasim Essbai
%%
close all

figure
subplot(4,1,1)
plot(indicesxmaxavg1100Hz.Channel1, 'm')
subplot(4,1,2)
plot(indicesxmaxavg1100Hz.Channel2, 'r')
subplot(4,1,3)
plot(indicesxmaxavg1100Hz.Channel3, 'g')
subplot(4,1,4)
plot(indicesxmaxavg1100Hz.Channel4, 'b')

pos_iniziale = 2000;
flag = indicesxmaxavg1100Hz.timestamp >= indicesxmaxavg1100Hz.timestamp(pos_iniziale) & indicesxmaxavg1100Hz.timestamp < indicesxmaxavg1100Hz.timestamp(pos_iniziale)+10000

milli_zero = indicesxmaxavg1100Hz.timestamp(pos_iniziale)

time = indicesxmaxavg1100Hz.timestamp-milli_zero
time = time ./1000

f = figure
plot(time(flag),indicesxmaxavg1100Hz.Channel1(flag), 'm')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED IR', 'Location', 'north');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'ired.pdf','Resolution',600)

f = figure
plot(time(flag),indicesxmaxavg1100Hz.Channel2(flag), 'r')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED RED', 'Location', 'north');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'red.pdf','Resolution',600)

f = figure
plot(time(flag),indicesxmaxavg1100Hz.Channel3(flag), 'g')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED GREEN', 'Location', 'north');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'green.pdf','Resolution',600)

f = figure
plot(time(flag),indicesxmaxavg1100Hz.Channel4(flag), 'b')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED BLU', 'Location', 'north');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'blu.pdf','Resolution',600)
