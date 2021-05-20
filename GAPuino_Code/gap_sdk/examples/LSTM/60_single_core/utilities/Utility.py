import numpy as np

##Scaling Factors
scale_shift=11 
scale=pow(2,scale_shift)
unscale=pow(2, -scale_shift)
scale2=pow(2,scale_shift*2)
unscale2=pow(2,-scale_shift*2)

def h_sig(i):
    inv = 0	
    p2_5 = np.int32(np.trunc(-2.5*scale))   #-2.5(32,12)
    Acc = np.int32(np.trunc(0.5*scale2))   #0.5(32,24)
    p0_2 = np.int32(np.trunc(0.2*scale))      #0.2(32,12)
    p1 = np.int32(np.trunc(1*scale2))   #1(32,24)	
    i = i>>scale_shift

    if (i>0):
        i = -i
        inv = 1
        
    if (i>=p2_5):
        r = Acc+p0_2*i #(32,24)		
    else:
        r = 0

    if (inv==1):
        r = (p1-r)>>scale_shift
        return r
    else:
        r = r>>scale_shift
        return r

def tan_h(i):#(32,24)
    i = i*unscale2
    r = np.tanh(i)
    r = np.int32(np.trunc(r*scale))
    return r

def hard_sig(x, fun=h_sig):
    return np.vectorize(fun)(x) 

