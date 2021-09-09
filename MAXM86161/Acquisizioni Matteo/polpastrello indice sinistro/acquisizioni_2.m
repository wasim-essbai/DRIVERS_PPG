%%
%@author Matteo Verzeroli
%%
close all
figure

subplot(3,1,1)
plot(maxmavg1100Hz.Channel1, 'g')
subplot(3,1,2)
plot(maxmavg1100Hz.Channel2, 'm')
subplot(3,1,3)
plot(maxmavg1100Hz.Channel3, 'r')

pos_iniziale = 200;

flag = maxmavg1100Hz.timestamp >= maxmavg1100Hz.timestamp(pos_iniziale) & maxmavg1100Hz.timestamp < maxmavg1100Hz.timestamp(pos_iniziale)+10000

milli_zero = maxmavg1100Hz.timestamp(pos_iniziale)

time = maxmavg1100Hz.timestamp-milli_zero
time = time ./1000

f = figure
plot(time(flag),maxmavg1100Hz.Channel1(flag), 'g')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED GREEN','Location','Northeast');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'green.pdf','Resolution',600)

f = figure
plot(time(flag),maxmavg1100Hz.Channel2(flag), 'm')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED IR','Location','Northeast');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'ired.pdf','Resolution',600)

f = figure
plot(time(flag),maxmavg1100Hz.Channel3(flag), 'r')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED RED','Location','Northeast');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'red.pdf','Resolution',600)

f = figure
samplepersecond = 20;

flag = maxmavg1100Hz.timestamp >= maxmavg1100Hz.timestamp(pos_iniziale) & maxmavg1100Hz.timestamp < maxmavg1100Hz.timestamp(pos_iniziale)+10000

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

milli_zero = maxmavg1100Hz.timestamp(pos_iniziale)
time = maxmavg1100Hz.timestamp-milli_zero
time = time ./1000

milli_zero_avg = maxmavg1100Hz.timestamp(pos_iniziale+20)
time_avg = maxmavg1100Hz.timestamp-milli_zero_avg
time_avg = time_avg ./1000

coeff = ones(1, samplepersecond)/samplepersecond;
smoothed = filter(coeff, 1, maxmavg1100Hz.Channel1(flag));
plot(time_avg(test), smoothed(samplepersecond+1:end),'g')
legend('LED GREEN')
xlabel('Tempo [s]');
ylabel('Valore ADC');
xlim([0 10])
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'green_moving_avg.pdf','Resolution',600)

f = figure
samplepersecond = 20;

flag = maxmavg1100Hz.timestamp >= maxmavg1100Hz.timestamp(pos_iniziale) & maxmavg1100Hz.timestamp < maxmavg1100Hz.timestamp(pos_iniziale)+10000

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

milli_zero = maxmavg1100Hz.timestamp(pos_iniziale)
time = maxmavg1100Hz.timestamp-milli_zero
time = time ./1000

milli_zero_avg = maxmavg1100Hz.timestamp(pos_iniziale+20)
time_avg = maxmavg1100Hz.timestamp-milli_zero_avg
time_avg = time_avg ./1000

coeff = ones(1, samplepersecond)/samplepersecond;
smoothed = filter(coeff, 1, maxmavg1100Hz.Channel2(flag));
plot(time_avg(test), smoothed(samplepersecond+1:end),'m')
legend('LED IR')
xlabel('Tempo [s]');
ylabel('Valore ADC');
xlim([0 10])
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'ir_moving_avg.pdf','Resolution',600)

f = figure
samplepersecond = 20;

flag = maxmavg1100Hz.timestamp >= maxmavg1100Hz.timestamp(pos_iniziale) & maxmavg1100Hz.timestamp < maxmavg1100Hz.timestamp(pos_iniziale)+10000

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

milli_zero = maxmavg1100Hz.timestamp(pos_iniziale)
time = maxmavg1100Hz.timestamp-milli_zero
time = time ./1000

milli_zero_avg = maxmavg1100Hz.timestamp(pos_iniziale+20)
time_avg = maxmavg1100Hz.timestamp-milli_zero_avg
time_avg = time_avg ./1000

coeff = ones(1, samplepersecond)/samplepersecond;
smoothed = filter(coeff, 1, maxmavg1100Hz.Channel3(flag));
plot(time_avg(test), smoothed(samplepersecond+1:end),'r')
legend('LED RED')
xlabel('Tempo [s]');
ylabel('Valore ADC');
xlim([0 10])
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'red_moving_avg.pdf','Resolution',600)