clc;
close all;
clear all;
[x,fs]=audioread('noisy.wav');%captura de la señal de audio.
fc1=954;%frecuencia central filtro 1.
fc2=15317;%frecuencia central filtro 2.
fp1l=800;%frecuencia 1 banda de paso filtro 1.
fp1h=11517;%frecuencia 1 banda de paso filtro 2.
fp2l=fc1^2/fp1l;%frecuencia 2 banda de paso filtro 1.
fp2h=fc2^2/fp1h;%frecuencia 2 banda de paso filtro 2.

fs1l=894;%frecuencia 1 banda de rechazo filtro 1.
fs1h=14300;%fecuencia 1 banda de rechazo filtro 2.
fs2l=fc1^2/fs1l;%frecuencia 2 banda de rechazo filtro 1.
fs2h=fc2^2/fs1h;%frecuencia 2 banda de rechazo filtro 2.
%Atenuación en la banda de paso y rechazo.
A_p=3;
A_s=30;
%Diseño digital directo del filtro 1.
[N, Omega_c] = buttord([fp1l fp2l]*2/fs,[fs1l fs2l]*2/fs, A_p, A_s);
[b_d1, a_d1]=butter(N,Omega_c,'stop');
%Diseño digital directo del filtro 2.
[N, Omega_c] = buttord([fp1h fp2h]*2/fs,[fs1h fs2h]*2/fs, A_p, A_s);
[b_d2, a_d2]=butter(N,Omega_c,'stop');
%respuestas en frecuencia de los filtros.
% [H, Omega]=freqz(b_d1,a_d1);
% figure;
% plot(Omega/(2*pi)*fs,20*log10(abs(H)));
% xlabel('f [Hz]');
% ylabel('|H(\Omega)|_{dB}');
% grid on;
% [H, Omega]=freqz(b_d2,a_d2);
% figure;
% plot(Omega/(2*pi)*fs,20*log10(abs(H)));
% xlabel('f [Hz]');
% ylabel('|H(\Omega)|_{dB}');
% grid on;
y=irr3(b_d1(:),a_d1(:),x(:));
y=irr3(b_d2(:),a_d2(:),y(:));
%y=myFilter1(b_d2(:),a_d2(:),x(:));
%y=filter(b_d1(:),a_d1(:),x(:));
%y=filter(b_d2(:),a_d2(:),y(:));
 [Y,Omega]=freqz(y,1,65536);%respuesta en frecuencia de la señal de auidio.
 figure;
 plot(Omega/(2*pi)*fs,abs(Y));
soundsc(y(800:end),fs)%reproducción de la señal de audio.