% WIP for post processing log data to see correlations between the 
% sensor readings and bloog glucose level.  
% No feature extraction used here, It is roughly based on/referencing
% https://www.ijltet.org/journal/151486536919.%2065.pdf and performing in 
% post processing what was done on hardware.  

NewLogData = LogData;
for PinState=0:3
    for LogNumber=1:72
        [idx]=find((LogData.("LogNumber")==LogNumber) & (LogData.("Pin_State")==PinState));
        TempSensorData=LogData.("T_940_Value")(idx);
        
        %TempSensorData=detrend(TempSensorData,5);
        TempSensorData=highpass(TempSensorData,2.34,300);
        TempSensorData=lowpass(TempSensorData,149,300);
        %TempSensorData=smoothdata(TempSensorData,"movmean");
        TempSensorData=mean(TempSensorData);
        
        NewLogData.("T_940_Value")(idx) = TempSensorData;
    end
end

coefficients = [];
for PinState = 0:3
    [idx]=find((NewLogData.("Person")==1) &(NewLogData.("IndexFinger")==1) & (NewLogData.("Pin_State")==PinState));
    TempSensorData=NewLogData.("T_940_Value")(idx);
    %TempSensorData=filloutliers(TempSensorData,"clip");

    TempBgData=mean([NewLogData.("PreLog-mean-BG-mg-dl"),NewLogData.("PostLog-mean-BG-mg-dl")],2);
    TempBgData=TempBgData(idx);
    r = corrcoef(TempSensorData, TempBgData);
    coefficients = [coefficients, r(1,2)];
end
coefficients

[idx]=find((NewLogData.("Person")==1) &(NewLogData.("IndexFinger")==1) & (NewLogData.("Pin_State")==2));
TempSensorData=NewLogData.("T_940_Value")(idx);
TempSensorData=filloutliers(TempSensorData,"clip");

TempBgData=mean([NewLogData.("PreLog-mean-BG-mg-dl"),NewLogData.("PostLog-mean-BG-mg-dl")],2);
TempBgData=TempBgData(idx);
%r = corrcoef(TempSensorData, TempBgData)

% TimeData=NewLogData.("Micros")(idx);
% scatter(TempSensorData,TempBgData)

p = polyfit(TempSensorData,TempBgData,2)
x1 = linspace(-1.2,.03);
y1 = polyval(p,x1);
figure
plot(TempSensorData,TempBgData,'o')
hold on
plot(x1,y1)
hold off