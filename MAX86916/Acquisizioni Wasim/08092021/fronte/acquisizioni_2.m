%%
%@author Wasim Essbai
%%
close all

figure
subplot(4,1,1)
plot(frontemaxavg1100Hz.Channel1, 'm')
subplot(4,1,2)
plot(frontemaxavg1100Hz.Channel2, 'r')
subplot(4,1,3)
plot(frontemaxavg1100Hz.Channel3, 'g')
subplot(4,1,4)
plot(frontemaxavg1100Hz.Channel4, 'b')

pos_iniziale = 3200;
flag = frontemaxavg1100Hz.timestamp >= frontemaxavg1100Hz.timestamp(pos_iniziale) & frontemaxavg1100Hz.timestamp < frontemaxavg1100Hz.timestamp(pos_iniziale)+10000

milli_zero = frontemaxavg1100Hz.timestamp(pos_iniziale)

time = frontemaxavg1100Hz.timestamp-milli_zero
time = time ./1000

f = figure
plot(time(flag),frontemaxavg1100Hz.Channel1(flag), 'm')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED IR');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'ired.pdf','Resolution',600)

f = figure
plot(time(flag),frontemaxavg1100Hz.Channel2(flag), 'r')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED RED','Location','south');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'red.pdf','Resolution',600)

f = figure
plot(time(flag),frontemaxavg1100Hz.Channel3(flag), 'g')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED GREEN','Location','south');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'green.pdf','Resolution',600)

f = figure
plot(time(flag),frontemaxavg1100Hz.Channel4(flag), 'b')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED BLU','Location','south');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'blu.pdf','Resolution',600)

samplepersecond = 10;
coeff = ones(1, samplepersecond)/samplepersecond;

smoothed = filter(coeff, 1, frontemaxavg1100Hz.Channel2(flag));
f = figure
plot(smoothed(samplepersecond:end),'r')
legend('LED RED')
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'red_moving_avg.pdf','Resolution',600)