def tan_iper(i):
    inv=0
    if i>0:
	    i=-i 
	    inv=1    
    if i>=-22984785 :
        if i>=-13421772 :
            if i>=-8724152 :
                if i>=-6375342 :
                    if i>=-5200936 :
                        if i>=-4529848 :
                            if i>=-4194304 :
                                if i>=0 :
                                    r= 0
                                else :
                                    r= np.int32(np.trunc(i*unscale))
                            else :
                                if i>=-4362076 :
                                    r= -1041
                                else :
                                    r= -1079
                        else :
                            if i>=-4865392 :
                                if i>=-4697620 :
                                    r= -1117
                                else :
                                    r= -1155
                            else :
                                if i>=-5033164 :
                                    r= -1193
                                else :
                                    r= -1230
                    else :
                        if i>=-5872025 :
                            if i>=-5536481 :
                                if i>=-5368709 :
                                    r= -1267
                                else :
                                    r= -1304
                            else :
                                if i>=-5704253 :
                                    r= -1341
                                else :
                                    r= -1377
                        else :
                            if i>=-6207569 :
                                if i>=-6039797 :
                                    r= -1413
                                else :
                                    r= -1449
                            else :
                                r= -1485
                else :
                    if i>=-7549747 :
                        if i>=-7046430 :
                            if i>=-6710886 :
                                if i>=-6543114 :
                                    r= -1521
                                else :
                                    r= -1556
                            else :
                                if i>=-6878658 :
                                    r= -1591
                                else :
                                    r= -1625
                        else :
                            if i>=-7381975 :
                                if i>=-7214202 :
                                    r= -1660
                                else :
                                    r= -1694
                            else :
                                r= -1728
                    else :
                        if i>=-8220835 :
                            if i>=-7885291 :
                                if i>=-7717519 :
                                    r= -1761
                                else :
                                    r= -1794
                            else :
                                if i>=-8053063 :
                                    r= -1827
                                else :
                                    r= -1860
                        else :
                            if i>=-8556380 :
                                if i>=-8388608 :
                                    r= -1892
                                else :
                                    r= -1924
                            else :
                                r= -1956
            else :
                if i>=-11072962 :
                    if i>=-9898557 :
                        if i>=-9395240 :
                            if i>=-9059696 :
                                if i>=-8891924 :
                                    r= -1988
                                else :
                                    r= -2019
                            else :
                                if i>=-9227468 :
                                    r= -2050
                                else :
                                    r= -2080
                        else :
                            if i>=-9730785 :
                                if i>=-9563013 :
                                    r= -2110
                                else :
                                    r= -2140
                            else :
                                r= -2170
                    else :
                        if i>=-10569646 :
                            if i>=-10234101 :
                                if i>=-10066329 :
                                    r= -2199
                                else :
                                    r= -2228
                            else :
                                if i>=-10401873 :
                                    r= -2257
                                else :
                                    r= -2285
                        else :
                            if i>=-10905190 :
                                if i>=-10737418 :
                                    r= -2313
                                else :
                                    r= -2341
                            else :
                                r= -2368
                else :
                    if i>=-12247367 :
                        if i>=-11744051 :
                            if i>=-11408506 :
                                if i>=-11240734 :
                                    r= -2396
                                else :
                                    r= -2422
                            else :
                                if i>=-11576279 :
                                    r= -2449
                                else :
                                    r= -2475
                        else :
                            if i>=-12079595 :
                                if i>=-11911823 :
                                    r= -2501
                                else :
                                    r= -2526
                            else :
                                r= -2552
                    else :
                        if i>=-12918456 :
                            if i>=-12582912 :
                                if i>=-12415139 :
                                    r= -2576
                                else :
                                    r= -2601
                            else :
                                if i>=-12750684 :
                                    r= -2625
                                else :
                                    r= -2649
                        else :
                            if i>=-13254000 :
                                if i>=-13086228 :
                                    r= -2673
                                else :
                                    r= -2696
                            else :
                                r= -2719
        else :
            if i>=-18287165 :
                if i>=-15938355 :
                    if i>=-14763950 :
                        if i>=-14092861 :
                            if i>=-13757317 :
                                if i>=-13589544 :
                                    r= -2742
                                else :
                                    r= -2765
                            else :
                                if i>=-13925089 :
                                    r= -2787
                                else :
                                    r= -2809
                        else :
                            if i>=-14428405 :
                                if i>=-14260633 :
                                    r= -2830
                                else :
                                    r= -2851
                            else :
                                if i>=-14596177 :
                                    r= -2872
                                else :
                                    r= -2893
                    else :
                        if i>=-15435038 :
                            if i>=-15099494 :
                                if i>=-14931722 :
                                    r= -2913
                                else :
                                    r= -2933
                            else :
                                if i>=-15267266 :
                                    r= -2953
                                else :
                                    r= -2973
                        else :
                            if i>=-15770583 :
                                if i>=-15602810 :
                                    r= -2992
                                else :
                                    r= -3011
                            else :
                                r= -3030
                else :
                    if i>=-17112760 :
                        if i>=-16609443 :
                            if i>=-16273899 :
                                if i>=-16106127 :
                                    r= -3048
                                else :
                                    r= -3066
                            else :
                                if i>=-16441671 :
                                    r= -3084
                                else :
                                    r= -3102
                        else :
                            if i>=-16944988 :
                                if i>=-16777216 :
                                    r= -3119
                                else :
                                    r= -3136
                            else :
                                r= -3153
                    else :
                        if i>=-17783848 :
                            if i>=-17448304 :
                                if i>=-17280532 :
                                    r= -3169
                                else :
                                    r= -3186
                            else :
                                if i>=-17616076 :
                                    r= -3202
                                else :
                                    r= -3218
                        else :
                            if i>=-18119393 :
                                if i>=-17951621 :
                                    r= -3233
                                else :
                                    r= -3248
                            else :
                                r= -3264
            else :
                if i>=-20635975 :
                    if i>=-19461570 :
                        if i>=-18958254 :
                            if i>=-18622709 :
                                if i>=-18454937 :
                                    r= -3278
                                else :
                                    r= -3293
                            else :
                                if i>=-18790481 :
                                    r= -3307
                                else :
                                    r= -3321
                        else :
                            if i>=-19293798 :
                                if i>=-19126026 :
                                    r= -3335
                                else :
                                    r= -3349
                            else :
                                r= -3362
                    else :
                        if i>=-20132659 :
                            if i>=-19797114 :
                                if i>=-19629342 :
                                    r= -3376
                                else :
                                    r= -3389
                            else :
                                if i>=-19964887 :
                                    r= -3402
                                else :
                                    r= -3414
                        else :
                            if i>=-20468203 :
                                if i>=-20300431 :
                                    r= -3427
                                else :
                                    r= -3439
                            else :
                                r= -3451
                else :
                    if i>=-21810380 :
                        if i>=-21307064 :
                            if i>=-20971520 :
                                if i>=-20803747 :
                                    r= -3462
                                else :
                                    r= -3474
                            else :
                                if i>=-21139292 :
                                    r= -3485
                                else :
                                    r= -3497
                        else :
                            if i>=-21642608 :
                                if i>=-21474836 :
                                    r= -3508
                                else :
                                    r= -3518
                            else :
                                r= -3529
                    else :
                        if i>=-22481469 :
                            if i>=-22145925 :
                                if i>=-21978152 :
                                    r= -3540
                                else :
                                    r= -3550
                            else :
                                if i>=-22313697 :
                                    r= -3560
                                else :
                                    r= -3570
                        else :
                            if i>=-22817013 :
                                if i>=-22649241 :
                                    r= -3580
                                else :
                                    r= -3589
                            else :
                                r= -3599
    else :
        if i>=-32547799 :
            if i>=-27850178 :
                if i>=-25501368 :
                    if i>=-24326963 :
                        if i>=-23655874 :
                            if i>=-23320330 :
                                if i>=-23152558 :
                                    r= -3608
                                else :
                                    r= -3617
                            else :
                                if i>=-23488102 :
                                    r= -3626
                                else :
                                    r= -3635
                        else :
                            if i>=-23991418 :
                                if i>=-23823646 :
                                    r= -3643
                                else :
                                    r= -3652
                            else :
                                if i>=-24159191 :
                                    r= -3660
                                else :
                                    r= -3668
                    else :
                        if i>=-24998051 :
                            if i>=-24662507 :
                                if i>=-24494735 :
                                    r= -3676
                                else :
                                    r= -3684
                            else :
                                if i>=-24830279 :
                                    r= -3692
                                else :
                                    r= -3700
                        else :
                            if i>=-25333596 :
                                if i>=-25165824 :
                                    r= -3707
                                else :
                                    r= -3714
                            else :
                                r= -3722
                else :
                    if i>=-26675773 :
                        if i>=-26172456 :
                            if i>=-25836912 :
                                if i>=-25669140 :
                                    r= -3729
                                else :
                                    r= -3736
                            else :
                                if i>=-26004684 :
                                    r= -3742
                                else :
                                    r= -3749
                        else :
                            if i>=-26508001 :
                                if i>=-26340229 :
                                    r= -3756
                                else :
                                    r= -3762
                            else :
                                r= -3768
                    else :
                        if i>=-27346862 :
                            if i>=-27011317 :
                                if i>=-26843545 :
                                    r= -3775
                                else :
                                    r= -3781
                            else :
                                if i>=-27179089 :
                                    r= -3787
                                else :
                                    r= -3793
                        else :
                            if i>=-27682406 :
                                if i>=-27514634 :
                                    r= -3798
                                else :
                                    r= -3804
                            else :
                                r= -3810
            else :
                if i>=-30198988 :
                    if i>=-29024583 :
                        if i>=-28521267 :
                            if i>=-28185722 :
                                if i>=-28017950 :
                                    r= -3815
                                else :
                                    r= -3821
                            else :
                                if i>=-28353495 :
                                    r= -3826
                                else :
                                    r= -3831
                        else :
                            if i>=-28856811 :
                                if i>=-28689039 :
                                    r= -3836
                                else :
                                    r= -3841
                            else :
                                r= -3846
                    else :
                        if i>=-29695672 :
                            if i>=-29360128 :
                                if i>=-29192355 :
                                    r= -3851
                                else :
                                    r= -3855
                            else :
                                if i>=-29527900 :
                                    r= -3860
                                else :
                                    r= -3865
                        else :
                            if i>=-30031216 :
                                if i>=-29863444 :
                                    r= -3869
                                else :
                                    r= -3873
                            else :
                                r= -3878
                else :
                    if i>=-31373393 :
                        if i>=-30870077 :
                            if i>=-30534533 :
                                if i>=-30366760 :
                                    r= -3882
                                else :
                                    r= -3886
                            else :
                                if i>=-30702305 :
                                    r= -3890
                                else :
                                    r= -3894
                        else :
                            if i>=-31205621 :
                                if i>=-31037849 :
                                    r= -3898
                                else :
                                    r= -3902
                            else :
                                r= -3905
                    else :
                        if i>=-32044482 :
                            if i>=-31708938 :
                                if i>=-31541166 :
                                    r= -3909
                                else :
                                    r= -3913
                            else :
                                if i>=-31876710 :
                                    r= -3916
                                else :
                                    r= -3920
                        else :
                            if i>=-32380026 :
                                if i>=-32212254 :
                                    r= -3923
                                else :
                                    r= -3926
                            else :
                                r= -3930
        else :
            if i>=-37245419 :
                if i>=-34896609 :
                    if i>=-33722204 :
                        if i>=-33218887 :
                            if i>=-32883343 :
                                if i>=-32715571 :
                                    r= -3933
                                else :
                                    r= -3936
                            else :
                                if i>=-33051115 :
                                    r= -3939
                                else :
                                    r= -3942
                        else :
                            if i>=-33554432 :
                                if i>=-33386659 :
                                    r= -3945
                                else :
                                    r= -3948
                            else :
                                r= -3951
                    else :
                        if i>=-34393292 :
                            if i>=-34057748 :
                                if i>=-33889976 :
                                    r= -3954
                                else :
                                    r= -3957
                            else :
                                if i>=-34225520 :
                                    r= -3959
                                else :
                                    r= -3962
                        else :
                            if i>=-34728837 :
                                if i>=-34561064 :
                                    r= -3965
                                else :
                                    r= -3967
                            else :
                                r= -3970
                else :
                    if i>=-36071014 :
                        if i>=-35567697 :
                            if i>=-35232153 :
                                if i>=-35064381 :
                                    r= -3972
                                else :
                                    r= -3974
                            else :
                                if i>=-35399925 :
                                    r= -3977
                                else :
                                    r= -3979
                        else :
                            if i>=-35903242 :
                                if i>=-35735470 :
                                    r= -3981
                                else :
                                    r= -3984
                            else :
                                r= -3986
                    else :
                        if i>=-36742103 :
                            if i>=-36406558 :
                                if i>=-36238786 :
                                    r= -3988
                                else :
                                    r= -3990
                            else :
                                if i>=-36574330 :
                                    r= -3992
                                else :
                                    r= -3994
                        else :
                            if i>=-37077647 :
                                if i>=-36909875 :
                                    r= -3996
                                else :
                                    r= -3998
                            else :
                                r= -4000
            else :
                if i>=-39594229 :
                    if i>=-38419824 :
                        if i>=-37916508 :
                            if i>=-37580963 :
                                if i>=-37413191 :
                                    r= -4002
                                else :
                                    r= -4004
                            else :
                                if i>=-37748736 :
                                    r= -4005
                                else :
                                    r= -4007
                        else :
                            if i>=-38252052 :
                                if i>=-38084280 :
                                    r= -4009
                                else :
                                    r= -4011
                            else :
                                r= -4012
                    else :
                        if i>=-39090913 :
                            if i>=-38755368 :
                                if i>=-38587596 :
                                    r= -4014
                                else :
                                    r= -4016
                            else :
                                if i>=-38923141 :
                                    r= -4017
                                else :
                                    r= -4019
                        else :
                            if i>=-39426457 :
                                if i>=-39258685 :
                                    r= -4020
                                else :
                                    r= -4022
                            else :
                                r= -4023
                else :
                    if i>=-40768634 :
                        if i>=-40265318 :
                            if i>=-39929774 :
                                if i>=-39762001 :
                                    r= -4025
                                else :
                                    r= -4026
                            else :
                                if i>=-40097546 :
                                    r= -4027
                                else :
                                    r= -4029
                        else :
                            if i>=-40600862 :
                                if i>=-40433090 :
                                    r= -4030
                                else :
                                    r= -4031
                            else :
                                r= -4032
                    else :
                        if i>=-41439723 :
                            if i>=-41104179 :
                                if i>=-40936407 :
                                    r= -4034
                                else :
                                    r= -4035
                            else :
                                if i>=-41271951 :
                                    r= -4036
                                else :
                                    r= -4037
                        else :
                            if i>=-41775267 :
                                if i>=-41607495 :
                                    r= -4038
                                else :
                                    r= -4040
                            else :
                                r= -4041
    if inv==1:
        return -r
    else: 
        return r

