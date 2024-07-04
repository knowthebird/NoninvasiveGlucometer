% WIP for post processing log data to see correlations between the 
% sensor readings and bloog glucose level.  

% No PPG feature extraction used here. 
% It can be used to roughly recreate in post processing what was done on 
% hardware in https://www.ijltet.org/journal/151486536919.%2065.pdf or
% to just try different filtering effects

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Process Raw Sensor Data
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

LogDataCopy = LogData;
for PinState=0:3
    for LogNumber=1:72
        [idx]=find((LogData.("LogNumber")==LogNumber) & (LogData.("Pin_State")==PinState));
        RawSensorReadings=LogData.("T_940_Value")(idx);
        
        ProcessedSensorReadings=detrend(RawSensorReadings,5);
        %ProcessedSensorReadings=highpass(ProcessedSensorReadings,2.34,300);
        ProcessedSensorReadings=lowpass(ProcessedSensorReadings,50,300);
        ProcessedSensorReadings=smoothdata(ProcessedSensorReadings,"movmean");
        ProcessedSensorReadings=mean(ProcessedSensorReadings);
        
        LogDataCopy.("T_940_Value")(idx) = ProcessedSensorReadings;
    end
end

[idx]=find((LogDataCopy.("Person")==1) &(LogDataCopy.("IndexFinger")==1) & (LogDataCopy.("Pin_State")==2));
ProcessedSensorReadings=LogDataCopy.("T_940_Value")(idx);
%ProcessedSensorReadings=filloutliers(ProcessedSensorReadings,"clip");

ReferenceBgReadings=mean([LogDataCopy.("PreLog-mean-BG-mg-dl"),LogDataCopy.("PostLog-mean-BG-mg-dl")],2);
ReferenceBgReadings=ReferenceBgReadings(idx);

% Timestamps=LogDataCopy.("Micros")(idx);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Fit Polynomial to Processed Sensor Data
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p = polyfit(ProcessedSensorReadings,ReferenceBgReadings,2);
ReferenceBgData = unique(ReferenceBgReadings);
PredictedBgData = polyval(p,unique(ProcessedSensorReadings));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Evaluate and Display Results
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure
plot(ProcessedSensorReadings,ReferenceBgReadings,'o')
hold on
x1 = linspace(min(ProcessedSensorReadings),max(ProcessedSensorReadings));
y1 = polyval(p,x1);
plot(x1,y1)
hold off

% scatter(ProcessedSensorReadings,ReferenceBgReadings)
r = corrcoef(ProcessedSensorReadings, ReferenceBgReadings);
r = r(1,2)

% scatter(ReferenceBgData,PredictedBgData)
r = corrcoef(ReferenceBgData, PredictedBgData);
r = r(1,2)

MARD = 100*mean((PredictedBgData-ReferenceBgData)./ReferenceBgData)
RMSE = mean((ReferenceBgData-PredictedBgData).^2)^.5