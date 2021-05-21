#include "UtilityFunc16_12.h"



//tangente iperbolica approssimata con funzione lineare a tratti(3 segmenti)
int tangente_iper(int x_value){
	int i = x_value;
	int r;
	_Bool inv=0;
	if (i>0) {
		i=-i; 
		inv=1;
		};
	if(i>=-402653184)
		if(i>=-134217728)
			r= i;
		else
			r=-268435456+((i+402653184)>>1);//-1+0.5*(i+1.5)
	else
		r= -268435456;

	if (inv)
		return (-r);
	else 
		return r;
}

/**************************************************************************************************************************************
	Tangente iperbolica(ingresso(16,12)) risultato(16,12)
**************************************************************************************************************************************/
short int tan_h(short int x_value){
    short int i = x_value;
    short int r;
    _Bool inv=0;
    if (i>0){
	    i=-i;
	    inv=1;
    }
    if (i>=-5611) 
        if (i>=-3276) 
            if (i>=-2129) 
                if (i>=-1556) 
                    if (i>=-1269) 
                        if (i>=-1105) 
                            if (i>=-1024) 
                                if (i>=0) 
                                    r= 0;
                                else 
                                    r= i;
                            else 
                                if (i>=-1064) 
                                    r= -1041;
                                else 
                                    r= -1079;
                        else 
                            if (i>=-1187) 
                                if (i>=-1146) 
                                    r= -1117;
                                else 
                                    r= -1155;
                            else 
                                if (i>=-1228) 
                                    r= -1193;
                                else 
                                    r= -1230;
                    else 
                        if (i>=-1433) 
                            if (i>=-1351) 
                                if (i>=-1310) 
                                    r= -1267;
                                else 
                                    r= -1304;
                            else 
                                if (i>=-1392) 
                                    r= -1341;
                                else 
                                    r= -1377;
                        else 
                            if (i>=-1515) 
                                if (i>=-1474) 
                                    r= -1413;
                                else 
                                    r= -1449;
                            else 
                                r= -1485;
                else 
                    if (i>=-1843) 
                        if (i>=-1720) 
                            if (i>=-1638) 
                                if (i>=-1597) 
                                    r= -1521;
                                else 
                                    r= -1556;
                            else 
                                if (i>=-1679) 
                                    r= -1591;
                                else 
                                    r= -1625;
                        else 
                            if (i>=-1802) 
                                if (i>=-1761) 
                                    r= -1660;
                                else 
                                    r= -1694;
                            else 
                                r= -1728;
                    else 
                        if (i>=-2007) 
                            if (i>=-1925) 
                                if (i>=-1884) 
                                    r= -1761;
                                else 
                                    r= -1794;
                            else 
                                if (i>=-1966) 
                                    r= -1827;
                                else 
                                    r= -1860;
                        else 
                            if (i>=-2088) 
                                if (i>=-2048) 
                                    r= -1892;
                                else 
                                    r= -1924;
                            else 
                                r= -1956;
            else 
                if (i>=-2703) 
                    if (i>=-2416) 
                        if (i>=-2293) 
                            if (i>=-2211) 
                                if (i>=-2170) 
                                    r= -1988;
                                else 
                                    r= -2019;
                            else 
                                if (i>=-2252) 
                                    r= -2050;
                                else 
                                    r= -2080;
                        else 
                            if (i>=-2375) 
                                if (i>=-2334) 
                                    r= -2110;
                                else 
                                    r= -2140;
                            else 
                                r= -2170;
                    else 
                        if (i>=-2580) 
                            if (i>=-2498) 
                                if (i>=-2457) 
                                    r= -2199;
                                else 
                                    r= -2228;
                            else 
                                if (i>=-2539) 
                                    r= -2257;
                                else 
                                    r= -2285;
                        else 
                            if (i>=-2662) 
                                if (i>=-2621) 
                                    r= -2313;
                                else 
                                    r= -2341;
                            else 
                                r= -2368;
                else 
                    if (i>=-2990) 
                        if (i>=-2867) 
                            if (i>=-2785) 
                                if (i>=-2744) 
                                    r= -2396;
                                else 
                                    r= -2422;
                            else 
                                if (i>=-2826) 
                                    r= -2449;
                                else 
                                    r= -2475;
                        else 
                            if (i>=-2949) 
                                if (i>=-2908) 
                                    r= -2501;
                                else 
                                    r= -2526;
                            else 
                                r= -2552;
                    else 
                        if (i>=-3153) 
                            if (i>=-3072) 
                                if (i>=-3031) 
                                    r= -2576;
                                else 
                                    r= -2601;
                            else 
                                if (i>=-3112) 
                                    r= -2625;
                                else 
                                    r= -2649;
                        else 
                            if (i>=-3235) 
                                if (i>=-3194) 
                                    r= -2673;
                                else 
                                    r= -2696;
                            else 
                                r= -2719;
        else 
            if (i>=-4464) 
                if (i>=-3891) 
                    if (i>=-3604) 
                        if (i>=-3440) 
                            if (i>=-3358) 
                                if (i>=-3317) 
                                    r= -2742;
                                else 
                                    r= -2765;
                            else 
                                if (i>=-3399) 
                                    r= -2787;
                                else 
                                    r= -2809;
                        else 
                            if (i>=-3522) 
                                if (i>=-3481) 
                                    r= -2830;
                                else 
                                    r= -2851;
                            else 
                                if (i>=-3563) 
                                    r= -2872;
                                else 
                                    r= -2893;
                    else 
                        if (i>=-3768) 
                            if (i>=-3686) 
                                if (i>=-3645) 
                                    r= -2913;
                                else 
                                    r= -2933;
                            else 
                                if (i>=-3727) 
                                    r= -2953;
                                else 
                                    r= -2973;
                        else 
                            if (i>=-3850) 
                                if (i>=-3809) 
                                    r= -2992;
                                else 
                                    r= -3011;
                            else 
                                r= -3030;
                else 
                    if (i>=-4177) 
                        if (i>=-4055) 
                            if (i>=-3973) 
                                if (i>=-3932) 
                                    r= -3048;
                                else 
                                    r= -3066;
                            else 
                                if (i>=-4014) 
                                    r= -3084;
                                else 
                                    r= -3102;
                        else 
                            if (i>=-4136) 
                                if (i>=-4096) 
                                    r= -3119;
                                else 
                                    r= -3136;
                            else 
                                r= -3153;
                    else 
                        if (i>=-4341) 
                            if (i>=-4259) 
                                if (i>=-4218) 
                                    r= -3169;
                                else 
                                    r= -3186;
                            else 
                                if (i>=-4300) 
                                    r= -3202;
                                else 
                                    r= -3218;
                        else 
                            if (i>=-4423) 
                                if (i>=-4382) 
                                    r= -3233;
                                else 
                                    r= -3248;
                            else 
                                r= -3264;
            else 
                if (i>=-5038) 
                    if (i>=-4751) 
                        if (i>=-4628) 
                            if (i>=-4546) 
                                if (i>=-4505) 
                                    r= -3278;
                                else 
                                    r= -3293;
                            else 
                                if (i>=-4587) 
                                    r= -3307;
                                else 
                                    r= -3321;
                        else 
                            if (i>=-4710) 
                                if (i>=-4669) 
                                    r= -3335;
                                else 
                                    r= -3349;
                            else 
                                r= -3362;
                    else 
                        if (i>=-4915) 
                            if (i>=-4833) 
                                if (i>=-4792) 
                                    r= -3376;
                                else 
                                    r= -3389;
                            else 
                                if (i>=-4874) 
                                    r= -3402;
                                else 
                                    r= -3414;
                        else 
                            if (i>=-4997) 
                                if (i>=-4956) 
                                    r= -3427;
                                else 
                                    r= -3439;
                            else 
                                r= -3451;
                else 
                    if (i>=-5324) 
                        if (i>=-5201) 
                            if (i>=-5120) 
                                if (i>=-5079) 
                                    r= -3462;
                                else 
                                    r= -3474;
                            else 
                                if (i>=-5160) 
                                    r= -3485;
                                else 
                                    r= -3497;
                        else 
                            if (i>=-5283) 
                                if (i>=-5242) 
                                    r= -3508;
                                else 
                                    r= -3518;
                            else 
                                r= -3529;
                    else 
                        if (i>=-5488) 
                            if (i>=-5406) 
                                if (i>=-5365) 
                                    r= -3540;
                                else 
                                    r= -3550;
                            else 
                                if (i>=-5447) 
                                    r= -3560;
                                else 
                                    r= -3570;
                        else 
                            if (i>=-5570) 
                                if (i>=-5529) 
                                    r= -3580;
                                else 
                                    r= -3589;
                            else 
                                r= -3599;
    else 
        if (i>=-7946) 
            if (i>=-6799) 
                if (i>=-6225) 
                    if (i>=-5939) 
                        if (i>=-5775) 
                            if (i>=-5693) 
                                if (i>=-5652) 
                                    r= -3608;
                                else 
                                    r= -3617;
                            else 
                                if (i>=-5734) 
                                    r= -3626;
                                else 
                                    r= -3635;
                        else 
                            if (i>=-5857) 
                                if (i>=-5816) 
                                    r= -3643;
                                else 
                                    r= -3652;
                            else 
                                if (i>=-5898) 
                                    r= -3660;
                                else 
                                    r= -3668;
                    else 
                        if (i>=-6103) 
                            if (i>=-6021) 
                                if (i>=-5980) 
                                    r= -3676;
                                else 
                                    r= -3684;
                            else 
                                if (i>=-6062) 
                                    r= -3692;
                                else 
                                    r= -3700;
                        else 
                            if (i>=-6184) 
                                if (i>=-6144) 
                                    r= -3707;
                                else 
                                    r= -3714;
                            else 
                                r= -3722;
                else 
                    if (i>=-6512) 
                        if (i>=-6389) 
                            if (i>=-6307) 
                                if (i>=-6266) 
                                    r= -3729;
                                else 
                                    r= -3736;
                            else 
                                if (i>=-6348) 
                                    r= -3742;
                                else 
                                    r= -3749;
                        else 
                            if (i>=-6471) 
                                if (i>=-6430) 
                                    r= -3756;
                                else 
                                    r= -3762;
                            else 
                                r= -3768;
                    else 
                        if (i>=-6676) 
                            if (i>=-6594) 
                                if (i>=-6553) 
                                    r= -3775;
                                else 
                                    r= -3781;
                            else 
                                if (i>=-6635) 
                                    r= -3787;
                                else 
                                    r= -3793;
                        else 
                            if (i>=-6758) 
                                if (i>=-6717) 
                                    r= -3798;
                                else 
                                    r= -3804;
                            else 
                                r= -3810;
            else 
                if (i>=-7372) 
                    if (i>=-7086) 
                        if (i>=-6963) 
                            if (i>=-6881) 
                                if (i>=-6840) 
                                    r= -3815;
                                else 
                                    r= -3821;
                            else 
                                if (i>=-6922) 
                                    r= -3826;
                                else 
                                    r= -3831;
                        else 
                            if (i>=-7045) 
                                if (i>=-7004) 
                                    r= -3836;
                                else 
                                    r= -3841;
                            else 
                                r= -3846;
                    else 
                        if (i>=-7249) 
                            if (i>=-7168) 
                                if (i>=-7127) 
                                    r= -3851;
                                else 
                                    r= -3855;
                            else 
                                if (i>=-7208) 
                                    r= -3860;
                                else 
                                    r= -3865;
                        else 
                            if (i>=-7331) 
                                if (i>=-7290) 
                                    r= -3869;
                                else 
                                    r= -3873;
                            else 
                                r= -3878;
                else 
                    if (i>=-7659) 
                        if (i>=-7536) 
                            if (i>=-7454) 
                                if (i>=-7413) 
                                    r= -3882;
                                else 
                                    r= -3886;
                            else 
                                if (i>=-7495) 
                                    r= -3890;
                                else 
                                    r= -3894;
                        else 
                            if (i>=-7618) 
                                if (i>=-7577) 
                                    r= -3898;
                                else 
                                    r= -3902;
                            else 
                                r= -3905;
                    else 
                        if (i>=-7823) 
                            if (i>=-7741) 
                                if (i>=-7700) 
                                    r= -3909;
                                else 
                                    r= -3913;
                            else 
                                if (i>=-7782) 
                                    r= -3916;
                                else 
                                    r= -3920;
                        else 
                            if (i>=-7905) 
                                if (i>=-7864) 
                                    r= -3923;
                                else 
                                    r= -3926;
                            else 
                                r= -3930;
        else 
            if (i>=-9093) 
                if (i>=-8519) 
                    if (i>=-8232) 
                        if (i>=-8110) 
                            if (i>=-8028) 
                                if (i>=-7987) 
                                    r= -3933;
                                else 
                                    r= -3936;
                            else 
                                if (i>=-8069) 
                                    r= -3939;
                                else 
                                    r= -3942;
                        else 
                            if (i>=-8192) 
                                if (i>=-8151) 
                                    r= -3945;
                                else 
                                    r= -3948;
                            else 
                                r= -3951;
                    else 
                        if (i>=-8396) 
                            if (i>=-8314) 
                                if (i>=-8273) 
                                    r= -3954;
                                else 
                                    r= -3957;
                            else 
                                if (i>=-8355) 
                                    r= -3959;
                                else 
                                    r= -3962;
                        else 
                            if (i>=-8478) 
                                if (i>=-8437) 
                                    r= -3965;
                                else 
                                    r= -3967;
                            else 
                                r= -3970;
                else 
                    if (i>=-8806) 
                        if (i>=-8683) 
                            if (i>=-8601) 
                                if (i>=-8560) 
                                    r= -3972;
                                else 
                                    r= -3974;
                            else 
                                if (i>=-8642) 
                                    r= -3977;
                                else 
                                    r= -3979;
                        else 
                            if (i>=-8765) 
                                if (i>=-8724) 
                                    r= -3981;
                                else 
                                    r= -3984;
                            else 
                                r= -3986;
                    else 
                        if (i>=-8970) 
                            if (i>=-8888) 
                                if (i>=-8847) 
                                    r= -3988;
                                else 
                                    r= -3990;
                            else 
                                if (i>=-8929) 
                                    r= -3992;
                                else 
                                    r= -3994;
                        else 
                            if (i>=-9052) 
                                if (i>=-9011) 
                                    r= -3996;
                                else 
                                    r= -3998;
                            else 
                                r= -4000;
            else 
                if (i>=-9666) 
                    if (i>=-9379) 
                        if (i>=-9256) 
                            if (i>=-9175) 
                                if (i>=-9134) 
                                    r= -4002;
                                else 
                                    r= -4004;
                            else 
                                if (i>=-9216) 
                                    r= -4005;
                                else 
                                    r= -4007;
                        else 
                            if (i>=-9338) 
                                if (i>=-9297) 
                                    r= -4009;
                                else 
                                    r= -4011;
                            else 
                                r= -4012;
                    else 
                        if (i>=-9543) 
                            if (i>=-9461) 
                                if (i>=-9420) 
                                    r= -4014;
                                else 
                                    r= -4016;
                            else 
                                if (i>=-9502) 
                                    r= -4017;
                                else 
                                    r= -4019;
                        else 
                            if (i>=-9625) 
                                if (i>=-9584) 
                                    r= -4020;
                                else 
                                    r= -4022;
                            else 
                                r= -4023;
                else 
                    if (i>=-9953) 
                        if (i>=-9830) 
                            if (i>=-9748) 
                                if (i>=-9707) 
                                    r= -4025;
                                else 
                                    r= -4026;
                            else 
                                if (i>=-9789) 
                                    r= -4027;
                                else 
                                    r= -4029;
                        else 
                            if (i>=-9912) 
                                if (i>=-9871) 
                                    r= -4030;
                                else 
                                    r= -4031;
                            else 
                                r= -4032;
                    else 
                        if (i>=-10117) 
                            if (i>=-10035) 
                                if (i>=-9994) 
                                    r= -4034;
                                else 
                                    r= -4035;
                            else 
                                if (i>=-10076) 
                                    r= -4036;
                                else 
                                    r= -4037;
                        else 
                            if (i>=-10199) 
                                if (i>=-10158) 
                                    r= -4038;
                                else 
                                    r= -4040;
                            else 
                                r= -4041;


    if (inv)
        return (-r);
    else 
        return r;

}

