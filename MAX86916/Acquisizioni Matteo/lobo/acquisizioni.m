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

pos_iniziale = 200;
flag = maxavg1100Hz.timestamp >= maxavg1100Hz.timestamp(pos_iniziale) & maxavg1100Hz.timestamp < maxavg1100Hz.timestamp(pos_iniziale)+10000

milli_zero = maxavg1100Hz.timestamp(pos_iniziale)

time = maxavg1100Hz.timestamp-milli_zero
time = time ./1000

figure

subplot(4,1,1)
plot(time(flag),maxavg1100Hz.Channel1(flag), 'm')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED IR');
subplot(4,1,2)
plot(time(flag),maxavg1100Hz.Channel2(flag), 'r')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED RED');
subplot(4,1,3)
plot(time(flag),maxavg1100Hz.Channel3(flag), 'g')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED GREEN');
subplot(4,1,4)
plot(time(flag),maxavg1100Hz.Channel4(flag), 'b')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED BLU');

samplepersecond = 10;
coeff = ones(1, samplepersecond)/samplepersecond;

smoothed = filter(coeff, 1, maxavg1100Hz.Channel1(flag));
figure
plot(smoothed(10:end))