def tan_iper16_12(i):
    i = i>>12
    inv=0
    if i>0:
	    i=-i 
	    inv=1
    if i>=-5611 :
        if i>=-3276 :
            if i>=-2129 :
                if i>=-1556 :
                    if i>=-1269 :
                        if i>=-1105 :
                            if i>=-1024 :
                                if i>=0 :
                                    r= 0
                                else :
                                    r= i
                            else :
                                if i>=-1064 :
                                    r= -1041
                                else :
                                    r= -1079
                        else :
                            if i>=-1187 :
                                if i>=-1146 :
                                    r= -1117
                                else :
                                    r= -1155
                            else :
                                if i>=-1228 :
                                    r= -1193
                                else :
                                    r= -1230
                    else :
                        if i>=-1433 :
                            if i>=-1351 :
                                if i>=-1310 :
                                    r= -1267
                                else :
                                    r= -1304
                            else :
                                if i>=-1392 :
                                    r= -1341
                                else :
                                    r= -1377
                        else :
                            if i>=-1515 :
                                if i>=-1474 :
                                    r= -1413
                                else :
                                    r= -1449
                            else :
                                r= -1485
                else :
                    if i>=-1843 :
                        if i>=-1720 :
                            if i>=-1638 :
                                if i>=-1597 :
                                    r= -1521
                                else :
                                    r= -1556
                            else :
                                if i>=-1679 :
                                    r= -1591
                                else :
                                    r= -1625
                        else :
                            if i>=-1802 :
                                if i>=-1761 :
                                    r= -1660
                                else :
                                    r= -1694
                            else :
                                r= -1728
                    else :
                        if i>=-2007 :
                            if i>=-1925 :
                                if i>=-1884 :
                                    r= -1761
                                else :
                                    r= -1794
                            else :
                                if i>=-1966 :
                                    r= -1827
                                else :
                                    r= -1860
                        else :
                            if i>=-2088 :
                                if i>=-2048 :
                                    r= -1892
                                else :
                                    r= -1924
                            else :
                                r= -1956
            else :
                if i>=-2703 :
                    if i>=-2416 :
                        if i>=-2293 :
                            if i>=-2211 :
                                if i>=-2170 :
                                    r= -1988
                                else :
                                    r= -2019
                            else :
                                if i>=-2252 :
                                    r= -2050
                                else :
                                    r= -2080
                        else :
                            if i>=-2375 :
                                if i>=-2334 :
                                    r= -2110
                                else :
                                    r= -2140
                            else :
                                r= -2170
                    else :
                        if i>=-2580 :
                            if i>=-2498 :
                                if i>=-2457 :
                                    r= -2199
                                else :
                                    r= -2228
                            else :
                                if i>=-2539 :
                                    r= -2257
                                else :
                                    r= -2285
                        else :
                            if i>=-2662 :
                                if i>=-2621 :
                                    r= -2313
                                else :
                                    r= -2341
                            else :
                                r= -2368
                else :
                    if i>=-2990 :
                        if i>=-2867 :
                            if i>=-2785 :
                                if i>=-2744 :
                                    r= -2396
                                else :
                                    r= -2422
                            else :
                                if i>=-2826 :
                                    r= -2449
                                else :
                                    r= -2475
                        else :
                            if i>=-2949 :
                                if i>=-2908 :
                                    r= -2501
                                else :
                                    r= -2526
                            else :
                                r= -2552
                    else :
                        if i>=-3153 :
                            if i>=-3072 :
                                if i>=-3031 :
                                    r= -2576
                                else :
                                    r= -2601
                            else :
                                if i>=-3112 :
                                    r= -2625
                                else :
                                    r= -2649
                        else :
                            if i>=-3235 :
                                if i>=-3194 :
                                    r= -2673
                                else :
                                    r= -2696
                            else :
                                r= -2719
        else :
            if i>=-4464 :
                if i>=-3891 :
                    if i>=-3604 :
                        if i>=-3440 :
                            if i>=-3358 :
                                if i>=-3317 :
                                    r= -2742
                                else :
                                    r= -2765
                            else :
                                if i>=-3399 :
                                    r= -2787
                                else :
                                    r= -2809
                        else :
                            if i>=-3522 :
                                if i>=-3481 :
                                    r= -2830
                                else :
                                    r= -2851
                            else :
                                if i>=-3563 :
                                    r= -2872
                                else :
                                    r= -2893
                    else :
                        if i>=-3768 :
                            if i>=-3686 :
                                if i>=-3645 :
                                    r= -2913
                                else :
                                    r= -2933
                            else :
                                if i>=-3727 :
                                    r= -2953
                                else :
                                    r= -2973
                        else :
                            if i>=-3850 :
                                if i>=-3809 :
                                    r= -2992
                                else :
                                    r= -3011
                            else :
                                r= -3030
                else :
                    if i>=-4177 :
                        if i>=-4055 :
                            if i>=-3973 :
                                if i>=-3932 :
                                    r= -3048
                                else :
                                    r= -3066
                            else :
                                if i>=-4014 :
                                    r= -3084
                                else :
                                    r= -3102
                        else :
                            if i>=-4136 :
                                if i>=-4096 :
                                    r= -3119
                                else :
                                    r= -3136
                            else :
                                r= -3153
                    else :
                        if i>=-4341 :
                            if i>=-4259 :
                                if i>=-4218 :
                                    r= -3169
                                else :
                                    r= -3186
                            else :
                                if i>=-4300 :
                                    r= -3202
                                else :
                                    r= -3218
                        else :
                            if i>=-4423 :
                                if i>=-4382 :
                                    r= -3233
                                else :
                                    r= -3248
                            else :
                                r= -3264
            else :
                if i>=-5038 :
                    if i>=-4751 :
                        if i>=-4628 :
                            if i>=-4546 :
                                if i>=-4505 :
                                    r= -3278
                                else :
                                    r= -3293
                            else :
                                if i>=-4587 :
                                    r= -3307
                                else :
                                    r= -3321
                        else :
                            if i>=-4710 :
                                if i>=-4669 :
                                    r= -3335
                                else :
                                    r= -3349
                            else :
                                r= -3362
                    else :
                        if i>=-4915 :
                            if i>=-4833 :
                                if i>=-4792 :
                                    r= -3376
                                else :
                                    r= -3389
                            else :
                                if i>=-4874 :
                                    r= -3402
                                else :
                                    r= -3414
                        else :
                            if i>=-4997 :
                                if i>=-4956 :
                                    r= -3427
                                else :
                                    r= -3439
                            else :
                                r= -3451
                else :
                    if i>=-5324 :
                        if i>=-5201 :
                            if i>=-5120 :
                                if i>=-5079 :
                                    r= -3462
                                else :
                                    r= -3474
                            else :
                                if i>=-5160 :
                                    r= -3485
                                else :
                                    r= -3497
                        else :
                            if i>=-5283 :
                                if i>=-5242 :
                                    r= -3508
                                else :
                                    r= -3518
                            else :
                                r= -3529
                    else :
                        if i>=-5488 :
                            if i>=-5406 :
                                if i>=-5365 :
                                    r= -3540
                                else :
                                    r= -3550
                            else :
                                if i>=-5447 :
                                    r= -3560
                                else :
                                    r= -3570
                        else :
                            if i>=-5570 :
                                if i>=-5529 :
                                    r= -3580
                                else :
                                    r= -3589
                            else :
                                r= -3599
    else :
        if i>=-7946 :
            if i>=-6799 :
                if i>=-6225 :
                    if i>=-5939 :
                        if i>=-5775 :
                            if i>=-5693 :
                                if i>=-5652 :
                                    r= -3608
                                else :
                                    r= -3617
                            else :
                                if i>=-5734 :
                                    r= -3626
                                else :
                                    r= -3635
                        else :
                            if i>=-5857 :
                                if i>=-5816 :
                                    r= -3643
                                else :
                                    r= -3652
                            else :
                                if i>=-5898 :
                                    r= -3660
                                else :
                                    r= -3668
                    else :
                        if i>=-6103 :
                            if i>=-6021 :
                                if i>=-5980 :
                                    r= -3676
                                else :
                                    r= -3684
                            else :
                                if i>=-6062 :
                                    r= -3692
                                else :
                                    r= -3700
                        else :
                            if i>=-6184 :
                                if i>=-6144 :
                                    r= -3707
                                else :
                                    r= -3714
                            else :
                                r= -3722
                else :
                    if i>=-6512 :
                        if i>=-6389 :
                            if i>=-6307 :
                                if i>=-6266 :
                                    r= -3729
                                else :
                                    r= -3736
                            else :
                                if i>=-6348 :
                                    r= -3742
                                else :
                                    r= -3749
                        else :
                            if i>=-6471 :
                                if i>=-6430 :
                                    r= -3756
                                else :
                                    r= -3762
                            else :
                                r= -3768
                    else :
                        if i>=-6676 :
                            if i>=-6594 :
                                if i>=-6553 :
                                    r= -3775
                                else :
                                    r= -3781
                            else :
                                if i>=-6635 :
                                    r= -3787
                                else :
                                    r= -3793
                        else :
                            if i>=-6758 :
                                if i>=-6717 :
                                    r= -3798
                                else :
                                    r= -3804
                            else :
                                r= -3810
            else :
                if i>=-7372 :
                    if i>=-7086 :
                        if i>=-6963 :
                            if i>=-6881 :
                                if i>=-6840 :
                                    r= -3815
                                else :
                                    r= -3821
                            else :
                                if i>=-6922 :
                                    r= -3826
                                else :
                                    r= -3831
                        else :
                            if i>=-7045 :
                                if i>=-7004 :
                                    r= -3836
                                else :
                                    r= -3841
                            else :
                                r= -3846
                    else :
                        if i>=-7249 :
                            if i>=-7168 :
                                if i>=-7127 :
                                    r= -3851
                                else :
                                    r= -3855
                            else :
                                if i>=-7208 :
                                    r= -3860
                                else :
                                    r= -3865
                        else :
                            if i>=-7331 :
                                if i>=-7290 :
                                    r= -3869
                                else :
                                    r= -3873
                            else :
                                r= -3878
                else :
                    if i>=-7659 :
                        if i>=-7536 :
                            if i>=-7454 :
                                if i>=-7413 :
                                    r= -3882
                                else :
                                    r= -3886
                            else :
                                if i>=-7495 :
                                    r= -3890
                                else :
                                    r= -3894
                        else :
                            if i>=-7618 :
                                if i>=-7577 :
                                    r= -3898
                                else :
                                    r= -3902
                            else :
                                r= -3905
                    else :
                        if i>=-7823 :
                            if i>=-7741 :
                                if i>=-7700 :
                                    r= -3909
                                else :
                                    r= -3913
                            else :
                                if i>=-7782 :
                                    r= -3916
                                else :
                                    r= -3920
                        else :
                            if i>=-7905 :
                                if i>=-7864 :
                                    r= -3923
                                else :
                                    r= -3926
                            else :
                                r= -3930
        else :
            if i>=-9093 :
                if i>=-8519 :
                    if i>=-8232 :
                        if i>=-8110 :
                            if i>=-8028 :
                                if i>=-7987 :
                                    r= -3933
                                else :
                                    r= -3936
                            else :
                                if i>=-8069 :
                                    r= -3939
                                else :
                                    r= -3942
                        else :
                            if i>=-8192 :
                                if i>=-8151 :
                                    r= -3945
                                else :
                                    r= -3948
                            else :
                                r= -3951
                    else :
                        if i>=-8396 :
                            if i>=-8314 :
                                if i>=-8273 :
                                    r= -3954
                                else :
                                    r= -3957
                            else :
                                if i>=-8355 :
                                    r= -3959
                                else :
                                    r= -3962
                        else :
                            if i>=-8478 :
                                if i>=-8437 :
                                    r= -3965
                                else :
                                    r= -3967
                            else :
                                r= -3970
                else :
                    if i>=-8806 :
                        if i>=-8683 :
                            if i>=-8601 :
                                if i>=-8560 :
                                    r= -3972
                                else :
                                    r= -3974
                            else :
                                if i>=-8642 :
                                    r= -3977
                                else :
                                    r= -3979
                        else :
                            if i>=-8765 :
                                if i>=-8724 :
                                    r= -3981
                                else :
                                    r= -3984
                            else :
                                r= -3986
                    else :
                        if i>=-8970 :
                            if i>=-8888 :
                                if i>=-8847 :
                                    r= -3988
                                else :
                                    r= -3990
                            else :
                                if i>=-8929 :
                                    r= -3992
                                else :
                                    r= -3994
                        else :
                            if i>=-9052 :
                                if i>=-9011 :
                                    r= -3996
                                else :
                                    r= -3998
                            else :
                                r= -4000
            else :
                if i>=-9666 :
                    if i>=-9379 :
                        if i>=-9256 :
                            if i>=-9175 :
                                if i>=-9134 :
                                    r= -4002
                                else :
                                    r= -4004
                            else :
                                if i>=-9216 :
                                    r= -4005
                                else :
                                    r= -4007
                        else :
                            if i>=-9338 :
                                if i>=-9297 :
                                    r= -4009
                                else :
                                    r= -4011
                            else :
                                r= -4012
                    else :
                        if i>=-9543 :
                            if i>=-9461 :
                                if i>=-9420 :
                                    r= -4014
                                else :
                                    r= -4016
                            else :
                                if i>=-9502 :
                                    r= -4017
                                else :
                                    r= -4019
                        else :
                            if i>=-9625 :
                                if i>=-9584 :
                                    r= -4020
                                else :
                                    r= -4022
                            else :
                                r= -4023
                else :
                    if i>=-9953 :
                        if i>=-9830 :
                            if i>=-9748 :
                                if i>=-9707 :
                                    r= -4025
                                else :
                                    r= -4026
                            else :
                                if i>=-9789 :
                                    r= -4027
                                else :
                                    r= -4029
                        else :
                            if i>=-9912 :
                                if i>=-9871 :
                                    r= -4030
                                else :
                                    r= -4031
                            else :
                                r= -4032
                    else :
                        if i>=-10117 :
                            if i>=-10035 :
                                if i>=-9994 :
                                    r= -4034
                                else :
                                    r= -4035
                            else :
                                if i>=-10076 :
                                    r= -4036
                                else :
                                    r= -4037
                        else :
                            if i>=-10199 :
                                if i>=-10158 :
                                    r= -4038
                                else :
                                    r= -4040
                            else :
                                r= -4041
    if inv==1:
        return -r
    else: 
        return r

