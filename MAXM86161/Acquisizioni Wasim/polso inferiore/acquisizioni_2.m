%%
%@author Wasim Essbai
%%
close all
figure

subplot(3,1,1)
plot(polsoinferioresxmaxmavg1100Hz.Channel1, 'g')
subplot(3,1,2)
plot(polsoinferioresxmaxmavg1100Hz.Channel2, 'm')
subplot(3,1,3)
plot(polsoinferioresxmaxmavg1100Hz.Channel3, 'r')

pos_iniziale = 1000;

flag = polsoinferioresxmaxmavg1100Hz.timestamp >= polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale) & polsoinferioresxmaxmavg1100Hz.timestamp < polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale)+10000

milli_zero = polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale)

time = polsoinferioresxmaxmavg1100Hz.timestamp-milli_zero
time = time ./1000

f = figure
plot(time(flag),polsoinferioresxmaxmavg1100Hz.Channel1(flag), 'g')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED GREEN','Location','Southeast');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'green.pdf','Resolution',600)

f = figure
plot(time(flag),polsoinferioresxmaxmavg1100Hz.Channel2(flag), 'm')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED IR','Location','Southeast');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'ired.pdf','Resolution',600)

f = figure
plot(time(flag),polsoinferioresxmaxmavg1100Hz.Channel3(flag), 'r')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED RED','Location','Southeast');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'red.pdf','Resolution',600)

%GREEN
f = figure
samplepersecond = 15;

flag = polsoinferioresxmaxmavg1100Hz.timestamp >= polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale) & polsoinferioresxmaxmavg1100Hz.timestamp < polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale)+10000

for i=1:length(flag)
    if int8(flag(i))-int8(flag(i+1)) == 1
        i
        break
    end
end
flag((i+1):(i+samplepersecond))= 1
test = flag

for i=1:length(flag)
    if int8(flag(i))-int8(flag(i+1)) == -1
        i
        break
    end
end
test(i+1:i+samplepersecond) = 0

milli_zero = polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale)
time = polsoinferioresxmaxmavg1100Hz.timestamp-milli_zero
time = time ./1000

milli_zero_avg = polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale+samplepersecond)
time_avg = polsoinferioresxmaxmavg1100Hz.timestamp-milli_zero_avg
time_avg = time_avg ./1000

coeff = ones(1, samplepersecond)/samplepersecond;
smoothed = filter(coeff, 1, polsoinferioresxmaxmavg1100Hz.Channel1(flag));
plot(time_avg(test), smoothed(samplepersecond+1:end),'g')
legend('LED GREEN','Location','Southeast')
xlabel('Tempo [s]');
ylabel('Valore ADC');
xlim([0 10])
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'polso_inferiore_green_moving_avg.pdf','Resolution',600)

%IR
f = figure
samplepersecond = 30;

flag = polsoinferioresxmaxmavg1100Hz.timestamp >= polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale) & polsoinferioresxmaxmavg1100Hz.timestamp < polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale)+10000

for i=1:length(flag)
    if int8(flag(i))-int8(flag(i+1)) == 1
        i
        break
    end
end
flag((i+1):(i+samplepersecond))= 1
test = flag

for i=1:length(flag)
    if int8(flag(i))-int8(flag(i+1)) == -1
        i
        break
    end
end
test(i+1:i+samplepersecond) = 0

milli_zero = polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale)
time = polsoinferioresxmaxmavg1100Hz.timestamp-milli_zero
time = time ./1000

milli_zero_avg = polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale+samplepersecond)
time_avg = polsoinferioresxmaxmavg1100Hz.timestamp-milli_zero_avg
time_avg = time_avg ./1000

coeff = ones(1, samplepersecond)/samplepersecond;
smoothed = filter(coeff, 1, polsoinferioresxmaxmavg1100Hz.Channel2(flag));
plot(time_avg(test), smoothed(samplepersecond+1:end),'m')
legend('LED IR','Location','Southeast')
xlabel('Tempo [s]');
ylabel('Valore ADC');
xlim([0 10])
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'polso_inferiore_ir_moving_avg.pdf','Resolution',600)

%RED
f = figure
samplepersecond = 30;

flag = polsoinferioresxmaxmavg1100Hz.timestamp >= polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale) & polsoinferioresxmaxmavg1100Hz.timestamp < polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale)+10000

for i=1:length(flag)
    if int8(flag(i))-int8(flag(i+1)) == 1
        i
        break
    end
end
flag((i+1):(i+samplepersecond))= 1
test = flag

for i=1:length(flag)
    if int8(flag(i))-int8(flag(i+1)) == -1
        i
        break
    end
end
test(i+1:i+samplepersecond) = 0

milli_zero = polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale)
time = polsoinferioresxmaxmavg1100Hz.timestamp-milli_zero
time = time ./1000

milli_zero_avg = polsoinferioresxmaxmavg1100Hz.timestamp(pos_iniziale+samplepersecond)
time_avg = polsoinferioresxmaxmavg1100Hz.timestamp-milli_zero_avg
time_avg = time_avg ./1000

coeff = ones(1, samplepersecond)/samplepersecond;
smoothed = filter(coeff, 1, polsoinferioresxmaxmavg1100Hz.Channel3(flag));
plot(time_avg(test), smoothed(samplepersecond+1:end),'r')
legend('LED RED','Location','Southeast')
xlabel('Tempo [s]');
ylabel('Valore ADC');
xlim([0 10])
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'polso_inferiore_red_moving_avg.pdf','Resolution',600)