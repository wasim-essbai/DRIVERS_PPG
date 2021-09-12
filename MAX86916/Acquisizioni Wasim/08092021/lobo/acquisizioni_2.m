%%
%@author Wasim Essbai
%%
close all

figure
subplot(4,1,1)
plot(lobosxmaxavg1100Hz.Channel1, 'm')
subplot(4,1,2)
plot(lobosxmaxavg1100Hz.Channel2, 'r')
subplot(4,1,3)
plot(lobosxmaxavg1100Hz.Channel3, 'g')
subplot(4,1,4)
plot(lobosxmaxavg1100Hz.Channel4, 'b')

pos_iniziale = 2300;
flag = lobosxmaxavg1100Hz.timestamp >= lobosxmaxavg1100Hz.timestamp(pos_iniziale) & lobosxmaxavg1100Hz.timestamp < lobosxmaxavg1100Hz.timestamp(pos_iniziale)+10000

milli_zero = lobosxmaxavg1100Hz.timestamp(pos_iniziale)

time = lobosxmaxavg1100Hz.timestamp-milli_zero
time = time ./1000

f = figure
plot(time(flag),lobosxmaxavg1100Hz.Channel1(flag), 'm')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED IR','Location', 'North');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'ired.pdf','Resolution',600)

f = figure
plot(time(flag),lobosxmaxavg1100Hz.Channel2(flag), 'r')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED RED','Location', 'North');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'red.pdf','Resolution',600)

f = figure
plot(time(flag),lobosxmaxavg1100Hz.Channel3(flag), 'g')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED GREEN','Location', 'North');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'green.pdf','Resolution',600)

f = figure
plot(time(flag),lobosxmaxavg1100Hz.Channel4(flag), 'b')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED BLU','Location', 'North');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'blu.pdf','Resolution',600)