def tan_iper16_11(i):
    i = i>>11
    inv=0
    if i>0:
	    i=-i 
	    inv=1
    if i>=-2805 :
        if i>=-1638 :
            if i>=-1064 :
                if i>=-778 :
                    if i>=-634 :
                        if i>=-552 :
                            if i>=-512 :
                                if i>=0 :
                                    r= 0
                                else :
                                    r= i
                            else :
                                if i>=-532 :
                                    r= -520
                                else :
                                    r= -539
                        else :
                            if i>=-593 :
                                if i>=-573 :
                                    r= -558
                                else :
                                    r= -577
                            else :
                                if i>=-614 :
                                    r= -596
                                else :
                                    r= -615
                    else :
                        if i>=-716 :
                            if i>=-675 :
                                if i>=-655 :
                                    r= -633
                                else :
                                    r= -652
                            else :
                                if i>=-696 :
                                    r= -670
                                else :
                                    r= -688
                        else :
                            if i>=-757 :
                                if i>=-737 :
                                    r= -706
                                else :
                                    r= -724
                            else :
                                r= -742
                else :
                    if i>=-921 :
                        if i>=-860 :
                            if i>=-819 :
                                if i>=-798 :
                                    r= -760
                                else :
                                    r= -778
                            else :
                                if i>=-839 :
                                    r= -795
                                else :
                                    r= -812
                        else :
                            if i>=-901 :
                                if i>=-880 :
                                    r= -830
                                else :
                                    r= -847
                            else :
                                r= -864
                    else :
                        if i>=-1003 :
                            if i>=-962 :
                                if i>=-942 :
                                    r= -880
                                else :
                                    r= -897
                            else :
                                if i>=-983 :
                                    r= -913
                                else :
                                    r= -930
                        else :
                            if i>=-1044 :
                                if i>=-1024 :
                                    r= -946
                                else :
                                    r= -962
                            else :
                                r= -978
            else :
                if i>=-1351 :
                    if i>=-1208 :
                        if i>=-1146 :
                            if i>=-1105 :
                                if i>=-1085 :
                                    r= -994
                                else :
                                    r= -1009
                            else :
                                if i>=-1126 :
                                    r= -1025
                                else :
                                    r= -1040
                        else :
                            if i>=-1187 :
                                if i>=-1167 :
                                    r= -1055
                                else :
                                    r= -1070
                            else :
                                r= -1085
                    else :
                        if i>=-1290 :
                            if i>=-1249 :
                                if i>=-1228 :
                                    r= -1099
                                else :
                                    r= -1114
                            else :
                                if i>=-1269 :
                                    r= -1128
                                else :
                                    r= -1142
                        else :
                            if i>=-1331 :
                                if i>=-1310 :
                                    r= -1156
                                else :
                                    r= -1170
                            else :
                                r= -1184
                else :
                    if i>=-1495 :
                        if i>=-1433 :
                            if i>=-1392 :
                                if i>=-1372 :
                                    r= -1198
                                else :
                                    r= -1211
                            else :
                                if i>=-1413 :
                                    r= -1224
                                else :
                                    r= -1237
                        else :
                            if i>=-1474 :
                                if i>=-1454 :
                                    r= -1250
                                else :
                                    r= -1263
                            else :
                                r= -1276
                    else :
                        if i>=-1576 :
                            if i>=-1536 :
                                if i>=-1515 :
                                    r= -1288
                                else :
                                    r= -1300
                            else :
                                if i>=-1556 :
                                    r= -1312
                                else :
                                    r= -1324
                        else :
                            if i>=-1617 :
                                if i>=-1597 :
                                    r= -1336
                                else :
                                    r= -1348
                            else :
                                r= -1359
        else :
            if i>=-2232 :
                if i>=-1945 :
                    if i>=-1802 :
                        if i>=-1720 :
                            if i>=-1679 :
                                if i>=-1658 :
                                    r= -1371
                                else :
                                    r= -1382
                            else :
                                if i>=-1699 :
                                    r= -1393
                                else :
                                    r= -1404
                        else :
                            if i>=-1761 :
                                if i>=-1740 :
                                    r= -1415
                                else :
                                    r= -1425
                            else :
                                if i>=-1781 :
                                    r= -1436
                                else :
                                    r= -1446
                    else :
                        if i>=-1884 :
                            if i>=-1843 :
                                if i>=-1822 :
                                    r= -1456
                                else :
                                    r= -1466
                            else :
                                if i>=-1863 :
                                    r= -1476
                                else :
                                    r= -1486
                        else :
                            if i>=-1925 :
                                if i>=-1904 :
                                    r= -1496
                                else :
                                    r= -1505
                            else :
                                r= -1515
                else :
                    if i>=-2088 :
                        if i>=-2027 :
                            if i>=-1986 :
                                if i>=-1966 :
                                    r= -1524
                                else :
                                    r= -1533
                            else :
                                if i>=-2007 :
                                    r= -1542
                                else :
                                    r= -1551
                        else :
                            if i>=-2068 :
                                if i>=-2048 :
                                    r= -1559
                                else :
                                    r= -1568
                            else :
                                r= -1576
                    else :
                        if i>=-2170 :
                            if i>=-2129 :
                                if i>=-2109 :
                                    r= -1584
                                else :
                                    r= -1593
                            else :
                                if i>=-2150 :
                                    r= -1601
                                else :
                                    r= -1609
                        else :
                            if i>=-2211 :
                                if i>=-2191 :
                                    r= -1616
                                else :
                                    r= -1624
                            else :
                                r= -1632
            else :
                if i>=-2519 :
                    if i>=-2375 :
                        if i>=-2314 :
                            if i>=-2273 :
                                if i>=-2252 :
                                    r= -1639
                                else :
                                    r= -1646
                            else :
                                if i>=-2293 :
                                    r= -1653
                                else :
                                    r= -1660
                        else :
                            if i>=-2355 :
                                if i>=-2334 :
                                    r= -1667
                                else :
                                    r= -1674
                            else :
                                r= -1681
                    else :
                        if i>=-2457 :
                            if i>=-2416 :
                                if i>=-2396 :
                                    r= -1688
                                else :
                                    r= -1694
                            else :
                                if i>=-2437 :
                                    r= -1701
                                else :
                                    r= -1707
                        else :
                            if i>=-2498 :
                                if i>=-2478 :
                                    r= -1713
                                else :
                                    r= -1719
                            else :
                                r= -1725
                else :
                    if i>=-2662 :
                        if i>=-2600 :
                            if i>=-2560 :
                                if i>=-2539 :
                                    r= -1731
                                else :
                                    r= -1737
                            else :
                                if i>=-2580 :
                                    r= -1742
                                else :
                                    r= -1748
                        else :
                            if i>=-2641 :
                                if i>=-2621 :
                                    r= -1754
                                else :
                                    r= -1759
                            else :
                                r= -1764
                    else :
                        if i>=-2744 :
                            if i>=-2703 :
                                if i>=-2682 :
                                    r= -1770
                                else :
                                    r= -1775
                            else :
                                if i>=-2723 :
                                    r= -1780
                                else :
                                    r= -1785
                        else :
                            if i>=-2785 :
                                if i>=-2764 :
                                    r= -1790
                                else :
                                    r= -1794
                            else :
                                r= -1799
    else :
        if i>=-3973 :
            if i>=-3399 :
                if i>=-3112 :
                    if i>=-2969 :
                        if i>=-2887 :
                            if i>=-2846 :
                                if i>=-2826 :
                                    r= -1804
                                else :
                                    r= -1808
                            else :
                                if i>=-2867 :
                                    r= -1813
                                else :
                                    r= -1817
                        else :
                            if i>=-2928 :
                                if i>=-2908 :
                                    r= -1821
                                else :
                                    r= -1826
                            else :
                                if i>=-2949 :
                                    r= -1830
                                else :
                                    r= -1834
                    else :
                        if i>=-3051 :
                            if i>=-3010 :
                                if i>=-2990 :
                                    r= -1838
                                else :
                                    r= -1842
                            else :
                                if i>=-3031 :
                                    r= -1846
                                else :
                                    r= -1850
                        else :
                            if i>=-3092 :
                                if i>=-3072 :
                                    r= -1853
                                else :
                                    r= -1857
                            else :
                                r= -1861
                else :
                    if i>=-3256 :
                        if i>=-3194 :
                            if i>=-3153 :
                                if i>=-3133 :
                                    r= -1864
                                else :
                                    r= -1868
                            else :
                                if i>=-3174 :
                                    r= -1871
                                else :
                                    r= -1874
                        else :
                            if i>=-3235 :
                                if i>=-3215 :
                                    r= -1878
                                else :
                                    r= -1881
                            else :
                                r= -1884
                    else :
                        if i>=-3338 :
                            if i>=-3297 :
                                if i>=-3276 :
                                    r= -1887
                                else :
                                    r= -1890
                            else :
                                if i>=-3317 :
                                    r= -1893
                                else :
                                    r= -1896
                        else :
                            if i>=-3379 :
                                if i>=-3358 :
                                    r= -1899
                                else :
                                    r= -1902
                            else :
                                r= -1905
            else :
                if i>=-3686 :
                    if i>=-3543 :
                        if i>=-3481 :
                            if i>=-3440 :
                                if i>=-3420 :
                                    r= -1907
                                else :
                                    r= -1910
                            else :
                                if i>=-3461 :
                                    r= -1913
                                else :
                                    r= -1915
                        else :
                            if i>=-3522 :
                                if i>=-3502 :
                                    r= -1918
                                else :
                                    r= -1920
                            else :
                                r= -1923
                    else :
                        if i>=-3624 :
                            if i>=-3584 :
                                if i>=-3563 :
                                    r= -1925
                                else :
                                    r= -1927
                            else :
                                if i>=-3604 :
                                    r= -1930
                                else :
                                    r= -1932
                        else :
                            if i>=-3665 :
                                if i>=-3645 :
                                    r= -1934
                                else :
                                    r= -1936
                            else :
                                r= -1939
                else :
                    if i>=-3829 :
                        if i>=-3768 :
                            if i>=-3727 :
                                if i>=-3706 :
                                    r= -1941
                                else :
                                    r= -1943
                            else :
                                if i>=-3747 :
                                    r= -1945
                                else :
                                    r= -1947
                        else :
                            if i>=-3809 :
                                if i>=-3788 :
                                    r= -1949
                                else :
                                    r= -1951
                            else :
                                r= -1952
                    else :
                        if i>=-3911 :
                            if i>=-3870 :
                                if i>=-3850 :
                                    r= -1954
                                else :
                                    r= -1956
                            else :
                                if i>=-3891 :
                                    r= -1958
                                else :
                                    r= -1960
                        else :
                            if i>=-3952 :
                                if i>=-3932 :
                                    r= -1961
                                else :
                                    r= -1963
                            else :
                                r= -1965
        else :
            if i>=-4546 :
                if i>=-4259 :
                    if i>=-4116 :
                        if i>=-4055 :
                            if i>=-4014 :
                                if i>=-3993 :
                                    r= -1966
                                else :
                                    r= -1968
                            else :
                                if i>=-4034 :
                                    r= -1969
                                else :
                                    r= -1971
                        else :
                            if i>=-4096 :
                                if i>=-4075 :
                                    r= -1972
                                else :
                                    r= -1974
                            else :
                                r= -1975
                    else :
                        if i>=-4198 :
                            if i>=-4157 :
                                if i>=-4136 :
                                    r= -1977
                                else :
                                    r= -1978
                            else :
                                if i>=-4177 :
                                    r= -1979
                                else :
                                    r= -1981
                        else :
                            if i>=-4239 :
                                if i>=-4218 :
                                    r= -1982
                                else :
                                    r= -1983
                            else :
                                r= -1985
                else :
                    if i>=-4403 :
                        if i>=-4341 :
                            if i>=-4300 :
                                if i>=-4280 :
                                    r= -1986
                                else :
                                    r= -1987
                            else :
                                if i>=-4321 :
                                    r= -1988
                                else :
                                    r= -1989
                        else :
                            if i>=-4382 :
                                if i>=-4362 :
                                    r= -1990
                                else :
                                    r= -1992
                            else :
                                r= -1993
                    else :
                        if i>=-4485 :
                            if i>=-4444 :
                                if i>=-4423 :
                                    r= -1994
                                else :
                                    r= -1995
                            else :
                                if i>=-4464 :
                                    r= -1996
                                else :
                                    r= -1997
                        else :
                            if i>=-4526 :
                                if i>=-4505 :
                                    r= -1998
                                else :
                                    r= -1999
                            else :
                                r= -2000
            else :
                if i>=-4833 :
                    if i>=-4689 :
                        if i>=-4628 :
                            if i>=-4587 :
                                if i>=-4567 :
                                    r= -2001
                                else :
                                    r= -2002
                            else :
                                if i>=-4608 :
                                    r= -2002
                                else :
                                    r= -2003
                        else :
                            if i>=-4669 :
                                if i>=-4648 :
                                    r= -2004
                                else :
                                    r= -2005
                            else :
                                r= -2006
                    else :
                        if i>=-4771 :
                            if i>=-4730 :
                                if i>=-4710 :
                                    r= -2007
                                else :
                                    r= -2008
                            else :
                                if i>=-4751 :
                                    r= -2008
                                else :
                                    r= -2009
                        else :
                            if i>=-4812 :
                                if i>=-4792 :
                                    r= -2010
                                else :
                                    r= -2011
                            else :
                                r= -2011
                else :
                    if i>=-4976 :
                        if i>=-4915 :
                            if i>=-4874 :
                                if i>=-4853 :
                                    r= -2012
                                else :
                                    r= -2013
                            else :
                                if i>=-4894 :
                                    r= -2013
                                else :
                                    r= -2014
                        else :
                            if i>=-4956 :
                                if i>=-4935 :
                                    r= -2015
                                else :
                                    r= -2015
                            else :
                                r= -2016
                    else :
                        if i>=-5058 :
                            if i>=-5017 :
                                if i>=-4997 :
                                    r= -2017
                                else :
                                    r= -2017
                            else :
                                if i>=-5038 :
                                    r= -2018
                                else :
                                    r= -2018
                        else :
                            if i>=-5099 :
                                if i>=-5079 :
                                    r= -2019
                                else :
                                    r= -2020
                            else :
                                r= -2020
    if inv==1:
        return -r
    else: 
        return r    


def tanh(x,fun= tan_iper16_11):
    return np.vectorize(fun)(x)

    
