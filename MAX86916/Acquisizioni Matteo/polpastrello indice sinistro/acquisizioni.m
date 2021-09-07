%%
%@author Matteo Verzeroli
%%
figure
subplot(4,1,1)
plot(maxavg1100Hz.Channel1, 'm')
subplot(4,1,2)
plot(maxavg1100Hz.Channel2, 'r')
subplot(4,1,3)
plot(maxavg1100Hz.Channel3, 'g')
subplot(4,1,4)
plot(maxavg1100Hz.Channel4, 'b')

pos_iniziale = 1100;
flag = maxavg1100Hz.timestamp >= maxavg1100Hz.timestamp(pos_iniziale) & maxavg1100Hz.timestamp < maxavg1100Hz.timestamp(pos_iniziale)+10000

milli_zero = maxavg1100Hz.timestamp(pos_iniziale)

time = maxavg1100Hz.timestamp-milli_zero
time = time ./1000

figure

subplot(4,1,1)
plot(time(flag),maxavg1100Hz.Channel1(flag), 'm')
title('polpastrello avg_1');
xlabel('Tempo [s]');
ylabel('Valore ADC');
subplot(4,1,2)
plot(time(flag),maxavg1100Hz.Channel2(flag), 'r')
xlabel('Tempo [s]');
ylabel('Valore ADC');
subplot(4,1,3)
plot(time(flag),maxavg1100Hz.Channel3(flag), 'g')
xlabel('Tempo [s]');
ylabel('Valore ADC');
subplot(4,1,4)
plot(time(flag),maxavg1100Hz.Channel4(flag), 'b')
xlabel('Tempo [s]');
ylabel('Valore ADC');

samplepersecond = 10;
coeff = ones(1, samplepersecond)/samplepersecond;

smoothed = filter(coeff, 1, maxavg1100Hz.Channel1(flag));
figure
plot(smoothed(10:end))

%%

figure
subplot(4,1,1)
plot(maxavg2100Hz.Channel1, 'm')
subplot(4,1,2)
plot(maxavg2100Hz.Channel2, 'r')
subplot(4,1,3)
plot(maxavg2100Hz.Channel3, 'g')
subplot(4,1,4)
plot(maxavg2100Hz.Channel4, 'b')

pos_iniziale = 600;
flag = maxavg2100Hz.timestamp >= maxavg2100Hz.timestamp(pos_iniziale) & maxavg2100Hz.timestamp < maxavg2100Hz.timestamp(pos_iniziale)+10000

milli_zero = maxavg2100Hz.timestamp(pos_iniziale)

time = maxavg2100Hz.timestamp-milli_zero
time = time ./1000

figure

subplot(4,1,1)
plot(time(flag),maxavg2100Hz.Channel1(flag), 'm')
title('polpastrello avg_2');
xlabel('Tempo [s]');
ylabel('Valore ADC');
subplot(4,1,2)
plot(time(flag),maxavg2100Hz.Channel2(flag), 'r')
xlabel('Tempo [s]');
ylabel('Valore ADC');
subplot(4,1,3)
plot(time(flag),maxavg2100Hz.Channel3(flag), 'g')
xlabel('Tempo [s]');
ylabel('Valore ADC');
subplot(4,1,4)
plot(time(flag),maxavg2100Hz.Channel4(flag), 'b')
xlabel('Tempo [s]');
ylabel('Valore ADC');

%%
figure
subplot(4,1,1)
plot(maxavg4100Hz.Channel1, 'm')
subplot(4,1,2)
plot(maxavg4100Hz.Channel2, 'r')
subplot(4,1,3)
plot(maxavg4100Hz.Channel3, 'g')
subplot(4,1,4)
plot(maxavg4100Hz.Channel4, 'b')

pos_iniziale = 800;
flag = maxavg4100Hz.timestamp >= maxavg4100Hz.timestamp(pos_iniziale) & maxavg4100Hz.timestamp < maxavg4100Hz.timestamp(pos_iniziale)+10000

milli_zero = maxavg4100Hz.timestamp(pos_iniziale)

time = maxavg4100Hz.timestamp-milli_zero
time = time ./1000

figure

subplot(4,1,1)
plot(time(flag),maxavg4100Hz.Channel1(flag), 'm')
title('polpastrello avg_4');
xlabel('Tempo [s]');
ylabel('Valore ADC');
subplot(4,1,2)
plot(time(flag),maxavg4100Hz.Channel2(flag), 'r')
xlabel('Tempo [s]');
ylabel('Valore ADC');
subplot(4,1,3)
plot(time(flag),maxavg4100Hz.Channel3(flag), 'g')
xlabel('Tempo [s]');
ylabel('Valore ADC');
subplot(4,1,4)
plot(time(flag),maxavg4100Hz.Channel4(flag), 'b')
xlabel('Tempo [s]');
ylabel('Valore ADC');





