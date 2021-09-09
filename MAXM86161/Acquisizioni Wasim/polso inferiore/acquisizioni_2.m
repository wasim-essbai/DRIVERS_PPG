%%
%@author Wasim Essbai
%%
close all

figure
subplot(4,1,1)
plot(polsoinferioresxmaxmavg1100Hz.Channel1, 'g')
subplot(4,1,2)
plot(polsoinferioresxmaxmavg1100Hz.Channel3, 'r')
subplot(4,1,3)
plot(polsoinferioresxmaxmavg1100Hz.Channel2, 'm')

pos_iniziale = 1000;
flag = polsoinferioresxmaxmavg1100Hz.timestamp >= polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale) & polsoinferioresxmaxmavg1100Hz.timestamp < polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale)+10000

milli_zero = polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale)

time = polsoinferioresxmaxmavg1100Hz.timestamp-milli_zero
time = time ./1000

f = figure
plot(time(flag),polsoinferioresxmaxmavg1100Hz.Channel2(flag), 'm')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED IR');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'ired.pdf','Resolution',600)

f = figure
plot(time(flag),polsoinferioresxmaxmavg1100Hz.Channel3(flag), 'r')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED RED');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'red.pdf','Resolution',600)

f = figure
plot(time(flag),polsoinferioresxmaxmavg1100Hz.Channel1(flag), 'g')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED GREEN');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'green.pdf','Resolution',600)

samplepersecond = 30;
coeff = ones(1, samplepersecond)/samplepersecond;

smoothed = filter(coeff, 1, polsoinferioresxmaxmavg1100Hz.Channel3(flag));
f = figure
plot(smoothed(samplepersecond:end),'r')
legend('LED RED')
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'red_moving_avg.pdf','Resolution',600)

samplepersecond = 30;
coeff = ones(1, samplepersecond)/samplepersecond;

smoothed = filter(coeff, 1, polsoinferioresxmaxmavg1100Hz.Channel2(flag));
f = figure
plot(smoothed(samplepersecond:end),'m')
legend('LED IR')
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'ir_moving_avg.pdf','Resolution',600)

samplepersecond = 15;
coeff = ones(1, samplepersecond)/samplepersecond;

smoothed = filter(coeff, 1, polsoinferioresxmaxmavg1100Hz.Channel1(flag));
f = figure
plot(smoothed(samplepersecond:end),'g')
legend('LED GREEN')
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'green_moving_avg.pdf','Resolution',600)