% Used for getting a big picture overview of correlations between
% sensor readings and Blood Glucose levels.

value = "R_940_Value";

[idx]=find((LogData.("Person")==1) &(LogData.("IndexFinger")==1));
TempSensorData=LogData.(value);
TempSensorData=TempSensorData(idx);

TempBgData=mean([LogData.("PreLog-mean-BG-mg-dl"),LogData.("PostLog-mean-BG-mg-dl")],2);
%TempBgData=LogData.("PreLog-mean-BG-mg-dl");
TempBgData=TempBgData(idx);
r = corrcoef(TempSensorData, TempBgData);
r(1,2)


[idx]=find((LogData.("Person")==1) &(LogData.("IndexFingerNail")==1));
TempSensorData=LogData.(value);
TempSensorData=TempSensorData(idx);

TempBgData=mean([LogData.("PreLog-mean-BG-mg-dl"),LogData.("PostLog-mean-BG-mg-dl")],2);
%TempBgData=LogData.("PreLog-mean-BG-mg-dl");
TempBgData=TempBgData(idx);
r = corrcoef(TempSensorData, TempBgData);
r(1,2)


[idx]=find((LogData.("Person")==1) &(LogData.("PinkyFinger")==1));
TempSensorData=LogData.(value);
TempSensorData=TempSensorData(idx);

TempBgData=mean([LogData.("PreLog-mean-BG-mg-dl"),LogData.("PostLog-mean-BG-mg-dl")],2);
%TempBgData=LogData.("PreLog-mean-BG-mg-dl");
TempBgData=TempBgData(idx);
r = corrcoef(TempSensorData, TempBgData);
r(1,2)


[idx]=find((LogData.("Person")==1) &(LogData.("PinkyFingerNail")==1));
TempSensorData=LogData.(value);
TempSensorData=TempSensorData(idx);

TempBgData=mean([LogData.("PreLog-mean-BG-mg-dl"),LogData.("PostLog-mean-BG-mg-dl")],2);
%TempBgData=LogData.("PreLog-mean-BG-mg-dl");
TempBgData=TempBgData(idx);
r = corrcoef(TempSensorData, TempBgData);
r(1,2)


