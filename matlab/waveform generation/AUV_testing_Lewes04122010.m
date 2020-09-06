clear all, close all, clc
%Sample program to generate cw signals for MIMO testing.
%
%April 6, 2010.
%-----------
%scheme:
%
%do 10 times
%{
%Tx1 : probes.wav  //1.daq
%[stop 35sec]
%Tx2: probes.wav   //2.daq
%[stop 35sec]
%Tx3: probes.wav   //3.daq
%[stop 35sec]

%Tx1 :  mseq1.wav  + Tx2:mseq2.wav  //4.daq
%[stop 50sec]
%Tx1 : mseq1.wav + Tx3: mseq2.wav   //5.daq
%[stop 50sec]
%}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
wavedir = './';
[probes fs] = wavread([wavedir,'probes.wav']);
[mseq1 fs] = wavread([wavedir,'mseq1.wav']);
[mseq2 fs]= wavread([wavedir,'mseq2.wav']);
sampling_rate=fs;%in Hertz

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if length(mseq1) ~= length(mseq2)
    warning('length(mseq1)>length(mseq2)!')
    warning('mseq1 will be truncated!')
    mseq1=mseq1(1:length(mseq2));
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     t_vec=[0: round(2*sampling_rate)].'/sampling_rate;
%     single_cw=sin(2*pi*1000.*t_vec);
% 
%     wf_output = zeros(4, length(single_cw));
%     wf_output(1,:) = single_cw';
%     wf=reshape(wf_output,1,numel(wf_output));
%     f1 = fopen('0.daq'],'w');
%     fwrite(f1,wf,'uint16');
%     fclose(f1);



for ix = 1:3
    wf_output = zeros(4, length(probes));
    wf_output(ix,:) = probes';
    
    wf_output = floor((wf_output*(2^16-1)/2+(2^16-1)/2)/10);

    wf=reshape(wf_output,1,numel(wf_output));
    f1 = fopen([num2str(ix),'.daq'],'w');
    fwrite(f1,wf,'uint16');
    fclose(f1);
end

wf_output = zeros(4,length(mseq1));
wf_output(1,:) = mseq1';
wf_output(2,:) = mseq2';
    wf_output = floor((wf_output*(2^16-1)/2+(2^16-1)/2)/10);

wf=reshape(wf_output,1,numel(wf_output));
f1 = fopen('4.daq','w');
fwrite(f1,wf,'uint16');
fclose(f1);

wf_output = zeros(4,length(mseq1));
wf_output(1,:) = mseq1';
wf_output(3,:) = mseq2';
    wf_output = floor((wf_output*(2^16-1)/2+(2^16-1)/2)/10);

wf=reshape(wf_output,1,numel(wf_output));
f1 = fopen('5.daq','w');
fwrite(f1,wf,'uint16');
fclose(f1);

wf_output = zeros(4,length(mseq1));
wf_output(1,:) = mseq1';
wf_output(2,:) = mseq1';
wf_output(3,:) = mseq1';
wf_output = floor((wf_output*(2^16-1)/2+(2^16-1)/2)/10);

wf=reshape(wf_output,1,numel(wf_output));
f1 = fopen('6.daq','w');
fwrite(f1,wf,'uint16');
fclose(f1);

