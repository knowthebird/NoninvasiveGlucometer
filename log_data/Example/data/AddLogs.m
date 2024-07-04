
LogInfo.Number = 72;
LogInfo.Person = 1;
LogInfo.Finger = 4; % 1 = Index, 2 = IndexNail, 3 = Pinky, 4 = PinkyNail
LogInfo.PreLog_mean_Sp02 = mean([97]);
LogInfo.PreLog_mean_BG_mg_dl = mean([126,127]);
LogInfo.PostLog_mean_Sp02 = mean([96,97]);
LogInfo.PostLog_mean_BG_mg_dl = mean([122,125])

%LogData = AddLogInfo(LOG1, LogInfo);
NewLog = AddLogInfo(LOG72, LogInfo);
LogData = AddLog(LogData, NewLog);
writetable(LogData,'ExampleSensorLogData.csv');
save('ExampleSensorLogData.mat', 'LogData');

function Log = AddLogInfo(Log, LogInfo)
    Log.("LogNumber") = ones(height(Log), 1) * LogInfo.Number;
    Log.("Person") = ones(height(Log), 1) * LogInfo.Person;
    Log.("IndexFinger") = zeros(height(Log), 1);
    Log.("IndexFingerNail") = zeros(height(Log), 1);
    Log.("PinkyFinger") = zeros(height(Log), 1);
    Log.("PinkyFingerNail") = zeros(height(Log), 1);

    if LogInfo.Finger == 1
        Log.("IndexFinger") = ones(height(Log), 1);
    elseif LogInfo.Finger == 2
        Log.("IndexFingerNail") = ones(height(Log), 1);
    elseif LogInfo.Finger == 3
        Log.("PinkyFinger") = ones(height(Log), 1);
    elseif LogInfo.Finger == 4
        Log.("PinkyFingerNail") = ones(height(Log), 1);
    end
    
    Log.("PreLog-mean-Sp02%") = ones(height(Log), 1) * LogInfo.PreLog_mean_Sp02;
    Log.("PreLog-mean-BG-mg-dl") = ones(height(Log), 1) * LogInfo.PreLog_mean_BG_mg_dl;
    Log.("PostLog-mean-Sp02") = ones(height(Log), 1) * LogInfo.PostLog_mean_Sp02;
    Log.("PostLog-mean-BG-mg-dl") = ones(height(Log), 1) * LogInfo.PostLog_mean_BG_mg_dl;
end

function OldLogs = AddLog(OldLogs, NewLog, MetaData)
    OldLogs = [OldLogs; NewLog];
end