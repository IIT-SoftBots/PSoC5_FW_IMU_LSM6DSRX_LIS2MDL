%%real time data plot from a serial port 
% This matlab script is for ploting a graph by accessing serial port data in
% real time. Change the com values and all variable values accroding to
% your requirements. Dont forget to add terminator in to your serial device program.
% This script can be modified to be used on any platform by changing the
% serialPort variable. 
% Author: Moidu thavot.

%%Clear all variables

clear all;
%%Variables (Edit yourself)

TimeInterval=0;%time interval between each input.
loop=12000;%count values
%%Set up the serial port object

s = serialport("COM12",57600);


time =now;
voltage = 0;
y = 0;
z=0;

%% Set up the figure 
figureHandle = figure('NumberTitle','off',...
    'Name','Voltage Characteristics',...
    'Color',[0 0 0],'Visible','off');

% Set axes
axesHandle = axes('Parent',figureHandle,...
    'YGrid','on',...
    'YColor',[0.9725 0.9725 0.9725],...
    'XGrid','on',...
    'XColor',[0.9725 0.9725 0.9725],...
    'Color',[0 0 0]);

hold on;

plotHandle = plot(axesHandle,time,voltage,'Marker','.','LineWidth',1,'Color',[0 1 0]);
plotHandle1 = plot(axesHandle,time,y,'Marker','.','LineWidth',1,'Color',[0 1 0]);
plotHandle2 = plot(axesHandle,time,z,'Marker','.','LineWidth',1,'Color',[0 1 0]);

xlim(axesHandle,[min(time) max(time+0.001)]);

% Create xlabel
xlabel('Time','FontWeight','bold','FontSize',14,'Color',[1 1 0]);

% Create ylabel
ylabel('Voltage in V','FontWeight','bold','FontSize',14,'Color',[1 1 0]);

% Create title
title('Real Time Data','FontSize',15,'Color',[1 1 0]);




%% Initializing variables

accx(1)=0;
accy(1)=0;
accz(1)=0;
gx(1)=0;
gy(1)=0;
gz(1)=0;
mx(1)=0;
my(1)=0;
mz(1)=0;
time(1)=0;
count = 2;
k=1;
while ~isequal(count,loop)
    
    %%Serial data accessing 
    
     accx(count) = read(s,1,"int16");
    % voltage(count)=(voltage(count)/32767)*2;

  accy(count) = read(s,1,"int16");
  % y(count)=(y(count)/32767)*2;

  accz(count)=read(s,1,"int16");
%z(count)=(z(count)/32767)*2;
% 
      gx(count) = read(s,1,"int16");
%     % voltage(count)=(voltage(count)/32767)*2;
% 
   gy(count) = read(s,1,"int16");
%   % y(count)=(y(count)/32767)*2;
% 
   gz(count)=read(s,1,"int16");
% %z(count)=(z(count)/32767)*2;ù
      mx(count) = read(s,1,"int16");
%     % voltage(count)=(voltage(count)/32767)*2;
% 
  my(count) = read(s,1,"int16");
%   % y(count)=(y(count)/32767)*2;
% 
mz(count)=read(s,1,"int16");
% %z(count)=(z(count)/32767)*2;
      time(count) = count;
   plotHandle1.Color='red';
   plotHandle2.Color='blue';
   
      
   %%PLOT AXEL
   set(plotHandle,'YData',accx,'XData',time);
   set(plotHandle1,'YData',accy,'XData',time);
   set(plotHandle2,'YData',accz,'XData',time);
%    
%    %%PLOT GYRO
%    set(plotHandle,'YData',gx,'XData',time);
%    set(plotHandle1,'YData',gy,'XData',time);
%    set(plotHandle2,'YData',gz,'XData',time);
%    
   %%PLOT MAG
%    set(plotHandle,'YData',mx,'XData',time);
%    set(plotHandle1,'YData',my,'XData',time);
%    set(plotHandle2,'YData',mz,'XData',time);
%    
   
   set(figureHandle,'Visible','on');
   datetick('x','mm/DD HH:MM');
    
   pause(TimeInterval);
    count = count +1;
end



%% Clean up the serial port

clear s;