%%
%@author Matteo Verzeroli
%%
figure
subplot(4,1,1)
plot(luceambiente.Channel1, 'm')
subplot(4,1,2)
plot(luceambiente.Channel2, 'r')
subplot(4,1,3)
plot(luceambiente.Channel3, 'g')
subplot(4,1,4)
plot(luceambiente.Channel4, 'b')

pos_iniziale = 2000;
flag = luceambiente.timestamp >= luceambiente.timestamp(pos_iniziale) & luceambiente.timestamp < luceambiente.timestamp(pos_iniziale)+10000

milli_zero = luceambiente.timestamp(pos_iniziale)

time = luceambiente.timestamp-milli_zero
time = time ./1000

f = figure
plot(time(flag),luceambiente.Channel1(flag), 'm')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED IR');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'ired.pdf','Resolution',600)

f = figure
plot(time(flag),luceambiente.Channel2(flag), 'r')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED RED');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'red.pdf','Resolution',600)

f = figure
plot(time(flag),luceambiente.Channel3(flag), 'g')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED GREEN');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'green.pdf','Resolution',600)


f = figure
plot(time(flag),luceambiente.Channel4(flag), 'b')
xlabel('Tempo [s]');
ylabel('Valore ADC');
legend('LED BLU');
f.Position(3:4) = [1511, 189]
set(f,'PaperSize',[1511 189])
exportgraphics(f,'blu.pdf','Resolution',600)



