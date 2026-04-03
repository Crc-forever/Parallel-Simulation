    function targMap = targDataMap(),

    ;%***********************
    ;% Create Parameter Map *
    ;%***********************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 9;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc paramMap
        ;%
        paramMap.nSections           = nTotSects;
        paramMap.sectIdxOffset       = sectIdxOffset;
            paramMap.sections(nTotSects) = dumSection; %prealloc
        paramMap.nTotData            = -1;

        ;%
        ;% Auto data (rtP)
        ;%
            section.nData     = 30;
            section.data(30)  = dumData; %prealloc

                    ;% rtP.ForIterator_IterationLimit
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.ForIterator_IterationLimit_hg54moyj5v
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% rtP.Constant1_Value
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% rtP.Constant2_Value
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% rtP.res_Y0
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% rtP.value_out_Y0
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 5;

                    ;% rtP.Constant_Value
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 6;

                    ;% rtP.Constant1_Value_mvhnwcihcx
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 7;

                    ;% rtP.DataStoreMemory_InitialValue
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 8;

                    ;% rtP.DataStoreMemory1_InitialValue
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 9;

                    ;% rtP.ForIterator_IterationLimit_pmnerygy22
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 10;

                    ;% rtP.Constant1_Value_cbj5azvbu2
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 11;

                    ;% rtP.Constant2_Value_az5chewn2m
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 12;

                    ;% rtP.DataStoreMemory_InitialValue_lpsnntvi5e
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 13;

                    ;% rtP.DataStoreMemory1_InitialValue_brapdgvyi0
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 14;

                    ;% rtP.ForIterator_IterationLimit_fr1lsyzo0v
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 15;

                    ;% rtP.Constant1_Value_old3zd5smi
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 16;

                    ;% rtP.Constant2_Value_nvs1o44prj
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 17;

                    ;% rtP.DataStoreMemory_InitialValue_gzmuee1ywg
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 18;

                    ;% rtP.DataStoreMemory1_InitialValue_mnzngyb5ay
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 19;

                    ;% rtP.ForIterator_IterationLimit_g3aj12bfdp
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 20;

                    ;% rtP.Constant1_Value_m12xkxpoza
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 21;

                    ;% rtP.Constant2_Value_gpro0fhmc1
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 22;

                    ;% rtP.DataStoreMemory_InitialValue_pwe1ttvdh5
                    section.data(24).logicalSrcIdx = 23;
                    section.data(24).dtTransOffset = 23;

                    ;% rtP.DataStoreMemory1_InitialValue_cywkg1i2ev
                    section.data(25).logicalSrcIdx = 24;
                    section.data(25).dtTransOffset = 24;

                    ;% rtP.Constant_Value_iilw0smpge
                    section.data(26).logicalSrcIdx = 25;
                    section.data(26).dtTransOffset = 25;

                    ;% rtP.Constant1_Value_moljqjpuv3
                    section.data(27).logicalSrcIdx = 26;
                    section.data(27).dtTransOffset = 26;

                    ;% rtP.Merge_InitialOutput
                    section.data(28).logicalSrcIdx = 27;
                    section.data(28).dtTransOffset = 27;

                    ;% rtP.Merge1_InitialOutput
                    section.data(29).logicalSrcIdx = 28;
                    section.data(29).dtTransOffset = 28;

                    ;% rtP.DataStoreMemory_InitialValue_glvqogqqzg
                    section.data(30).logicalSrcIdx = 29;
                    section.data(30).dtTransOffset = 29;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section

            section.nData     = 6;
            section.data(6)  = dumData; %prealloc

                    ;% rtP.Constant_Value_mq0yqq5e0x
                    section.data(1).logicalSrcIdx = 30;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.Constant1_Value_b00i5gskzd
                    section.data(2).logicalSrcIdx = 31;
                    section.data(2).dtTransOffset = 1;

                    ;% rtP.Constant_Value_dp3hb0zdw4
                    section.data(3).logicalSrcIdx = 32;
                    section.data(3).dtTransOffset = 2;

                    ;% rtP.Constant_Value_pwsvvqm1ni
                    section.data(4).logicalSrcIdx = 33;
                    section.data(4).dtTransOffset = 3;

                    ;% rtP.DataStoreMemory1_InitialValue_jiyg3kkzow
                    section.data(5).logicalSrcIdx = 34;
                    section.data(5).dtTransOffset = 4;

                    ;% rtP.DataStoreMemory2_InitialValue
                    section.data(6).logicalSrcIdx = 35;
                    section.data(6).dtTransOffset = 5;

            nTotData = nTotData + section.nData;
            paramMap.sections(2) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtP.ax0jrtpwut.res_Y0
                    section.data(1).logicalSrcIdx = 36;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.ax0jrtpwut.value_out_Y0
                    section.data(2).logicalSrcIdx = 37;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            paramMap.sections(3) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtP.ebgpvzxvo3.Constant_Value
                    section.data(1).logicalSrcIdx = 38;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.ebgpvzxvo3.Constant1_Value
                    section.data(2).logicalSrcIdx = 39;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            paramMap.sections(4) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtP.cnsb0spyuq.res_Y0
                    section.data(1).logicalSrcIdx = 40;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.cnsb0spyuq.value_out_Y0
                    section.data(2).logicalSrcIdx = 41;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            paramMap.sections(5) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtP.axnaqsojmf.Constant_Value
                    section.data(1).logicalSrcIdx = 42;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.axnaqsojmf.Constant1_Value
                    section.data(2).logicalSrcIdx = 43;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            paramMap.sections(6) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtP.jhnifdm04yv.res_Y0
                    section.data(1).logicalSrcIdx = 44;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.jhnifdm04yv.value_out_Y0
                    section.data(2).logicalSrcIdx = 45;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            paramMap.sections(7) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtP.olreyz4euj.Constant_Value
                    section.data(1).logicalSrcIdx = 46;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.olreyz4euj.Constant1_Value
                    section.data(2).logicalSrcIdx = 47;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            paramMap.sections(8) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtP.fficko2a024.Constant_Value
                    section.data(1).logicalSrcIdx = 48;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.fficko2a024.Constant1_Value
                    section.data(2).logicalSrcIdx = 49;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            paramMap.sections(9) = section;
            clear section


            ;%
            ;% Non-auto Data (parameter)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        paramMap.nTotData = nTotData;



    ;%**************************
    ;% Create Block Output Map *
    ;%**************************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 4;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc sigMap
        ;%
        sigMap.nSections           = nTotSects;
        sigMap.sectIdxOffset       = sectIdxOffset;
            sigMap.sections(nTotSects) = dumSection; %prealloc
        sigMap.nTotData            = -1;

        ;%
        ;% Auto data (rtB)
        ;%
            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtB.bbkvllqsze
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.evxnnnvraz
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtB.ax0jrtpwut.pjxodb2nb1
                    section.data(1).logicalSrcIdx = 4;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.ax0jrtpwut.e0womlsjmm
                    section.data(2).logicalSrcIdx = 5;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            sigMap.sections(2) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtB.cnsb0spyuq.pjxodb2nb1
                    section.data(1).logicalSrcIdx = 6;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.cnsb0spyuq.e0womlsjmm
                    section.data(2).logicalSrcIdx = 7;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            sigMap.sections(3) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtB.jhnifdm04yv.pjxodb2nb1
                    section.data(1).logicalSrcIdx = 8;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.jhnifdm04yv.e0womlsjmm
                    section.data(2).logicalSrcIdx = 9;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            sigMap.sections(4) = section;
            clear section


            ;%
            ;% Non-auto Data (signal)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        sigMap.nTotData = nTotData;



    ;%*******************
    ;% Create DWork Map *
    ;%*******************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 11;
        sectIdxOffset = 4;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc dworkMap
        ;%
        dworkMap.nSections           = nTotSects;
        dworkMap.sectIdxOffset       = sectIdxOffset;
            dworkMap.sections(nTotSects) = dumSection; %prealloc
        dworkMap.nTotData            = -1;

        ;%
        ;% Auto data (rtDW)
        ;%
            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.be1ypkg3oi.TempDoubleOutput
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 4;
            section.data(4)  = dumData; %prealloc

                    ;% rtDW.da55vtlacw.ExcelLoader
                    section.data(1).logicalSrcIdx = 1;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.m3nqpukfpp.AQHandles
                    section.data(2).logicalSrcIdx = 2;
                    section.data(2).dtTransOffset = 3;

                    ;% rtDW.pddfetaq22.AQHandles
                    section.data(3).logicalSrcIdx = 3;
                    section.data(3).dtTransOffset = 4;

                    ;% rtDW.iiocir3hzh.AQHandles
                    section.data(4).logicalSrcIdx = 4;
                    section.data(4).dtTransOffset = 5;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
            clear section

            section.nData     = 9;
            section.data(9)  = dumData; %prealloc

                    ;% rtDW.jfxiebzt11
                    section.data(1).logicalSrcIdx = 5;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.fmekapcoh3
                    section.data(2).logicalSrcIdx = 6;
                    section.data(2).dtTransOffset = 16;

                    ;% rtDW.nthmb1rxyk
                    section.data(3).logicalSrcIdx = 7;
                    section.data(3).dtTransOffset = 17;

                    ;% rtDW.goiz0aciqk
                    section.data(4).logicalSrcIdx = 8;
                    section.data(4).dtTransOffset = 18;

                    ;% rtDW.bdc5i1qumz
                    section.data(5).logicalSrcIdx = 9;
                    section.data(5).dtTransOffset = 19;

                    ;% rtDW.lybbyc3wp4
                    section.data(6).logicalSrcIdx = 10;
                    section.data(6).dtTransOffset = 20;

                    ;% rtDW.d2sncbrt0x
                    section.data(7).logicalSrcIdx = 11;
                    section.data(7).dtTransOffset = 21;

                    ;% rtDW.k5kdf43z5e
                    section.data(8).logicalSrcIdx = 12;
                    section.data(8).dtTransOffset = 22;

                    ;% rtDW.mtop4afcg4
                    section.data(9).logicalSrcIdx = 13;
                    section.data(9).dtTransOffset = 23;

            nTotData = nTotData + section.nData;
            dworkMap.sections(3) = section;
            clear section

            section.nData     = 16;
            section.data(16)  = dumData; %prealloc

                    ;% rtDW.ka2crnf4zk
                    section.data(1).logicalSrcIdx = 14;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.gn4mbidhbe
                    section.data(2).logicalSrcIdx = 15;
                    section.data(2).dtTransOffset = 16;

                    ;% rtDW.m31ezypo53
                    section.data(3).logicalSrcIdx = 16;
                    section.data(3).dtTransOffset = 17;

                    ;% rtDW.ly4sytvojr
                    section.data(4).logicalSrcIdx = 17;
                    section.data(4).dtTransOffset = 18;

                    ;% rtDW.l2hwiyqftr
                    section.data(5).logicalSrcIdx = 18;
                    section.data(5).dtTransOffset = 19;

                    ;% rtDW.k1vr2ypctj
                    section.data(6).logicalSrcIdx = 19;
                    section.data(6).dtTransOffset = 20;

                    ;% rtDW.cvtoivpdg4
                    section.data(7).logicalSrcIdx = 20;
                    section.data(7).dtTransOffset = 21;

                    ;% rtDW.ljgif2qtik
                    section.data(8).logicalSrcIdx = 21;
                    section.data(8).dtTransOffset = 22;

                    ;% rtDW.b3a5gs5r5m
                    section.data(9).logicalSrcIdx = 22;
                    section.data(9).dtTransOffset = 23;

                    ;% rtDW.ocomjcomln
                    section.data(10).logicalSrcIdx = 23;
                    section.data(10).dtTransOffset = 24;

                    ;% rtDW.mpsw5o2vtm
                    section.data(11).logicalSrcIdx = 24;
                    section.data(11).dtTransOffset = 25;

                    ;% rtDW.kwoyf2vgju
                    section.data(12).logicalSrcIdx = 25;
                    section.data(12).dtTransOffset = 26;

                    ;% rtDW.epgh3rv3tm
                    section.data(13).logicalSrcIdx = 26;
                    section.data(13).dtTransOffset = 27;

                    ;% rtDW.olzc4eepgs
                    section.data(14).logicalSrcIdx = 27;
                    section.data(14).dtTransOffset = 28;

                    ;% rtDW.lo3dyuq41b
                    section.data(15).logicalSrcIdx = 28;
                    section.data(15).dtTransOffset = 29;

                    ;% rtDW.c5xvbnkpnx
                    section.data(16).logicalSrcIdx = 29;
                    section.data(16).dtTransOffset = 30;

            nTotData = nTotData + section.nData;
            dworkMap.sections(4) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.ax0jrtpwut.gnp0dzznxb
                    section.data(1).logicalSrcIdx = 30;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(5) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.ebgpvzxvo3.o4lcay5ifo
                    section.data(1).logicalSrcIdx = 31;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(6) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.cnsb0spyuq.gnp0dzznxb
                    section.data(1).logicalSrcIdx = 32;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(7) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.axnaqsojmf.o4lcay5ifo
                    section.data(1).logicalSrcIdx = 33;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(8) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.jhnifdm04yv.gnp0dzznxb
                    section.data(1).logicalSrcIdx = 34;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(9) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.olreyz4euj.o4lcay5ifo
                    section.data(1).logicalSrcIdx = 35;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(10) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.fficko2a024.o4lcay5ifo
                    section.data(1).logicalSrcIdx = 36;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(11) = section;
            clear section


            ;%
            ;% Non-auto Data (dwork)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        dworkMap.nTotData = nTotData;



    ;%
    ;% Add individual maps to base struct.
    ;%

    targMap.paramMap  = paramMap;
    targMap.signalMap = sigMap;
    targMap.dworkMap  = dworkMap;

    ;%
    ;% Add checksums to base struct.
    ;%


    targMap.checksum0 = 2732562820;
    targMap.checksum1 = 3618147763;
    targMap.checksum2 = 1495580333;
    targMap.checksum3 = 2324113380;

