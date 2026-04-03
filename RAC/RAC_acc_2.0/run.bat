@echo off
SimAcc2.exe 100000000 1000000 10 12333 3 3 1000 "../test_data.bin"
REM         <Total Step>
REM                   <Slice Step>
REM                            <OutBuffer Count>
REM                                <State Sample Step>
REM                                     <State Top N>
REM                                       <Parallel Slice Delay>
REM                                         <Paralled Count>
REM                                            <Input File Path>



REM         printf("Usage:\n");
REM         printf("  <Total Step>\n");
REM         printf("  <Slice Step>\n");
REM         printf("  <OutBuffer Count>\n");
REM         printf("  <State Sample Step>\n");
REM         printf("  <State Top N>\n");
REM         printf("  <Parallel Slice Delay>\n");
REM         printf("  <Paralled Count>\n");
REM         printf("  <Input File Path>\n");