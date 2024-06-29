% for i = 0:3
%     [idx]=find((LogData.("Person")==1) &(LogData.("IndexFinger")==1) & (LogData.("Pin_State")==i));
%     TempSensorData=LogData.("T_Vis_Value");
%     TempSensorData=TempSensorData(idx);
% 
%     %TempBgData=mean([LogData.("PreLog-mean-BG-mg-dl"),LogData.("PostLog-mean-BG-mg-dl")],2);
%     TempBgData=LogData.("PostLog-mean-BG-mg-dl");
%     TempBgData=TempBgData(idx);
%     r = corrcoef(TempSensorData, TempBgData);
%     r(1,2)
% end

% [idx]=find((LogData.("Person")==1) &(LogData.("IndexFinger")==1) & (LogData.("Pin_State")==3));
% TempSensorData=LogData.("T_940_Value");
% TempSensorData=TempSensorData(idx);
% TempSensorData=filloutliers(TempSensorData,"clip");
% 
% %TempSensorData=detrend(TempSensorData,12);
% %TempSensorData=lowpass(TempSensorData,10,300);
% %TempSensorData=highpass(TempSensorData,.00001,300);
% 
% TempBgData=mean([LogData.("PreLog-mean-BG-mg-dl"),LogData.("PostLog-mean-BG-mg-dl")],2);
% TempBgData=TempBgData(idx);
% r = corrcoef(TempSensorData, TempBgData);
% r(1,2)
% 
% scatter(TempBgData,TempSensorData)

NewLogData = LogData;
for p=0:3
    for n=1:72
        [idx]=find((LogData.("LogNumber")==n) & (LogData.("Pin_State")==p));
        TempSensorData=LogData.("T_940_Value")(idx);
        
        TempSensorData=detrend(TempSensorData,5);
        TempSensorData=lowpass(TempSensorData,50,300);
        TempSensorData=smoothdata(TempSensorData,"movmean");
        TempSensorData=median(TempSensorData);
        
        NewLogData.("T_940_Value")(idx) = TempSensorData;
    end
end

for i = 0:3
    [idx]=find((NewLogData.("Person")==1) &(NewLogData.("IndexFinger")==1) & (NewLogData.("Pin_State")==i));
    TempSensorData=NewLogData.("T_940_Value")(idx);
    %TempSensorData=filloutliers(TempSensorData,"clip");

    TempBgData=mean([NewLogData.("PreLog-mean-BG-mg-dl"),NewLogData.("PostLog-mean-BG-mg-dl")],2);
    TempBgData=TempBgData(idx);
    r = corrcoef(TempSensorData, TempBgData);
    r(1,2)
end

% 
% [idx]=find((NewLogData.("Person")==1) &(NewLogData.("IndexFinger")==1) & (NewLogData.("Pin_State")==2));
% TempSensorData=NewLogData.("T_940_Value")(idx);
% TempSensorData=filloutliers(TempSensorData,"clip");
% 
% TempBgData=mean([NewLogData.("PreLog-mean-BG-mg-dl"),NewLogData.("PostLog-mean-BG-mg-dl")],2);
% TempBgData=TempBgData(idx);
% r = corrcoef(TempSensorData, TempBgData)
% 
% % TimeData=NewLogData.("Micros")(idx);
% scatter(TempSensorData,TempBgData)
% 
% p = polyfit(TempSensorData,TempBgData,2)
% x1 = linspace(-.01,.005);
% y1 = polyval(p,x1);
% figure
% plot(TempSensorData,TempBgData,'o')
% hold on
% plot(x1,y1)
% hold off