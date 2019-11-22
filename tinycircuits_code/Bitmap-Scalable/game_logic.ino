void AddEXP(short int change){
    short int EXP = (short int)GetGameVariables(0);
    unsigned char LEVEL = GetGameVariables(1);

    EXP = max(0, EXP + change);
    LEVEL = (unsigned char)sqrt(EXP*2);

    WriteGameVariables(EXP, 0);
    WriteGameVariables(LEVEL, 1);
}

void CompletedTask(){
  AddEXP(2);
  unsigned char TasksCompleted = GetGameVariables(2);
  TasksCompleted ++;
  WriteGameVariables(TasksCompleted, 2);
}

void FailedTask(){
  AddEXP(-1);
  unsigned char TasksFailed = GetGameVariables(3);
  TasksFailed ++;
  WriteGameVariables(TasksFailed, 3);
}
